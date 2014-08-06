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
 * File:    wic_packet.c
 * ----------------------------------------------------------------------------
 */
#include "wic_packet.h"
const WicPacketType WIC_PACKET_JOIN = {0, 0};
const WicPacketType WIC_PACKET_RESPOND_JOIN = {1, 2 * sizeof(unsigned char)};
const unsigned char WIC_PACKET_RESPOND_JOIN_OKAY = 0;
const unsigned char WIC_PACKET_RESPOND_JOIN_FULL = 1;
const unsigned char WIC_PACKET_RESPOND_JOIN_BANNED = 2;
const WicPacketType WIC_PACKET_LEAVE = {2, 0};
const WicPacketType WIC_PACKET_KICK = {3, 0};
const WicPacketType WIC_PACKET_BAN = {4, 0};
const WicPacketType WIC_PACKET_SERVER_SHUTDOWN = {5,0};
const size_t WIC_PACKET_HEADER_SIZE = sizeof(unsigned char) +
                                      sizeof(WicPacketType);
enum WicError wic_get_packet_from_buffer(unsigned char* buffer,
                                         WicPacket* result)
{
    if(buffer == 0)
        return wic_report_error(WICER_BUFFER);
    if(result == 0)
        return wic_report_error(WICER_RESULT);
    memcpy(result, buffer, WIC_PACKET_HEADER_SIZE);
    memcpy(result->data, buffer + WIC_PACKET_HEADER_SIZE, result->type.size);
    return wic_report_error(WICER_NONE);
}
enum WicError wic_convert_packet_to_buffer(unsigned char* result,
                                           WicPacket* packet)
{
    if(result == 0)
        return wic_report_error(WICER_BUFFER);
    if(packet == 0)
        return wic_report_error(WICER_RESULT);
    memcpy(result, packet, WIC_PACKET_HEADER_SIZE + packet->type.size);
    return wic_report_error(WICER_NONE);
}
bool wic_is_reserved_packet_id(unsigned char packet_id)
{
    return packet_id <= 5;
}