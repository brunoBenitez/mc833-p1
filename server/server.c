#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "comm.h"
#include "database.h"

void handle_request(int sock_fd)
{
    size_t recv_size, recvd_size, read_size, send_size;
    void *recv_buffer;
    ProtocolData *req_data;
    UserProfile *profile_buf;

    recv_size = sizeof(ProtocolData) + sizeof(UserProfile);
    recv_buffer = malloc(recv_size);
    recvd_size = recv(sock_fd, recv_buffer, recv_size, 0);

    ProtocolData *data = (ProtocolData *)recv_buffer;
    profile_buf = (UserProfile *)(recv_buffer + sizeof(ProtocolData));

    // Should all cases send response?
    switch (req_data->op)
    {
    case CREATE:
        create_user(profile_buf);
        break;
    case READ:
        read_db(&profile_buf);
        // TODO: send profile_buf
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