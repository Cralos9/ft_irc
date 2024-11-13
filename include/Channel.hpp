/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:21:07 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/13 14:39:55 by cacarval         ###   ########.fr       */
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

typedef std::map<User *, int>::iterator it_ch_users;

class Channel
{
	public:
		Channel();
		~Channel();
		Channel(const std::string &name);

		
		/* Settters */
		void set_name(const std::string &name);
		void set_admin(const std::string &admin);
		void set_user(const std::string &user);
		void set_topic(const std::string &topic);
		void set_user_limit(int limit);
		void set_ch_password(std::string pass);

		/* Getters */
		const std::string &get_topic() const;
		const std::string &get_name() const;
		const std::string &get_admin() const;
		const std::string get_user_size() const;
		const std::map<User *, int> &get_users() const;

		std::string get_ch_password();
		size_t	 get_user_limit();
		User *get_user(const std::string &username);
		User *get_op_user(const std::string &username);
		void add_user(User &user);
		void delete_user(User &del_user);
		void change_user_it(User &user, char sig);
		bool is_user_OP(User &user);
		bool is_user_on_ch(User &user);

private:

		std::string _password;
		int _user_limit;
		std::string _topic;
		std::map<User*, int> _user_map;
		std::string all_users;
		std::string _name;
		std::string _admin;
		std::string _users;

};


#endif