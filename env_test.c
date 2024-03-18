#include <stdio.h>
#include "./Libft/libft.h"

char	**find_cmdpath(char *env[])
{
	int i = 0;
	int j = 0;
	char *paths_raw;
	char **paths;
	while (env[i] != NULL)
	{
		j = 0;
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			while (env[i][j] != ':')
				j++;
			paths_raw= ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			paths = ft_split(paths_raw,':');
			return(paths);
		}
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	int i;
	i = 0;
	char **paths = find_cmdpath(env);
	char *path_cmd;
	while(paths[i])
	{
		paths[i] = ft_strjoin(paths[i],"/");
		path_cmd = ft_strjoin(paths[i],"ls");
		if (access(path_cmd,F_OK))
		{
			printf("%s is working.\n",path_cmd);
		}
		else
		{
			printf("%s is NOT working.\n",path_cmd);

		}
		i++;
	}
}
