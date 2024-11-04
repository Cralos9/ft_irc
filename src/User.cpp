/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:33:09 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/04 10:50:05 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _fd(0), _nick("Default"), _auth(true)
{
	/* std::cout << "User default constructor" << std::endl; */
}

User::User(const int &fd, const std::string &hostname) :welcome_flag(false) , error_flag(0), _fd(fd), _hostname(hostname), _auth(true)
{
/* 	std::cout << "User Constructor" << std::endl; */
}

User::~User()
{
	/* std::cout << "User Destructor" << std::endl; */
}

/* User getters */

const int &User::get_fd() const
{
	return (_fd);
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

const std::string &User::get_hostname() const
{
	return(this->_hostname);
}

const std::string &User::get_password() const
{
	return(this->_password);
}

const std::string &User::get_realname() const
{
	return (_realname);
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

void User::set_buffer(const std::string &buffer)
{
	this->_buffer = buffer;
}

void User::set_password(const std::string &password)
{
	_password = password;
}

void User::set_realname(const std::string &realname)
{
	_realname = realname;
}

void User::_set_auth(const bool &status)
{
	
	this->_auth = status;
}

/* -------------------------------------- */

const std::string User::get_name(const std::string &buffer, const std::string &attribute,
									const char delimiter)
{
	size_t pos = buffer.find(attribute);

	if (pos != std::string::npos)
	{
		pos += attribute.length();
		return (buffer.substr(pos, buffer.find_first_of(delimiter, pos) - pos - 1));
	}
	return ("ERROR");
}

void User::erase_buffer()
{
	this->_buffer.erase();
}

bool User::get_info()
{
	const std::string password = get_name(_buffer, "PASS ", '\n');
	const std::string nick = get_name(_buffer, "NICK ", '\n');
	const std::string username = get_name(_buffer, "USER ", '0');
	const std::string realname = get_name(_buffer, ":", '\n');

	if (nick != "ERROR")
		_nick = nick;
	if(username != "ERROR")
		_username = username;
	if(password != "ERROR")
		_password = password;
	if (realname != "ERROR")
		_realname = realname;
	if (!(this->_nick.empty()) && !(this->_username.empty()) && !(this->_password.empty()))
 		return (1);
	return (0);
}

void User::prepare_buffer(const std::string &command)
{
	std::ostringstream oss;
	oss << ":" << this->_nick << "!" << this->_username << "@" << this->_hostname << " " << command;
	this->_buffer = oss.str();
}

std::ostream &operator<<(std::ostream &out, const User &user)
{
	out << YELLOW << "Nick: " << user.get_nick() << std::endl
		<< "User: " << user.get_username() << std::endl
		<< "PASS: " << user.get_password() << std::endl
		<< "RealName: " << user.get_realname() << RESET << std::endl;
	return (out);
}
