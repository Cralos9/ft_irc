/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:33:09 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/04 15:23:55 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _nick("Default")
{
	std::cout << "User default constructor" << std::endl;
}

User::User(std::string nick)
{
	std::cout << "User Constructor" << std::endl;
	this->_nick = nick;
}


User::~User()
{
	std::cout << "User Destructor" << std::endl;
}

std::string User::get_nick() const
{
	return(this->_nick);
}

void User::set_nick(const std::string &nick)
{
	this->_nick = nick;
}