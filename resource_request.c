#include <stdio.h>

struct process {
  int allocation[10];
  int maxNeed[10];
  int remainNeed[10];
  int flag; // Flag indicating process completion (0: incomplete, 1: complete)
};

struct process p[10];
int i, j; // Indices
int n, r; // Number of processes and resources
int available[10];

// below function is of bankers algorithm
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
            p[i].allocation[j] =0; // Reset allocated resources for the completed process
            p[i].remainNeed[j] =0; // Reset remaining need for the completed process
          }
          count++;
          sequence[count - 1] =i; // Assign index of completed process to sequence array
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
      printf("P%d --> ",sequence[i]); // Print process indices in the safe sequence
    }
  } 
  if(count!=n){
    printf("\nSystem is not in a safe state");
  }
}

// below function is for resourse request
void resource_request() {
  int pid, request[10];
  printf("\nEnter new request details\n");
  printf("Enter process number (NOTE: - Process starts from index 0 and ends at index n-1): ");
  scanf("%d", &pid);

  printf("Enter request for resources\n");
  for (j = 0; j < r; j++) {
    scanf("%d", &request[j]);
    // Check if the request is valid
    if (request[j] > available[j]) {
      printf("Invalid request\n");
      return;
    }
  }

  // Update allocation and available arrays
  for (j = 0; j < r; j++) {
    p[pid].allocation[j] = p[pid].allocation[j] + request[j];
    available[j] = available[j] - request[j];
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < r; j++) {
      p[pid].remainNeed[j] = p[pid].maxNeed[j] - p[pid].allocation[j];

      if (p[pid].remainNeed[j] < 0)
        p[pid].remainNeed[j] = 0;
    }
  }

  printf("\nAfter resource request:");
  printf("\nAvailable resources: ");
  for (i = 0; i < r; i++) {
    printf("%d ", available[i]);
  }

  // Check if the system is in a safe state after the request
  safeSequence(p, available, n, r);
}

int main() {
  printf("Enter number of processes: ");
  scanf("%d", &n);

  printf("Enter number of resources: ");
  scanf("%d", &r);

  for (i = 0; i < n; i++) {
    printf("\nEnter details for process P%d\n", i);

    // Allocation
    printf("Enter instances allocated of %d resources simultaneously: ", r);
    for (j = 0; j < r; j++) {
      scanf("%d", &p[i].allocation[j]);
    }

    // Maximum need
    printf("Enter maximum need of all %d resources: ", r);
    for (j = 0; j < r; j++) {
      scanf("%d", &p[i].maxNeed[j]);
    }

    // Remaining need
    for (j = 0; j < r; j++) {
      p[i].remainNeed[j] = p[i].maxNeed[j] - p[i].allocation[j];
    }

    p[i].flag = 0; // Initialize the flag to indicate the process is incomplete
  }

  // Available resources
  printf("\nEnter available resources\n");
  for (i = 0; i < r; i++) {
    printf("Available resource of R%d: ", i + 1);
    scanf("%d", &available[i]);
  }

  printf("\nInitial state:");

  printf("\nAvailable resources: ");
  for (i = 0; i < r; i++) {
    printf("%d ", available[i]);
  }
  resource_request();
  safeSequence(p, available, n,r); // Commented out as it should be called after resource_request()

  return 0;
}