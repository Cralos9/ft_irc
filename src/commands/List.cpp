/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:08:45 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/28 13:27:39 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

List::List(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
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