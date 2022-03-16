//
// Created by ilnur on 16.03.2022.
//

#ifndef MASTER_CPP_NETWORK_H
#define MASTER_CPP_NETWORK_H

#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

class Network{
public:
    static int Socket(int domain, int type, int protocol);

    static void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    static void Listen(int sockfd, int backlog);

    static int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    size_t Read(int fd, void *buf, size_t count);

    static void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    static void Inet_pton(int af, const char *src, void *dst);

};

#endif //MASTER_CPP_NETWORK_H
