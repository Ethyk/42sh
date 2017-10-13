#include "job_control.h"

/* Find the active job with the indicated pgid.  */
job	*find_job(pid_t pgid)
{
	job *j;

	j = first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return j;
		j = j->next;
	}
	return NULL;
}


/* Return true if all processes in the job have stopped or completed.  */
int	job_is_stopped(job *j)
{
	process *p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed && !p->stopped)
			return 0;
	return 1;
}


/* Return true if all processes in the job have completed.  */
int	job_is_completed(job *j)
{
	process *p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed)
			return 0;
	return 1;
}
