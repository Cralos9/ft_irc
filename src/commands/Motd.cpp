/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:30:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/26 11:39:58 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Motd::Motd(Server &server) : ACommand(server, false, 0)
{
/* 	std::cout << "Motd Server Constructor" << std::endl; */
}

Motd::~Motd()
{
/* 	std::cout << "Motd Destructor" << std::endl; */
}

int Motd::run()
{
	std::ifstream file(MOTD_FILE);
	std::string line;

	if (!file.is_open())
	{
		_server.send_numeric(*_user, ERR_NOMOTD, ":MOTD File is missing");
		return (1);
	}
	_server.send_numeric(*_user, RPL_MOTDSTART, ":- %s Message of the day -", _server.get_host().c_str());
	while (std::getline(file, line))
		_server.send_numeric(*_user, RPL_MOTD, ":- %s", line.c_str());
	_server.send_numeric(*_user, RPL_ENDOFMOTD, ":End of /MOTD");
	file.close();
	return (0);
}