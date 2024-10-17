/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:30:02 by jmarinho          #+#    #+#             */
/*   Updated: 2024/10/16 12:20:39 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::signal_handler(int signum)
{
	std::cout << std::endl;
	if (signum == SIGINT)
		std::cout << "Received signal Ctrl + C: Exiting server" << std::endl;
	else if (signum == SIGQUIT)
		std::cout << "Received signal Ctrl + \\: Exiting server" << std::endl;
	Server::should_end = true;
}
