// Bankers Algorithm

#include <stdio.h>

struct process {
  int allocation[10];
  int maxNeed[10];
  int remainNeed[10];
  int flag; // Flag indicating process completion (0: incomplete, 1: complete)
};

void safeSequence(struct process p[], int available[], int n) {
  int i, count = 0, check = 1;
  int sequence[n];

  while (count < n) {
    for (i = 0; i < n; i++) {
      if (p[i].remainNeed[0] <= available[0] && p[i].remainNeed[1] <= available[1] && p[i].remainNeed[2] <= available[2]) {
        p[i].flag = 1;
        available[0] += p[i].allocation[0];
        available[1] += p[i].allocation[1];
        available[2] += p[i].allocation[2];
        count++;
        sequence[count - 1] = i; // Assign index of completed process to sequence array
        break; // Move to next process if a safe sequence is found
      }
    }

    for (i = 0; i < n; i++) {
      if (p[i].flag == 0) {
        check = 1; // Incomplete process found
        break;
      }
    }

    if (check == 1) {
      printf("System is not in safe state");
      return; // Terminate function if no safe sequence exists
    }
  }

  if (count == n) { // Safe sequence found
    printf("\nSafe sequence: ");
    for (i = 0; i < n; i++) {
      printf("P%d-->", sequence[i]); // Print process indices in safe sequence
    }
  }
}

int main() {
  struct process p[5];
  int i, j; // Indices
  int n, r; // Number of processes and resources
  int available[10];

  printf("Enter number of process\n");
  scanf("%d", &n);

  printf("Enter number of resources\n");
  scanf("%d", &r);

  for (i = 0; i < n; i++) {
    printf("\nEnter details for process p%d\n", i);

    // Allocation
    for (j = 0; j < r; j++) {
      printf("Enter instances allocated of R%d:", j + 1);
      scanf("%d", &p[i].allocation[j]);
    }

    printf("\n");
    // Maximum need
    for (j = 0; j < r; j++) {
      printf("Enter maximum need of resource R%d:", j + 1);
      scanf("%d", &p[i].maxNeed[j]);
    }

    printf("\n");
    // Remaining need
    for (j = 0; j < n; j++) {
      p[i].remainNeed[j] = p[i].maxNeed[j] - p[i].allocation[j];
    }

    p[i].flag = 0; // Initialize flag to indicate process is incomplete
  }

  // Available resources
  printf("Enter available resources\n");
  for (i = 0; i < r; i++) {
    printf("Available resource of R%d", i + 1);
    scanf("%d", &available[i]);
  }

  printf("\nSafe sequence");

  safeSequence(p, available, n);

  return 0;
}

