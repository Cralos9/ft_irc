/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:45:32 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/23 10:27:20 by rumachad         ###   ########.fr       */
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
#include <algorithm>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

void print_error(std::string error_msg);

template <typename Container>
typename Container::iterator advance_map(Container &map, int index)
{
	typename Container::iterator it;

	for (it = map.begin(); it->first != index; it++)
		;
	return (it);
}



#endif
