#ifndef HASH_TABLE_H
# define HASH_TABLE_H
# include "t_env.h"

# define HASH_TABLE_SIZE 998

void	free_hash_table(t_list ***has_table);
char	*hash_get(t_list **hash_table, char *value);
int		create_hash_table(t_list ***hash_table, char **environ);

void	env_reload_tree_hash(t_env *env);
#endif
