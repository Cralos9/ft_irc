/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:08:45 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/07 12:02:29 by rumachad         ###   ########.fr       */
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
    const std::map<std::string, Channel> &channels = _server.get_channels();

    _server.send_numeric(*_user, RPL_LISTSTART, "Channel :Users Name");
    for (std::map<std::string, Channel>::const_iterator it = channels.begin(); it != channels.end(); it++) {
        _server.send_numeric(*_user, RPL_LIST, "%s %s :%s", it->second.get_name().c_str(),
                            it->second.get_user_size().c_str(), it->second.get_topic().c_str());
    }
    _server.send_numeric(*_user, RPL_LISTEND, ":End of /LIST");
    return(1);
}