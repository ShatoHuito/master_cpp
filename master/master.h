//
// Created by ilnur on 16.03.2022.
//

#ifndef MASTER_CPP_MASTER_H
#define MASTER_CPP_MASTER_H

#include <sys/poll.h>
#include <cstdint>
#include <cstring>
#include <fcntl.h>


class Master{
public:
    Master();
    struct pollfd ufds;

    bool init_network();
    void start_message_exchange();

private:
    uint16_t server_fd = 0;
    uint16_t client_fd = 0;
};

#endif //MASTER_CPP_MASTER_H
