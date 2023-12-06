#include <stdio.h>

int at[4], bt[4], ct[4], tat[4], wt[4];
int completed[4] = {0, 0, 0, 0}; // To keep track of completed processes.

int turn_around_time(int i) { return tat[i] = ct[i] - at[i]; }

int completion_time(int i) {
  if (i == 0 || ct[i - 1] < at[i])
    return ct[i] = at[i] + bt[i];
  else
    return ct[i] = ct[i - 1] + bt[i];
}

int find_shortest_job(int current_time) {
  int shortest_job = -1;
  int shortest_time = 9999; // A large initial value for comparison.
  
  for (int i = 0; i < 4; i++) {
    if (!completed[i] && at[i] <= current_time && bt[i] < shortest_time) {
      shortest_time = bt[i];
      shortest_job = i;
    }
  }
  
  return shortest_job;
}

int main() {
  for (int i = 0; i < 4; i++) {
    printf("Enter Arrival Time of Process %d: ", i + 1);
    scanf("%d", &at[i]);
  }
  for (int i = 0; i < 4; i++) {
    printf("Enter Burst Time of Process %d: ", i + 1);
    scanf("%d", &bt[i]);
  }

  int current_time = 0;
  int completed_processes = 0;
  while (completed_processes < 4) {
    int shortest_job = find_shortest_job(current_time);
    if (shortest_job != -1) {
      ct[shortest_job] = completion_time(shortest_job);
      completed_processes++;
      completed[shortest_job] = 1;
      turn_around_time(shortest_job);
    } else {
      current_time++;
    }
  }

  printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < 4; i++) {
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], tat[i] - bt[i]);
  }

  float avg_wt = 0, avg_tat = 0;
  for (int i = 0; i < 4; i++) {
    avg_wt += tat[i] - bt[i];
    avg_tat += tat[i];
  }
  avg_wt /= 4.0;
  avg_tat /= 4.0;

  printf("Average Waiting Time: %.2f\n", avg_wt);
  printf("Average Turnaround Time: %.2f\n", avg_tat);

  return 0;
}