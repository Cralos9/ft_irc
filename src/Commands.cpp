/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:18:50 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/28 14:21:06 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

ACommand::ACommand(Server &server) : _user(NULL), _server(server)
{
/* 	std::cout << "ACommands Constructor" << std::endl; */
}

ACommand::~ACommand()
{
/* 	std::cout << "ACommand Destructor" << std::endl; */
}

void ACommand::set_args(std::vector<std::string> &args)
{
	_args = args;
}

void ACommand::set_user(User *user) 
{
	this->_user = user;
}

/* Split the buffer into tokens
The 1 token is the Command Name
The rest is params for the Command */


std::vector<std::string> split_lines(const std::string &buffer)
{
	std::istringstream iss(buffer);
	std::string token;
	std::vector<std::string> args;

	while (std::getline(iss, token))
		args.push_back(token);
	return (args);
}

std::vector<std::string> parse_split(const std::string &buffer)
{
	std::istringstream iss(buffer.substr(0, buffer.find('\r')));
	std::string token;
	std::vector<std::string> args;

	while (std::getline(iss, token, ' '))
		args.push_back(token);
	return (args);
}
