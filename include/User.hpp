/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:30:44 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/04 17:08:40 by rumachad         ###   ########.fr       */
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
		bool operator<(User& other) const
		{
        	return _nick < other._nick;
    	}
		void set_nick(const std::string &nick);
		void set_hostname(const std::string &hostname);
		void set_buffer(const std::string &buffer);
		const std::string &get_buffer() const;
		std::string get_nick() const;
		void prepare_buffer(const std::string &command);
	private:
		std::string _nick;
		std::string _hostname;
		std::string _buffer;
};


#endif