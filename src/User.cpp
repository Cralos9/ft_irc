/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:33:09 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/13 18:27:43 by rumachad         ###   ########.fr       */
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

bool User::get_auth() const
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
	_buffer += buffer;
}

void User::set_password(const std::string &password)
{
	_password = password;
}

void User::set_realname(const std::string &realname)
{
	_realname = realname;
}

void User::set_auth(const bool &status)
{
	
	_auth = status;
}

/* -------------------------------------- */

void User::erase_pass()
{
	_password.clear();
}
void User::erase_buffer()
{
	this->_buffer.clear();
}

void User::make_msg(const std::string &command, const std::vector<std::string> &params)
{
	_buffer = ":" + _nick + "!" + _username + "@" + _hostname + " " + command + " ";
	for (std::vector<std::string>::const_iterator it = params.begin(); it != params.end(); it++) {
		_buffer.append(*it + ' ');
	}
	_buffer.append("\r\n");
}

std::ostream &operator<<(std::ostream &out, const User &user)
{
	out << YELLOW << "Nick: " << user.get_nick() << std::endl
		<< "User: " << user.get_username() << std::endl
		<< "PASS: " << user.get_password() << std::endl
		<< "RealName: " << user.get_realname() << RESET << std::endl;
	return (out);
}

bool User::is_registered()
{
	if (_nick.empty() || _realname.empty() || _username.empty() || _password.empty())
		return (false);
	return (true);
}

void User::erase_nick()
{
	_nick.clear();
}
