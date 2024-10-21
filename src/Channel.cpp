
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


void Channel::set_name(std::string name)
{
	this->_name = name;
}

std::string Channel::get_name()
{
	return(this->_name);
}

void Channel::set_admin(std::string admin)
{
	this->_admin = admin;
}

std::string Channel::get_admin()
{
	return(this->_admin);
}

void Channel::set_user(std::string user)
{
	if (this->_users.empty())
		this->_users = user;
	else
		this->_users = this->_users + " " + user;
}

bool Channel::is_user_OP(User &user)
{
	std::map<User *, int>::iterator it = _user_map.find(&user);
	if (it == _user_map.end())
		return (false);
	if (it->second == NOP)
		return (false);
	return (true);
}

std::string Channel::get_topic()
{
	if (this->_topic.empty())
		return("Channel has no topic");
	return(this->_topic);
}

void Channel::set_topic(std::string topic)
{
	this->_topic = topic;
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

const std::map<User *, int> &Channel::get_users() const
{
	return (_user_map);
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

void Channel::delete_user_vec(User &del_user)
{
	_user_map.erase(_user_map.find(&del_user));
}

void Channel::add_user(User &user)
{
	if (this->_user_map.empty())
		this->_user_map[&user] = OP;
	else
		this->_user_map[&user] = NOP;
	for (std::map<User *, int>::iterator it = this->_user_map.begin(); it != this->_user_map.end(); it++)
	{
		if (it->second == OP)
			this->all_users = this->all_users + "@" + it->first->get_nick() + " ";
		else
			this->all_users = this->all_users + it->first->get_nick() + " ";
	}
	std::string user_list;
	user_list = ":" + user.get_hostname() + " 353 " + user.get_nick() + " = " + this->_name + " " + this->all_users + "\r\n";
	user.set_buffer(user_list);
	std::cout << user.get_buffer();
	this->all_users = "";
	/* for (std::vector<std::string>::iterator it = this->_user_map.begin(); it != this->_user_map.end(); it++)
		std::cout << *it << std::endl; */
}
