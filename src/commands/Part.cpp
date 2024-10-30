/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:38:31 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:55 by rumachad         ###   ########.fr       */
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
    Channel *channel = _server.check_channel(this->_args[0]);
    if (channel == NULL)
    {
        _numeric_args.push_back(_args[0]);
        _server.send_numeric(*_user, ERR_NOSUCHCHANNEL, _numeric_args, ":No such channel");
        return (1);
    }
    if (!channel->is_user_on_ch(*_user))
    {
        _numeric_args.push_back(_args[0]);
        _server.send_numeric(*_user, ERR_NOTONCHANNEL, _numeric_args, ":You're not on that channel");
        return (1);
    }
    _user->prepare_buffer("PART " + _args[0] + "\r\n");
    _server.print(_user->get_buffer());
    _server.send_msg_to_channel(*channel, *_user, CHSELF);
    channel->delete_user_vec(*_user);
    return(1);
}
