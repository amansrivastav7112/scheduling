#include <stdio.h>
#include <stdlib.h>

// Structure for process
struct Process {
    int id;       // Process ID
    int burst;    // Burst Time
    int arrival;  // Arrival Time
    int priority; // Priority
    int wait;     // Waiting Time
    int turnaround; // Turnaround Time
    int remaining; // For Round Robin
};

void calculateAverageTime(struct Process p[], int n) {
    float totalWait = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        totalWait += p[i].wait;
        totalTurnaround += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f", totalWait / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
}

// First-Come, First-Served Scheduling
void fcfs(struct Process p[], int n) {
    printf("\n--- FCFS Scheduling ---\n");
    p[0].wait = 0;
    for (int i = 1; i < n; i++) {
        p[i].wait = p[i - 1].wait + p[i - 1].burst;
    }
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].wait + p[i].burst;
    }
    calculateAverageTime(p, n);
}

// Shortest Job Next Scheduling
void sjf(struct Process p[], int n) {
    printf("\n--- SJF Scheduling ---\n");
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].burst < p[i].burst) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    p[0].wait = 0;
    for (int i = 1; i < n; i++) {
        p[i].wait = p[i - 1].wait + p[i - 1].burst;
    }
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].wait + p[i].burst;
    }
    calculateAverageTime(p, n);
}

// Priority Scheduling
void priorityScheduling(struct Process p[], int n) {
    printf("\n--- Priority Scheduling ---\n");
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].priority < p[i].priority) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    p[0].wait = 0;
    for (int i = 1; i < n; i++) {
        p[i].wait = p[i - 1].wait + p[i - 1].burst;
    }
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].wait + p[i].burst;
    }
    calculateAverageTime(p, n);
}

// Round Robin Scheduling
void roundRobin(struct Process p[], int n, int quantum) {
    printf("\n--- Round Robin Scheduling ---\n");
    int time = 0, completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].wait = time - p[i].burst;
                    p[i].remaining = 0;
                    p[i].turnaround = p[i].wait + p[i].burst;
                    completed++;
                }
            }
        }
    }
    calculateAverageTime(p, n);
}

int main() {
    int n, choice, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time, arrival time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].burst, &p[i].arrival, &p[i].priority);
        p[i].id = i + 1;
        p[i].remaining = p[i].burst;
    }

    do {
        printf("\nChoose a Scheduling Algorithm:\n");
        printf("1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf(p, n);
                break;
            case 3:
                priorityScheduling(p, n);
                break;
            case 4:
                printf("Enter time quantum: ");
                scanf("%d", &quantum);
                roundRobin(p, n, quantum);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}