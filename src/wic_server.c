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
#include "wic_server.h"
struct WicClient
{
    bool joined_ro;
    struct sockaddr_in address_ro;
    socklen_t address_length_ro;
};
enum WicError wic_init_server(WicServer* target, unsigned port,
                              unsigned char max_clients)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(port < 1025)
        return wic_report_error(WICER_RESERVED_PORT);
    int tmp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(tmp_socket == -1)
        return wic_report_error(WICER_SOCKET);
    fcntl(tmp_socket, F_SETFL, O_NONBLOCK);
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    int result = bind(tmp_socket, (struct sockaddr*) &address, sizeof(address));
    if(result == -1)
    {
        close(tmp_socket);
        if(errno == EADDRINUSE)
            return wic_report_error(WICER_PORT_IN_USE);
        else
            return wic_report_error(WICER_ADDRESS_BIND);
    }
    WicClient* clients = malloc(max_clients * sizeof(WicClient));
    if(clients == 0)
    {
        close(tmp_socket);
        return wic_report_error(WICER_HEAP);
    }
    for(unsigned char client_id = 0; client_id < max_clients; client_id++)
        clients[client_id].joined_ro = false;
    
    target->socket_ro = tmp_socket;
    target->address_ro = address;
    target->address_length_ro = sizeof(address);
    target->max_clients_ro = max_clients;
    target->clients_ro = clients;
    target->blacklist_len_ro = 0;
    target->blacklist_ro = 0;
    return wic_report_error(WICER_NONE);
}
bool wic_is_valid_client(WicServer* server, unsigned char client_id)
{
    return client_id < server->max_clients_ro &&
           server->clients_ro[client_id].joined_ro;
}
void wic_send_packet_to_address(WicServer* server, WicPacket* packet,
                                struct sockaddr* address,
                                socklen_t address_length)
{
    size_t size = WIC_PACKET_HEADER_SIZE + packet->type.size;
    wic_convert_packet_to_buffer(server->send_buffer_ro, packet);
    sendto(server->socket_ro, server->send_buffer_ro, size, 0, address,
           address_length);
}
enum WicError wic_send_packet_to_player(WicServer* server, WicPacket* packet,
                                        unsigned char client_id)
{
    if(server == 0)
        return wic_report_error(WICER_SERVER);
    if(packet == 0)
        return wic_report_error(WICER_PACKET);
    if(wic_is_valid_client(server, client_id))
    {
        wic_send_packet_to_address(server, packet,
                (struct sockaddr*) &server->clients_ro[client_id].address_ro,
                server->clients_ro[client_id].address_length_ro);
        return wic_report_error(WICER_NONE);
    }
    return wic_report_error(WICER_CLIENT_DNE);
}
enum WicError wic_send_packet_to_other_clients(WicServer* server,
                                               WicPacket* packet,
                                               unsigned char client_id_exclude)
{
    if(server == 0)
        return wic_report_error(WICER_SERVER);
    if(packet == 0)
        return wic_report_error(WICER_PACKET);
    for(unsigned char client_id = 0; client_id < server->max_clients_ro;
        client_id++)
    {
        if(client_id != client_id_exclude)
            wic_send_packet_to_player(server, packet, client_id);
    }
    return wic_report_error(WICER_NONE);
}
enum WicError wic_send_packet_to_clients(WicServer* server, WicPacket* packet)
{
    if(server == 0)
        return wic_report_error(WICER_SERVER);
    if(packet == 0)
        return wic_report_error(WICER_PACKET);
    for(unsigned char client_id = 0; client_id < server->max_clients_ro;
        client_id++)
        wic_send_packet_to_player(server, packet, client_id);
    return wic_report_error(WICER_NONE);
}
enum WicError wic_server_get_client_address(WicServer* server,
                                            unsigned char client_id,
                                            char* result, size_t result_len)
{
    if(server == 0)
        return wic_report_error(WICER_SERVER);
    if(result == 0)
        return wic_report_error(WICER_RESULT);
    if(result_len < INET_ADDRSTRLEN)
        return wic_report_error(WICER_RESULT_LEN);
    if(wic_is_valid_client(server, client_id))
    {
        const char* code = inet_ntop(AF_INET,
                            &server->clients_ro[client_id].address_ro.sin_addr,
                            result, result_len);
        if(code == 0)
            return wic_report_error(WICER_ADDRESS);
        return wic_report_error(WICER_NONE);
    }
    return wic_report_error(WICER_CLIENT_DNE);
}
bool wic_is_client_address(WicServer* server, struct sockaddr_in address)
{
    for(unsigned char client_id = 0; client_id < server->max_clients_ro;
        client_id++)
    {
        if(wic_is_valid_client(server, client_id) &&
           server->clients_ro[client_id].address_ro.sin_addr.s_addr ==
           address.sin_addr.s_addr &&
           server->clients_ro[client_id].address_ro.sin_port ==
           address.sin_port)
            return true;
    }
    return false;
}
enum WicError wic_server_recv_packet(WicServer* server, WicPacket* result)
{
    if(server == 0)
        return wic_report_error(WICER_SERVER);
    if(result == 0)
        return wic_report_error(WICER_RESULT);
    struct sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);
    ssize_t length = recvfrom(server->socket_ro, server->recv_buffer_ro,
                              sizeof(server->recv_buffer_ro), 0,
                              (struct sockaddr*) &client_address,
                              &client_address_length);
    if(length > 0)
    {
        wic_get_packet_from_buffer(server->recv_buffer_ro, result);
        if(result->type.id == WIC_PACKET_JOIN.id)
        {
            WicPacket response;
            response.type = WIC_PACKET_RESPOND_JOIN;
            for(size_t i = 0; i < server->blacklist_len_ro; i++)
            {
                if(server->blacklist_ro[i] == client_address.sin_addr.s_addr)
                {
                    response.data[0] = WIC_PACKET_RESPOND_JOIN_BANNED;
                    wic_send_packet_to_address(server, &response,
                                    (struct sockaddr*) &client_address,
                                               client_address_length);
                    return wic_report_error(WICER_BANNED_PACKET);
                }
            }
            for(unsigned char new_id = 0; new_id < server->max_clients_ro;
                new_id++)
            {
                if(!server->clients_ro[new_id].joined_ro)
                {
                    server->clients_ro[new_id].joined_ro = true;
                    server->clients_ro[new_id].address_ro = client_address;
                    server->clients_ro[new_id].address_length_ro =
                    client_address_length;
                    response.client_id = new_id;
                    result->client_id = new_id;
                    response.data[0] = WIC_PACKET_RESPOND_JOIN_OKAY;
                    response.data[1] = server->max_clients_ro;
                    wic_send_packet_to_clients(server, &response);
                    return wic_report_error(WICER_NONE);
                }
            }
            response.data[0] = WIC_PACKET_RESPOND_JOIN_FULL;
            wic_send_packet_to_address(server, &response,
                                       (struct sockaddr*) &client_address,
                                       client_address_length);
            return wic_report_error(WICER_REJECTED_CONNECT_PACKET);
        }
        if(wic_is_client_address(server, client_address))
        {
            if(result->type.id == WIC_PACKET_LEAVE.id)
            {
                unsigned char client_id = result->client_id;
                wic_send_packet_to_other_clients(server, result, client_id);
                server->clients_ro[client_id].joined_ro = false;
                return wic_report_error(WICER_NONE);
            }
            return wic_report_error(WICER_NONE);
        }
        return wic_report_error(WICER_PACKET_UNKNOWN_SOURCE);
    }
    return wic_report_error(WICER_NO_PACKET);
}
enum WicError wic_kick_client(WicServer* server, unsigned char client_id)
{
    if(server == 0)
        return wic_report_error(WICER_SERVER);
    if(wic_is_valid_client(server, client_id))
    {
        WicPacket packet;
        packet.client_id = client_id;
        packet.type = WIC_PACKET_KICK;
        wic_send_packet_to_clients(server, &packet);
        server->clients_ro[client_id].joined_ro = false;
        return wic_report_error(WICER_NONE);
    }
    else
        return wic_report_error(WICER_CLIENT_DNE);
}
enum WicError wic_ban_client(WicServer* server, unsigned char client_id)
{
    if(wic_is_valid_client(server, client_id))
    {
        server->blacklist_len_ro++;
        server->blacklist_ro = realloc(server->blacklist_ro,
                                       server->blacklist_len_ro *
                                       sizeof(in_addr_t));
        server->blacklist_ro[server->blacklist_len_ro-1] =
                        server->clients_ro[client_id].address_ro.sin_addr.s_addr;
        WicPacket packet;
        packet.client_id = client_id;
        packet.type = WIC_PACKET_BAN;
        wic_send_packet_to_clients(server, &packet);
        server->clients_ro[client_id].joined_ro = false;
        return wic_report_error(WICER_NONE);
    }
    return wic_report_error(WICER_CLIENT_DNE);
}
enum WicError wic_ban_address(WicServer* server, char* address)
{
    if(server == 0)
        return wic_report_error(WICER_SERVER);
    if(address == 0)
        return wic_report_error(WICER_ADDRESS_NULL);
    struct sockaddr_in net_address;
    int result = inet_pton(AF_INET, address, &net_address);
    if(result == 0 || result == -1)
        return wic_report_error(WICER_ADDRESS);
    for(unsigned char client_id = 0; client_id < server->max_clients_ro;
        client_id++)
    {
        if(wic_is_valid_client(server, client_id) &&
           server->clients_ro[client_id].address_ro.sin_addr.s_addr ==
           net_address.sin_addr.s_addr)
        {
            wic_ban_client(server, client_id);
            return wic_report_error(WICER_NONE);
        }
    }
    server->blacklist_len_ro++;
    server->blacklist_ro = realloc(server->blacklist_ro,
                                   server->blacklist_len_ro *
                                   sizeof(in_addr_t));
    server->blacklist_ro[server->blacklist_len_ro-1] =
                                                  net_address.sin_addr.s_addr;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_unban_address(WicServer* server, char* address)
{
    if(server == 0)
        return wic_report_error(WICER_SERVER);
    if(address == 0)
        return wic_report_error(WICER_ADDRESS_NULL);
    struct sockaddr_in net_address;
    int result = inet_pton(AF_INET, address, &net_address);
    if(result == 0 || result == -1)
        return wic_report_error(WICER_ADDRESS);
    for(int i = 0; i < server->blacklist_len_ro; i++)
    {
        if(net_address.sin_addr.s_addr == server->blacklist_ro[i])
        {
            memcpy(server->blacklist_ro+i, server->blacklist_ro+i+1,
                   server->blacklist_len_ro-i-1);
            server->blacklist_len_ro--;
            server->blacklist_ro = realloc(server->blacklist_ro,
                                           server->blacklist_len_ro);
            return wic_report_error(WICER_NONE);
        }
    }
    return wic_report_error(WICER_ADDRESS_DNE);
}
enum WicError wic_free_server(WicServer* target)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    WicPacket packet;
    packet.type = WIC_PACKET_SERVER_SHUTDOWN;
    wic_send_packet_to_clients(target, &packet);
    close(target->socket_ro);
    target->socket_ro = -1;
    bzero(&target->address_ro, sizeof(target->address_ro));
    target->address_length_ro = 0;
    target->max_clients_ro = 0;
    free(target->clients_ro);
    target->clients_ro = 0;
    target->blacklist_len_ro = 0;
    free(target->blacklist_ro);
    target->blacklist_ro = 0;
    return wic_report_error(WICER_NONE);
}