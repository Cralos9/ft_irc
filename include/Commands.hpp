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

/**
* @brief Constructor for the ACommand class.
* 
* @param _server Reference to the Server instance associated with this command.
* @param _usable_pre_reg A boolean flag indicating if the command can be used
*        before the user has completed registration.
* @param _min_params The minimum number of parameters required for the command
*        to execute.
*/
class ACommand
{
public:

	ACommand(Server &server, bool usable_pre_reg, const size_t min_params);
	virtual ~ACommand();

	void set_args(std::deque<std::string> args);
	void set_user(User *user);
	virtual int run() = 0;

	bool _usable_pre_reg;
	const size_t _min_params;

protected:

	std::deque<std::string> _args;
	User *_user;
	Server &_server;
};

class Join : public ACommand
{
public:

	Join(Server &server);
	~Join();

	void join_channel(Channel *ch, std::deque<std::string> &params);
	int can_join(Channel *ch, const std::string &password);
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

	void use_modes(char signal, char mode, std::string param, Channel *ch);
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

class Pong : public ACommand
{
public:

	Pong(Server &server);
	~Pong();

	int run();
};

class UserCMD : public ACommand
{
public:

	UserCMD(Server &server);
	~UserCMD();

	int run();
};

class Motd : public ACommand
{
public:

	Motd(Server &server);
	~Motd();

	int run();
};

#endif
