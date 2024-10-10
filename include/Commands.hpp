/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:16:40 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/10 12:00:48 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "User.hpp"
# include "Channel.hpp"
# include "Server.hpp"

class Server;

typedef std::map<int, User>::iterator it_user;

class ACommand
{
public:

	ACommand(Server &server);
	virtual ~ACommand();

	void set_args(const std::string &args);
	void set_user(it_user &user);
	virtual int run() = 0;

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

	int run();
};

class Who : public ACommand
{
public:
	
	Who(Server &server);
	~Who();

	int run();
};

class Mode : public ACommand
{
public:
	
	Mode(Server &server);
	~Mode();

	int run();
};

class Nick : public ACommand
{
public:
	
	Nick(Server &server);
	~Nick();

	int run();
};

class Quit : public ACommand
{
public:
	
	Quit(Server &server);
	~Quit();

	int run();
};

class PrivMsg : public ACommand
{
public:
	
	PrivMsg(Server &server);
	~PrivMsg();

	int run();
};

class Cap : public ACommand
{
public:
	
	Cap(Server &server);
	~Cap();

	int run();
};

#endif
