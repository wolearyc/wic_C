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
 * File:    wic_packet.c
 * ----------------------------------------------------------------------------
 */
#include "wic_packet.h"
const uint8_t WIC_NAME_SIZE = 20;
const WicNodeIndex WIC_SERVER_INDEX = 0;
const WicPacketType WIC_PACKET_REQUEST_JOIN = {0, 21};
const WicPacketType WIC_PACKET_RESPOND_JOIN = {1, 24};
const uint8_t WIC_PACKET_RESPOND_JOIN_OKAY = 0;
const uint8_t WIC_PACKET_RESPOND_JOIN_FULL = 1;
const uint8_t WIC_PACKET_RESPOND_JOIN_BANNED = 2;

const WicPacketType WIC_PACKET_CLIENT_JOINED = {2, 22};
const WicPacketType WIC_PACKET_IN_CLIENT  = {3, 22};

const WicPacketType WIC_PACKET_LEAVE = {4, 0};
const WicPacketType WIC_PACKET_KICK_CLIENT = {5, 51};
const WicPacketType WIC_PACKET_BAN_CLIENT = {6, 51};
const WicPacketType WIC_PACKET_CLIENT_LEFT = {7, 53};
const uint8_t WIC_PACKET_CLIENT_LEFT_NORMALLY = 0;
const uint8_t WIC_PACKET_CLIENT_LEFT_KICKED = 1;
const uint8_t WIC_PACKET_CLIENT_LEFT_BANNED = 2;

const WicPacketType WIC_PACKET_SERVER_SHUTDOWN = {8,0};

const size_t WIC_PACKET_HEADER_SIZE = sizeof(WicNodeIndex) +
                                      sizeof(WicPacketType);
bool wic_get_packet_from_buffer(uint8_t* buffer, WicPacket* result)
{
    if(!buffer)
        return wic_throw_error(WIC_ERRNO_NULL_BUFFER);
    if(!result)
        return wic_throw_error(WIC_ERRNO_NULL_RESULT);
    
    memcpy(result, buffer, WIC_PACKET_HEADER_SIZE);
    memcpy(result->data, buffer + WIC_PACKET_HEADER_SIZE, result->type.size);
    bzero(result->data + result->type.size, 255 - result->type.size);
    return true;
}
bool wic_convert_packet_to_buffer(uint8_t* result, WicPacket* packet)
{
    if(!result)
        return wic_throw_error(WIC_ERRNO_NULL_RESULT);
    if(!packet)
        return wic_throw_error(WIC_ERRNO_NULL_PACKET);
    
    memcpy(result, packet, WIC_PACKET_HEADER_SIZE + packet->type.size);
    return true;
}
bool wic_is_reserved_packet_id(uint8_t packet_id)
{
    return packet_id <= 15;
}
