#include <stdio.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void round_robin(Process p[], int n, int quantum) {
    int time, completed = 0,loop=0,OT,i,j,index;
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    // Sort by arrival time
    for (i = 0; i < n - 1; i++)
	for (j = 0; j < n - i - 1; j++)
	    if (p[j].arrival_time > p[j+1].arrival_time) {
		Process temp = p[j];
		p[j] = p[j+1];
		p[j+1] = temp;
	    }

    queue[rear++] = 0; // Add first process to queue
    visited[0] = 1;
    time=p[0].arrival_time;
    while (completed < n) {
	getch();
	printf("\n %d",++loop);
	index = queue[front++];
	if (p[index].remaining_time > 0) {
		OT=time;
	    if (p[index].remaining_time > quantum) {
		time += quantum;
		p[index].remaining_time -= quantum;
	    } else {
		time += p[index].remaining_time;
		p[index].completion_time = time;
		p[index].turnaround_time = p[index].completion_time - p[index].arrival_time;
		p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
		p[index].remaining_time = 0;
		completed++;
	    }
	printf("\n P%d ST %d  ET %d",p[index].pid,OT,time);
	    // Add new processes that have arrived
	    for ( i = 0; i < n; i++) {
		if (p[i].arrival_time <= time && !visited[i] && p[i].remaining_time > 0) {
		    printf("\n New process Added %d", p[i].pid);
		    queue[rear++] = i;
		    visited[i] = 1;
		}
	    }

	    // Re-add current process if it's not done
	    if (p[index].remaining_time > 0) {
		printf("\n Again process Added %d", p[index].pid);
		queue[rear++] = index;
	    }
	}

	// If queue becomes empty, find the next process
	if (front == rear) {
	    for (i = 0; i < n; i++) {
		if (p[i].remaining_time > 0) {
		    printf("\n In empty New process Added %d", p[i].pid);
		    queue[rear++] = i;
		    visited[i] = 1;
		    time = p[i].arrival_time;
		    break;
		}
	    }
	}
    }
}

int main() {
    int n,i, quantum;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    for (i = 0; i < n; i++) {
	p[i].pid = i + 1;
	printf("Enter arrival time and burst time for P%d: ", i + 1);
	scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
	p[i].remaining_time = p[i].burst_time;
    }

    round_robin(p, n, quantum);

    printf("\n%-8s%-15s%-12s%-15s%-15s%-15s\n",
	   "Process", "Arrival Time", "Burst Time", "Completion Time", "Turnaround Time", "Waiting Time");

    for ( i = 0; i < n; i++) {
	printf("P%-7d%-15d%-12d%-15d%-15d%-15d\n",
	       p[i].pid, p[i].arrival_time, p[i].burst_time,
	       p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    getch();
    return 0;
}
