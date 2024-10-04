/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:33:09 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/04 17:12:43 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _nick("Default")
{
	/*std::cout << "User default constructor" << std::endl;*/
}

User::User(std::string nick, const std::string &hostname)
{
	/*std::cout << "User Constructor" << std::endl;*/
	this->_nick = nick;
	this->_hostname = hostname;
}


User::~User()
{
	/*std::cout << "User Destructor" << std::endl;*/
}

std::string User::get_nick() const
{
	return(this->_nick);
}

void User::set_nick(const std::string &nick)
{
	this->_nick = nick;
}

void User::set_hostname(const std::string &hostname)
{
	this->_hostname = hostname;
}

void User::set_buffer(const std::string &buffer)
{
	this->_buffer = buffer;
}

const std::string &User::get_buffer() const
{
	return (this->_buffer);
}

void User::prepare_buffer(const std::string &command)
{
	std::ostringstream oss;
	oss << ":" << this->_nick << "!" << this->_nick << "@" << this->_hostname << " " << command;
	this->_buffer = oss.str();
}