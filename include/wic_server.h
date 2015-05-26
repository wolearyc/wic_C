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
/** \brief a simple UDP server that connects to multiple clients
 *
 *  A WicServer works by sending and recieving packets to and from players.
 *  WicServer handles certain low level functions, such as joining,  kicking, 
 *  and banning players. More advanced features can be implemented by users by
 *  pulling recieved packets out of a WicServer and processing them accordingly.
 *  Only one WicServer can be initialized at a time. 
 *
 *  Since WicServer uses UDP, packets are likely, but not guaranteed, to arrive
 *  in order. Packets may not even arrive at all.
 *
 * As a rule, the members of a WicServer should not be altered directly; they
 * should be treated as read only.
 */
typedef struct WicServer
{
    char* name;
    uint8_t max_nodes;
    bool* used;
    char** names;
    char** ips;
    size_t len_blacklist;
    char** blacklist;
} WicServer;
/** \brief initializes a WicServer, allowing remote clients to connect
 *  \param target the target WicServer
 *  \param name the desired name of the server; must have 1-20 characters
 *  \param port the desired port
 *  \param max_clients the desired maximum number of connected clients; must be
 *         in the range 1-254
 *  \return true on success, false on failure
 */
bool wic_init_server(WicServer* target, char* name, unsigned port,
                     uint8_t max_clients);
/** \brief sends a single packet to a client
 *  \param server the WicServer
 *  \param packet the packet to send
 *  \param dest_index the index of the client to sent it to; must be > 0
 *  \return true on success, false on failure
 */
bool wic_server_send_packet(WicServer* target, WicPacket* packet,
                            WicNodeIndex dest_index);
/** \brief sends a packet to all connected clients but one
 *  \param server the WicServer
 *  \param packet the packet to send
 *  \param exclude_index the index of the client to exclude; must be > 0
 *  \return true on success, false on failure
 */
bool wic_server_send_packet_exclude(WicServer* target, WicPacket* packet,
                                    WicNodeIndex exclude_index);
/** \brief sends a packet to all connected clients
 *  \param server the WicServer
 *  \param packet the packet to send
 *  \return true on success, false on failure
 */
bool wic_server_send_packet_all(WicServer* target, WicPacket* packet);
/** \brief fetches and processes a single packet from a client
 *  \param server the WicServer
 *  \param result the destination of the received packet
 *  \return true on success, false on failure
 */
bool wic_server_recv_packet(WicServer* target, WicPacket* result);
/** \brief kicks a client
 *  \param server the WicServer
 *  \param client_index the client's index; must be > 0
 *  \param reason string given the reason for kick; must be 0-50 characters
 *  \return true on success, false on failure
 */
bool wic_server_kick_client(WicServer* target, WicNodeIndex client_index,
                            char* reason);
/** \brief bans a name or IP address
 *  \param server the WicServer
 *  \param name_or_ip a name or IP address
 *  \return true on success, false on failure
 */
bool wic_server_ban(WicServer* target, char* name_or_ip);
/** \brief bans a client (in both name and IP address) for the lifetime of the 
 *         WicServer, disconnecting the client
 *  \param server the WicServer
 *  \param reason string given the reason for kick; must be 0-50 characters
 *  \param client_index the client's index; must be > 0
 */
bool wic_server_ban_client(WicServer* target, WicNodeIndex client_index,
                           char* reason);/** \brief unbans a certain name or IP address from connecting to the server
 *  \param server the WicServer
 *  \param name_or_ip a name or IP address
 *  \return true on success, false on failure
 */
bool wic_server_unban(WicServer* target, char* name_or_ip);
/** \brief frees a WicServer, disconnecting all connected clients cleanly
 *  \param server the WicServer
 *  \return true on success, false on failure
 */
bool wic_free_server(WicServer* target);
#endif