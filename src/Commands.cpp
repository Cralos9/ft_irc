/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:18:50 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/23 10:30:21 by rumachad         ###   ########.fr       */
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

void ACommand::set_args(const std::string &args)
{
	std::istringstream iss(args);
	std::string token;

	this->_args.erase(this->_args.begin(), this->_args.end());
	while (std::getline(iss, token, ' '))
    {
        std::size_t pos = token.find('\r');
        if (pos != std::string::npos)
			token = token.substr(0, pos);
        this->_args.push_back(token);
    }
}

void ACommand::set_user(User *user) 
{
	this->_user = user;
}
