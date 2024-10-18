/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:33:09 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/18 10:09:01 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _fd(0), _nick("Default"), _auth(true)
{
	std::cout << "User default constructor" << std::endl;
}

User::User(const int &fd, const std::string &hostname) : _fd(fd)
{
	/* std::cout << "User Constructor" << std::endl; */
	this->_hostname = hostname;
	_auth = true;
}

User::~User()
{
	std::cout << "User Destructor" << std::endl;
}

/* User getters */

const int &User::get_fd() const
{
	return (this->_fd);
}

const std::string &User::get_nick() const
{
	return(this->_nick);
}

const std::string &User::get_buffer() const
{
	return (this->_buffer);
}

const std::string &User::get_username() const
{
	return(this->_username);
}

const std::string &User::get_password() const
{
	return(this->_password);
}

bool User::_get_auth() const
{
	return(_auth);
}

/* -------------------------------------------------- */

/* User setters */

void User::set_nick(const std::string &nick)
{
	this->_nick = nick;
}

void User::set_username(const std::string &username)
{
	this->_username = username;
}

void User::set_hostname(const std::string &hostname)
{
	this->_hostname = hostname;
}

std::string User::get_hostname()
{
	return(this->_hostname);
}

void User::set_buffer(const std::string &buffer)
{
	this->_buffer = buffer;
}

void User::_set_auth(const bool &status)
{
	
	this->_auth = status;
}

std::string User::get_name(const std::string &string, int what)
{	
	if (string.find("PASS ") != std::string::npos && what == 0)
	{
		int pos = string.find("PASS ") + 5;
		return(string.substr(pos, (string ).find_first_of("\n", pos) - pos - 1));
	}
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

bool User::get_info()
{
	std::string password = get_name(this->get_buffer(), 0);
	std::string nick = get_name(this->get_buffer(), 1);
	std::string username = get_name(this->get_buffer(), 2);
	/* std::cout << RED << "SavedPasssword:\n" << BLUE << password << RESET << std::endl;
	std::cout << RED << "SavedNick:\n" << BLUE << nick << RESET << std::endl;
	std::cout << RED << "SavedUsername:\n" << BLUE << username << RESET << std::endl; */
	
	if ((nick != "ERROR" && nick.find("USER ") == std::string::npos)&& username != "ERROR")
	{
		this->_nick = nick;
		this->_username = username;
		this->_password = password;
 		return (1);
	}
	return (0);
}


void User::prepare_buffer(const std::string &command)
{
	std::ostringstream oss;
	oss << ":" << this->_nick << "!" << this->_username << "@" << this->_hostname << " " << command;
	this->_buffer = oss.str();
}