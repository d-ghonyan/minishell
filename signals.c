#include "minishell.h"

void	sigint_p(int signum);

//ignore ctrl+\ and set ctrl+c
void	init_signals_parent(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	sigemptyset(&(action.sa_mask));
	action.sa_handler = SIG_IGN;
	signal(SIGINT, &sigint_p);
	sigaction(SIGQUIT, &action, NULL);
}

//default signal handlers for the child
void	init_signals_child(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	sigemptyset(&(action.sa_mask));
	action.sa_handler = SIG_DFL;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	sigint_p(int signum)
{
	// rl_done = 1;
}
