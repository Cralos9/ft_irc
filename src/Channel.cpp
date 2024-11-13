
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/17 15:02:05 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
/* 	std::cout << "Channel Constructor" << std::endl; */
}

Channel::~Channel()
{
/* 	std::cout << "Channel Destructor" << std::endl; */
}

Channel::Channel(const std::string &name) : _user_limit(50) ,_name(name)
{
/* 	std::cout << "Channel Name constructor" << std::endl; */
}

/* Setters */
void Channel::set_name(const std::string &name)
{
	this->_name = name;
}

void Channel::set_admin(const std::string &admin)
{
	this->_admin = admin;
}

void Channel::set_user(const std::string &user)
{
	if (this->_users.empty())
		this->_users = user;
	else
		this->_users = this->_users + " " + user;
}

void Channel::set_topic(const std::string &topic)
{
	this->_topic = topic;
}

void Channel::set_user_limit(int limit)
{
	_user_limit = limit;
}

/* Getters */
const std::string &Channel::get_name() const
{
	return(this->_name);
}

const std::string Channel::get_user_size() const
{
	std::ostringstream oss;
	oss << _user_map.size();
	return (oss.str());
}

const std::string &Channel::get_admin() const
{
	return(this->_admin);
}

const std::string &Channel::get_topic() const
{
	return(this->_topic);
}

const std::map<User *, int> &Channel::get_users() const
{
	return (_user_map);
}

size_t	Channel::get_user_limit()
{
	return(_user_limit);
}

/* Utility Functions */
bool Channel::is_user_OP(User &user)
{
	std::map<User *, int>::iterator it = _user_map.find(&user);
	if (it == _user_map.end())
		return (false);
	if (it->second == NOP)
		return (false);
	return (true);
}

bool Channel::is_user_on_ch(User &user)
{
	if((this->_user_map.find(&user)) != this->_user_map.end())
		return(1);
	return(0);
}

User *Channel::get_op_user(const std::string &username)
{
	std::map<User *, int>::iterator it;
	for (it = _user_map.begin(); it != _user_map.end(); it++) {
		if (it->second == OP && it->first->get_nick().compare(username) == 0)
			return (it->first);
	}
	return (NULL);
}

User *Channel::get_user(const std::string &username)
{
	std::map<User *, int>::iterator it;
	for (it = _user_map.begin(); it != _user_map.end(); it++) {
		if (it->first->get_nick().compare(username) == 0)
			return (it->first);
	}
	return (NULL);
}

void Channel::change_user_it(User &user, char sig)
{
	std::map<User *, int>::iterator it = _user_map.find(&user);
	if (it == _user_map.end())
		return ;
	if (sig == '+')
		it->second = OP;
	else if (sig == '-')
		it->second = NOP;
}

void Channel::delete_user(User &del_user)
{
	_user_map.erase(_user_map.find(&del_user));
}

void Channel::add_user(User &user)
{
	if (this->_user_map.empty())
		this->_user_map[&user] = OP;
	else
		this->_user_map[&user] = NOP;
}
