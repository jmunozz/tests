/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 14:55:29 by jmunoz            #+#    #+#             */
/*   Updated: 2016/09/08 15:50:18 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

int			ft_getenvline(char *str, char **e)
{
	int		i;

	i = 0;
	if (!e)
		return (-1);
	while (e[i])
	{
		if (!ft_strncmp(e[i], str, ft_strlenc(e[i], '=')) &&
				ft_strlenc(e[i], '=') == (int)ft_strlen(str))
			return (i);
		i++;
	}
	return (i);
}

static char		**ft_getenvtab(char *str, char **e)
{
	int		i;
	char	*ret;

	if (!e)
		return (NULL);
	i = ft_getenvline(str, e);
	if (e[i] == NULL)
		return (NULL);
	ret = ft_strrchr(e[i], '=');
	return ((ret) ? ft_strsplit(ret + 1, ':') : ft_strsplit(e[i], ':'));
}

static void		freetab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	tab = NULL;
}

static char			*find_bin(char *str, char **e)
{
	char			**path;
	DIR				*stream;
	struct dirent	*file;
	char			*tmp;
	char			*ret;

	ret = NULL;
	path = ft_getenvtab("PATH", e);
	while (path && *path != NULL && !ret)
	{
		if ((stream = opendir(*path)))
			while ((file = readdir(stream)) != NULL && !ret)
				if (!ft_strcmp(str, file->d_name))
				{
					tmp = ft_strjoin(*path, "/");
					ret = ft_strjoin(tmp, file->d_name);
					free(tmp);
				}
		path++;
	}
	if (path)
		freetab(path);
	return (ret);
}

int					launch_bin(char **tab, char **e)
{
	char	*path;
	pid_t	pid;

	if (tab[0][0] == '.' || tab[0][0] == '/')
		path = ft_strdup(tab[0]);
	else if (!(path = find_bin(tab[0], e)))
	{
		free(path);
		return (-1);
	}
	if (execve(path, tab, e) == -1)
		exit(-1);
	free(path);
	return (0);
}
