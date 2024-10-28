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
# include "RPL.hpp"

class Server;

typedef std::map<int, User>::iterator it_user;

class ACommand
{
public:

	ACommand(Server &server, bool &usable_pre_reg);
	virtual ~ACommand();

	void check();
	void set_args(std::vector<std::string> &args);
	void set_user(User *user);
	virtual int run() = 0;

protected:

	std::vector<std::string> _args;
	User *_user;
	Server &_server;
	bool &_usable_pre_reg;
};

class Join : public ACommand
{
public:

	Join(Server &server, bool usable_pre_reg);
	~Join();

	int run();
};

class Who : public ACommand
{
public:
	
	Who(Server &server, bool usable_pre_reg);
	~Who();

	int run();
};

class Mode : public ACommand
{
public:
	
	Mode(Server &server, bool usable_pre_reg);
	~Mode();

	int run();
};

class Nick : public ACommand
{
public:
	
	Nick(Server &server, bool usable_pre_reg);
	~Nick();

	int run();
};

class Quit : public ACommand
{
public:
	
	Quit(Server &server, bool usable_pre_reg);
	~Quit();

	int run();
};

class PrivMsg : public ACommand
{
public:
	
	PrivMsg(Server &server, bool usable_pre_reg);
	~PrivMsg();

	int run();
};

class Kick : public ACommand
{
public:
	
	Kick(Server &server, bool usable_pre_reg);
	~Kick();

	int run();
};

class Topic : public ACommand
{
public:
	
	Topic(Server &server, bool usable_pre_reg);
	~Topic();

	int run();
};

class List : public ACommand
{
public:
	
	List(Server &server, bool usable_pre_reg);
	~List();

	int run();
};

class Part : public ACommand
{
public:
	
	Part(Server &server, bool usable_pre_reg);
	~Part();

	int run();
};
class Invite : public ACommand
{
public:
	
	Invite(Server &server, bool usable_pre_reg);
	~Invite();

	int run();
};

class WhoIs : public ACommand
{
public:
	
	WhoIs(Server &server, bool usable_pre_reg);
	~WhoIs();

	int run();
};

class Pass : public ACommand
{
public:

	Pass(Server &server, bool usable_pre_reg);
	~Pass();

	int run();
};

class Pong : public ACommand
{
public:

	Pong(Server &server, bool usable_pre_reg);
	~Pong();

	int run();
};

std::vector<std::string> parse_split(const std::string &buffer);
std::vector<std::string> split_lines(const std::string &buffer);

#endif
