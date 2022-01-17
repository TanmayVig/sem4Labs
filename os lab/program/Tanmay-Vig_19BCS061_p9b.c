#include<stdio.h>

typedef struct{
    char process_name[3];
    int size,allocated;
}process;

void algorithm(int mem_block[],process pr[],int m, int n){
    int i,j,k=0;
    for(i=0;i<m;i++){
        j=k;
        while(1){
            if(mem_block[j]>=pr[i].size){
                mem_block[j]-=pr[i].size;
                pr[i].allocated=j+1;
                k=j;
                break;
            }
            j=(j+1)%n;
            if(j==k) break;
        }
    }
}

void print_table(process pr[],int m, int mem_block[]){
	int i,frag;
    puts(" __________________________________________");
    puts("| Process name | Size | Alloted | Fragment |");
    puts("|______________|______|_________|__________|");
    for(i=0;i<m;i++){
        if(pr[i].allocated==-1)
            frag =-1;
        else
            frag=mem_block[pr[i].allocated-1];
    printf("|      %s     | %3d  |    %2d   |    %3d   |\n",
                        pr[i].process_name,pr[i].size,pr[i].allocated,frag);
    }
    puts("|______________|______|_________|__________|");
}

void main(){
    int n,m,i,j;
    printf("Enter total number of memory blocks\t");
    scanf("%d",&n);
    int mem_block[n];
    printf("Enter the block sizes\n");
    for(i=0;i<n;i++){
        scanf("%d",&mem_block[i]);
    }
    printf("Enter total number of processes\t");
    scanf("%d",&m);
    process pr[m];
    printf("Enter process details--> Process Name, Process Size.\n");
    for(i=0;i<m;i++){
        scanf("%s %d",pr[i].process_name,&pr[i].size);
        pr[i].allocated=-1;
    }
    algorithm(mem_block,pr,m,n);
    print_table(pr,m,mem_block);
}