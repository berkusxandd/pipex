#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex_b
{
	char	***commands;
	char	**command_paths;
	char	*path;
	int		outfile_fd;
	int		infile_fd;
}			t_pipex_b;

void		free_tabs(t_pipex_b *pipex);
void		close_fds(t_pipex_b *pipex);

#endif
