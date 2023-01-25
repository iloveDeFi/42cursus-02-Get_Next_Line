/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:45:20 by bbessard          #+#    #+#             */
/*   Updated: 2023/01/25 10:27:07 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

static char		*_fill_line_buffer(int fd, char *left_c, char *buffer);
static char		*_set_line(char *line);
static char		*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	/* There's only a minimal difference to make the bonus
	 * work
	 * It's basically transforming our static char * variable
	 * to an array of char *
	 * as you can see I set the number of elements of the array to 
	 * the constant MAX_FD (see get_next_line.h to see what it is)
	 */
	static char	*left_c[MAX_FD];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		/* as we changed our static char * to an array
		 * we have to specify wich index we wanna work on
		 * the easier thing to do is to set it to fd
		 */
		free(left_c[fd]);
		free(buffer);
		left_c[fd] = NULL;
		buffer = NULL;
		return (0);
	}
	if (!buffer)
		return (NULL);
	/* again here, we want to store the left characters in 
	 * the array at the index of the fd, so if we have another fd
	 * we won't be overwriting what was left from the other fd
	 */
	line = _fill_line_buffer(fd, left_c[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	/* and here again, we have to switch from left_c to left_c[fd]
	 * that's the last thing we have to change, all the other place
	 * we use left_c (in all other functions), we use it as a string
	 * therefore, because we are passing left_c[fd] as parameter
	 * we basically are passing strings as parameter
	 * so no problem there, and nothing to change.
	 */
	left_c[fd] = _set_line(line);
	return (line);
}

static char	*_set_line(char *line_buffer)
{
	char	*left_c;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (0);
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
			return (0);
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

	fd = open("test.fd", O_RDONLY);
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

