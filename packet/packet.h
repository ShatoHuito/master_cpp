//
// Created by ilnur on 16.03.2022.
//

#ifndef MASTER_CPP_PACKET_H
#define MASTER_CPP_PACKET_H

#include "packet_struct.h"

class Packet{
public:
    static bool read_paket(packet_t *packet, const uint8_t *buff);
    static bool check_master_node_CRC(packet_from_spot_to_master_t *packet);
    static uint8_t prepare_answer_from_master_to_spot(uint8_t *byte_arr);

};

#endif //MASTER_CPP_PACKET_H
