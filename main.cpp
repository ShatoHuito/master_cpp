//
// Created by ilnur on 16.03.2022.
//

#include <cstdint>
#include <cstdio>
#include "defines.h"
#include "network/network.h"
#include "packet/packet_struct.h"
#include "master/master.h"

Master master_unit;

///КОД ДЛЯ КООРДИНАТОРА

int main() {
    ///инициализация соединения
    master_unit.init_network();

    master_unit.start_message_exchange();

    return 0;
}

