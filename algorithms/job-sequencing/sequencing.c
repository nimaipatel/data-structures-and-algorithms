#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void
sort_by_profit(int *deadlines, int *profits, int *ids, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n-1; ++j)
        {
            if ( profits[j] < profits[j+1] )
            {
                swap(profits + j, profits + j + 1);
                swap(deadlines + j, deadlines + j + 1);
                swap(ids + j, ids + j + 1);
            }
        }
    }
}

int
find_max_deadline(int *deadlines, int n)
{
    int max_deadline = deadlines[0];
    for (int i = 0; i < n; ++i)
    {
        if (deadlines[i] > max_deadline)
        {
            max_deadline = deadlines[i];
        }
    }
    return max_deadline;
}

int *
job_sequencing(int *profits, int *deadlines, int *ids, int n_jobs, int n_timeslots)
{
    sort_by_profit(deadlines, profits, ids, n_jobs);
    int *timeslots = (int*)malloc(n_timeslots * sizeof(int));
    for (int i = 0; i < n_timeslots; ++i) timeslots[i] = -1;
    for (int i = 0; i < n_jobs; ++i)
    {
        /* finding slot for ith job (after sorting by profit) */
        for (int k = n_timeslots - 1; k >= 0; --k)
        {
            if (k+1 <= deadlines[i] && timeslots[k] == -1)
            {
                timeslots[k] = ids[i];
                break;
            }
        }
    }
    return timeslots;
}

int main() {
    int ids[] = { 1, 2, 3, 4, 5, 6, 7 };
    int deadlines[] = { 1,3,4,3,2,1,2 };
    int profits[] = { 4,5,20,18,2,7,30 };
    int *timeslots = job_sequencing(profits, deadlines, ids, 7, 4);
    for (int i = 0; i < 4; ++i) printf("%d ", timeslots[i]);
    return 0;
}
