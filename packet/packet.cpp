//
// Created by ilnur on 16.03.2022.
//

#include <cstdint>
#include <cstring>
#include <cstdio>
#include "packet.h"
#include "packet_struct.h"
#include "../crc/crc.h"


bool Packet::read_paket(packet_t *packet, const uint8_t *buff) {
    packet->length = buff[0];
    packet->counter = buff[1] & 0b11;
    packet->address = (buff[2] << 6) | (buff[1] >> 2);
    packet->info = buff[3] | buff[4] << 8 | buff[5] << 16 | buff[6] << 24;
    packet->crc = buff[7] | buff[8] << 8;

    return false;
}

/**
 * Функция проверяет контрольную сумму входящего пакета-запроса
 * @param packet адрес входящего пакета-запроса
 * @return возвращает true, если сумма корректна
 */

bool Packet::check_master_node_CRC(packet_from_spot_to_master_t *packet)
{
    uint16_t crc;
    uint16_t rx_crc;

    //для принятых пакетов используется прямая контрольная сумма
    rx_crc = packet->crc;
    packet->crc = 0;
    packet->crc = dallasCrc16((uint8_t *) packet, (packet->length - 1));
    return (packet->crc == rx_crc);
}

/**
 * Функция обрабатывает полученный запрос и подготавливает на него ответ, если запрос валидный
 *
 * @param spotDeviceInfo структура с данными спота и очередями готовых пакетов для узлов
 * @param packet_tx адрес пакета, в который записывается необходимая для передачи информация
 * @return возвращает 0, если полученный запрос валидный
 */

uint8_t Packet::prepare_answer_from_master_to_spot(uint8_t *byte_arr)
{
    packet_from_spot_to_master_t packet;

    memcpy(&packet, byte_arr, sizeof(packet_from_spot_to_master_t));

    ///проверяем пакет по приходу от спота
    if(check_master_node_CRC(&packet)) {
        printf("CRC node_master_ok &&&&&&&&&&\n");
    }

    packet.crc = 0;
    packet.crc = dallasCrc16((uint8_t *) &packet, (packet.length - 1));
    memcpy(byte_arr, &packet, sizeof(packet_from_spot_to_master_t));


    return 0;
}



