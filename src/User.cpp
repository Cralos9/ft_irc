/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:33:09 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/04 14:51:52 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _nick("Default")
{
	std::cout << "User default constructor" << std::endl;
}

User::User(std::string nick)
{
	std::cout << "User Constructor" << std::endl;
	this->_nick = nick;
}


User::~User()
{
	std::cout << "User Destructor" << std::endl;
}