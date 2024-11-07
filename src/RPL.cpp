/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:29:25 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/07 12:34:20 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"

const std::string client_rpl(const std::string &hostname, const std::string &nickname
								, const std::string &rpl_numeric)
{
	return (":" + hostname + " " + rpl_numeric + " " + nickname + " ");
}

const std::string numeric_motd(const std::string &hostname, const std::string &user_nick)
{
	std::string rpl = client_rpl(hostname, user_nick, RPL_MOTDSTART) + ":- " + hostname
					+ " make_msg of the day -\r\n";
	rpl.append(client_rpl(hostname, user_nick, RPL_MOTD) + ":- Jose Figueiras is innocent 🇵🇹\r\n");
	rpl.append(client_rpl(hostname, user_nick, RPL_ENDOFMOTD) + ":End of /MOTD\r\n");
	return (rpl);
}
