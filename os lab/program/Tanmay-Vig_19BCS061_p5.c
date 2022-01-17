/*
input => process, arrival time, burst time(execution time)
output(normal) => average of all attributes 
output(in a matrix table) =>(all input and) complete time, turn around time(total time the program stayes in queue), wait time. response time
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    char process_name[3];
    int arrival_time;
    int burst_time;
    int complete_time;
    int turn_around_time;
    int wait_time;
    int response_time;
	int time_left;
} process;

int have_task(process arr[], int n){
	// printf("HERE");
	int have = 0,i;
	for(i=0; i<n;i++){
		if(arr[i].time_left > 0){
			have=1;
			break;
		}
	}
	return have;
}

void print_process_table(process arr[],int n){
	int i;
    puts(" ______________ _______________ ____________ _______________ __________________ ___________ _______________");
    puts("| Process Name | Arrival Time  | Burst Time | Complete Time | Turn Around Time | Wait Time | Response Time |");
    for(i=0; i<n;i++){
        puts("|______________|_______________|____________|_______________|__________________|___________|_______________|");
        printf("|      %3s     |      %3d      |     %3d    |      %3d      |       %4d       |    %3d    |      %3d      |\n",
        arr[i].process_name,arr[i].arrival_time,arr[i].burst_time,arr[i].complete_time,arr[i].turn_around_time,arr[i].wait_time,arr[i].response_time);
    }
    puts("|______________|_______________|____________|_______________|__________________|___________|_______________|");

}

void get_average(process arr[], int n){
    double tat=0,wt=0,rt=0;
    int i;
    for(i=0;i<n;i++){
        tat += (double)arr[i].turn_around_time;
        wt += (double)arr[i].wait_time;
        rt += (double)arr[i].response_time;
    }
    printf("Total time to Complete = %3d        Average Time to Complete = %.3f\n",arr[n-1].complete_time,(double)arr[n-1].complete_time/(double)n);
    printf("Total Turn Around Time = %.3f     Average Turn Around Time = %.3f\n",tat,tat/(double)n);
    printf("Total Waiting Time = %.3f         Average Waiting Time = %.3f\n",wt,wt/(double)n);
    printf("Total Response Time = %.3f        Average Response Time = %.3f\n",rt,rt/(double)n);
}

void gnatt(process arr[],int n,int time_quantum){
	int i,j,time=0,total_time=0;
	for(i=0; i<n;i++){
		arr[i].time_left = arr[i].burst_time;
	}
    printf("\n|");
	i=0;
	while(have_task(arr,n)==1){
		if(arr[i].time_left>0){
			printf("%3s  ",arr[i].process_name);
			printf("|");
		}
		if(time_quantum<arr[i].time_left){
			time = time_quantum ? time_quantum<arr[i].time_left : arr[i].time_left;
		}else{
			time = arr[i].time_left;
		}
		arr[i].time_left-=time;
		i++;
		i%=n;
	}
	printf("\n");
	for(i=0; i<n;i++){
		arr[i].time_left = arr[i].burst_time;
	}
	i=0;
	while(have_task(arr,n)==1){
		if(arr[i].time_left>0){
			printf("%2d",total_time);
			printf("    ",arr[i].process_name);
			
		}
		if(time_quantum<arr[i].time_left){
			time = time_quantum ? time_quantum<arr[i].time_left : arr[i].time_left;
		}else{
			time = arr[i].time_left;
		}
		arr[i].time_left-=time;
		total_time+=time;
		i++;
		i%=n;
	}
	printf("%d",total_time);
    
}

void main()
{
    int n =0,i, total_time=0, time_quantum;
    printf("Enter the number of processes\t");
    scanf("%d",&n);
    printf("Enter the Time Quantum\t");
    scanf("%d",&time_quantum);
    process arr[n];
    printf("Enter PROCESS_NAME ARRIVAL_TIME and BURST_TIME\n");
    for(i=0; i<n;i++)
    {
        scanf("%s %d %d",arr[i].process_name,&arr[i].arrival_time,&arr[i].burst_time);
		arr[i].time_left=arr[i].burst_time;
		// response time
		arr[i].response_time = total_time;
		if(arr[i].burst_time<time_quantum){
			total_time += arr[i].burst_time;
		}else{
			total_time += time_quantum;
		}
    }
	// complete time
	total_time=0;
	i=0;
	while(have_task(arr,n)==1){
		// printf("HERE IN WHILE");
		if(arr[i].time_left > 0){
			if(time_quantum<arr[i].time_left){
				total_time+=time_quantum;
				arr[i].time_left -= time_quantum;
			}else{
				total_time+=arr[i].time_left;
				arr[i].time_left -= arr[i].time_left;
			}
			if(arr[i].time_left==0){
				arr[i].complete_time = total_time;
				arr[i].turn_around_time = arr[i].complete_time-arr[i].arrival_time;
				arr[i].wait_time = arr[i].turn_around_time-arr[i].burst_time;
			}
		}
		i++;
		i%=n;
	}
	print_process_table(arr,n);
    get_average(arr, n);
    printf("---------------------- GNATT CHART -------------------\n");
    gnatt(arr,n,time_quantum);
}
