/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:41:19 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/25 11:01:45 by rumachad         ###   ########.fr       */
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

std::vector<pollfd>::iterator find_fd(std::vector<pollfd> &vec, const int fd)
{
	for (std::vector<pollfd>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		if (it->fd == fd)
			return (it);
	}
	return (vec.end());
}

std::deque<std::string> split_block(const std::string &buffer)
{
	std::istringstream iss(buffer);
	std::string token;
	std::deque<std::string> args;

	while (std::getline(iss, token))
		args.push_back(token);
	return (args);
}

std::deque<std::string> split_line(const std::string &buffer)
{
	std::istringstream iss(buffer.substr(0, buffer.find('\r')));
	std::string token;
	std::deque<std::string> args;

	if (buffer.find(':') != std::string::npos)
		iss.str(buffer.substr(0, buffer.find(':') - 1));

	while (std::getline(iss, token, ' '))
		args.push_back(token);

	if (buffer.find(':') != std::string::npos)
		args.push_back(std::strchr(buffer.c_str(), ':'));

	return (args);
}
