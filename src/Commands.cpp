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
	: _user(NULL), _server(server), _usable_pre_reg(usable_pre_reg), _min_params(min_params)
{
/* 	std::cout << "ACommands Constructor" << std::endl; */
}

ACommand::~ACommand()
{
/* 	std::cout << "ACommand Destructor" << std::endl; */
}

void ACommand::set_args(std::vector<std::string> args)
{
	_args = args;
}

void ACommand::set_user(User *user) 
{
	_user = user;
}

int ACommand::check()
{
	const std::string command_name = _args[0];
	_args.erase(_args.begin());

	if (_user->get_auth() == true && !_usable_pre_reg)
	{
		_server.send_numeric(*_user, ERR_NOTREGISTERED, "* :You have not registered");
		return (1);
	}
	if (_args.size() < _min_params)
	{
		_server.send_numeric(*_user, ERR_NEEDMOREPARAMS, "%s :Not enough parameters",
								command_name.c_str());
		return (1);
	}
	return (0);
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
