#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct process {
    int p_id;    // process id
    double bt;   // burst time
    double at;   // arrival time
    double ct;   // completion time
    double st;   // start time
    double wt;   // waiting time
    double tat;  // turnaround time
};

void swap(struct process* p1, struct process* p2) {
    struct process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_by_at(struct process* processes, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at) {
                swap(processes + j, processes + j + 1);
            }
        }
    }
}

void simulate(struct process* processes, int n) {
    sort_by_at(processes, n);
    double* original_bt = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        *(original_bt + i) = (processes + i)->bt;
    }
    double time = 0;
    struct process* current = processes;
    current->st = 0;
    int completed_processes = 0;
    while (completed_processes != n) {
        time++;
        current->bt--;
        if (current->bt == 0) {
            if ((current + 1)->at < time) {
                // next process has arrived
                current->ct = time;
                current++;
                current->st = time;
                completed_processes++;
            }
        }
    }
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
    simulate(processes, n);
    return 0;
}
