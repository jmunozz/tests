#include "thread.h"

static int count_pipes(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == '|')
			i++;
		str++;
	}
	printf("pipes_nb = %d\n", i);
	return (i);
}


static int	**build_pipes(int pipes)
{
	int		**tab;
	int		n;

	n = -1;;
	tab = (int**)malloc(sizeof(int*) * (pipes));
	while (++n < pipes)
		tab[n] = (int*)malloc(sizeof(int) * 2);
	n = -1;
	while (++n < pipes)
	{
		printf("on construit un pipe  = %d\n", n);
		pipe(tab[n]);
	}
	return (tab);
}




int main(int ac , char **av, char **env)
{
	char	**all;
	char	**command;
	int		pipes;
	pid_t	pid;
	int		**tab;
	int 	son_id;
	int		n;
	int		*tab_pid;

	all = ft_strsplit(av[1], '|');
	pid = 1;
	if (ac > 1)
	{
		n = -1;;
		son_id = -1;
		pipes = count_pipes(av[1]);
		tab = build_pipes(pipes);		
		n = 0;
		tab_pid = ft_add_tabi(NULL, 0);
		while (n <= pipes + 1)
		{
			if (n <= pipes && tab_pid[son_id])
			{
				tab_pid = ft_add_tabi(tab_pid, son_id + 2);
				tab_pid[++son_id] = fork();
				command = ft_strsplit(all[son_id], ' ');
			}
			else if (n == pipes + 1 && !tab_pid[son_id])
			{	
				printf("je suis le fils numero %d, mon pid est %d\n", son_id, getpid());
				printf("mon pere est %d\n", getppid());
				printf("___COMMANDE___\n");
				ft_printtab(command);
				if (son_id == 0)
				{
					close(tab[son_id][0]);
					dup2(tab[son_id][1], STDOUT_FILENO);
					close(tab[son_id][1]);
					launch_bin(command, env);
				}
				else
				{
					if (son_id < pipes)
					{
						dup2(tab[son_id][1], STDOUT_FILENO);
						close(tab[son_id][0]);
						close(tab[son_id][1]);
					}
					dup2(tab[son_id - 1][0], STDIN_FILENO);
					close(tab[son_id - 1][0]);
					close(tab[son_id - 1][1]);
					launch_bin(command, env);
					printf("commande effectuee");
				}
			}
			n++;
		}
		n = -1;
		if (pid)
		{
			while (++n <= pipes)
			{
				waitpid(tab_pid[n], NULL, 0);
				printf("Le fils %d s'est termine\n", tab_pid[n]);
				if (n < pipes)
				{
					close(tab[n][1]);
					close(tab[n][0]);
				}
			}
		}
	}
}
