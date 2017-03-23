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
 * File:    wic_packet.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_PACKET_H
#define WIC_PACKET_H
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include "wic_error.h"
/** \brief the maximum number of bytes alloted to any wic server or client name
 */
extern const uint8_t WIC_NAME_SIZE;
/** \brief identifies some basic identifying information about a packet
 * 
 *  Typically, constant WicPacketTypes are defined at compile time and form the
 *  standard interface between a WicServer and WicClients.
 */
typedef struct WicPacketType
{
    /** \brief the packet type id
     *
     *  The packet type id is used to determine the type of the packet. The
     *  value of id should never be in the range 0-15 since wic reserves
     *  these ids.
     */
    uint8_t id;
    uint8_t size; /**< the size, in bytes, of the packet's data payload */
} WicPacketType;
/** \brief identifies the index of a node (either the server or a client) */
typedef uint8_t WicNodeIndex;
/** \brief the server's index (always 0) */
extern const WicNodeIndex WIC_SERVER_INDEX;
/** \brief a packet containing source and type information as well as
 *         a data payload */
typedef struct WicPacket
{
    WicNodeIndex sender_index; /**< the node index of the sender */
    WicPacketType type;        /**< the packet type */
    uint8_t data[255];         /**< the data payload */
} WicPacket;
/** \brief the reserved packet a client sends the server to request to join
 *  
 *  This packet contains the 21 byte name of the client.
 */
extern const WicPacketType WIC_PACKET_REQUEST_JOIN;
/** \brief the reserved packet a server sends to a client who requested to join
 *
 *  This packet contains 24 bytes of data: first, a join response code.
 *  Second, the number of nodes the server supports (1 + maxiumum number of
 *  clients). Third, the newly connected client's assigned index. 
 *  Fourth, the 21 byte name of the server.
 */
extern const WicPacketType WIC_PACKET_RESPOND_JOIN;
/** \brief successful join response code */
extern const uint8_t WIC_PACKET_RESPOND_JOIN_OKAY;
/** \brief unsuccessful join response code due to full server */
extern const uint8_t WIC_PACKET_RESPOND_JOIN_FULL;
/** \brief unsuccessful join response code due to ban */
extern const uint8_t WIC_PACKET_RESPOND_JOIN_BANNED;

/** \brief the reserved packet recieved by server and all previously connected
 *         clients announcing that a new client has successfully joined
 *  
 *  This packet contains 22 bytes of data. First, the index of the newly joined
 *  client. Second, the 21 byte name of the newly joined client.
 */
extern const WicPacketType WIC_PACKET_CLIENT_JOINED;
/** \brief the reserved packet sent from a server to a client that just joined
 *         announcing a single client already in the server
 *  This packet contains 22 bytes of data. First, the index of the client
 *  already in the server. Second, the 21 byte name of the client already in
 *  the server.
 */
extern const WicPacketType WIC_PACKET_IN_CLIENT;

/** \brief the reserved packet sent from a client to a server indicating the 
 *         client has left
 *
 *  This packet contains no data.
 */
extern const WicPacketType WIC_PACKET_LEAVE;
/** \brief the reserved packet sent from a server to a client indicating that 
 *         the client has been kicked from the server
 *
 *  This packet contains a 51 byte string explaining the reason for the kick.
 */
extern const WicPacketType WIC_PACKET_KICK_CLIENT;
/** \brief the reserved packet sent from a server to a client indicating that
 *         the client has been banned from the server
 *
 *  This packet contains a 51 byte string explaining the reason for the ban.
 */
extern const WicPacketType WIC_PACKET_BAN_CLIENT;
/** \brief the reserved packet sent from a server to >1 clients indicating that
 *         another client has left
 *
 *  This packet contains 53 bytes of data. First, the index of the client who
 *  left. Second, the 1 byte leave code. Third, a 51 byte string explaining why
 *  the client left. In the case of kick or ban, this string will be the
 *  explaination of the kick or ban. Else, the string will be empty.
 */
extern const WicPacketType WIC_PACKET_CLIENT_LEFT;
/** \brief normal client leave code */
extern const uint8_t WIC_PACKET_CLIENT_LEFT_NORMALLY;
/** \brief kicked client leave code */
extern const uint8_t WIC_PACKET_CLIENT_LEFT_KICKED;
/** \brief banned client leave code */
extern const uint8_t WIC_PACKET_CLIENT_LEFT_BANNED;
/** \brief the reserved packet sent from a server to all joined clients
 *         indicating server shutdown
 *
 *  This packet contains no data.
 */
extern const WicPacketType WIC_PACKET_SERVER_SHUTDOWN;
/** \brief the size of the packet header */
extern const size_t WIC_PACKET_HEADER_SIZE;
/** \brief parses a packet from a given buffer 
 *  \param buffer a buffer with enough spcae to store the entire WicPacket
 *  \param result the resulting packet
 *  \return true on success, false on failure
 */
bool wic_get_packet_from_buffer(uint8_t* buffer, WicPacket* result);
/** \brief copies packet data into a buffer
 *
 *  \param result a buffer with enough space to store the entire WicPacket
 *  \param packet a packet
 *  \return true on success, false on failure
 */
bool wic_convert_packet_to_buffer(uint8_t* result, WicPacket* packet);
/** \brief determines whether or not a packet id is reserved
 *  \return whether or not the packet id is reserved by wic
 */
bool wic_is_reserved_packet_id(uint8_t packet_id);
#endif
