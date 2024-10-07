/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:45:32 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/07 11:59:26 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

#include <cstring>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>

void print_error(std::string error_msg);
std::string get_message(char *buffer, int i);

template <typename Container>
typename Container::iterator advance_map(Container &map, int index)
{
	typename Container::iterator it;

	for (it = map.begin(); it->first != index; it++)
		;
	return (it);
}

#endif
