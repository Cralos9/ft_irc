/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:41:19 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/24 12:05:26 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::print(const std::string &str)
{
	std::cout << GREEN << "Server: " << RESET << str << std::endl;
}

void Server::print_recv(const std::string &str)
{
	std::cout << RED << "Client BUFFER:\n" << BLUE << str << RESET;
}

it_fd find_fd(std::vector<pollfd> &vec, const int fd)
{
	it_fd it;
	for (it = vec.begin(); it->fd != fd; it++)
		;
	return (it);
}