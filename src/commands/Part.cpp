/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:38:31 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/21 18:26:42 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Part::Part(Server &server) : ACommand(server, false, 2)
{
/* 	std::cout << "Part Server Constructor" << std::endl; */
}

Part::~Part()
{
/* 	std::cout << "Part Destructor" << std::endl; */
}

const std::vector<std::string> split(const std::string &targets)
{
    std::vector<std::string> vec;
    std::istringstream iss(targets);
    std::string channel;

    while (std::getline(iss, channel, ','))
        vec.push_back(channel);
    return (vec);
}

int Part::run()
{
	const std::vector<std::string> &targets = split(_args[0]);
	std::deque<std::string> params(2);

	params[1] = _args[1];
	for (std::vector<std::string>::const_iterator it = targets.begin(); it != targets.end(); it++)
	{
		params[0] = *it;
		Channel *channel = _server.check_channel(*it);
		if (channel == NULL)
		{
			_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
									it->c_str());
			return (1);
		}

		if (!channel->is_user_on_ch(*_user))
		{
			_server.send_numeric(*_user, ERR_NOTONCHANNEL, "%s :You're not on that channel",
									it->c_str());
			return (1);
		}
		_user->make_msg("PART", params);
		_server.send_msg_to_channel(*channel, *_user, CHSELF);
		channel->delete_user(*_user);
		if (channel->get_users().size() == 0)
			_server.delete_channel(*channel);
	}
	return(1);
}
