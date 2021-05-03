/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "comm.h"
#include "utils.h"

#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

UserProfile *client_connect(ProtocolData comando, UserProfile prof_buf, int *n_profiles)
{
	int sockfd, numbytes;  
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	/*if (argc != 2) {
	    fprintf(stderr,"usage: client hostname\n");
	    exit(1);
	}*/

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) { // Alterar NULL caso necessario
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return NULL;
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			perror("client: connect");
			close(sockfd);
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return NULL;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure

	// Envio de comandos

	int protocol_bytes = sizeof(ProtocolData);
	int profile_bytes = sizeof(UserProfile);
	memcpy(buf, &comando, protocol_bytes);
	memcpy(buf+protocol_bytes, &prof_buf, profile_bytes);

	if (send(sockfd, buf, protocol_bytes, 0) == -1) // Adicionar tamanho do UserProfile?
                perror("send"); 

	// Recebimento da resposta inicial (ProtocolData)

	if ((numbytes = recv(sockfd, buf, protocol_bytes, 0)) == -1) {
	    perror("recv");
	    exit(1);
	}

	buf[numbytes] = '\0';

	printf("client: received '%s'\n",buf);
	ProtocolData resposta;
	UserProfile *profile_list;

	// Capturando protocol data resposta
	memcpy(&resposta, buf, protocol_bytes);

	// Se nao for READ, capturar se houve sucesso ou erro na operacao, e encerrar
	if (comando.op != READ)
	{
		*n_profiles = resposta.op; // ERROR ou SUCCES neste caso
		close(sockfd);
		return NULL;
	}

	// Sabemos quantos profiles vao chegar atraves de resposta.profiles_num
	profile_list = (UserProfile*)malloc(profile_bytes * resposta.profiles_num); // Alocar a lista
	*n_profiles = resposta.profiles_num;

	// Receber N Profiles
	for (size_t i = 0; i < resposta.profiles_num; i++)
	{
		if ((numbytes = recv(sockfd, buf, profile_bytes, 0)) == -1) {
	    	perror("recv");
	    	exit(1);
		}

		// Transferir para a lista
		memcpy(profile_list + (i * profile_bytes), buf, profile_bytes);
	}

	close(sockfd);

	return profile_list;
}
