/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_Commands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:16 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/03 12:06:48 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::join_Channel(std::string buffer, int pos)
{
	std::cout << "Joining " << buffer.substr(pos, (buffer.find_first_of("\n") - pos - 1))<< " ..." << std::endl;
}


// void Server::use_commands(std::string command)
// {
// 	std::cout << command << std::endl;
// 	if (command == "JOIN")
// 		this->join_Channel();
// }