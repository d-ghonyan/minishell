#include "header.h"

int pipe_count(char **argv)
{
	int i = 0;
	int count = 0;

	while (argv[i])
	{
		if (!strcmp(argv[i], "|"))
			count++;
		i++;
	}
	return (count);
}

void	single(char **cmd, char **env)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(cmd[0], cmd, env);
		printf("NOPE");
	}
	wait(NULL);
}

void	dup_pipes(int (*pipes)[2], int i, int count)
{
	if (i == 0)
	{
		if (dup2(pipes[0][1], STDOUT_FILENO) < 0)
			perror("");
	}
	else if (i == count)
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
			perror("DP");
	}
	else
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
			perror("asd");
		if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
			perror("asd");
	}
	int j = 0;
	while (j < count)
	{
		if (close(pipes[j][0]))
			perror("cl");
		if (close(pipes[j][1]))
			perror("cl");
		j++;
	}
}

int ptr_arr_len(char **arr)
{
	int i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	a(void)
{
	write(1, "ASd\n", 4);
}

void	execute(char **cmd, char **envp)
{
	int i = 0, j = 0, n = 0, len = ptr_arr_len(cmd), dzu = pipe_count(cmd);

	if (pipe_count(cmd) == 0)
		single(cmd, envp);
	else
	{
		int		(*pipes)[2];
		pid_t	*pids;

		pipes = malloc(sizeof (*pipes) * dzu);
		pids = malloc(sizeof (*pids) * (dzu + 1));

		for (int k = 0; k < dzu; k++)
			pipe(pipes[k]);

		while (i < len)
		{
			while (cmd[j] && strcmp(cmd[j], "|"))
				j++;
			cmd[j] = NULL;
			if (!strcmp("cd", (cmd + i)[0]))
			{
				a();
			}
			else
			{
				pid_t pid = fork();
				if (pid == 0)
				{
					dup_pipes(pipes, n, dzu);
					execve((cmd + i)[0], cmd + i, envp);
				}
			}
			i = ++j;
			n++;
		}
		for (int k = 0; k < dzu; k++)
		{
			close(pipes[k][0]);
			close(pipes[k][1]);
		}
		for (int k = 0; k < dzu + 1; k++)
		{
			wait(NULL);
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	int i = 1, j = 1;
	if (argc == 1)
		return (0);
	while (i < argc)
	{
		while (argv[j] && strcmp(argv[j], ";"))
			j++;
		argv[j] = NULL;
		execute(argv + i, envp);
		j++;
		i = j;
	}
}