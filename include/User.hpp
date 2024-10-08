/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:30:44 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/08 12:01:24 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include "ft_irc.hpp"


class User
{
	public:
		User();
		User(std::string nick, const std::string &hostname);
		~User();
		void set_nick(const std::string &nick);
		void set_username(const std::string &username);
		void set_hostname(const std::string &hostname);
		void set_buffer(const std::string &buffer);
		const std::string &get_buffer() const;
		bool get_info();
		std::string get_nick() const;
		std::string get_username() const;
		std::string get_hostname();
		std::string get_name(const std::string &string, int what);
		void prepare_buffer(const std::string &command);
	private:
		std::string _username;
		std::string _nick;
		std::string _hostname;
		std::string _buffer;
};


#endif