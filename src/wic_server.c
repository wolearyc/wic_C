/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2017  Willis O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    wic_server.c
 * ----------------------------------------------------------------------------
 */
#include "wic_server.h"
static int wic_socket;
static struct sockaddr_in wic_addr;
static socklen_t wic_size_addr = sizeof(wic_addr);
static struct sockaddr_in* addrs;
static uint8_t wic_buffer[sizeof(WicPacket)];
static size_t wic_size_buffer = sizeof(wic_buffer);
static bool wic_initialized = false;
static WicPacket wic_packet;
char** wic_alloc_string_array(unsigned num_string, unsigned size_string)
{
    char** result = malloc(num_string * sizeof(char*));
    if(!result)
        return 0;
    for(uint8_t i = 0; i < num_string; i++)
    {
        result[i] = malloc(size_string * sizeof(char));
        if(!result[i])
        {
            i--;
            for(; i >= 0; i--)
                free(result[i]);
            free(result);
            return 0;
        }
    }
    return result;
}
void wic_free_string_array(char** array, unsigned len)
{
    for(unsigned i = 0; i < len; i++)
        free(array[i]);
    free(array);
}
bool wic_init_server(WicServer* target, char* name, unsigned port,
                     uint8_t max_clients)
{
    if(wic_initialized)
        wic_throw_error(WIC_ERRNO_ALREADY_INIT);
    if(!target)
        wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!name)
        wic_throw_error(WIC_ERRNO_NULL_NAME);
    if(strlen(name) < 1)
        wic_throw_error(WIC_ERRNO_SMALL_NAME);
    if(strlen(name) > 20)
        wic_throw_error(WIC_ERRNO_LARGE_NAME);
    if(port < 1025)
        wic_throw_error(WIC_ERRNO_RESERVED_PORT);
    if(max_clients < 1)
        wic_throw_error(WIC_ERRNO_SMALL_MAX_CLIENTS);
    if(max_clients > 254)
        wic_throw_error(WIC_ERRNO_LARGE_MAX_CLIENTS);
    
    wic_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(wic_socket == -1)
        return wic_throw_error(WIC_ERRNO_SOCKET_FAIL);
    fcntl(wic_socket, F_SETFL, O_NONBLOCK);
    bzero(&wic_addr, wic_size_addr);
    wic_addr.sin_family = AF_INET;
    wic_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    wic_addr.sin_port = htons(port);
    int result = bind(wic_socket, (struct sockaddr*) &wic_addr, wic_size_addr);
    if(result == -1)
    {
        close(wic_socket);
        if(errno == EADDRINUSE)
            return wic_throw_error(WIC_ERRNO_PORT_IN_USE);
        else
            return wic_throw_error(WIC_ERRNO_SOCKET_BIND_FAIL);
    }
    wic_packet.sender_index = 0;
    uint8_t max_nodes = 1 + max_clients;
    addrs = malloc(max_nodes * wic_size_addr);
    if(!addrs)
    {
        close(wic_socket);
        wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    addrs[0] = wic_addr;
    bool* used = calloc(max_nodes, sizeof(bool));
    if(!used)
    {
        close(wic_socket);
        free(addrs);
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    used[0] = true;
    char** names = wic_alloc_string_array(max_nodes, 21);
    if(!names)
    {
        close(wic_socket);
        free(addrs);
        free(used);
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    strcpy(names[0], name);
    char** ips = wic_alloc_string_array(max_nodes, INET_ADDRSTRLEN);
    if(!ips)
    {
        close(wic_socket);
        free(addrs);
        free(used);
        wic_free_string_array(names, max_nodes);
        wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    inet_ntop(AF_INET, &wic_addr.sin_addr, ips[0], INET_ADDRSTRLEN);
    
    target->name = name;
    target->max_nodes = max_nodes;
    target->used = used;
    target->names = names;
    target->ips = ips;
    target->len_blacklist = 0;
    target->blacklist = 0;
    return true;
}
bool wic_server_send_packet(WicServer* target, WicPacket* packet,
                            WicNodeIndex dest_index)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!packet)
        return wic_throw_error(WIC_ERRNO_NULL_PACKET);
    if(dest_index < 1)
        return wic_throw_error(WIC_ERRNO_NOT_CLIENT_INDEX);
    if(dest_index >= target->max_nodes)
        return wic_throw_error(WIC_ERRNO_IMPOSSIBLE_INDEX);
    
    if(target->used[dest_index])
    {
        size_t size = WIC_PACKET_HEADER_SIZE + packet->type.size;
        wic_convert_packet_to_buffer(wic_buffer, packet);
        sendto(wic_socket, wic_buffer, size, 0,
               (struct sockaddr*) &addrs[dest_index],
               wic_size_addr);
        return true;
    }
    return wic_throw_error(WIC_ERRNO_INDEX_UNUSED);
}
bool wic_server_send_packet_exclude(WicServer* target, WicPacket* packet,
                                    WicNodeIndex exclude_index)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!packet)
        return wic_throw_error(WIC_ERRNO_NULL_PACKET);
    if(exclude_index < 1)
        return wic_throw_error(WIC_ERRNO_NOT_CLIENT_INDEX);
    if(exclude_index >= target->max_nodes)
        return wic_throw_error(WIC_ERRNO_IMPOSSIBLE_INDEX);
    
    for(WicNodeIndex i = 1; i < target->max_nodes; i++)
    {
        if(i != exclude_index && target->used[i])
            wic_server_send_packet(target, packet, i);
    }
    return true;
}
bool wic_server_send_packet_all(WicServer* target, WicPacket* packet)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!packet)
        return wic_throw_error(WIC_ERRNO_NULL_PACKET);
    
    for(WicNodeIndex i = 1; i < target->max_nodes; i++)
    {
        if(target->used[i])
            wic_server_send_packet(target, packet, i);
    }
    return true;
}
bool wic_server_recv_packet(WicServer* target, WicPacket* result)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!result)
        return wic_throw_error(WIC_ERRNO_NULL_RESULT);
    
    struct sockaddr_in recv_addr;
    socklen_t len_recv_addr = sizeof(recv_addr);
    ssize_t length = recvfrom(wic_socket, wic_buffer, wic_size_buffer, 0,
                              (struct sockaddr*) &recv_addr, &len_recv_addr);
    if(length > 0)
    {
        WicNodeIndex index;
        wic_get_packet_from_buffer(wic_buffer, result);
        if(result->type.id == WIC_PACKET_REQUEST_JOIN.id)
        {
            wic_packet.type = WIC_PACKET_RESPOND_JOIN;
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &recv_addr.sin_addr, &ip[0], INET_ADDRSTRLEN);
            for(unsigned i = 0; i < target->len_blacklist; i++)
            {
                if(!strcmp(&ip[0], target->blacklist[i]) ||
                    !strcmp((char*) &result->data[0], target->blacklist[i]))
                {
                    wic_packet.data[0] = WIC_PACKET_RESPOND_JOIN_BANNED;
                    size_t size = WIC_PACKET_HEADER_SIZE + wic_packet.type.size;
                    wic_convert_packet_to_buffer(wic_buffer, &wic_packet);
                    sendto(wic_socket, wic_buffer, size, 0,
                           (struct sockaddr*) &recv_addr, wic_size_addr);
                    return false;
                }
            }
            uint8_t connections = 0;
            for(WicNodeIndex i = 1; i < target->max_nodes; i++)
            {
                if(target->used[i])
                    connections++;
            }
            if(connections == target->max_nodes - 1)
            {
                wic_packet.data[0] = WIC_PACKET_RESPOND_JOIN_FULL;
                size_t size = WIC_PACKET_HEADER_SIZE + wic_packet.type.size;
                wic_convert_packet_to_buffer(wic_buffer, &wic_packet);
                sendto(wic_socket, wic_buffer, size, 0,
                       (struct sockaddr*) &recv_addr, wic_size_addr);
                return false;
            }
            wic_packet.data[0] = WIC_PACKET_RESPOND_JOIN_OKAY;
            wic_packet.data[1] = target->max_nodes;
            for(WicNodeIndex i = 0; i < target->max_nodes; i++)
            {
                if(!target->used[i])
                {
                    index = i;
                    wic_packet.data[2] = i;
                    break;
                }
            }
            strcpy((char*) &wic_packet.data[3], target->name);
            addrs[index] = recv_addr;
            target->used[index] = true;
            strcpy(target->names[index], (char*) result->data);
            inet_ntop(AF_INET, &recv_addr.sin_addr, target->ips[index],
                      INET_ADDRSTRLEN);
            wic_server_send_packet(target, &wic_packet, index);
            
            wic_packet.type = WIC_PACKET_CLIENT_JOINED;
            wic_packet.data[0] = index;
            strcpy((char*) &wic_packet.data[1], target->names[index]);
            wic_server_send_packet_exclude(target, &wic_packet, index);
            memcpy(result, &wic_packet, sizeof(WicPacket));
            wic_packet.type = WIC_PACKET_IN_CLIENT;
            for(WicNodeIndex i = 1; i < target->max_nodes; i++)
            {
                if(target->used[i])
                {
                    wic_packet.data[0] = i;
                    strcpy((char*) &wic_packet.data[1], target->names[i]);
                    wic_server_send_packet(target, &wic_packet, index);
                }
            }
            return true;
        }
        index = wic_buffer[0];
        if(index > 0 && index < target->max_nodes && target->used[index] &&
           recv_addr.sin_addr.s_addr == addrs[index].sin_addr.s_addr &&
           recv_addr.sin_port == addrs[index].sin_port)
        {
            if(result->type.id == WIC_PACKET_LEAVE.id)
            {
                wic_packet.type = WIC_PACKET_CLIENT_LEFT;
                wic_packet.data[0] = index;
                wic_packet.data[1] = WIC_PACKET_CLIENT_LEFT_NORMALLY;
                wic_packet.data[2] = '\0';
                wic_server_send_packet_exclude(target, &wic_packet, index);
                target->used[index] = false;
            }
            return true;
        }
        return wic_throw_error(WIC_ERRNO_PACKET_UNKNOWN_SOURCE);
    }
    return false;
}
bool wic_server_kick_client(WicServer* target, WicNodeIndex client_index,
                            char* reason)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(client_index < 1)
        return wic_throw_error(WIC_ERRNO_NOT_CLIENT_INDEX);
    if(client_index >= target->max_nodes)
        return wic_throw_error(WIC_ERRNO_IMPOSSIBLE_INDEX);
    if(!target->used[client_index])
        return wic_throw_error(WIC_ERRNO_INDEX_UNUSED);
    if(strlen(reason) > 50)
        return wic_throw_error(WIC_ERRNO_LARGE_REASON);
    
    wic_packet.type = WIC_PACKET_KICK_CLIENT;
    strcpy((char*) &wic_packet.data[0], reason);
    wic_server_send_packet(target, &wic_packet, client_index);
    wic_packet.type = WIC_PACKET_CLIENT_LEFT;
    wic_packet.data[0] = client_index;
    wic_packet.data[1] = WIC_PACKET_CLIENT_LEFT_KICKED;
    strcpy((char*) &wic_packet.data[2], reason);
    wic_server_send_packet_exclude(target, &wic_packet, client_index);
    target->used[client_index] = false;
    return true;
}
bool wic_server_ban(WicServer* target, char* name_or_ip)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!name_or_ip)
        return wic_throw_error(WIC_ERRNO_NULL_NAME_OR_IP);
    if(strlen(name_or_ip) > 20)
        return wic_throw_error(WIC_ERRNO_LARGE_NAME_OR_IP);
    
    char** new_blacklist = realloc(target->blacklist,
                                   (target->len_blacklist + 1) * sizeof(char*));
    if(!new_blacklist)
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    new_blacklist[target->len_blacklist] = malloc(21 * sizeof(char));
    if(!new_blacklist[target->len_blacklist])
    {
        realloc(target->blacklist, target->len_blacklist);
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    target->len_blacklist++;
    target->blacklist = new_blacklist;
    strcpy(target->blacklist[target->len_blacklist-1], name_or_ip);
    return true;
}
bool wic_server_ban_client(WicServer* target, WicNodeIndex client_index,
                           char* reason)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(client_index < 1)
        return wic_throw_error(WIC_ERRNO_NOT_CLIENT_INDEX);
    if(client_index >= target->max_nodes)
        return wic_throw_error(WIC_ERRNO_IMPOSSIBLE_INDEX);
    if(!target->used[client_index])
        return wic_throw_error(WIC_ERRNO_INDEX_UNUSED);
    if(strlen(reason) > 50)
        return wic_throw_error(WIC_ERRNO_LARGE_REASON);
    
    if(!wic_server_ban(target, target->names[client_index]))
        return false;
    if(!wic_server_ban(target, target->ips[client_index]))
    {
        target->len_blacklist--;
        target->blacklist = realloc(target->blacklist, target->len_blacklist);
        return false;
    }
    
    wic_packet.type = WIC_PACKET_BAN_CLIENT;
    strcpy((char*) &wic_packet.data[0], reason);
    wic_server_send_packet(target, &wic_packet, client_index);
    wic_packet.type = WIC_PACKET_CLIENT_LEFT;
    wic_packet.data[0] = client_index;
    wic_packet.data[1] = WIC_PACKET_CLIENT_LEFT_BANNED;
    strcpy((char*) &wic_packet.data[2], reason);
    wic_server_send_packet_exclude(target, &wic_packet, client_index);
    target->used[client_index] = false;
    return true;
}
bool wic_server_unban(WicServer* target, char* name_or_ip)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!name_or_ip)
        return wic_throw_error(WIC_ERRNO_NULL_NAME_OR_IP);
    if(strlen(name_or_ip) > 20)
        return wic_throw_error(WIC_ERRNO_LARGE_NAME_OR_IP);
    
    for(unsigned i = 0; i < target->len_blacklist; i++)
    {
        if(!strcmp(name_or_ip, target->blacklist[i]))
        {
            free(target->blacklist[i]);
            if(target->len_blacklist - i != 0)
            {
                memmove(&target->blacklist[i], &target->blacklist[i+1],
                        (target->len_blacklist - i) * sizeof(char*));
                target->len_blacklist--;
                target->blacklist = realloc(target->blacklist,
                                            target->len_blacklist *
                                            sizeof(char*));
            }
            return true;
        }
    }
    return wic_throw_error(WIC_ERRNO_UNBANNED_NAME_OR_IP);
}
unsigned wic_server_get_index(WicServer* target, char* name_or_ip)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!name_or_ip)
        return wic_throw_error(WIC_ERRNO_NULL_NAME_OR_IP);
    if(strlen(name_or_ip) > 20)
        return wic_throw_error(WIC_ERRNO_LARGE_NAME_OR_IP);
    
    for(unsigned i = 0; i < target->max_nodes; i++)
    {
        if(target->used[i] && (!strcmp(name_or_ip, target->names[i])
                               || !strcmp(name_or_ip, target->ips[i])))
        {
            return i;
        }
    }
    return wic_throw_error(WIC_ERRNO_NO_SUCH_CLIENT);
}
bool wic_free_server(WicServer* target)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    
    wic_packet.type = WIC_PACKET_SERVER_SHUTDOWN;
    wic_server_send_packet_all(target, &wic_packet);
    
    close(wic_socket);
    free(addrs);
    target->name = 0;
    free(target->used);
    target->used = 0;
    wic_free_string_array(target->names, target->max_nodes);
    target->names = 0;
    wic_free_string_array(target->ips, target->max_nodes);
    target->ips = 0;
    wic_free_string_array(target->blacklist, target->len_blacklist);
    target->blacklist = 0;
    target->len_blacklist = 0;
    target->max_nodes = 0;
    return true;
}
