/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:43:48 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/29 16:06:49 by rumachad         ###   ########.fr       */
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
	Server::should_end = false;
	
	if (argc < 3) 
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return EXIT_FAILURE;
	}

	signal(SIGINT, Server::signal_handler);
	signal(SIGQUIT, Server::signal_handler);

	Server irc_server(std::atoi(argv[1]), argv[2]);
	
	irc_server.create_server();
	irc_server.main_loop();
	return(0);
}