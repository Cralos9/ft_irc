/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:43:48 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/02 12:11:00 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "Server.hpp"

void print_error(std::string error_msg)
{
	std::perror(error_msg.c_str());
	exit(EXIT_FAILURE);
}

int main(int argc, char  **argv)
{
	if (argc < 2) 
	{
		std::cerr << "Usage: ./ircserv <port>" << std::endl;
		return EXIT_FAILURE;
	}

	Server irc_server(std::atoi(argv[1]));
	pollfd	fds[2];
	nfds_t fd_nbr = 1;
	
	std::memset(&fds, 0, sizeof(fds));
	if (irc_server.create_server() == 1)
		return (EXIT_FAILURE);
	fds[0].fd = irc_server.get_fd();
	fds[0].events = POLLIN;
	int ret = 0;
	char buffer[1024] = {0};
	int active_fds = 0;
	while (1)
	{
		std::cout << "Waiting poll" << std::endl;
		ret = poll(fds, fd_nbr, -1);
		if (ret == -1)
			print_error("Poll Error");
		if (ret == 0)
		{
			std::cout << "Pool timeout" << std::endl;
			return (EXIT_FAILURE);
		}
		active_fds = fd_nbr;
		for (int i = 0; i < active_fds; i++)
		{
			if (fds[i].revents == 0)
				continue;
			if (fds[i].revents != POLLIN)
				print_error("Error revents");
			if (fds[i].fd == irc_server.get_fd())
			{
				fds[i].fd = accept(irc_server.get_fd(), NULL, NULL);
				if (fds[i].fd < 0)
					print_error("Accept Error");
				std::cout << "New client: " << fds[i].fd << " connected" << std::endl;
			}
			else {
				ret = recv(fds[i].fd, buffer, sizeof(buffer), 0);
				if (ret == -1)
					print_error("Recv Error");
				std::cout << "Buffer: " << buffer << std::endl;
			}
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