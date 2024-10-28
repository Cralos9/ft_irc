/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:38:31 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/28 13:27:52 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Part::Part(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "Part Server Constructor" << std::endl; */
}

Part::~Part()
{
/* 	std::cout << "Part Destructor" << std::endl; */
}

int Part::run()
{
    Channel *ch = _server.check_channel(this->_args[0]);
    _user->prepare_buffer(_user->get_buffer());
    _server.send_msg_to_channel(*ch, *_user, CHSELF);
    ch->delete_user_vec(*_user);
    return(1);
}