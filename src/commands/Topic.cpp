/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:46:18 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/17 16:33:28 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Topic::Topic(Server &server) : ACommand(server)
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
		ch->set_topic(this->_args[1]);
		response = "TOPIC " + ch->get_name() + " " + ch->get_topic() + "\r\n";
		this->_user->prepare_buffer(response);
	}
	else
	{
		response = ":" + _user->get_hostname() + " 331 " + this->_user->get_nick() + " " + ch->get_name() + " " + ch->get_topic() + "\r\n";
		this->_user->set_buffer(response);
	}
	std::cout << this->_user->get_buffer();
    this->_server.send_msg_to_channel(*ch, *_user, CHSELF);
	return(1);
}
