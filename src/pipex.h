/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:50 by bince             #+#    #+#             */
/*   Updated: 2024/02/21 18:17:51 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**commands[2];
	char	*command_paths[2];
	char	*path;
	int		outfile_fd;
	int		infile_fd;
	int		end[2];
}			t_pipex;

void		free_tabs(t_pipex *pipex);
void		close_fds(t_pipex *pipex);

#endif
