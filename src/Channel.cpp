/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/08 14:55:01 by cacarval         ###   ########.fr       */
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