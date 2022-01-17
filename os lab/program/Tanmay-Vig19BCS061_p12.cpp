#include<iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
/*
fcfs page replacement
input => total programs, total page capacity
output => detail about each page fault, average page fault

detail about page fault => "number of page fault ={}, 
if fault occure
(raplacing {} with {}.)"
*/
float algorithm(int max_page,queue<int> programs){
    int fault=0,oldest=0;
    vector<int> page;
    for(int i=0;i<max_page;i++){
        page.push_back(programs.front());
        cout<<"Number of Faults= 1.\nAdding "<<programs.front()<<" to Page Table."<<endl;
        cout<<"----------------------------------------"<<endl;
        programs.pop();
        fault+=1;
    }
    while(!programs.empty()){
        bool mila=false;
        for (int i=0; i<=(int)page.size(); i++){
            if(programs.front()==page[i]){
                mila=true;
                break;
            }
        }
        if(mila){
            cout<<"Number of Faults= 0."<<endl;
            cout<<"----------------------------------------"<<endl;
        }else{
            fault+=1;
            cout<<"Number of Faults= 1.\nReplacing "<<page[oldest]<<" with "<<programs.front()<<"."<<endl;
            cout<<"----------------------------------------"<<endl;
            page[oldest]=programs.front();
            oldest= ++oldest % (int)page.size();
        }
        programs.pop();
    }
    return (float)fault;
}
int main(){
    queue<int> programs;
    int max_page,n,ind=0,t;
    string s,temp;
    cout<< "Enter Maximum Page Holding Capacity"<<endl;
    cin>>max_page;
    cout<< "Enter Page Refrencing String(to end reading enter $):\n";
    while(true){
        cin>>t;
        cin>>temp; 
        programs.push(t);
        if(temp[0]=='$'){
            break;
        }
    }
    float total_faults=algorithm(max_page, programs);
    cout<<"Average Page Fault= "<<total_faults/programs.size()<<endl;
    return 0;
}