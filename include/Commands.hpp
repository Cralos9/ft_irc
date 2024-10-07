/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:16:40 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/07 19:10:59 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "ft_irc.hpp"

class ACommand
{
public:

	ACommand();
	virtual ~ACommand();

	void get_args();
	virtual void run() = 0;

protected:

	std::vector<std::string> _args;
};

class Join : public ACommand
{
public:

	Join();
	~Join();

	void run();
};

#endif