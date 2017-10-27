#include "job_control.h"

/* Find the active job with the indicated pgid.  */
t_job	*find_job(t_job_control *jc, pid_t pgid)
{
	t_job *j;

	j = jc->first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return j;
		j = j->next;
	}
	return NULL;
}


/* Return true if all processes in the job have stopped or completed.  */
int	job_is_stopped(t_job *j)
{
	t_process *p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed && !p->stopped)
			return 0;
	return 1;
}


/* Return true if all processes in the job have completed.  */
int	job_is_completed(t_job *j)
{
	t_process *p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed)
			return 0;
	return 1;
}

t_job	*job_new()
{
	t_job	*new;

	new = ft_memalloc(sizeof(t_job));
	return (new);
}

t_process	*process_new(t_ast *command)
{
	t_process	*new;

	new = ft_memalloc(sizeof(t_process));
	new->command = command;
	return (new);
}

void	process_add(t_process *new, t_process **first_process)
{
	new->next = *first_process;
	*first_process = new;
}