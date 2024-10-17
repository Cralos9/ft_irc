/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:33:09 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/17 14:02:15 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _fd(0), _nick("Default"), _firstTime(true)
{
	/* std::cout << "User default constructor" << std::endl; */
}

User::User(const int &fd, const std::string &hostname) : _fd(fd)
{
	/* std::cout << "User Constructor" << std::endl; */
	this->_hostname = hostname;
	_firstTime = true;
}

User::~User()
{
	/* std::cout << "User Destructor" << std::endl; */
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

bool User::get_first_time() const
{
	return(_firstTime);
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

void User::set_first_time(const bool &status)
{
	
	this->_firstTime = status;
}

std::string User::get_name(const std::string &string, int what)
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
	if (string.find("PASS ") != std::string::npos && what == 3)
	{
		int pos = string.find("PASS ") + 5;
		return(string.substr(pos, (string ).find_first_of("0", pos) - pos - 1));
	}
	else if (string.find("PASS ") == std::string::npos)
	{
		return "123";
	}
	return("ERROR");
}

bool User::get_info()
{
	std::string nick = get_name(this->get_buffer(), 1);
	std::string username = get_name(this->get_buffer(), 2);
	std::string password = get_name(this->get_buffer(), 3);
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