/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:45:32 by cacarval          #+#    #+#             */
/*   Updated: 2024/11/07 12:23:51 by rumachad         ###   ########.fr       */
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
#include <cstdarg>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

void print_error(std::string error_msg);


#endif
