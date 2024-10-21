/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:08:45 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/21 14:38:16 by cacarval         ###   ########.fr       */
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
    _server.channel_list(*_user);
    return(1);
}