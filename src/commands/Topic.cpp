/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:46:18 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/30 15:00:36 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Topic::Topic(Server &server, bool usable_pre_reg) : ACommand(server, usable_pre_reg)
{
/* 	std::cout << "Topic Server Constructor" << std::endl;
 */}

Topic::~Topic()
{
/* 	std::cout << "Topic Destructor" << std::endl;
 */}

int Topic::run()
{
	std::string response;
	Channel *ch = _server.check_channel(_args[0]);
	if ((_args.size() > 1))
	{
		if (ch->is_user_OP(*_user))
		{
			ch->set_topic(this->_args[1]);
			response = "TOPIC " + ch->get_name() + " " + ch->get_topic() + "\r\n";
			_user->prepare_buffer(response);
		}
		else
		{
			_numeric_args.push_back(_args[0]);
			_server.send_numeric(*_user, ERR_CHANOPRIVSNEEDED, _numeric_args, ":You're not the channel operator");
			return(1);
		}
	}
	else
	{
		_numeric_args.push_back(_args[0]);
		if (ch->get_topic() == "")
			_server.send_numeric(*_user, RPL_NOTOPIC, _numeric_args, ":No topic is set");
		else
			_server.send_numeric(*_user, RPL_TOPIC, _numeric_args, ":" + ch->get_topic());
		return(1);
	}
    _server.send_msg_to_channel(*ch, *_user, CHSELF);
	return(1);
}
