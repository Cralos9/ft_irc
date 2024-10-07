/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:33:09 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/07 12:02:12 by cacarval         ###   ########.fr       */
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


std::string User::get_username() const
{
	return(this->_username);
}

void User::set_username(const std::string &username)
{
	this->_username = username;
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


std::string get_name(const std::string &string, int what)
{
	if (string.find("NICK ") != std::string::npos && what == 1)
	{
		int pos = string.find("NICK ") + 5;
		return(string.substr(pos, (string ).find_first_of("\n", pos) - pos - 1));
	}
	if (string.find("USER ") != std::string::npos && what == 2)
	{
		int pos = string.find("USER ") + 5;
		return(string.substr(pos, (string ).find_first_of("0", pos) - pos - 1));
	}
	return("ERROR");
}

void User::get_info()
{
	std::string nick = get_name(this->get_buffer(), 1);
	std::string username = get_name(this->get_buffer(), 2);
	if (nick != "ERROR" && username != "ERROR")
	{
		this->set_nick(nick);
		this->set_username(username);
	}
}

void User::prepare_buffer(const std::string &command)
{
	std::ostringstream oss;
	oss << ":" << this->_nick << "!" << this->_username << "@" << this->_hostname << " " << command;
	this->_buffer = oss.str();
}