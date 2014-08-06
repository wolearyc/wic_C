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
     *  value of id should never be 0, 1, 2, 3, 4, or 5, since wic reserves 
     *  these ids.
     */
    unsigned char id;   /**< the type id */
    unsigned char size; /**< the size, in bytes, of the packet data */
} WicPacketType;
typedef struct WicPacket
{
    unsigned char client_id;   /**< the client id associated with this packet */
    WicPacketType type;        /**< the packet type */
    unsigned char data[255];   /**< the data payload */
} WicPacket;
/** \brief the reserved join request packet
 *  
 *  This packet contains no data.
 */
const extern WicPacketType WIC_PACKET_JOIN;
/** \brief the reserved join response packet
 *
 *  This packet contains two bytes of data: first, a join response code.
 *  Second, the maximum number of clients the server supports.
 */
const extern WicPacketType WIC_PACKET_RESPOND_JOIN;
/** \brief successful join response code */
const extern unsigned char WIC_PACKET_RESPOND_JOIN_OKAY;
/** \brief unsuccessful join response code due to full server */
const extern unsigned char WIC_PACKET_RESPOND_JOIN_FULL;
/** \brief unsuccessful join response code due to ban */
const extern unsigned char WIC_PACKET_RESPOND_JOIN_BANNED;
/** \brief the reserved disconnect packet 
 *
 *  This packet contains no data.
 */
const extern WicPacketType WIC_PACKET_LEAVE;
/** \brief the reserved kick packet
 *
 *  This packet contains no data.
 */
const extern WicPacketType WIC_PACKET_KICK;
/** \brief the reserved ban packet
 *
 *  This packet contains no data.
 */
const extern WicPacketType WIC_PACKET_BAN;
/** \brief the reserved server shutdown packet 
 *  
 *  This packet contains no data.
 */
const extern WicPacketType WIC_PACKET_SERVER_SHUTDOWN;
/** \brief the size of the packet header */
const extern size_t WIC_PACKET_HEADER_SIZE;
/** \brief parses a packet from a given buffer 
 *  \param buffer a buffer with enough spcae to store an entire WicPackets
 *  \param result the resulting packet
 *  \return the error code
 */
enum WicError wic_get_packet_from_buffer(unsigned char* result,
                                         WicPacket* packet);
/** \brief copies packet data into a buffer
 *
 *  \param result a buffer with enough space to store and entire WicPacket
 *  \param packet a packet
 *  \return the error code
 */
enum WicError wic_convert_packet_to_buffer(unsigned char* result,
                                           WicPacket* packet);
/** \brief determines whether or not a packet id is reserved
 *  \return whether or not the packet id is reserved
 */
bool wic_is_reserved_packet_id(unsigned char packet_id);
#endif