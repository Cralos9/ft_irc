/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:46:18 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/28 14:56:56 by rumachad         ###   ########.fr       */
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
	Channel *ch = _server.check_channel(this->_args[0]);
	if ((this->_args.size() > 1))
	{
		if (ch->is_user_OP(*_user))
		{
			ch->set_topic(this->_args[1]);
			response = "TOPIC " + ch->get_name() + " " + ch->get_topic() + "\r\n";
			this->_user->prepare_buffer(response);
		}
		else
		{
			response = client_rpl(_user->get_hostname(), _user->get_nick(), "482");
			response = response + " " + ch->get_name() + " " + "You're not the channel operator" + "\r\n";
			this->_user->set_buffer(response);
			this->_server.send_msg_one_user(_user->get_fd(), *_user);
			return(1);
		}
	}
	else
	{
		response = client_rpl(_user->get_hostname(), _user->get_nick(), "331");
		response = response + " " + ch->get_name() + " ";
		if (ch->get_topic() == "")
			response = response + "No topic is set" + "\r\n";
		else
			response = response + ch->get_topic() + "\r\n";
		this->_user->set_buffer(response);
		this->_server.send_msg_one_user(_user->get_fd(), *_user);
		return(1);
	}
	std::cout << this->_user->get_buffer();
    this->_server.send_msg_to_channel(*ch, *_user, CHSELF);
	return(1);
}
