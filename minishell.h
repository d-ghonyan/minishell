#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "/goinfre/dghonyan/include/readline/history.h"
# include "/goinfre/dghonyan/include/readline/readline.h"

# include "colors.h"
# include "libft/libft.h"

typedef struct s_exec {
	char	*exec;
	char	**argv;
}	t_exec;

typedef struct s_cmd {
	int		len;
	char	*command;
	char	*infile;
	char	*outfile;
	char	*heredoc;
	int		append;
	char	*here_str;
	char	**envp;
	t_exec	exec;
}	t_cmd;

int		redirection_index(char *cmd, int i, char red);
int		count_pipes(char *s);
int 	final_len(char *s);
int		expanded_len(char *s, int i, int quote);
int		var_len(char *s, int i, int quote);
int		check_quotes(char *s);
int		is_a_builtin(char *s);
void	exec_argv(t_cmd *cmd);
void	init_signals_parent(void);
void	init_signals_child(void);
void	free_cmd(t_cmd *cmd);
char	*get_path(char *command);
char	*alloc_command(char *line, int i, int size, int j);
char	*expand_line(char *cmd);
t_cmd	*parse_line(char *line, char **envp);

#endif