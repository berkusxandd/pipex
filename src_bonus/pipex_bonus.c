#include "pipex_bonus.h"
#include <stdio.h>
char	**cmd_parser(char *cmd_arg)
{
	char	**cmd_parsed;
	cmd_parsed = ft_split(cmd_arg, ' ');

	return (cmd_parsed);
}
void child_proc(char *cmd_raw,t_pipex_b* pipex)
{
	char **cmd;
	char *cmd_path;
	pid_t proc;

	cmd = cmd_parser(cmd_raw);
	cmd_path = ft_strjoin(pipex->path,cmd[0]);
	dup2(pipex->infile_fd,0);
	close(pipex->infile_fd);
	execve(cmd_path,cmd,NULL);
	dup2(pipex->outfile_fd,1);
	close(pipex->outfile_fd);
}

int	main(int ac, char *av[])
{
	t_pipex_b	*pipex;

	pipex = malloc(sizeof(t_pipex_b));
	pipex->path = "/usr/bin/";
	int i;
	i = 2;
	pipex->infile_fd = open(av[1], O_RDONLY, 0666);
	pipex->outfile_fd = open(av[ac-1], O_WRONLY | O_CREAT, 0777);

	while (i < ac-2)
	{
		child_proc(av[i],pipex);
		i++;
	}
}
