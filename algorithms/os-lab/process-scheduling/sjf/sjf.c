#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
    int p_id;    // process id
    double bt;   // burst time
    double at;   // arrival time
    double st;   // start time
    double ct;   // completion time
    double wt;   // waiting time
    double tat;  // turn around time
};

void swap_processes(struct process* p1, struct process* p2) {
    struct process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_by_at(struct process* processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if ((processes + j)->at > (processes + j + 1)->at) {
                swap_processes((processes + j), (processes + j + 1));
            }
        }
    }
}

struct process* find_shortest(double time, struct process* processes, int n) {
    struct process* shortest = processes;
    for (struct process* iter = processes; iter != processes + n; iter++) {
        if (iter->at <= time && iter->bt != 0) {
            shortest = iter;
        }
    }
    return shortest;
}

void sjf(struct process* processes, int n) {
    sort_by_at(processes, n);
    double* original_bt = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        *(original_bt + i) = (processes + i)->bt;
    }
    double time = 0;
    int completed_processes = 0;
    struct process* current = processes;
    current->st = 0;
    while (completed_processes != n) {
        time++;
        current->bt--;
        if (current->bt == 0) {
            current->ct = time;
            current = find_shortest(time, processes, n);
            current->st = time;
            completed_processes++;
        }
    }
    processes->st = 0;
    double avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        (processes + i)->bt = *(original_bt + i);
        (processes + i)->tat = (processes + i)->ct - (processes + i)->at;
        (processes + i)->wt = (processes + i)->st - (processes + i)->at;
        avg_wt += (processes + i)->wt;
        avg_tat += (processes + i)->tat;
    }
    free(original_bt);
    avg_wt /= n;
    avg_tat /= n;
    printf("\nAverage Waiting Time: %f\nAverage Turn Around Time: %f", avg_wt, avg_tat);
}

int main() {
    // processes array containing p_id, wt, at
    struct process processes[5] = {{1, 6, 2}, {2, 2, 5}, {3, 8, 1}, {4, 3, 0}, {5, 4, 4}};
    // n is number of processes
    int n = sizeof(processes) / sizeof(processes[0]);
    sjf(processes, n);
}
