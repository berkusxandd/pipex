/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:53 by bince             #+#    #+#             */
/*   Updated: 2024/02/27 18:48:11 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> ///////////////////UNUTMAAAAAAAAAAA

char	*find_cmdpath(char *env[])
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		j = 0;
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			while (env[i][j] != ':')
				j++;
			path = ft_substr(env[i], 5, j - 5);
			path[ft_strlen(path)] = '/';
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	error_handling(char *err_msg, t_pipex *pipex)
{
	perror(err_msg);
	free_tabs(pipex);
	close_fds(pipex);
	exit(-1);
}

void	child_process(t_pipex *pipex, char *cmd[], char *cmd_path, char *infile)
{
	pipex->infile_fd = open(infile, O_RDONLY, 0666);
	if (pipex->infile_fd == -1)
		error_handling("input file error: ", pipex);
	dup2(pipex->infile_fd, 0);
	dup2(pipex->end[1], 1);
	close(pipex->end[0]);
	if (execve(cmd_path, cmd, NULL) == -1)
		error_handling("command not executed: ", pipex);
}

void	parent_process(t_pipex *pipex, char *cmd[], char *command_path,
		char *outfile)
{
	pipex->outfile_fd = open(outfile, O_WRONLY | O_CREAT, 0777);
	if (pipex->outfile_fd == -1)
		error_handling("outfile error: ", pipex);
	dup2(pipex->end[0], 0);
	close(pipex->end[1]);
	dup2(pipex->outfile_fd, 1);
	if (execve(command_path, cmd, NULL) == -1)
		error_handling("command not executed", pipex);
}

char	**cmd_parser(char *cmd_arg)
{
	char	**cmd_parsed;

	cmd_parsed = ft_split(cmd_arg, ' ');
	return (cmd_parsed);
}

int	main(int ac, char *av[])
{
	t_pipex	*pipex;
	pid_t	proc;

	pipex = malloc(sizeof(t_pipex));
	pipex->path = "/usr/bin/";
	pipe(pipex->end);
	proc = fork();
	// path = find_cmdpath(env);
	pipex->cmds[0] = cmd_parser(av[2]);
	pipex->cmds[1] = cmd_parser(av[3]);
	pipex->cmd_paths[0] = ft_strjoin(pipex->path, pipex->cmds[0][0]);
	pipex->cmd_paths[1] = ft_strjoin(pipex->path, pipex->cmds[1][0]);
	if (!pipex->cmds[0] || !pipex->cmds[1] || !pipex->cmd_paths[0]
		|| !pipex->cmd_paths[1])
		error_handling("malloc error", pipex);
	if (proc == 0)
		child_process(pipex, pipex->cmds[0], pipex->cmd_paths[0], av[1]);
	else if (proc != 0)
	{
		wait(&proc);
		parent_process(pipex, pipex->cmds[1], pipex->cmd_paths[1], av[ac - 1]);
	}
	close_fds(pipex);
	free_tabs(pipex);
	return (0);
}
