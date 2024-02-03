#include <stdio.h>
#include <stdlib.h>

struct process {
  int allocation[10];
  int maxNeed[10];
  int remainNeed[10];
  int flag; // Flag indicating process completion (0: incomplete, 1: complete)
};

struct process *p;
int n, r; // Number of processes and resources
int *available;

// Function for Banker's algorithm to find a safe sequence
void safeSequence(struct process p[], int available[], int n, int r) {
  int i, count = 0, check = 1;
  int sequence[n];

  while (count < n) {
    for (i = 0; i < n; i++) {
      if (p[i].flag == 0) {
        int safe = 1;
        for (int j = 0; j < r; j++) {
          if (p[i].remainNeed[j] > available[j]) {
            safe = 0;
            break;
          }
        }
        if (safe) {
          p[i].flag = 1;
          for (int j = 0; j < r; j++) {
            available[j] += p[i].allocation[j]; // Update available resources
            p[i].allocation[j] = 0; // Reset allocated resources for the completed process
            p[i].remainNeed[j] = 0; // Reset remaining need for the completed process
          }
          count++;
          sequence[count - 1] = i; // Assign index of completed process to sequence array
        }
      }
    }

    check = 0;
    for (i = 0; i < n; i++) {
      if (p[i].flag == 0) {
        check = 1; // Incomplete process found
        break;
      }
    }

    if (check == 0) {
      // All processes completed
      break;
    }
  }

  if (count == n) { // Safe sequence found
    printf("\nSafe sequence: ");
    for (i = 0; i < n; i++) {
      printf("P%d --> ", sequence[i]); // Print process indices in the safe sequence
    }
  } else {
    printf("\nSystem is not in a safe state");
  }
}

// Function for resource request
void resource_request() {
  int pid, *request;
  printf("\nEnter new request details\n");
  printf("Enter process number: ");
  scanf("%d", &pid);

  // Check if the process number is valid
  if (pid < 0 || pid >= n) {
    printf("Invalid process number\n");
    return;
  }

  request = (int *)malloc(r * sizeof(int));

  printf("Enter request for resources\n");
  for (int j = 0; j < r; j++) {
    scanf("%d", &request[j]);
    // Check if the request is valid
    if (request[j] > available[j]) {
      printf("Invalid request\n");
      free(request);
      return;
    }
  }

  // Update allocation and available arrays
  for (int j = 0; j < r; j++) {
    p[pid].allocation[j] += request[j];
    available[j] -= request[j];
  }

  // Update remaining need array for the process that made the request
  for (int j = 0; j < r; j++) {
    p[pid].remainNeed[j] = p[pid].maxNeed[j] - p[pid].allocation[j];
    if (p[pid].remainNeed[j] < 0)
      p[pid].remainNeed[j] = 0;
  }

  printf("\nAfter resource request:");
  printf("\nAvailable resources: ");
  for (int i = 0; i < r; i++) {
    printf("%d ", available[i]);
  }

  // Check if the system is in a safe state after the request
  safeSequence(p, available, n, r);

  free(request);
}

int main() {
  printf("Enter number of processes: ");
  scanf("%d", &n);

  printf("Enter number of resources: ");
  scanf("%d", &r);

  p = (struct process *)malloc(n * sizeof(struct process));
  available = (int *)malloc(r * sizeof(int));

  for (int i = 0; i < n; i++) {
    printf("\nEnter details for process P%d\n", i);

    // Allocation
    printf("Enter instances allocated of %d resources simultaneously: ", r);
    for (int j = 0; j < r; j++) {
      scanf("%d", &p[i].allocation[j]);
    }

    // Maximum need
    printf("Enter maximum need of all %d resources: ", r);
    for (int j = 0; j < r; j++) {
      scanf("%d", &p[i].maxNeed[j]);
    }

    // Remaining need
    for (int j = 0; j < r; j++) {
      p[i].remainNeed[j] = p[i].maxNeed[j] - p[i].allocation[j];
    }

    p[i].flag = 0; // Initialize the flag to indicate the process is incomplete
  }

  // Available resources
  printf("\nEnter available resources\n");
  for (int i = 0; i < r; i++) {
    printf("Available resource of R%d: ", i + 1);
    scanf("%d", &available[i]);
  }

  printf("\nInitial state:");

  printf("\nAvailable resources: ");
  for (int i = 0; i < r; i++) {
    printf("%d ", available[i]);
  }

  resource_request();

  // Deallocate memory
  free(p);
  free(available);

  return 0;
}
