/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:16:40 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/09 13:09:23 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Server.hpp"
# include "User.hpp"

class Server;

class ACommand
{
public:

	ACommand(Server &server);
	virtual ~ACommand();

	void set_args(const std::string &args);
	void set_user(User &user);
	virtual void run() = 0;

protected:

	std::vector<std::string> _args;
	User *_user;
	Server &_server;
};

class Join : public ACommand
{
public:

	Join(Server &server);
	~Join();

	void run();
};

#endif