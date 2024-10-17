/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:19:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/17 11:40:28 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Who::Who(Server &server) : ACommand(server)
{
/* 	std::cout << "Who constructor" << std::endl; */
}

Who::~Who()
{
/* 	std::cout << "Who destructor" << std::endl; */
}

int Who::run()
{
	/* std::cout << "Mode Command" << std::endl; */
	return (0);
}