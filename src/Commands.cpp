/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:18:50 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/07 19:11:04 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

ACommand::ACommand()
{
/* 	std::cout << "ACommands Constructor" << std::endl; */
}

ACommand::~ACommand()
{
/* 	std::cout << "ACommand Destructor" << std::endl; */
}

void ACommand::get_args(const std::string &args)
{
	std::istringstream iss(args);
	std::string token;
	while (std::getline(iss, token, ' '))
		this->_args.push_back(token);
}