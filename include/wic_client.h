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
 *  received packets out of a WicClient and processing them accordingly. Only
 *  one WicClient can be initialized at a time in a game.
 *
 *  Since WicClient uses UDP, packets are likely, but not guaranteed, to arrive
 *  in order. Packets may not even arrive at all.
 
 * As a rule, the members of a WicClient should not be altered directly; they 
 * should be treated as read only.
 */
typedef struct WicClient
{
    bool joined;
    WicNodeIndex index;
    char* name;
    uint8_t max_nodes;
    bool* used;
    char** names;
} WicClient;
/** \brief initializes a WicClient
 *  \param target the target WicClient
 *  \param name the client's name; must have 1-20 characters
 *  \param server_port the server port; must be > 1024
 *  \param server_ip the server IP address
 *  \return true on success, false on failure
 */
bool wic_init_client(WicClient* target, char* name, unsigned server_port,
                     char* server_ip);
/** \brief attempts to join a client to its server
 *  \param client the WicClient
 *  \param result the destination of the server's response
 *  \param the join timeout in seconds
 *  \return true on success, false on failure
 */
bool wic_client_join_server(WicClient* client, WicPacket* result,
                            double timeout);
/** \brief sends a packet to a client's server
 *  \param target the target WicClient
 *  \param packet the packet to send
 *  \return true on success, false on failure
 */
bool wic_client_send_packet(WicClient* target, WicPacket* packet);
/** \brief fetches and processes a single packet from the server
 *  \param target the target WicClient
 *  \param result the destination of the received packet
 *  \return true on success, false on failure
 */
bool wic_client_recv_packet(WicClient* target, WicPacket* result);
/** \brief leaves the server
 *  \param client the WicClient
 *  \return true on success, false on failure
 */
bool wic_client_leave(WicClient* target);
/** \brief frees a WicClient
 *  \param target the target WicClient
 *  \return true on success, false on failure
 */
bool wic_free_client(WicClient* target);
#endif