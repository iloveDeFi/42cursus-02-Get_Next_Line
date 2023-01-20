/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:11:08 by bbessard          #+#    #+#             */
/*   Updated: 2023/01/17 15:15:15 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

//get_next_line_utils.c
int	ft_strlen(char *str);
char	*ft_strdup(char *str);

//get_next_line.c
char *get_next_line(int fd);

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 5

# endif

