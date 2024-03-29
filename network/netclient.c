/*
    file:   netclient.c

    Simple sockets client
*/
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Client can connect to a server either on the local machine
// or across the network.
#define LOCAL "127.0.0.1"
#define REMOTE "192.168.15.50"
#define BUFLEN 80

int main (int argc, char *argv[])
{
    int client_socket;
    struct sockaddr_in client_addr;
    char ch, text[BUFLEN];
    char *server = LOCAL;
    int result, len;

    if (argc > 1)
        if (strcmp (argv[1], "remote") == 0)
            server = REMOTE;

// Create unnamed socket and then name it
    client_socket = socket (AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family = AF_INET;
    result = inet_aton (server, &client_addr.sin_addr);
    if (result == 0)
    {
        perror ("inet_aton error");
        exit (1);
    }
    client_addr.sin_port = htons (PORT);

// Connect to the server
    result = connect (client_socket, (struct sockaddr *) &client_addr, sizeof (client_addr));
    if (result < 0)
    {
        perror ("Client can't connect");
        exit (1);
    }
// Connection established.  Transfer data
    do
    {
        printf ("Client> ");
        fgets (text, BUFLEN, stdin);
        ch = text[0];
        write (client_socket, text, strlen (text));
        len = read (client_socket, text, sizeof (text));
        text[len] = 0;
        puts (text);
    }
    while (ch != 'q');
    close (client_socket);
    return 0;
}

