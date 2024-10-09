/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:18:50 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/09 11:05:33 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

ACommand::ACommand() : _user(NULL)
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

	while (std::getline(iss, token, ' '))
		this->_args.push_back(token);
}

void ACommand::set_user(User &user)
{
	this->_user = &user;
}