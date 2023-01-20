/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:11:08 by bbessard          #+#    #+#             */
/*   Updated: 2023/01/20 10:51:15 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

int			ft_strlen(const char *str);
char		*ft_strchr(char *str, int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*get_next_line(int fd);
char		*ft_fill_stash(int fd, char *stash);
char		*ft_extract_line(char *stash);
char		*ft_new_stash(char *stash);

#endif