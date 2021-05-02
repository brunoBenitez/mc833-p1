#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "comm.h"
#include "database.h"

static void send_success(int sock_fd)
{
    ProtocolData data;
    data.op = htonl(SUCCESS);
    data.profiles_num = 0;
    send(sock_fd, &data, sizeof(ProtocolData), 0);
}

static void send_success(int sock_fd)
{
    ProtocolData data;
    data.op = htonl(ERROR);
    data.profiles_num = 0;
    send(sock_fd, &data, sizeof(ProtocolData), 0);
}

static void send_profiles(int sock_fd, UserProfile *profs, int n_profs)
{
    size_t send_size = sizeof(ProtocolData) + n_profs * sizeof(UserProfile);
    uint8_t *send_buf = malloc(send_size);
    ProtocolData data;
    data.op = htonl(SUCCESS);
    data.profiles_num = htonl(n_profs);

    memcpy(send_buf, &data, sizeof(ProtocolData));
    memcpy(send_buf + sizeof(ProtocolData), profs, n_profs * sizeof(UserProfile));

    if (send(sock_fd, send_buf, send_size, 0) != send_size)
    {
        perror("buffers not sent completely");
    }
}

void handle_request(int sock_fd)
{
    size_t recv_size;
    int n_profs;
    uint8_t *recv_buffer;
    ProtocolData *req_data;
    UserProfile *profile_buf;

    recv_size = sizeof(ProtocolData) + sizeof(UserProfile);
    recv_buffer = malloc(recv_size);
    recv(sock_fd, recv_buffer, recv_size, 0);

    req_data = (ProtocolData *)recv_buffer;
    profile_buf = (UserProfile *)(recv_buffer + sizeof(ProtocolData));

    // Should all cases send response?
    switch (ntohl(req_data->op))
    {
    case CREATE:
        if (create_user(profile_buf))
            send_success(sock_fd);
        else
            send_error(sock_fd);
        break;
    case READ:
        n_profs = read_db(&profile_buf);
        if (n_profs > 0)
            send_profiles(sock_fd, profile_buf, n_profs);
        else
            send_error(sock_fd);
        break;
    case UPDATE:
        if (update_user(profile_buf))
            send_success(sock_fd);
        else
            send_error(sock_fd);
        break;
    case DELETE:
        if (delete_user(profile_buf))
            send_success(sock_fd);
        else
            send_error(sock_fd);
        break;

    default:
        perror("Operação inválida recebida\n");
        exit(1);
        break;
    }
}