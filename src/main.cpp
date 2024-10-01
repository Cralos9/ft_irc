/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:43:48 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/01 14:59:20 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "Server.hpp"

int main(int argc, char  **argv)
{
	if (argc < 2) 
	{
		std::cerr << "Usage: ./ircserv <port>" << std::endl;
		return EXIT_FAILURE;
	}

	Server irc_server(std::atoi(argv[1]));
	int client_fd;
	sockaddr_in client_address;
	socklen_t address_len;
	
	irc_server.create_server();
	while(1)
	{
		client_fd = accept(irc_server.get_fd(), (struct sockaddr *)&client_address, &address_len);
		if (client_fd < 0)
		{
			std::cout << "skill issue no accept" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout << "Client " << client_fd << " connected" << std::endl;
		while(1)
		{
			char buffer[1024] = {0};
			recv(client_fd, buffer, sizeof(buffer), 0);
			std::cout << "Buffer: " << buffer << std::endl;
		}
	}

/*  Function to use the server with the pc ip
	if (inet_pton(AF_INET, ip_address, &server_address.sin_addr) <= 0)
	{
		std::cout <<("Invalid address or address not supported") << std::endl;
		return EXIT_FAILURE;
	} */
	return(0);
}