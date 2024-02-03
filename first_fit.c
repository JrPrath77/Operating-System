#include<stdio.h>

int partition[5];
int process_size[5];
int i,j,k; // declare variables outside the functions

void first_fit(){
    int used[5];
    for(i=0; i<5; i++)
        used[i]=0; // initialize the array with zeros
	for(i=0; i<4; i++){
		for(j=0; j<5; j++){
	      if(used[j]==0 && process_size[i]<=partition[j]){ // check if the partition is free before comparing sizes
		   printf("Process %d in partition %d\n",i+1,j+1);
		   used[j]=1; // mark the partition as used
		   k=i; // use k=i instead of k++
		   used[k]=j+1;
		   break;
	  } 
	}
	if(j==5) // if no partition is found for the process
        printf("Process %d is not allocated\n",i+1); // print a message
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
	first_fit();
	return 0;
}