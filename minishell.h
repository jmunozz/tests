/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 14:56:30 by jmunoz            #+#    #+#             */
/*   Updated: 2016/09/08 15:49:27 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>

# define ERCDNOTFOUND 1
# define ERPATH 2
# define ERCDMULT 3
# define ERUNSETARG 4
# define ERUNSETOPT 5
# define ERENVDIR 6
# define ERCDACCESS 7
# define ERCDNOTDIR 8
# define ABSOLUTE 0
# define RELATIVE 1
# define ENV_TMP 0
# define ENV 1

#endif
