#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include "libft/Includes/libft.h"
#include "minishell.h"

#define SIZE_MESS 256
#define PATH1 "/bin/"
#define PATH2 "/usr/bin"

int		launch_bin(char **tab, char **e);
