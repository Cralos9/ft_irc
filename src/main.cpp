/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:43:48 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/09 14:11:26 by rumachad         ###   ########.fr       */
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
	
	irc_server.create_server();
	irc_server.main_loop();
	irc_server.close_all_fds();
	return(0);
}