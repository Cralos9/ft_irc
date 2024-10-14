/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/14 17:25:57 by rumachad         ###   ########.fr       */
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


void Channel::change_user_it(std::string name)
{
	std::vector<std::string>::iterator it;
	for (it = user_vec.begin(); it != user_vec.end(); it++)
	{
		std::cout << *it << " " << name << std::endl;
		if (*it == name)
		{
			*it = "@" + *it;
			std::cout << *it << std::endl;
		}
	}
}

void Channel::delete_user_vec(const std::string &name)
{
	for(std::vector<std::string>::iterator it = this->user_vec.begin(); it != this->user_vec.end(); it++)
	{
		if (*it == name)
		{
			this->user_vec.erase(it);
			break;
		}
	}
}

void Channel::user_list(User &user)
{
	if (this->user_vec.empty())
		this->user_vec.push_back("@" + user.get_nick());
	else
		this->user_vec.push_back(user.get_nick());
	for (std::vector<std::string>::iterator it2 = this->user_vec.begin(); it2 != this->user_vec.end(); it2++)
		this->all_users = this->all_users + *it2 + " ";
	std::string user_list;
	user_list = ":" + user.get_hostname() + " 353 " + user.get_nick() + " =" + this->_name + " " + this->all_users + "\r\n";
	user.set_buffer(user_list);
	this->all_users = "";
	for (std::vector<std::string>::iterator it2 = this->user_vec.begin(); it2 != this->user_vec.end(); it2++)
		std::cout << *it2 << std::endl;
}