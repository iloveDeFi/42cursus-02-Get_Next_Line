/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:46:31 by bbessard          #+#    #+#             */
/*   Updated: 2023/01/21 17:08:17 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ssize_t read(int fildes, void *buf, size_t nbyte);
// ssize_t read(7, void *buf, 5);
// buf = Hello
// nbyte 5
// envoyer le buffer dans une variable de réserve stash
// free ou ecraser le buffer
// boucler
// Si dans la stash \n ou 0 ou $
// extraire cette ligne dans une variable line la réserve mais que avant le $
// enlever de la réserve stash ce qu'on a extrait
// get_next_line return (line)
// problème de tete de lecture. Le curseur reste au meme endroit 
//quand on rappelle GNL mais la stash est écrasée donc rendre la stash static
// La taille du buffer sera définie à la compilation
// ft_strjoin pour join le left_c dans tmp avec le buffer
// strchr pour chercher le \n  dans le buffer

#include "get_next_line.h"
#include "stdio.h"

static char	*_fill_line_buffer(int fd, char *left_c, char *buffer);
static char	*_set_line(char *line);
static char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*left_c;
	char	*line;
    char	*buffer;
    
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
    {
		free(left_c);
		free(buffer);
		left_c = NULL;
		buffer = NULL;
		return (NULL);
    }
    if (!buffer)
		return (NULL);
    line = _fill_line_buffer(fd, left_c, buffer);
    free(buffer);
    buffer = NULL;
    if (!line)
		return (NULL);
	left_c = _set_line(line);
	return (line);
}

static char *_set_line(char *line_buffer)
{
    char    *left_c;
    ssize_t    i;
    
    i = 0;
    while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
        i++;
    if (line_buffer[i] == 0 || line_buffer[1] == 0)
        return (NULL);
    left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
    if (*left_c == 0)
    {
        free(left_c);
        left_c = NULL;
    }
    line_buffer[i + 1] = 0;
    return (left_c);
}

static char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = 0;
		if (!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

int main()
{
	int	fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	return(0);
}

/*
int	main(int ac, char	**av)
{
	(void)ac;
	(void)av;
	int	fd ;
	
	fd = open("text.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
}
*/