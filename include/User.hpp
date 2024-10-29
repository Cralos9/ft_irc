/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:30:44 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/29 14:47:25 by cacarval         ###   ########.fr       */
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
		void set_nick(const std::string &nick);
		void set_username(const std::string &username);
		void set_hostname(const std::string &hostname);
		void set_buffer(const std::string &buffer);
		void set_password(const std::string &password);
		void set_realname(const std::string &realname);

		const int &get_fd() const;
		const std::string &get_nick() const;
		const std::string &get_buffer() const;
		const std::string &get_username() const;
		const std::string &get_hostname() const;
		const std::string &get_password() const;
		const std::string &get_realname() const;

		void erase_buffer();
		void get_Test();
		bool get_info();
		const std::string get_name(const std::string &buffer, const std::string &attribute,
									const char delimiter);
		void prepare_buffer(const std::string &command);
		
		bool		_get_auth() const;
		void 		_set_auth(const bool &status);
		bool		welcome_flag;
		int			error_flag;
	private:
		int _fd;
		std::string _username;
		std::string _realname;
		std::string _nick;
		std::string _hostname;
		std::string _buffer;
		std::string _password;
		bool 		_auth;
};

std::ostream &operator<<(std::ostream &out, const User &user);

#endif