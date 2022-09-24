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
		execve(cmd[0], cmd, env);
	wait(NULL);
}

int ptr_arr_len(char **arr)
{
	int i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	execute(char **cmd, char **envp)
{
	int last = 0, i = 0, j = 0, len = ptr_arr_len(cmd), dzu = pipe_count(cmd);

	int	dup_out, dup_in, writeTo, readFrom, fds[2];

	dup_out = dup(STDOUT_FILENO);
	dup_in = dup(STDIN_FILENO);
	readFrom = dup(STDIN_FILENO);

	if (pipe_count(cmd) == 0)
		single(cmd, envp);
	else
	{
		while (!last)
		{
			while (cmd[j] && strcmp(cmd[j], "|")) j++;
			if (!cmd[j])
				last = 1;
			cmd[j] = NULL;
			
			pipe(fds);

			if (last) writeTo = dup_out;
			else writeTo = fds[1];

			dup2(readFrom, STDIN_FILENO);
			close(readFrom);
			dup2(writeTo, STDOUT_FILENO);
			close(writeTo);
			pid_t pid = fork();
			if (pid == 0)
			{
				execve((cmd + i)[0], cmd + i, envp);
				exit(1);
			}
			else
				readFrom = fds[0];
			i = ++j;
		}
		for (int k = 0; k < dzu + 1; k++)
			wait(NULL);
		dup2(dup_in, STDIN_FILENO);
		close(dup_in);
		close(fds[0]);
		close(fds[1]);
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

// #include <unistd.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/wait.h>

// size_t ft_strlen(const char *str)
// {
// 	size_t i = 0;
// 	while (str[i]) { ++i; }
// 	return (i);
// }

// int fatal_error(void)
// {
// 	write(STDERR_FILENO, "error: fatal\n", 13);
// 	return (1);
// }

// int cd(char **cmd)
// {
// 	int i = 0;
// 	while (cmd[i]) { i++; }

// 	if (i != 2)
// 		write(STDERR_FILENO, "error: cd: bad arguments\n", 25);
// 	else if (chdir(cmd[1]) == -1)
// 	{
// 		write(STDERR_FILENO, "error: cd: cannot change directory to ", 38);
// 		write(STDERR_FILENO, cmd[1], ft_strlen(cmd[1]));
// 		write(STDERR_FILENO, "\n", 1);
// 	}
// 	else
// 		return (0);
// 	return (1);
// }

// void child_execute_command(char **cmd, char **env)
// {
// 	if (!strcmp(cmd[0], "cd")) { exit(cd(cmd)); }

// 	execve(cmd[0], cmd, env);
// 	write(STDERR_FILENO, "error: cannot execute ", 22);
// 	write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
// 	write(STDERR_FILENO, "\n", 1);
// 	exit(1);
// }

// void execute_command(char **cmd, char **env)
// {
// 	int i, j, last, readFrom, writeTo;
// 	int dup_in, dup_out, pid;
// 	int fd[2];

// 	j = 0;
// 	while (cmd[j] && strcmp(cmd[j], "|")) { ++j; }
// 	if (!cmd[j] && !strcmp(cmd[0], "cd")) { cd(cmd); return ; }

// 	if ((readFrom = dup(STDIN_FILENO)) == -1) { fatal_error(); }
// 	if ((dup_in = dup(STDIN_FILENO)) == -1) { fatal_error(); }
// 	if ((dup_out = dup(STDOUT_FILENO)) == -1) { fatal_error(); }

// 	last = i = j = 0;
// 	while (!last)
// 	{
// 		while (cmd[j] && strcmp(cmd[j], "|")) { ++j; }
// 		if (!cmd[j]) { last = 1; }
// 		cmd[j] = NULL;

// 		if (pipe(fd) == -1) { fatal_error(); }

// 		if (last) { writeTo = dup_out; }
// 		else { writeTo = fd[1]; }

// 		if (dup2(readFrom, STDIN_FILENO) == -1) { fatal_error(); }
// 		close(readFrom);
// 		if (dup2(writeTo, STDOUT_FILENO) == -1) { fatal_error(); }
// 		close(writeTo);

// 		if ((pid = fork()) == -1) { fatal_error(); }

// 		if (pid == 0)
// 			child_execute_command(cmd + i, env);
// 		else
// 			readFrom = fd[0];
// 		i = ++j;
// 	}

// 	while (wait(NULL) != -1);

// 	if (dup2(dup_in, STDIN_FILENO) == -1) { fatal_error(); }
// 	close(dup_in); close(fd[1]); close(readFrom);
// }

// int main(int argc, char **argv, char **env)
// {
// 	int i = 1;
// 	int j = 1;

// 	while (i < argc)
// 	{
// 		while (argv[j] && strcmp(argv[j], ";")) { j++; }
// 		argv[j] = NULL;
// 		if (argv[i]) { execute_command(argv + i, env); }
// 		i = ++j;
// 	}

// 	return (0);
// }