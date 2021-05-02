#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "comm.h"
#include "database.h"

static void send_profiles(int sock_fd, UserProfile *profs, int n_profs)
{
    size_t send_size = sizeof(ProtocolData) + n_profs * sizeof(UserProfile);
    uint8_t *send_buf = malloc(send_size);
    ProtocolData data;
    // data.op = SUCCESS;
    data.profiles_num = n_profs;

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
    switch (req_data->op)
    {
    case CREATE:
        create_user(profile_buf);
        break;
    case READ:
        n_profs = read_db(&profile_buf);
        send_profiles(sock_fd, profile_buf, n_profs);
        break;
    case UPDATE:
        update_user(profile_buf);
        break;
    case DELETE:
        delete_user(profile_buf);
        break;

    default:
        perror("Operação inválida recebida\n");
        exit(1);
        break;
    }
}