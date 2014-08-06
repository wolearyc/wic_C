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
#include "wic_client.h"
enum WicError wic_init_client(WicClient* target, unsigned server_port,
                              char* server_address, size_t server_address_len)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(server_port < 1025)
        return wic_report_error(WICER_RESERVED_PORT);
    if(server_address == 0)
        return wic_report_error(WICER_ADDRESS_NULL);
    int tmp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(tmp_socket == -1)
        return wic_report_error(WICER_SOCKET);
    fcntl(tmp_socket, F_SETFL, O_NONBLOCK);
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(0);
    int result = bind(tmp_socket, (struct sockaddr*) &address, sizeof(address));
    if(result == -1)
    {
        close(tmp_socket);
        if(errno == EADDRINUSE)
            return wic_report_error(WICER_PORT_IN_USE);
        else
            return wic_report_error(WICER_ADDRESS_BIND);
    }
    struct sockaddr_in sock_server_address;
    bzero(&sock_server_address, sizeof(sock_server_address));
    sock_server_address.sin_family = AF_INET;
    sock_server_address.sin_addr.s_addr = inet_addr(server_address);
    sock_server_address.sin_port = htons((server_port));
    
    target->socket_ro = tmp_socket;
    target->address_ro = address;
    target->address_length_ro = sizeof(address);
    target->server_address_ro = sock_server_address;
    target->server_address_length_ro = sizeof(sock_server_address);
    target->max_server_clients_ro = 0;
    target->joined_ro = false;
    target->kicked_ro = false;
    target->banned_ro = false;
    target->id_ro = 0;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_client_join_server(WicClient* client, WicPacket* response,
                                     double timeout)
{
    if(client == 0)
        return wic_report_error(WICER_CLIENT);
    WicPacket packet;
    packet.type = WIC_PACKET_JOIN;
    wic_send_packet_to_server(client, &packet);
    clock_t initial_clock = clock();
    while((clock() - initial_clock)/CLOCKS_PER_SEC <= timeout)
    {
        struct sockaddr_in server_address;
        socklen_t server_address_length = sizeof(server_address);
        ssize_t length = recvfrom(client->socket_ro, client->recv_buffer_ro,
                                  sizeof(client->recv_buffer_ro), 0,
                                  (struct sockaddr*) &server_address,
                                  &server_address_length);
        if(length > 0 && server_address.sin_addr.s_addr ==
           client->server_address_ro.sin_addr.s_addr &&
           server_address.sin_port == client->server_address_ro.sin_port)
        {
            wic_get_packet_from_buffer(client->recv_buffer_ro, response);
            if(response->type.id == WIC_PACKET_RESPOND_JOIN.id)
            {
                if(response->data[0] == WIC_PACKET_RESPOND_JOIN_OKAY)
                {
                    client->max_server_clients_ro = response->data[1];
                    client->id_ro = response->client_id;
                    client->joined_ro = true;
                }
                return wic_report_error(WICER_NONE);
            }
        }
    }
    return wic_report_error(WICER_TIMEOUT);
}
enum WicError wic_send_packet_to_server(WicClient* client, WicPacket* packet)
{
    if(client == 0)
        return wic_report_error(WICER_CLIENT);
    if(packet == 0)
        return wic_report_error(WICER_PACKET);
    packet->client_id = client->id_ro;
    size_t size = WIC_PACKET_HEADER_SIZE + packet->type.size;
    wic_convert_packet_to_buffer(client->send_buffer_ro, packet);
    sendto(client->socket_ro, client->send_buffer_ro, size, 0,
           (struct sockaddr*) &client->server_address_ro,
           client->server_address_length_ro);
    return wic_report_error(WICER_NONE);
}
enum WicError wic_client_get_server_address(WicClient* client, char* result,
                                            size_t result_len)
{
    if(client == 0)
        return wic_report_error(WICER_CLIENT);
    if(result == 0)
        return wic_report_error(WICER_RESULT);
    if(result_len < 16)
        return wic_report_error(WICER_RESULT_LEN);
    const char* code = inet_ntop(AF_INET, &client->server_address_ro.sin_addr,
                                 result, result_len);
    if(code == 0)
        return wic_report_error(WICER_ADDRESS);
    return wic_report_error(WICER_NONE);
}
enum WicError wic_client_recv_packet(WicClient* client, WicPacket* result)
{
    if(client == 0)
        return wic_report_error(WICER_CLIENT);
    if(result == 0)
        return wic_report_error(WICER_RESULT);
    struct sockaddr_in server_address;
    socklen_t server_address_length = sizeof(server_address);
    ssize_t length = recvfrom(client->socket_ro, client->recv_buffer_ro,
                              sizeof(client->recv_buffer_ro), 0,
                              (struct sockaddr*) &server_address,
                              &server_address_length);
    if(length > 0)
    {
        if(server_address.sin_addr.s_addr ==
           client->server_address_ro.sin_addr.s_addr &&
           server_address.sin_port == client->server_address_ro.sin_port)
        {
            wic_get_packet_from_buffer(client->recv_buffer_ro, result);
            if(result->type.id == WIC_PACKET_KICK.id &&
               result->client_id == client->id_ro)
            {
                client->kicked_ro = true;
                client->joined_ro = false;
            }
            else if(result->type.id == WIC_PACKET_BAN.id)
            {
                client->banned_ro = true;
                client->joined_ro = false;
            }
            else if(result->type.id == WIC_PACKET_SERVER_SHUTDOWN.id)
                client->joined_ro = false;
            return wic_report_error(WICER_NONE);
        }
        return wic_report_error(WICER_PACKET_UNKNOWN_SOURCE);
    }
    return wic_report_error(WICER_NO_PACKET);
}
enum WicError wic_client_leave_server(WicClient* client)
{
    if(client == 0)
        return wic_report_error(WICER_CLIENT);
    if(client->joined_ro == false)
        return wic_report_error(WICER_NOT_JOINED);
    client->joined_ro = false;
    WicPacket packet;
    packet.type = WIC_PACKET_LEAVE;
    wic_send_packet_to_server(client, &packet);
    return wic_report_error(WICER_NONE);
}
enum WicError wic_free_client(WicClient* target)
{
    if(target == 0)
        return wic_report_error(WICER_NONE);
    close(target->socket_ro);
    target->socket_ro = -1;
    bzero(&target->address_ro, sizeof(target->address_ro));
    target->address_length_ro = 0;
    bzero(&target->server_address_ro, sizeof(target->server_address_ro));
    target->server_address_length_ro = 0;
    target->max_server_clients_ro = 0;
    target->joined_ro = false;
    target->kicked_ro = false;
    target->banned_ro = false;
    target->id_ro = 0;
    return wic_report_error(WICER_NONE);
}