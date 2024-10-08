/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:21:07 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/08 15:01:17 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "ft_irc.hpp"

class Channel
{
	public:
		Channel(){};
		~Channel(){};
		Channel(std::string name)
		{
			this->_name = name;
		}
		void set_name(std::string name);
		std::string get_name();
		void set_admin(std::string admin);
		std::string get_admin();
		void set_user(std::string user);
		std::string get_user();
		std::vector<std::string> user;

private:
		std::string _name;
		std::string _admin;
		std::string _users;

};


#endif