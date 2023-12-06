#include <stdio.h>

int at[4], bt[4], ct[4], tat[4], wt[4], rt[4];

int turn_around_time(int i) { return tat[i] = ct[i] - at[i]; }

int completion_time(int i) { return ct[i] = rt[i] + at[i]; }

int wait_time(int i) { return wt[i] = tat[i] - bt[i]; }

float average_wt() { return (wt[0] + wt[1] + wt[2] + wt[3]) / 4.0; }

float average_tat() { return (tat[0] + tat[1] + tat[2] + tat[3]) / 4.0; }

void sort_by_arrival_time() {
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (at[i] > at[j]) {
        int temp = at[i];
        at[i] = at[j];
        at[j] = temp;

        temp = bt[i];
        bt[i] = bt[j];
        bt[j] = temp;
      }
    }
  }
}

void preemptive_sjf() {
  int complete = 0, shortest = 0, time = 0, min = 9999, check = 0;

  for (int i = 0; i < 4; i++) {
    rt[i] = bt[i];
  }

  while (complete != 4) {
    for (int j = 0; j < 4; j++) {
      if ((at[j] <= time) && (rt[j] < min) && rt[j] > 0) {
        min = rt[j];
        shortest = j;
        check = 1;
      }
    }

    if (check == 0) {
      time++;
      continue;
    }

    rt[shortest]--;
    min = rt[shortest];
    if (min == 0)
      min = 9999;

    if (rt[shortest] == 0) {
      complete++;
      check = 0;
      min = 9999;
      ct[shortest] = time + 1;
      turn_around_time(shortest);
      wait_time(shortest);
    }
    time++;
  }
}

void display(int i) { printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
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

  sort_by_arrival_time();
  preemptive_sjf();
  printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < 4; i++) {
    display(i);
  }

  printf("\nAverage Waiting Time: %f", average_wt());
  printf("\nAverage Turn Around Time: %f\n", average_tat());

  return 0;
}