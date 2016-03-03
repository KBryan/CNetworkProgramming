//
//  TCPServer.c
//  NetworkProgramming
//
//  Created by KBryan on 2016-02-25.
//  Copyright © 2016 KBryan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    /**
     *  @author Kwame Bryan
     *
     *  @brief file pointer to hold data
     */
    FILE *html_data;
    html_data = fopen("index.html", "r");
    char response_data[1024];
    fgets(response_data, 1024, html_data);
    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);
    /**
     *  @author Kwame Bryan
     *
     *  @brief create a socket
     */
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    /**
     *  @author Kwame Bryan
     *
     *  @brief define the server address
     */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;
    /**
     *  @author Kwame Bryan
     *
     *  @brief <#Description#>
     *
     *  @param server_socket <#server_socket description#>
     *  @param sockaddr      <#sockaddr description#>
     *
     *  @return <#return value description#>
     */
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, 5);
    int client_socket;
    while (1) {

        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header),0);
        close(server_socket);
    
    }
    return 0;
}