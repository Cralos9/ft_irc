/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:21:07 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/14 17:26:04 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "ft_irc.hpp"
#include "User.hpp"

typedef std::map<int, User>::iterator it_user;

class Channel
{
	public:
		Channel(){};
		~Channel(){};
		Channel(std::string name)
		{
			this->all_users = "";
			this->_name = name;
		}
		void set_name(std::string name);
		std::string get_name();
		void set_admin(std::string admin);
		std::string get_admin();
		void set_user(std::string user);
		std::string get_user();
		void user_list(User &user);
		void delete_user_vec(const std::string &name);
		void change_user_it(std::string name);

private:
		std::vector<std::string> user_vec;
		std::string all_users;
		std::string _name;
		std::string _admin;
		std::string _users;

};


#endif