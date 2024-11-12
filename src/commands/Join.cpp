/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/12 14:28:15 by cacarval         ###   ########.fr       */
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

std::vector<std::string> split_channel(const std::string& channels) 
{
    std::vector<std::string> splited_ch;
    size_t start = 0;
    size_t end = channels.find(',');

    while (end != std::string::npos) 
	{
        splited_ch.push_back(channels.substr(start, end - start));
        start = end + 1;
        end = channels.find(',', start);
    }
    splited_ch.push_back(channels.substr(start));

	for(std::vector<std::string>::iterator it = splited_ch.begin(); it != splited_ch.end(); it++)
		std::cout << *it << std::endl;
    return splited_ch;
}

int Join::run()
{
	const std::string channel = _args[0];
	std::vector<std::string> splited_ch;
	
	if (channel[0] != '#')
	{
		_server.send_numeric(*_user, ERR_NOSUCHCHANNEL, "%s :No such channel",
								_args[0].c_str());
		return(1);
	}
	splited_ch = split_channel(_args[0]);
	for(std::vector<std::string>::iterator it = splited_ch.begin(); it != splited_ch.end(); it++)
	{
		_args[0] = *it;
		_user->make_msg("JOIN", _args);
		Channel *ch = _server.check_channel(_args[0]);
		if (ch == NULL)
			ch = _server.create_channel(channel);
		if (ch->get_users().size() < ch->get_user_limit())
		{
			ch->add_user(*_user);
			_server.send_msg_to_channel(*ch, *_user, CHSELF);
		}
		else
		{
			_server.send_numeric(*_user, "471", "%s :Cannot join channel (+l)",
								_args[0].c_str());
		}
	}
	return (0);
}
