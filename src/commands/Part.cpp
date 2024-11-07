/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:38:31 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/07 15:24:11 by cacarval         ###   ########.fr       */
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
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
        return (1);
    }
    if (!channel->is_user_on_ch(*_user))
    {
        _server.send_numeric(*_user, ERR_NOTONCHANNEL, "%s :You're not on that channel",
                                _args[0].c_str());
        return (1);
    }
    _user->make_msg("PART", _args);
    _server.send_msg_to_channel(*channel, *_user, CHSELF);
    channel->delete_user(*_user);
    return(1);
}
