/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:10:39 by bbessard          #+#    #+#             */
/*   Updated: 2023/01/19 13:55:26 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	return(i);
}

/*
The SUBSTR( ) function returns characters from the string value starting at the 
character position specified by start. The number of characters returned 
is specified by length.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{

}

/*
Searches for the first occurrence of the character c 
(an unsigned char)in the string pointed to by the argument str.
*/
char	*ft_strchr(const char *s, int i)
{

}

/*
The function strdup() is used to duplicate a string. It returns a pointer 
to null-terminated byte string.
*/
char	*ft_strdup(const char *s)
{

}

/*
str = strjoin( C ) constructs str by linking the elements of C with a space 
between consecutive elements. C can be a cell array of character vectors or a 
string array. str = strjoin( C , delimiter ) constructs str by linking each element 
of C with the elements in delimiter .
*/
char	*strjoin(char const *s1, char const *s2)
{

}
