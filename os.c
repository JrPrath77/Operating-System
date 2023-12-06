#include <stdio.h>

int at[4], bt[4], ct[4], tat[4], wt[4];

int turn_around_time(int i) { return tat[i] = ct[i] - at[i]; }

int complition_time(int i) {
  if (i == 0)
    return ct[i] = bt[i] + at[i];
  else
    return ct[i] = ct[i - 1] + bt[i];
}


int wait_time(int i) { return wt[i] = tat[i] - bt[i]; }

float average_wt() { return (wt[0] + wt[1] + wt[2] + wt[3]) / 4.0; }

float average_tat() { return (tat[0] + tat[1] + tat[2] + tat[3]) / 4.0; }

void display(int i){
    printf("\n For process P%d:",i+1);
    printf("\n--------------------------");
    printf("\nArrival Time:%d",at[i]);
    printf("\nBurst Time:%d",bt[i]);
    printf("\nComplition Time:%d",complition_time(i));
    printf("\nTurn Around Time:%d",turn_around_time(i));
    printf("\nWait time:%d",wait_time(i));
    printf("\n");
}

int main() { 
    for(int i=0; i<4; i++){
        printf("Enter Arrival Time of Process %d :",i+1);
        scanf("%d",&at[i]);
    }
    for(int i=0; i<4; i++){
        printf("Enter Burst Time of Process %d :",i+1);
        scanf("%d",&bt[i]);
    }

    display(0);
    display(1);
    display(2);
    display(3);

    printf("\nAverage Waiting Time:%f",average_wt());
    printf("\nAverage Turn Around Time:%f",average_tat());

    return 0; 
    }