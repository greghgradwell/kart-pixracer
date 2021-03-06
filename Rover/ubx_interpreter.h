/**
 *
 * UbxInterpreter.h
 * A C++ class for reading/writing messages that conform to the U-blox UBX protocol
 *
 * Parsing logic based on the UBX_Parser library written by Simon D. Levy
 * https://github.com/simondlevy/UBX_Parser
 *
 *
 * Copyright (C) 2021 Copperpunk
 *
 * This code is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this code.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <AP_HAL/AP_HAL.h>
#include <AP_NavEKF3/AP_NavEKF3.h>

#ifndef _UBXINTERPRETER_H_
#define _UBXINTERPRETER_H_

#define START_BYTE_1 0xB5
#define START_BYTE_2 0x62
#define PAYLOAD_OFFSET 6             // SB1, SB2, Class, ID, Len LSB, Len MSB
#define PAYLOAD_LENGTH_ADDED_BYTES 8 // Additional bytes wrt to the payload: SB1, SB2, Class, Id, Len LSB, Len MSB, CK_A, CK_B

const int kBufferSize = 100;
const int kPayloadSize = 100;
const int kMessageLengthMax = kPayloadSize - 7;

class UbxInterpreter
{
public:
    UbxInterpreter();
    // ---------------- TX -------------------
    void packPixhawkMessage();
    void setHeaderValues(uint8_t msg_class, uint8_t msg_id, uint16_t payload_length);
    void prepareMessage();
    int writeMessage(AP_HAL::UARTDriver *uart);
    void printWriteBuffer();
    int messageBuffer(uint8_t msg_buffer[]);

    template <typename T>
    void packValue(T value, int offset)
    {
        memcpy(&tx_buffer_[PAYLOAD_OFFSET + offset], &value, sizeof(value));
    }

private:
    //---------- Tx ------------//
    void calculateChecksum(uint8_t payload[], int payload_length, uint8_t &chka, uint8_t &chkb);

    uint8_t tx_buffer_[kBufferSize];
    uint16_t tx_payload_length_ = 0;
    int tx_buffer_write_length_ = 0;
};
#endif