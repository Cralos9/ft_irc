/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:43:48 by cacarval          #+#    #+#             */
/*   Updated: 2024/09/30 18:58:27 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main(int argc, char  **argv)
{
	if (argc < 2) 
	{
		std::cerr << "Usage: ./ircserv <port>" << std::endl;
		return EXIT_FAILURE;
    }

    int socket_fd;
    const char* ip_address = "10.11.3.6";
    sockaddr_in server_address;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
       	std::cout <<("Socket creation failed") << std::endl;
        return EXIT_FAILURE;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(std::atoi(argv[1]));

    if (inet_pton(AF_INET, ip_address, &server_address.sin_addr) <= 0)
	{
       	std::cout <<("Invalid address or address not supported") << std::endl;
        return EXIT_FAILURE;
    }
    if (bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) 
	{
       	std::cout <<("Bind failed") << std::endl;
        return EXIT_FAILURE;
    }
    if (listen(socket_fd, 5) < 0) 
	{
       	std::cout <<("Listen failed") << std::endl;
        return EXIT_FAILURE;
    }
	sockaddr_in client_address;
	socklen_t address_len = sizeof(client_address);
	int client_socket;
	while(1)
	{
		client_socket = accept(socket_fd, (struct sockaddr *)&client_address, &address_len);
		if (client_socket < 0)
		{
			std::cout << "skill issue no accept" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout << "Client connected" << std::endl;
		while(1)
		{
			char buffer[1024] = {0};
			recv(client_socket, buffer, sizeof(buffer), 0);
			if (buffer[0] != '\0')
				std::cout << "Buffer: " << buffer << std::endl;
		}
	}
	close(socket_fd);
	return(0);
}