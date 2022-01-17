
#include <bits/stdc++.h>
using namespace std;
  
struct process_elements {
    int PID;
    int AT, BT, RT, CT, WT, TAT;
};

int GANTT_CHART[100];

void FindWT(process_elements Process[], int n)
{
    int RemainingTime[n];
    for(int i=0; i<n; i++)
        Process[i].RT = -1;
    
    for (int i = 0; i < n; i++)
        RemainingTime[i] = Process[i].BT;
    
    for(int i=0; i<100; i++)
        GANTT_CHART[i] = 0;

    int complete = 0,
    t = 0,
    min = INT_MAX; 
    int shortest = 0; 
    bool check = false;

    while (complete != n)
    {

        for (int j = 0; j < n; j++)
        {
            if ((Process[j].AT <= t) && (RemainingTime[j] < min) && RemainingTime[j] > 0)
            {
                min = RemainingTime[j];
                shortest = j;
                check = true; 
                if(Process[j].RT == -1)
                    Process[j].RT = t;
            }
        }

        if (check == false)
        {
            GANTT_CHART[t] = -1;
            t++;
            continue;
        }
        GANTT_CHART[t] = shortest;
        RemainingTime[shortest]--;
        min = RemainingTime[shortest];
        if (min == 0)
            min = INT_MAX;
        if (RemainingTime[shortest] == 0) 
        {
            complete++;
            check = false;
            Process[shortest].CT = t + 1;
            Process[shortest].WT = Process[shortest].CT - Process[shortest].BT - Process[shortest].AT;
            if (Process[shortest].WT < 0)
                Process[shortest].WT = 0;
        }
        t++;
    }
}
  
void FindTAT(process_elements Process[], int n)
{
    for (int i = 0; i < n; i++)
        Process[i].TAT = Process[i].BT + Process[i].WT;
}

void calc_avg_time(process_elements Process[], int n)
{
    int TotalCT = 0;
    int TotalRT = 0;
    int TotalWT = 0;
    int TotalTAT = 0;

    FindWT(Process, n);
    FindTAT(Process, n);
     
    cout<<"\nPROCESS ID\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\t  WAITING TIME\t TURNAROUND TIME    RESPONSE TIME\n";
  
    for (int i = 0; i < n; i++) {
        TotalWT += Process[i].WT;
        TotalTAT += Process[i].TAT;
        TotalCT += Process[i].CT;
        TotalRT += Process[i].RT;
        cout << Process[i].PID << "\t\t" << Process[i].AT << "\t\t" << Process[i].BT << "\t\t " << Process[i].CT << "\t\t  "<< Process[i].WT << "\t\t " << Process[i].TAT << "\t\t    " << Process[i].RT << endl;
    }
    cout << "\nAVERAGE COMPLETION TIME = "<< (float)TotalCT / (float)n;
    cout << "\nAVERAGE WAITING TIME = "<< (float)TotalWT / (float)n;
    cout << "\nAVERAGE TURNAROUND TIME = "<< (float)TotalTAT / (float)n;
    cout << "\nAVERAGE RESPONSE TIME = "<< (float)TotalRT / (float)n;
    
 
}
void print_gantt_chart(process_elements Process[])
{
    cout<<"\nGANTT CHART FOR THE ENTERED PROCESSES IS AS FOLLOWS :\n\n";
    cout <<"|";
    for(int i=0; i<100; i++)
    {
        if(GANTT_CHART[i+1]!=GANTT_CHART[i])
            cout <<"P" << GANTT_CHART[i] << "\t|";
    }
    cout << endl;
    cout << Process[0].AT << " \t";
    for(int i=0; i<100; i++)
    {
        if(GANTT_CHART[i+1]!=GANTT_CHART[i])
            cout << i << "\t";
    }
    cout<<endl<<endl;
}


int main()
{
    int n;
    cout<<"\n\t\t\t\tSJF (NON PRE-EMPTIVE) SCHEDULING IN C++ LANGUAGE IN OPERATING SYSTEM\n\n";
    cout << "Enter the number of Processes : ";
    cin >> n;

    process_elements Process[n];
    cout<<"\nFor each process, Enter the Process Details in this format: \n";
	cout<<"\nProcess ID <space> Arrival Time <space> Burst Time :  \n\n";
    cout << "Enter the processes details : \n";
    for(int i=0; i<n; i++)
        cin >> Process[i].PID >> Process[i].AT >> Process[i].BT;

    calc_avg_time(Process, n);
    print_gantt_chart(Process);


    cout<<endl<<endl;
    return 0;
}