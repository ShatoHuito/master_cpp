//
// Created by ilnur on 16.03.2022.
//

#include <sys/socket.h>
#include <unistd.h>
#include "master.h"
#include "../defines.h"
#include "../network/network.h"
#include "../packet/packet_struct.h"
#include "../packet/packet.h"

Master::Master() {
    this->server_fd = 0;
    this->client_fd = 0;
}

bool Master::init_network() {
    struct sockaddr_in serv_adr = {0};

    this->client_fd = Network::Socket(AF_INET, SOCK_STREAM, 0);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(PORT);
    Network::Bind(this->client_fd, (const struct sockaddr *) &serv_adr, sizeof serv_adr);
    write(1, "server: listining clients...\n", 29);
    Network::Listen(this->client_fd, 5);
    socklen_t adrlen = sizeof serv_adr;
    this->server_fd = Network::Accept(this->client_fd, (struct sockaddr *) &serv_adr, &adrlen);

    this->ufds.fd = this->server_fd;
    this->ufds.events = POLLIN;

    return false;
}

int print_paket(uint8_t *byte_arr, char *str)
{
    uint8_t length;
    uint8_t i = 0;
    length = byte_arr[i];

    printf("********  %s  ********\n", str);
    printf ("length = %d", length);
    printf ("   Addres = %d", (byte_arr[++i] | byte_arr[++i] << 8 ));
    printf("    rssi = %d", byte_arr[++i]);
    printf("\n---------PACKET------------\n");
    printf ("length = %d", byte_arr[++i]);
    printf ("   Counter = %d", (byte_arr[++i] & 0b11));
    printf ("   Addres = %d", ((byte_arr[i] >> 2) | (byte_arr[++i] << 6)));
    printf ("   Info = %d", byte_arr[++i] | byte_arr[++i] << 8 | byte_arr[++i] << 16 | byte_arr[++i] << 24);
    printf("    Crc = %d", (byte_arr[++i] | byte_arr[++i] << 8 ));
    printf("    Grand Crc = %d", (byte_arr[++i] | byte_arr[++i] << 8 ));
    printf("\n--------   END   -------------\n");

    return 0;
}

void Master::start_message_exchange() {
    uint8_t byte_arr[sizeof(packet_from_spot_to_master_t)];
    packet_from_spot_to_master_t packet;
    int i = 0;

    while(this->server_fd > 0){
        poll(&ufds, 1, 1);
        if(ufds.revents && POLLIN){
            recv(server_fd, byte_arr, BUFF_SIZE, 0);
            memcpy(&packet, byte_arr, sizeof(packet_from_spot_to_master_t));
            if(!(Packet::check_master_node_CRC(&packet)))
                continue;
            printf("\n  ->  count = %d\n", i++);
            ///получаем сообщение от спота
            recv(server_fd, byte_arr, BUFF_SIZE, 0);
            print_paket(byte_arr, "MASTER GET FROM SPOT");

            ///ниже нужно править функции read_packet
            Packet::prepare_answer_from_master_to_spot(byte_arr);
            print_paket(byte_arr, "MASTER SEND TO SPOT");
            send(server_fd, byte_arr, sizeof(packet_from_spot_to_master_t), 0);
        }
    }
    close(client_fd);
    close(server_fd);
}
