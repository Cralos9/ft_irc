/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:14:16 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/24 14:32:02 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "ft_irc.hpp"

class Parser
{
public:

	static void parse_buffer(const std::string &buffer);

	static std::string command_name;
	static std::string params;

private:

	Parser();
	~Parser();
};

#endif
