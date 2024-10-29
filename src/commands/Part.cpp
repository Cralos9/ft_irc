/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:38:31 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/29 15:59:14 by rumachad         ###   ########.fr       */
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
        const std::string err = client_rpl(_server._hostname, _user->get_nick(),
                            ERR_NOSUCHCHANNEL) + _args[0] + " :No such channel\r\n";
        _user->set_buffer(err);
        _server.print(err);
        _server.send_msg_one_user(_user->get_fd(), *_user);
        return (1);
    }
    if (!channel->is_user_on_ch(*_user))
    {
        const std::string err = client_rpl(_server._hostname, _user->get_nick(),
                            ERR_NOTONCHANNEL) + channel->get_name() + " :You're not on that channel\r\n";
        _user->set_buffer(err);
        _server.print(err);
        _server.send_msg_one_user(_user->get_fd(), *_user);
        return (1);
    }
    _user->prepare_buffer("PART " + _args[0] + "\r\n");
    _server.print(_user->get_buffer());
    _server.send_msg_to_channel(*channel, *_user, CHSELF);
    channel->delete_user_vec(*_user);
    return(1);
}
