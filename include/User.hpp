/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:30:44 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/13 18:27:03 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include "ft_irc.hpp"

class User
{
	public:
		User();
		User(const int &fd, const std::string &hostname);

		~User();
		
		/* Setters */
		void set_nick(const std::string &nick);
		void set_username(const std::string &username);
		void set_hostname(const std::string &hostname);
		void set_buffer(const std::string &buffer);
		void set_password(const std::string &password);
		void set_realname(const std::string &realname);
		void set_auth(const bool &status);

		/* Getters */
		const int &get_fd() const;
		const std::string &get_nick() const;
		const std::string &get_buffer() const;
		const std::string &get_username() const;
		const std::string &get_hostname() const;
		const std::string &get_password() const;
		const std::string &get_realname() const;
		bool get_auth() const;

		void erase_buffer();
		void erase_pass();
		void erase_nick();
		bool is_registered();
		void make_msg(const std::string &command, const std::vector<std::string> &params);
		bool welcome_flag;
		int error_flag;

	private:
		int _fd;
		std::string _username;
		std::string _realname;
		std::string _nick;
		std::string _hostname;
		std::string _buffer;
		std::string _password;
		bool _auth;
};

std::ostream &operator<<(std::ostream &out, const User &user);

#endif