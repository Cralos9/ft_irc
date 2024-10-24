/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:21:53 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/24 14:31:54 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser()
{
	std::cout << "Parser Constructor" << std::endl;
}

Parser::~Parser()
{
	std::cout << "Parser Destructor" << std::endl;	
}

/* ----------------------------------------------- */

void Parser::parse_buffer(const std::string &buffer)
{
	std::istringstream iss(buffer);
	std::string token;

	while (std::getline(iss, token, ' '))
	{
		std::cout << token << std::endl;
	}
}