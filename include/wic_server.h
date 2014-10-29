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
 * File:    wic_server.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_SERVER_H
#define WIC_SERVER_H
#include "wic_error.h"
#include "wic_packet.h"
typedef struct WicClient;
/** \brief a simple UDP server that connects to multiple clients
 *
 *  A WicServer works by sending and recieving packets to and from players.
 *  WicServer handles certain low level functions, such as joining,  kicking, 
 *  and banning players. More advanced features can be implemented by users by
 *  pulling recieved packets out of a WicServer and processing them accordingly.
 *
 *  Since WicServer uses UDP, packets are likely, but not guaranteed, to arrive
 *  in order. Packets may not even arrive at all.
 */
typedef struct WicServer
{
    int socket_ro; /**< the socket */
    struct sockaddr_in address_ro; /**< the address */
    socklen_t address_length_ro; /**< the address length */
    unsigned char max_players_ro; /**< the maximum connected clients */
    WicClient* clients_ro; /**< the clients */
    size_t blacklist_len_ro; /**< the blacklist length */
    in_addr_t* blacklist_ro; /**< the blacklist */
    unsigned char send_buffer_ro[sizeof(WicPacket)]; /**< the send buffer */
    unsigned char recv_buffer_ro[sizeof(WicPacket)]; /**< the recieve buffer */
} WicServer;
/** \brief initializes a WicServer, allowing remote clients to connect
 *  \param target the target WicServer
 *  \param port the desired port
 *  \param max_clients the desired maximum number of connected clients
 *  \return the error code
 */
enum WicError wic_init_server(WicServer* target, unsigned port,
                              unsigned char max_clients);
/** \brief sends a single packet to a client
 *  \param server the WicServer
 *  \param packet the packet to send
 *  \param client_id the client's client id
 *  \return the error code
 */
enum WicError wic_send_packet_to_player(WicServer* server, WicPacket* packet,
                                        unsigned char client_id);
/** \brief sends a packet to all connected clients but one
 *  \param server the WicServer
 *  \param packet the packet to send
 *  \param client_id_exclude the excluded client's client id
 *  \return the error code
 */
enum WicError wic_send_packet_to_other_clients(WicServer* server,
                                               WicPacket* packet,
                                               unsigned char client_id_exclude);
/** \brief sends a packet to all connected clients
 *  \param server the WicServer
 *  \param packet the packet to send
 *  \return the error code
 */
enum WicError wic_send_packet_to_clients(WicServer* server, WicPacket* packet);
/** \brief retrieves a client's IP address and stores it in result
 *  \param server the WicServer
 *  \param client_id the client's client id
 *  \param result the buffer to store the IP address
 *  \param result_len the length of result; must be >= 16
 *  \return the error code
 */
enum WicError wic_server_get_client_address(WicServer* server,
                                            unsigned char client_id,
                                            char* result, size_t result_len);
/** \brief fetches and processes a single recieved packet, and then passes the
 *         packet to the user for further processing
 *  \param server the WicServer
 *  \param result the destination of the recieved packet
 *  \return the error code
 */
enum WicError wic_server_recv_packet(WicServer* server, WicPacket* result);
/** \brief kicks a client
 *  \param server the WicServer
 *  \param client_id the client's client id
 *  \return the error code
 */
enum WicError wic_kick_client(WicServer* server, unsigned char client_id);
/** \brief bans a client for the lifetime of the WicServer
 *  \param server the WicServer
 *  \param client_id the client's client id
 */
enum WicError wic_ban_client(WicServer* server, unsigned char client_id);
/** \brief bans any client with a certain IP address for the lifetime of the
 *         WicServer
 *  \param server the WicServer
 *  \param address the IP address
 *  \return the error code
 */
enum WicError wic_ban_address(WicServer* server, char* address);
/** \brief unbans a certain IP address from connecting to the server
 *  \param server the WicServer
 *  \param address the IP address
 *  \return the error code
 */
enum WicError wic_unban_address(WicServer* server, char* address);
/** \brief frees a WicServer, kicking all connected clients
 *  \param server the WicServer
 *  \return the error code
 */
enum WicError wic_free_server(WicServer* target);
#endif