/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:41:19 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/21 13:18:14 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void print(const std::string &str)
{
	std::cout << GREEN << "Server: " << RESET << str;
}

void print_recv(const User &user)
{
	std::cout << RED << "Client " << user.get_nick() << ": " << YELLOW << user.get_buffer() << RESET;
}

it_fd find_fd(std::vector<pollfd> &vec, const int fd)
{
	it_fd it;
	for (it = vec.begin(); it->fd != fd; it++)
		;
	return (it);
}

