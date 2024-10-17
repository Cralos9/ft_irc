/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:21:07 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/17 15:37:50 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "ft_irc.hpp"
#include "User.hpp"

#define OP 1
#define NOP 0
// #define LEAVING 1
// #define STAY 0

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
		User *get_user(const std::string &username);
		User *get_op_user(const std::string &username);
		const std::map<User *, int> &get_users() const;
		void add_user(User &user);
		void delete_user_vec(User &del_user);
		void change_user_it(User &user, char sig);
		bool is_user_OP(User &user);
		bool is_user_on_ch(User &user);
		std::string get_topic();
		void set_topic(std::string topic);
private:
		std::string _topic;
		std::map<User*, int> _user_map;
		std::string all_users;
		std::string _name;
		std::string _admin;
		std::string _users;

};


#endif