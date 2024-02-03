BANKER’s ALGORITM PROGRAM
PROGRAM:
#include<stdio.h>
int main(){
int alc[5][3], max[5][3], avail[3], remain[5][3], p[5], i, j, k, l;
//setting process completion flag to 0 [false]
p[0] = p[1] = p[2] = p[3] = p[4] = 0;
//getting some basic inputs from user
printf("HOW MANY RESOURCES ARE AVAILABLE: ");
for(i=0; i<3; i++){
 scanf("%d", &avail[i]);
}
printf("\nENTER MAX NEED FOR\n");
for(i=0; i<5; i++){
 printf("\tP%d: ", i);
 for(j=0; j<3; j++){
 scanf("%d", &max[i][j]);
 }
}
printf("\nENTER ALLOCATED RESOURCES FOR\n");
for(i=0; i<5; i++){
 printf("\tP%d: ", i);
 for(j=0; j<3; j++){
 scanf("%d", &alc[i][j]);
 }
}
//calculating remaining need and available need
for(i=0; i<3; i++){
 for(j=0; j<5; j++){
 avail[i] -= alc[j][i];
 }
}
for(i=0; i<5; i++){
 for(j=0; j<3; j++){
 remain[i][j] = max[i][j] - alc[i][j];
 }
}
//allocating algorithm logic
printf("\n|-------------------------------------------------|\n\tPROCESSES COMPLETED IN THIS PATTERN:
\n\t\t");
for(l=0; l<5; l++){
for(i=0; i<5; i++){
 for(j=0; j<3; j++){
 if(remain[i][j]>avail[j]){
 break;
 }
 }
 if(p[i]==0){
 if(j==3){
 for(k=0; k<3; k++){
 avail[k] += alc[i][k];
 }
 printf("--> P%d ", i);
 p[i] = 1;
 }
}
}
}
//checking is there any deadlock or not
 if((p[0] + p[1]+ p[2] +p[3] +p[4]) ==5)
 printf("\n\n\tDEALOCK STATUS: NO DEADLOCK");
 else
 printf("\n\nDEALOCK STATUS: DEADLOCK");
printf("\n|-------------------------------------------------|");
return 0;
}
OUTPUT :
 