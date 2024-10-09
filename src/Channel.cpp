/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/09 11:47:43 by cacarval         ###   ########.fr       */
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

void Channel::user_list(it_user user)
{
	if (this->user.empty())
		this->user.push_back(" @" + user->second.get_nick());
	else
		this->user.push_back(user->second.get_nick());
	for (std::vector<std::string>::iterator it2 = this->user.begin(); it2 != this->user.end(); it2++)
		this->all_users = this->all_users + *it2 + " ";
	std::string user_list;
	user_list = ":" + user->second.get_hostname() + " 353 " + user->second.get_nick() + " =" + this->_name + this->all_users + "\r\n";
	user->second.set_buffer(user_list);
}