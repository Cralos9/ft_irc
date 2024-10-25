/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:16:40 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/14 16:20:21by rumachad         ###   ########.fr       */
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

	void set_args(std::vector<std::string> &args);
	void set_user(User *user);
	virtual int run() = 0;

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

class Kick : public ACommand
{
public:
	
	Kick(Server &server);
	~Kick();

	int run();
};

class Topic : public ACommand
{
public:
	
	Topic(Server &server);
	~Topic();

	int run();
};

class List : public ACommand
{
public:
	
	List(Server &server);
	~List();

	int run();
};

class Part : public ACommand
{
public:
	
	Part(Server &server);
	~Part();

	int run();
};
class Invite : public ACommand
{
public:
	
	Invite(Server &server);
	~Invite();

	int run();
};

class WhoIs : public ACommand
{
public:
	
	WhoIs(Server &server);
	~WhoIs();

	int run();
};

class Pass : public ACommand
{
public:

	Pass(Server &server);
	~Pass();

	int run();
};

std::vector<std::string> parse_split(const std::string &buffer);

#endif
