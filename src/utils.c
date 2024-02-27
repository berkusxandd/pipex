/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:47 by bince             #+#    #+#             */
/*   Updated: 2024/02/27 16:16:46 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tabs(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 2 && pipex->cmds[i])
	{
		j = 0;
		while (pipex->cmds[i][j])
		{
			free(pipex->cmds[i][j]);
			j++;
		}
		free(pipex->cmds[i]);
		i++;
	}
	i = 0;
	while (i < 2 && pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex);
}

void	close_fds(t_pipex *pipex)
{
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
	close(pipex->end[0]);
	close(pipex->end[1]);
	dup2(0, 0);
	dup2(1, 1);
}
