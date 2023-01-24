/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:11:08 by bbessard          #+#    #+#             */
/*   Updated: 2023/01/24 15:09:45 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
MAX_FD 10240 est une constante qui définit le nombre maximal de descripteurs 
de fichiers qu'un processus est autorisé à avoir ouvert à un moment donné. 
Les descripteurs de fichiers sont utilisés par le système d'exploitation pour 
garder la trace des fichiers ouverts et d'autres ressources, et la valeur 
maximale de 10240 signifie qu'un processus peut avoir jusqu'à 10240 fichiers et 
ressources ouvertes en même temps. Cette valeur peut être définie dans un 
fichier de configuration ou dans le code source d'un programme et peut être 
ajustée selon les besoins.
*/

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 15
# endif
# define MAX_FD 10240
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> 


char    *get_next_line(int fd);
char    *ft_strdup(char *s);
size_t    ft_strlen(char *s);
char    *ft_substr(char *s, unsigned int start, size_t len);
char    *ft_strjoin(char *s1, char *s2);
void    fill_str(char *res, char *s1, char *s2);

#endif