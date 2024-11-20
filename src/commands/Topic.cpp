/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:46:18 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/19 15:16:31 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Topic::Topic(Server &server) : ACommand(server, false, 1)
{
/* 	std::cout << "Topic Server Constructor" << std::endl;
 */}

Topic::~Topic()
{
/* 	std::cout << "Topic Destructor" << std::endl; */
}

int Topic::run()
{
	Channel *ch = _server.check_channel(_args[0]);

	if (ch == NULL)
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
		return (1);
	}
	if ((_args.size() > 1))
	{
		/* Erase the ':' from Topic Name */
		const std::string topic = _args[1].substr(1, _args[1].length() - 1);
		if (!ch->is_user_on_ch(*_user))
		{
			_server.send_numeric(*_user, ERR_NOTONCHANNEL, "%s :You're not on that channel");
			return (0);
		}
		if (ch->get_statusTopicRestrictions() == false || ch->is_user_OP(*_user))
		{
			ch->set_topic(topic);
			_user->make_msg("TOPIC", _args);
		}
		if (ch->get_statusTopicRestrictions() == true && !ch->is_user_OP(*_user))
		{
			_server.send_numeric(*_user, ERR_CHANOPRIVSNEEDED,
										"%s :You're not the channel operator", _args[0].c_str());
			return(EXIT_FAILURE);
		}
	}
	else
	{
		if (ch->get_topic().empty())
			_server.send_numeric(*_user, RPL_NOTOPIC, "%s :No topic is set", _args[0].c_str());
		else
			_server.send_numeric(*_user, RPL_TOPIC, "%s :%s", ch->get_name().c_str(),
									ch->get_topic().c_str());
		return(1);
	}
    _server.send_msg_to_channel(*ch, *_user, CHSELF);
	return(1);
}
