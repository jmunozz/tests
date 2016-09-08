#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

typedef int	t_pipe[2];

int count_pipes(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == '|')
			i++;
		str++;
	}
	return (i);
}

int main(int ac , char **av)
{
	int		pipes;
	int 	p;
	pid_t	pid;
	int		**tab;
	int 	son_id;
	char 	c;
	int		n;


	pid = 1;
	if (ac > 1)
	{
		n = -1;;
		son_id = -1;
		pipes = count_pipes(av[1]);
		printf("pipes_nb = %d\n", pipes);
		tab = (int**)malloc(sizeof(int*) * (pipes));
		while (++n < pipes)
			tab[n] = (int*)malloc(sizeof(int) * 2);
		n = -1;
		while (++n < pipes)
		{
			printf("on construit un pipe  = %d\n", n);
			pipe(tab[n]);
		}
	
		p = pipes;
		n = 0;
		while (n <= pipes + 1)
		{
			if (n <= pipes && pid)
			{
				pid = fork();
				son_id++;
			}
			else if (n == pipes + 1 && !pid)
			{	
				printf("je suis le fils numero %d, mon pid est %d\n", son_id, getpid());
				printf("mon pere est %d\n", getppid());
				if (son_id == 0)
				{
					c = 'a';
					close(tab[son_id][0]);
					write(tab[son_id][1], &c, 1);
				}
				else
				{
					if (read(tab[son_id - 1][0], &c, 1) == -1)
						exit(-1);
					else
					{
						printf("le caractere : %c a ete lu par le fils numero %d\n", c, son_id);
						if (son_id < pipes)
							write(tab[son_id][1], &c, 1);
					}
				}
			}
			n++;
		}
		if (pid)
		{
			while (p-- >= 0)
			{
				wait(NULL);
				printf("Un fils s'est termine\n");
			}
		}
	}
}
