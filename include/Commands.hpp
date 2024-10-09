/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:16:40 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/09 13:42:03 by cacarval         ###   ########.fr       */
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
	void set_user(it_user &user);
	virtual void run() = 0;

protected:

	std::vector<std::string> _args;
	it_user _user;
	Server &_server;
};

class Join : public ACommand
{
public:

	Join(Server &server);
	~Join();

	void run();
};

class Who : public ACommand
{
public:
	
	Who(Server &server);
	~Who();

	void run();
};

class Mode : public ACommand
{
public:
	
	Mode(Server &server);
	~Mode();

	void run();
};

class Nick : public ACommand
{
public:
	
	Nick(Server &server);
	~Nick();

	void run();
};

#endif