/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:45:32 by cacarval          #+#    #+#             */
/*   Updated: 2024/10/03 13:48:10 by rumachad         ###   ########.fr       */
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

void print_error(std::string error_msg);
std::string get_message(char *buffer, int i);

#endif
