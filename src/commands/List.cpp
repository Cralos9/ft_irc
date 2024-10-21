/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:08:45 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/21 13:37:12 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

List::List(Server &server) : ACommand(server)
{
/* 	std::cout << "List Server Constructor" << std::endl; */
}

List::~List()
{
/* 	std::cout << "List Destructor" << std::endl; */
}

int List::run()
{
    //std::string response = ":" + _user->get_hostname() + " 322 " + this->_user->get_nick() + " " + ch->get_name() + " " + "You're not the channel operator" + "\r\n";
    std::cout << "list" << std::endl;
    return(1);
}