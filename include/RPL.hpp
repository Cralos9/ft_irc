/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:30:53 by rumachad          #+#    #+#             */
/*   Updated: 2024/11/07 11:01:33 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_HPP
# define RPL_HPP

#include "ft_irc.hpp"

/* RPL_ Messages */
#define RPL_WELCOME				"001"
#define RPL_YOURHOST			"002"
#define RPL_CREATED				"003"
#define RPL_MYINFO				"004"
#define RPL_ISUPPORT			"005"
#define RPL_WHOISCERTFP			"276"
#define RPL_WHOISREGNICK		"307"
#define RPL_WHOISUSER			"311"
#define RPL_WHOISSERVER 		"312"
#define RPL_WHOISOPERATOR		"313"
#define RPL_ENDOFWHOIS			"318"
#define RPL_WHOISCHANNELS 		"319"
#define RPL_LISTSTART			"321"
#define RPL_LIST				"322"
#define RPL_LISTEND				"323"
#define RPL_NOTOPIC				"331"
#define RPL_TOPIC				"332"
#define RPL_INVITING			"341"
#define RPL_WHOREPLY			"352"
#define RPL_MOTD				"372"
#define RPL_MOTDSTART			"375"
#define RPL_ENDOFMOTD			"376"

/* ERR_ Messages*/
#define ERR_NOSUCHNICK			"401"
#define ERR_NOSUCHCHANNEL		"403"
#define ERR_NOMOTD				"422"
#define ERR_NICKNAMEINUSE		"433"
#define ERR_USERNOTINCHANNEL	"441"
#define ERR_USERONCHANNEL		"443"
#define ERR_NOTREGISTERED		"451"
#define ERR_NOTONCHANNEL		"442"
#define ERR_ALREADYREGISTERED	"462"
#define ERR_CHANOPRIVSNEEDED	"482"

const std::string client_rpl(const std::string &hostname, const std::string &nickname
								, const std::string &rpl_numeric);
const std::string numeric_motd(const std::string &hostname, const std::string &user_nick);
const std::string make_numeric(const std::string &hostname, const std::string &nickname
						, const std::string &numeric, std::vector<std::string> &args, const std::string &msg);
#endif