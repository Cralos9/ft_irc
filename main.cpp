/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:43:48 by cacarval          #+#    #+#             */
/*   Updated: 2024/09/30 15:34:40 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main(int argc, char  **argv)
{
	if (argc != 2)
	{
		std::cout << "Try ./ircserv <port> <password>" << std::endl;
		return(0);
	}
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		std::cout << "skill issue no socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(std::atoi(argv[1]));;
	server_address.sin_addr.s_addr = INADDR_ANY;
	if(bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		std::cout << "skill issue no bind" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(socket_fd, 5) < 0)
	{
		std::cout << "skill issue no listen" << std::endl;
		exit(EXIT_FAILURE);
	}
	sockaddr_in client_address;
	socklen_t address_len = sizeof(client_address);
	while(1)
	{
		int client_socket = accept(socket_fd, (struct sockaddr *)&client_address, &address_len);
		if (client_socket < 0)
		{
			std::cout << "skill issue no accept" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	return(0);
}