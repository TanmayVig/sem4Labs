#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

typedef struct{
    char process_name[3];
    int size,allocated;
}process;

void print_table(process pr[],int m, int mem_block[]){
	int i,frag;
    puts(" __________________________________________");
    puts("| Process name | Size | Alloted | Fragment |");
    puts("|______________|______|_________|__________|");
    for(i=0;i<m;i++){
        if(pr[i].allocated==-1)
            frag =-1;
        else
            frag=mem_block[pr[i].allocated];
    printf("|      %s     | %3d  |    %2d   |    %3d   |\n",
                        pr[i].process_name,pr[i].size,pr[i].allocated,frag);
    }
    puts("|______________|______|_________|__________|");
}

void main()
{
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
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(mem_block[j]>=pr[i].size){
                mem_block[j]-=pr[i].size;
                pr[i].allocated=j+1;
                break;
            }
        }
    }
    print_table(pr,m, mem_block);
}
