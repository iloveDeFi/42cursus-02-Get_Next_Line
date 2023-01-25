/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:46:31 by bbessard          #+#    #+#             */
/*   Updated: 2023/01/25 10:25:51 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ssize_t read(int fildes, void *buf, size_t nbyte);
// ex : ssize_t read(7, "hello", 5);
// buf = Hello ; nbyte 5

// envoyer le buffer dans une variable de réserve stash
// free ou écraser le buffer
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

/*
La fonction principale get_next_line effectue principalement des vérifications 
sur le descripteur de fichier et sur les différentes allocations de mémoire qui 
pourraient se produire. Une fois toutes les vérifications effectuées, elle 
appelle la fonction _fill_line_buffer pour lire le descripteur de fichier 
jusqu'à ce qu'elle trouve un caractère \n ou \0.
Une fois la variable line remplie, nous libérons le buffer pour éviter toute 
fuite de mémoire, puisqu'il n'est plus utilisé par la suite. Une fois le buffer 
libéré, nous fixons la line avec la fonction _set_line et nous retournons 
la line, en stockant la valeur de retour de _set_line dans une variable statique 
de sorte que la prochaine fois que nous appelons la fonction get_next_line, 
nous ayons accès aux premiers caractères de la line qui ont pu 
être lus auparavant. Par exemple, notre fichier contient 1\n234\0, 
notre BUFFER_SIZE est de 4. La première fois que nous lirons le fichier, 
nous lirons 1\n23, donc ce que nous allons stocker dans notre variable statique 
est 23 parce que la prochaine fois que nous appellerons la fonction sur le même 
descripteur de fichier, elle commencera à lire au 4ème caractère du fichier.
*/

char	*get_next_line(int fd)
{
	static char	*left_c;
	char	*line;
    char	*buffer;
    
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
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

/*
Cette fonction prend le buffer de line comme paramètre, elle le lit 
jusqu'à ce qu'un caractère \n ou \0 soit trouvé, signifiant la fin d'une ligne, 
ou la fin du fichier. Cette fonction met le 
buffer de line à \0 à la fin de la ligne qui s'y trouve et renvoie 
une sous-chaîne du buffer, de la fin de la ligne à la fin du bufer. 
Cette sous-chaîne est retournée en tant que left_c.
*/
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

/*
Cette fonction remplit le Buffer (mémoire tampon).
Elle lira les caractères BUFFER_SIZE à chaque itération jusqu'à ce 
qu'il y ait un caractère \n ou \0 dans le BUFFER. À chaque 
fois que la boucle est parcourue, elle vérifie s'il y a déjà des données 
dans le BUFFER left_c. Si c'est le cas, elle y ajoute les nouveaux 
caractères lus. Sinon, il dupliquera le contenu du BUFFER de lecture 
dans le BUFFER left_c. Si une erreur est trouvée, elle sort de la boucle 
et retourne le BUFFER left_c après y avoir ajouté les caractères lus.
*/
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
// Cette fonction recherche la première occurrence du caractère passé 
// en second paramètre dans la chaîne de caractères spécifiée 
// via le premier paramètre.
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

/*
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
*/
