/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:00:14 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/10 12:01:34by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Cap::Cap(Server &server) : ACommand(server)
{
	std::cout << "Cap Server Constructor" << std::endl;
}

Cap::~Cap()
{
	std::cout << "Cap Destructor" << std::endl;
}

int Cap::run()
{
	return (1);
}