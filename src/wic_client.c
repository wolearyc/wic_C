/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2014  Will O'Leary
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
 * File:    wic_client.c
 * ----------------------------------------------------------------------------
 */
/* TODO: add wic_ in front of global variables for consistency */
#include "wic_client.h"
static int wic_socket;
static struct sockaddr_in wic_addr;
static const socklen_t len_addr = sizeof(wic_addr);
static struct sockaddr_in wic_server_addr;
static uint8_t wic_buffer[sizeof(WicPacket)];
static size_t wic_size_buffer = sizeof(wic_buffer);
static bool wic_initialized = false;

bool wic_init_client(WicClient* target, char* name, unsigned server_port,
                     char* server_ip)
{
    if(wic_initialized)
        return wic_throw_error(WIC_ERRNO_ALREADY_INIT);
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!name)
        return wic_throw_error(WIC_ERRNO_NULL_NAME);
    if(!strlen(name))
        return wic_throw_error(WIC_ERRNO_SMALL_NAME);
    if(strlen(name) > 20)
        return wic_throw_error(WIC_ERRNO_LARGE_NAME);
    if(server_port < 1025)
        return wic_throw_error(WIC_ERRNO_RESERVED_PORT);
    if(!server_ip)
        return wic_throw_error(WIC_ERRNO_NULL_SERVER_IP);
    if(strlen(server_ip) < 7)
        return wic_throw_error(WIC_ERRNO_SMALL_LEN_SERVER_IP);
    
    wic_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(wic_socket == -1)
        return wic_throw_error(WIC_ERRNO_SOCKET_FAIL);
    fcntl(wic_socket, F_SETFL, O_NONBLOCK);
    bzero(&wic_addr, sizeof(wic_addr));
    wic_addr.sin_family = AF_INET;
    wic_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    wic_addr.sin_port = htons(0);
    int result = bind(wic_socket, (struct sockaddr*) &wic_addr, sizeof(wic_addr));
    if(result == -1)
    {
        close(wic_socket);
        if(errno == EADDRINUSE)
            return wic_throw_error(WIC_ERRNO_PORT_IN_USE);
        else
            return wic_throw_error(WIC_ERRNO_SOCKET_BIND_FAIL);
    }
    bzero(&wic_server_addr, sizeof(wic_server_addr));
    wic_server_addr.sin_family = AF_INET;
    wic_server_addr.sin_addr.s_addr = inet_addr(server_ip);
    wic_server_addr.sin_port = htons((server_port));
    
    target->joined = false;
    target->name = name;
    target->used = 0;
    target->names = 0;
    wic_initialized = true;
    return true;
}
bool wic_client_join_server(WicClient* target, WicPacket* result,
                            double timeout)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!result)
        return wic_throw_error(WIC_ERRNO_NULL_RESULT);
    if(target->joined)
        return wic_throw_error(WIC_ERRNO_CLIENT_ALREADY_JOINED);
    
    WicPacket packet;
    bzero(&packet, sizeof(WicPacket));
    packet.type = WIC_PACKET_REQUEST_JOIN;
    memcpy(packet.data, target->name, strlen(target->name) + 1);
    wic_client_send_packet(target, &packet);
    clock_t initial_clock = clock();
    while((clock() - initial_clock)/CLOCKS_PER_SEC <= timeout)
    {
        struct sockaddr_in response_addr;
        ssize_t length = recvfrom(wic_socket, wic_buffer, sizeof(wic_buffer), 0,
                                  (struct sockaddr*) &response_addr, 0);
        if(length > 0)
        {
            wic_get_packet_from_buffer(wic_buffer, result);
            if(result->type.id == WIC_PACKET_RESPOND_JOIN.id)
            {
                if(result->data[0] == WIC_PACKET_RESPOND_JOIN_OKAY)
                {
                    target->max_nodes = result->data[1];
                    bool* used = calloc(target->max_nodes, sizeof(bool));
                    if(!used)
                        return wic_throw_error(WIC_ERRNO_NO_HEAP);
                    char** names = malloc(target->max_nodes * sizeof(char*));
                    if(!names)
                    {
                        free(used);
                        wic_throw_error(WIC_ERRNO_NO_HEAP);
                    }
                    for(uint8_t i = 0; i < target->max_nodes; i++)
                    {
                        names[i] = malloc(21 * sizeof(char));
                        if(!names[i])
                        {
                            i--;
                            for(; i >= 0; i--)
                                free(names[i]);
                            free(names);
                            return wic_throw_error(WIC_ERRNO_NO_HEAP);
                        }
                    }
                    
                    target->joined = true;
                    target->index = result->data[2];
                    target->used = used;
                    used[0] = true;
                    used[target->index] = true;
                    target->names = names;
                    memcpy(target->names[0], &result->data[3], 21);
                    strcpy(target->names[target->index], target->name);
                    wic_server_addr = response_addr;
                    return true;
                }
                else if(result->data[0] == WIC_PACKET_RESPOND_JOIN_FULL)
                    return wic_throw_error(WIC_ERRNO_JOIN_FAIL_FULL);
                else if(result->data[0] == WIC_PACKET_RESPOND_JOIN_BANNED)
                    return wic_throw_error(WIC_ERRNO_JOIN_FAIL_BANNED);
            }
        }
    }
    return wic_throw_error(WIC_ERRNO_TIMEOUT);
}
bool wic_client_send_packet(WicClient* target, WicPacket* packet)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!packet)
        return wic_throw_error(WIC_ERRNO_NULL_PACKET);
    
    packet->sender_index = target->index;
    size_t size = WIC_PACKET_HEADER_SIZE + packet->type.size;
    wic_convert_packet_to_buffer(wic_buffer, packet);
    sendto(wic_socket, wic_buffer, size, 0, (struct sockaddr*) &wic_server_addr,
           len_addr);
    return true;
}
bool wic_client_recv_packet(WicClient* target, WicPacket* result)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!result)
        return wic_throw_error(WIC_ERRNO_NULL_RESULT);
    if(!target->joined)
        return wic_throw_error(WIC_ERRNO_CLIENT_NOT_JOINED);
    
    struct sockaddr_in recv_addr;
    ssize_t length = recvfrom(wic_socket, wic_buffer, wic_size_buffer, 0,
                              (struct sockaddr*) &recv_addr, 0);
    if(length > 0)
    {
        if(recv_addr.sin_addr.s_addr == wic_server_addr.sin_addr.s_addr &&
           recv_addr.sin_port == wic_server_addr.sin_port)
        {
            wic_get_packet_from_buffer(wic_buffer, result);
            WicNodeIndex index;
            if(result->type.id == WIC_PACKET_CLIENT_JOINED.id ||
               result->type.id == WIC_PACKET_IN_CLIENT.id)
            {
                    index = result->data[0];
                    target->used[index] = true;
                    memcpy(target->names[index], &result->data[1], 21);
            }
            else if(result->type.id == WIC_PACKET_KICK_CLIENT.id ||
                    result->type.id == WIC_PACKET_BAN_CLIENT.id ||
                    result->type.id == WIC_PACKET_SERVER_SHUTDOWN.id)
            {
                target->joined = false;
            }
            else if(result->type.id == WIC_PACKET_CLIENT_LEFT.id)
            {
                    index = result->data[0];
                    target->used[index] = false;
            }
            return true;
        }
        return wic_throw_error(WIC_ERRNO_PACKET_UNKNOWN_SOURCE);
    }
    return false;
}
bool wic_client_leave(WicClient* target)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!target->joined)
        return wic_throw_error(WIC_ERRNO_CLIENT_NOT_JOINED);
        
    WicPacket packet;
    packet.type = WIC_PACKET_LEAVE;
    wic_client_send_packet(target, &packet);
    target->joined = false;
    return true;
}
bool wic_free_client(WicClient* target)
{
    if(target == 0)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    
    close(wic_socket);
    wic_socket = -1;
    bzero(&wic_addr, len_addr);
    bzero(&wic_server_addr, len_addr);
    target->max_nodes = 0;
    target->joined = 0;
    target->index = 0;
    free(target->used);
    target->used = 0;
    free(target->names);
    target->names = 0;
    wic_initialized = false;
    return true;
}