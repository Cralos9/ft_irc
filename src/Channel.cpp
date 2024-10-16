/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/16 13:26:36 by cacarval         ###   ########.fr       */
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

std::string Channel::get_user()
{
	return(this->_users);
}


void Channel::change_user_it(std::string name, char sig)
{
	std::map<User *, int>::iterator it;
	for (it = _user_map.begin(); it != _user_map.end(); it++)
	{
		if (it->first->get_nick() == name)
		{
			if (sig == '+')
				it->second = OP;
			if (sig == '-')
				it->second = NOP;
		}
		
	}
}

void Channel::delete_user_vec(const std::string &name)
{
	for(std::map<User *, int>::iterator it = this->_user_map.begin(); it != this->_user_map.end(); it++)
	{
		if (it->first->get_nick() == name)
		{
			this->_user_map.erase(it);
			break;
		}
	}
}

void Channel::user_list(User &user)
{
	if (this->_user_map.empty())
		this->_user_map[&user] = OP;
	else
		this->_user_map[&user] = NOP;
	for (std::map<User *, int>::iterator it = this->_user_map.begin(); it != this->_user_map.end(); it++)
	{
		std::cout << it->first->get_nick()<< std::endl;
		if (it->second == OP)
			this->all_users = this->all_users + "@" + it->first->get_nick() + " ";
		else
			this->all_users = this->all_users + it->first->get_nick() + " ";
	}
	std::string user_list;
	user_list = ":" + user.get_hostname() + " 353 " + user.get_nick() + " = " + this->_name + " " + this->all_users + "\r\n";
	user.set_buffer(user_list);
	this->all_users = "";
	/* for (std::vector<std::string>::iterator it = this->_user_map.begin(); it != this->_user_map.end(); it++)
		std::cout << *it << std::endl; */
}