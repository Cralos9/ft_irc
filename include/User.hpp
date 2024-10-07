/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:30:44 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/07 15:46:14 by cacarval         ###   ########.fr       */
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
		void prepare_buffer(const std::string &command);
		std::string get_name(const std::string &string, int what);
	private:
		std::string _username;
		std::string _nick;
		std::string _hostname;
		std::string _buffer;
};


#endif