/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:41:19 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/07 12:29:13 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::print(const std::string &str)
{
	std::cout << GREEN << "Server: " << RESET << str;
}

void Server::print_recv(const std::string &str)
{
	std::cout << RED << "Client BUFFER: " << YELLOW << str << RESET;
}

it_fd find_fd(std::vector<pollfd> &vec, const int fd)
{
	it_fd it;
	for (it = vec.begin(); it->fd != fd; it++)
		;
	return (it);
}

