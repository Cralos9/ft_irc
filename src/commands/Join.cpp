/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/18 16:54:46y rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Join::Join(Server &server) : ACommand(server, false, 1)
{
/* 	std::cout << "Join Server Constructor" << std::endl; */
}

Join::~Join()
{
/* 	std::cout << "Join Destructor" << std::endl; */
}

std::vector<std::pair<std::string, std::string> > split_channel(const std::string &channels, const std::string &keys) 
{
	std::istringstream channel_iss(channels);
	std::istringstream keys_iss(keys);
	std::string channel;
	std::string key;
	std::vector<std::pair<std::string, std::string> > vec;

	while (std::getline(channel_iss, channel, ','))
	{
		std::getline(keys_iss, key, ',');
		vec.push_back(std::make_pair(channel, key));
	}
	return (vec);
}

const std::string users_from_channel(const std::map<User *, int> &channel_users)
{
	std::string users;
	for (std::map<User *, int>::const_iterator it = channel_users.begin(); it != channel_users.end(); it++)
	{
		if (it->second == OP)
			users.append('@' + it->first->get_nick() + ' ');
		else
		 	users.append(it->first->get_nick() + " ");
	}
	return (users);
}

void Join::join_channel(Channel *ch, std::deque<std::string> &params)
{
	ch->add_user(*_user);
	_user->make_msg("JOIN", params);
	_server.send_msg_to_channel(*ch, *_user, CHSELF);
	if (!ch->get_topic().empty())
		_server.send_numeric(*_user, RPL_TOPIC, "%s :%s", ch->get_name().c_str(),
						ch->get_topic().c_str());
	_server.send_numeric(*_user, RPL_NAMREPLY, "= %s :%s", ch->get_name().c_str(),
						users_from_channel(ch->get_users()).c_str());
	
}

int Join::can_join(Channel *ch, const std::string &password)
{
	const std::vector<std::string> &invited_channels = _user->get_invited_channels();

	if (ch->get_users().size() > ch->get_user_limit())
	{
		_server.send_numeric(*_user, ERR_CHANNELISFULL, "%s :Cannot join channel (+l)",
							_args[0].c_str());
		return (false);
	}
	if (!ch->get_password().empty() && ch->get_password() != password)
	{
		_server.send_numeric(*_user, ERR_BADCHANNELKEY, "%s :Cannot join channel (+k)",
						_args[0].c_str());
		return (false);
	}
	if (ch->get_statusInviteOnly() &&
		std::find(invited_channels.begin(), invited_channels.end(), ch->get_name()) == invited_channels.end())
	{
		_server.send_numeric(*_user, ERR_INVITEONLYCHAN, "%s :Cannot join channel (+i)",
					_args[0].c_str());
		return (false);
	}
	return (true);
}

int Join::run()
{
	if (_args[0][0] != '#')
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
		return(1);
	}

	std::deque<std::string> params(2);
	std::vector<std::pair<std::string, std::string> > channels;

	if (_args.size() != 2)
		channels = split_channel(_args[0], "");
	else
		channels = split_channel(_args[0], _args[1]);

	for (std::vector<std::pair<std::string, std::string> >::iterator it = channels.begin();
			it != channels.end(); it++)
	{
		params[0] = it->first;
		params[1] = it->second;
		Channel *ch = _server.check_channel(it->first);
		if (ch == NULL)
		{
			ch = _server.create_channel(it->first);
			join_channel(ch, params);
		}
		else
		{
			if (can_join(ch, it->second))
				join_channel(ch, params);
		}
	}
	return (0);
}
