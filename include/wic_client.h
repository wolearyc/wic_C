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
 * File:    wic_client.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_CLIENT_H
#define WIC_CLIENT_H
#include "wic_packet.h"
/** \brief a simple UDP client that connects to a server
 *  
 *  A WicClient works by sending and recieving packets to and from a server.
 *  WicClient handles certain low level functions, such as joining, kicking, and
 *  banning. More advanced features can be implemented by users by pulling 
 *  recievied packets out of a WicServer and processing them accordingly.
 *
 *  Since WicClient uses UDP, packets are likely, but not guaranteed, to arrive
 *  in order. Packets may not even arrive at all.
 */
typedef struct WicClient
{
    int socket_ro; /**< the socket */
    struct sockaddr_in address_ro; /**< the address */
    socklen_t address_length_ro; /**< the address length */
    struct sockaddr_in server_address_ro; /**< the server address */
    socklen_t server_address_length_ro; /**< the server address length */
    unsigned char max_server_clients_ro; /**< the max clients of the server */
    unsigned char send_buffer_ro[sizeof(WicPacket)]; /**< the send buffer */
    unsigned char recv_buffer_ro[sizeof(WicPacket)]; /**< the receive buffer */
    bool joined_ro; /**< whether or not the client is connected to the server */
    bool kicked_ro; /**< whether or not the client has been kicked */
    bool banned_ro; /**< whether or not the client has been banned */
    unsigned char id_ro; /**< the client's id */
} WicClient;
/** \brief initializes a WicClient
 *  \param target the target WicClient
 *  \param server_port the server port
 *  \param server_address the server IP address
 *  \param server_address_len the length of server_address
 *  \return the error code
 */
enum WicError wic_init_client(WicClient* target, unsigned server_port,
                              char* server_address, size_t server_address_len);
/** \brief attempts to join the server
 *  \param client the WicClient
 *  \param response the server response
 *  \param the join timeout
 *  \return the error code
 */
enum WicError wic_client_join_server(WicClient* client, WicPacket* response,
                                     double timeout);
/** \brief sends a packet to the server
 *  \param client the WicClient
 *  \param packet the packet to send
 *  \return the error code
 */
enum WicError wic_send_packet_to_server(WicClient* client, WicPacket* packet);
/** \brief retrieves the server's IP address and stores it in result
 *  \param client the WicClient
 *  \param result the buffer to store the IP address
 *  \param result_len the length of result; must be >= 16
 *  \return the error code
 */
enum WicError wic_client_get_server_address(WicClient* client, char* result,
                                            size_t result_len);
/** \brief fetches and processes a single recieved packet, and then passes the
 *         packet to the user for further processing
 *  \param client the WicClient
 *  \param result the destination of the recieved packet
 *  \return the error code
 */
enum WicError wic_client_recv_packet(WicClient* client, WicPacket* result);
/** \brief leaves the server
 *  \param client the WicClient
 *  \return the error code
 */
enum WicError wic_client_leave_server(WicClient* client);
/** \brief frees a WicClient
 *  \param target the target WicClient
 *  \return the error code
 */
enum WicError wic_free_client(WicClient* target);
#endif