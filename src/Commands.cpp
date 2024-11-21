/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:18:50 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/28 15:16:59by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

ACommand::ACommand(Server &server, bool usable_pre_reg, const size_t min_params)
	: _usable_pre_reg(usable_pre_reg), _min_params(min_params), _user(NULL), _server(server)
{
/* 	std::cout << "ACommands Constructor" << std::endl; */
}

ACommand::~ACommand()
{
/* 	std::cout << "ACommand Destructor" << std::endl; */
}

void ACommand::set_args(std::deque<std::string> args)
{
	_args = args;
}

void ACommand::set_user(User *user) 
{
	_user = user;
}

/* Split the buffer into tokens
The 1 token is the Command Name
The rest is params for the Command */

std::deque<std::string> split_lines(const std::string &buffer)
{
	std::istringstream iss(buffer);
	std::string token;
	std::deque<std::string> args;

	int i = 0;
	while (std::getline(iss, token))
	{
		if (!token.empty()) {
			std::cout << "TOKEN " << i << ": " << token << std::endl;
			args.push_back(token);
			i++;
		}
	}

	return (args);
}

std::deque<std::string> parse_split(const std::string &buffer)
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
