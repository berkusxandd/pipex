#include "pipex.h"
#include <stdio.h> ///////////////////UNUTMAAAAAAAAAAA

// char *find_cmdpath(char *env[])
// {
// 	int i;
// 	int j;
// 	char *path;

// 	i = 0;
// 	j = 0;
// 	while (env[i] != NULL)
// 	{
// 		j = 0;
// 		if (ft_strncmp(env[i],"PATH=",5) == 0)
// 		{
// 			while(env[i][j] != ':')
// 				j++;
// 			path = ft_substr(env[i],5,j - 5);
// 			path[ft_strlen(path)] = '/';
// 			return (path);
// 		}
// 		i++;
// 	}
// }


void free_tabs(t_pipex* pipex)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 2 && pipex->commands[i])
	{
		j = 0;
		while(pipex->commands[i][j])
		{
			free(pipex->commands[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 2 && pipex->command_paths[i])
	{
		free(pipex->command_paths[i]);
		i++;
	}
}

void error_handling(char *err_msg, t_pipex* pipex)
{
	ft_putstr_fd(err_msg, 2);
	free_tabs(pipex);
	exit(-1);
}

int child_process(int end[2], char* cmd[], char *command_path, char* infile) //AKA FIRST COMMAND
{
	int infile_fd;

	infile_fd = open(infile, O_RDONLY,0666);
	if (infile_fd == -1)
	{
		perror("input file error: ");
		return (-1);
	}
	dup2(end[1],1);
	close(end[0]);
	dup2(infile_fd,0);
	if (execve(command_path,cmd,NULL) == -1)
	{
		perror("command error: ");
		return (-1);
	}
}

int parent_process(t_pipex* pipex, char* outfile)
{
	int outfile_fd;
	int exec_value;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT,0777);
	if (outfile_fd == -1)
	{
		perror("output file error:");
		return -1;
	}
	dup2(end[0],0);
	close(end[1]);
	dup2(outfile_fd,1);
	if(execve(command_path, cmd, NULL) == -1)
		error_handling("command not executed",pipex);
}

char **cmd_parser(char *cmd_arg)
{
	char **cmd_parsed;
	cmd_parsed = ft_split(cmd_arg, ' ');
	return (cmd_parsed);
}

int main(int ac, char *av[], char **env)
{
	t_pipex* pipex;
	pid_t proc;
	int outfile;

	pipex = malloc(sizeof(t_pipex));
	pipex->path = "/usr/bin/";
	pipe(pipex->end);	
	proc = fork();
	//path = find_cmdpath(env);
	pipex->commands[0] = cmd_parser(av[2]);
	pipex->commands[1] = cmd_parser(av[3]);
	pipex->command_paths[0] = ft_strjoin(pipex->path,pipex->commands[0][0]);
	pipex->command_paths[1] = ft_strjoin(pipex->path,pipex->commands[1][0]);
	if (!pipex->commands[0] ||!pipex->commands[1] || !pipex->command_paths[0] || !pipex->command_paths[1])
		error_handling("malloc error". pipex);
	error_handling(pipex);
	if (proc == 0)
		child_process(pipex->end,pipex->commands[0],pipex->command_paths[0],av[1]);
	else if (proc != 0)
	{
		wait(&proc);
		parent_process(pipex->end,pipex->commands[1],pipex->command_paths[1],av[ac-1]);
	}
}