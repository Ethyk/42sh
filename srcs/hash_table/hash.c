#include <stdio.h>
# include <dirent.h>
# include "libft.h"
# include "env.h"

size_t	hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % 997;
}


char	*hash_get(t_list **hash_table, char *value)
{
	return (hash_table[hash((unsigned char *)value)]->data);
}

void	hash_add(t_list **hash_table, char *value)
{
	ft_simple_lst_add(hash_table + hash((unsigned char *)value), ft_simple_lst_create(value));
	//printf("\nname: %s \n",hash_table[hash((unsigned char *)value)]);
}

void	hash_add_dir(t_list **hash_table, char *dir_path)
{
	struct dirent	*dirent;
	DIR		*dir;
	int		i;

	i = 0;
	dir = NULL;
	if (!(dir = opendir(dir_path)))
		return ;
	while ((dirent = readdir(dir)) != NULL)
	{
	//	printf("\nd_name: %s \n", dirent->d_name);
		if (dirent->d_name[0] != '.')
			hash_add(hash_table, ft_strjoin3_free(dir_path, "/" ,dirent->d_name, 0));
		//printf("\nd_name: %s\n", bins[i]);
		i++;
	}
	closedir(dir);
}

int	create_hash_table(t_env *env)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (!(path = env_getenv((const char**)env->environ, "PATH", NULL)))
		return (0);
	env->hash_table = ft_memalloc(sizeof(t_list *) * 997);
	paths = ft_strsplit(path, ":");
	while (paths[i])
	{
		hash_add_dir(env->hash_table, paths[i]);
		i++;
	}
	return (1);
}
