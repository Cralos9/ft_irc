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

ACommand::ACommand(Server &server, bool usable_pre_reg) : _user(NULL), _server(server), _usable_pre_reg(usable_pre_reg)
{
/* 	std::cout << "ACommands Constructor" << std::endl; */
}

ACommand::~ACommand()
{
/* 	std::cout << "ACommand Destructor" << std::endl; */
}

void ACommand::set_args(std::vector<std::string> &args)
{
	args.erase(args.begin());
	_args = args;
}

void ACommand::set_user(User *user) 
{
	this->_user = user;
}

void ACommand::check()
{
	if (_user->_get_auth() == true && !_usable_pre_reg)
	{
		/* Need to change the throw */
		throw (std::range_error("Test"));
	}
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
