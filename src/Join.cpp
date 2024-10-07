/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/07 18:34:22 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Join::Join()
{
	std::cout << "Join Constructor" << std::endl;
}

Join::~Join()
{
	std::cout << "Join Destructor" << std::endl;
}

void Join::run()
{
	std::cout << "Running Join function" << std::endl;
}