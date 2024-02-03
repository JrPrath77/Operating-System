#include<stdio.h>

int partition[5];
int process_size[5];
int i, j, k; // declare variables outside the functions

void first_fit(){
    int used[5];
    for(i = 0; i < 5; i++)
        used[i] = 0; // initialize the array with zeros
    for(i = 0; i < 4; i++){
        for(j = 0; j < 5; j++){
            if(used[j] == 0 && process_size[i] <= partition[j]){ // check if the partition is free before comparing sizes
                printf("Process %d in partition %d\n", i + 1, j + 1);
                used[j] = 1; // mark the partition as used
                k = i; // use k = i instead of k++
                used[k] = j + 1;
                break;
            } 
        }
        if(j == 5) // if no partition is found for the process
            printf("Process %d is not allocated\n", i + 1); // print a message
    }
}

void worst_fit(){
    int used[5];
    for(i = 0; i < 5; i++)
        used[i] = 0; // initialize the array with zeros
    for(i = 0; i < 4; i++){
        int worst_fit_index = -1;
        for(j = 0; j < 5; j++){
            if(used[j] == 0 && process_size[i] <= partition[j]){ // check if the partition is free before comparing sizes
                if(worst_fit_index == -1 || partition[j] > partition[worst_fit_index]){
                    worst_fit_index = j;
                }
            } 
        }
        if(worst_fit_index != -1){
            printf("Process %d in worst fit partition %d\n", i + 1, worst_fit_index + 1);
            used[worst_fit_index] = 1; // mark the partition as used
            k = i; // use k = i instead of k++
            used[k] = worst_fit_index + 1;
        } else {
            printf("Process %d is not allocated\n", i + 1); // print a message
        }
    }
}

void best_fit(){
    int used[5];
    for(i = 0; i < 5; i++)
        used[i] = 0; // initialize the array with zeros
    for(i = 0; i < 4; i++){
        int best_fit_index = -1;
        for(j = 0; j < 5; j++){
            if(used[j] == 0 && process_size[i] <= partition[j]){ // check if the partition is free before comparing sizes
                if(best_fit_index == -1 || partition[j] < partition[best_fit_index]){
                    best_fit_index = j;
                }
            } 
        }
        if(best_fit_index != -1){
            printf("Process %d in best fit partition %d\n", i + 1, best_fit_index + 1);
            used[best_fit_index] = 1; // mark the partition as used
            k = i; // use k = i instead of k++
            used[k] = best_fit_index + 1;
        } else {
            printf("Process %d is not allocated\n", i + 1); // print a message
        }
    }
}

int main(){
    
    for(i = 0; i < 5; i++){
        printf("Enter size of partition %d:", i + 1);
        scanf("%d", &partition[i]);
    }
    printf("\n");
    for(i = 0; i < 4; i++){
        printf("Enter size of process %d:", i + 1);
        scanf("%d", &process_size[i]);
    }
    printf("\n");

    // Call the best_fit function instead of first_fit
    best_fit();

    return 0;
}
