#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct process {
    int p_id;      // process id
    int priority;  // priority of process
    double bt;     // burst time
    double at;     // arrival time
    double wt;     // waiting time, initializes to 0 by default
};

void swap_processes(struct process *p1, struct process *p2) {
    struct process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_by_at(struct process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if ((processes + j)->at > (processes + j + 1)->at) {
                swap_processes((processes + j), (processes + j + 1));
            }
        }
    }
}

void increment_wt(double time, struct process *processes, int n) {
    // loop through all the processes
    for (int i = 0; i < n; i++) {
        // increment waiting time IF process has arrived AND its burst time isn't 0 (incomplete)
        if ((processes + i)->at <= time && (processes + i)->bt != 0) {
            (processes + i)->wt++;
        }
    }
}

struct process *next_process(double time, struct process *processes, struct process *curr, int n) {
    // next_process will be returned, initialized to current running process
    struct process *next_process = curr;
    // loop through all processes to check
    for (struct process *iter = processes; iter != processes + n; iter++) {
        if (iter->priority <= next_process->priority && iter->at <= time && iter->bt != 0) {
            if (iter->priority < next_process->priority) {
                next_process = iter;
            } else {
                if (iter->at < next_process->at) {
                    next_process = iter;
                }
            }
        }
    }
    return next_process;
}

void priority(struct process *processes, int n) {
    sort_by_at(processes, n);
    double original_bt[n];
    for (int i = 0; i < n; i++) {
        *(original_bt + i) = (processes + i)->bt;
    }
    double time = 0;
    int completed_processes = 0;

    // find highest priority process from all that have arrived at t=0
    struct process *curr = processes;
    while ((curr + 1)->at == 0) {
        if ((curr + 1)->priority < curr->priority) {
            curr++;
        } else {
            break;
        }
    }

    // execution loop
    while (completed_processes != n) {
        printf(" %d", curr->p_id);
        time++;
        curr->bt--;
        /*printf("\t%f", curr->bt);*/
        if (curr->bt == 0) {
            curr = next_process(time, processes, curr, n);
            completed_processes++;
        }
        increment_wt(time, processes, n);
    }
}

int main() {
    struct process processes[5] = {
        {1, 1, 4, 0}, {2, 2, 3, 0}, {3, 1, 7, 6}, {4, 3, 4, 11}, {5, 2, 2, 12},
    };
    // n is number of processes
    int n = sizeof(processes) / sizeof(processes[0]);
    priority(processes, n);
    return 0;
}
