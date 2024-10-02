/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:43:48 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/02 14:32:23 by cacarval         ###   ########.fr       */
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
	pollfd	fds[200];
	nfds_t fd_nbr = 1;
	
	std::memset(&fds, 0, sizeof(fds));
	if (irc_server.create_server() == 1)
		return (EXIT_FAILURE);
	fds[0].fd = irc_server.get_fd();
	fds[0].events = POLLIN;
	int ret = 0;
	int active_fds = 0;
	while (1)
	{
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
				int client_fd = accept(irc_server.get_fd(), NULL, NULL);
				if (fds[i].fd < 0)
					print_error("Accept Error");
				fds[fd_nbr].fd = client_fd;
                fds[fd_nbr].events = POLLIN;
				std::cout << "New client " << fd_nbr << " connected" << std::endl;
                fd_nbr++;
			}
			else 
			{
				char buffer[1024] = {0};
				ret = recv(fds[i].fd, buffer, sizeof(buffer), 0);
				if (ret == 0)
				{
					std::cout << "Client " << i << " disconnected" << std::endl;
					close (fds[i].fd);
					active_fds--;
					fd_nbr--;
					for (int j = i; j < active_fds; j++)
						fds[j] = fds[j + 1];
					i--;
					continue;
				}
				if (ret == -1)
					print_error("Recv Error");
				std::cout << "Client " << i << ": " << buffer ;
				std::ostringstream oss;
				oss << "Client " << i << ": " << buffer;
				std::string teste = oss.str();
				for(int j = 1; j < active_fds; j++)
				{
					if (j != i)
						send(fds[j].fd, teste.c_str(), teste.length(), 0);
				}
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