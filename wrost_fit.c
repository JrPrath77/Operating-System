#include<stdio.h>

int partition[5];
int process_size[5];
int i,j,k; // declare variables outside the functions

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


int main(){
	
	for(i=0; i<5; i++){
		printf("Enter size of partition %d:",i+1);
		scanf("%d",&partition[i]);
	}
	printf("\n");
	for(i=0; i<4; i++){
		printf("Enter size of process %d:",i+1);
		scanf("%d",&process_size[i]);
	}
	printf("\n");
	worst_fit();
	return 0;
}