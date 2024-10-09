/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:28 by rumachad          #+#    #+#             */
/*   Updated: 2024/10/09 11:05:19 by rumachad         ###   ########.fr       */
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
	const std::string channel = this->_args.front();
	std::cout << "Joining " << channel << " ..." << std::endl;
	std::ostringstream oss; 
	oss << "JOIN" << channel << "\r\n";
	this->_user->prepare_buffer(oss.str());
	std::cout << this->_user->get_buffer() << std::endl;
}