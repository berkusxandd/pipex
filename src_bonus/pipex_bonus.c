#include "pipex_bonus.h"
#include <stdio.h>
char	**cmd_parser(char *cmd_arg)
{
	char	**cmd_parsed;
	cmd_parsed = ft_split(cmd_arg, ' ');

	return (cmd_parsed);
}

int execute_command(char *cmd_raw, t_pipex_b* pipex)
{
	char **cmd;
	char *cmd_path;
	cmd = cmd_parser(cmd_raw);
	cmd_path = ft_strjoin(pipex->path,cmd[0]);
	execve(cmd_path,cmd,NULL);
	perror("command error: ");
}
void child_proc_begin(char* cmd_raw, t_pipex_b* pipex)
{
	pid_t proc;
	int end[2];

	pipe(end);
	proc = fork();
	if (proc == -1)
		exit(-1);
	else if(proc == 0)
	{
		close(end[0]);
		dup2(end[1],1);
		execute_command(cmd_raw,pipex);
	}
	else
	{
		close(end[1]);
		close(pipex->fds[0]);
		dup2(end[0],0);
	}
}

void child_proc_middle(char *cmd_raw,t_pipex_b* pipex)
{
	char **cmd;
	char *cmd_path;
	pid_t proc;
	int end[2];

	cmd = cmd_parser(cmd_raw);
	cmd_path = ft_strjoin(pipex->path,cmd[0]);
	pipe(end);
	proc = fork();
	if (proc == -1)
		exit(-1);
	else if(proc == 0)
	{
		close(end[0]);
		dup2(end[1],1);
		execve(cmd_path,cmd,NULL);
	}
	else
	{
		close(end[1]);
		dup2(end[0],0);
	}
}

int	main(int ac, char *av[])
{
	t_pipex_b	*pipex;

	pipex = malloc(sizeof(t_pipex_b));
	pipex->path = "/usr/bin/";
	int i;
	i = 2;
	pipex->fds[0] = open(av[1], O_RDONLY, 0666);
	pipex->fds[1] = open(av[ac-1], O_WRONLY | O_CREAT, 0777);

	dup2(pipex->fds[0],0);
	while (i < ac - 2)
		child_proc_begin(av[i++], pipex);
	dup2(pipex->fds[1],1);
	execute_command(av[ac-2],pipex);
}
