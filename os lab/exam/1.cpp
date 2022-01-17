#include <iostream>
#include <vector>
#include <cmath>
/*
sstf
1. find closest point to current pos
3. table to show disk movement
2. total seek time
*/
using namespace std;
int algo(vector<int> programs, int pos){
    int total_movement=0, diff,next;
    
    cout<<"Disk Movement:-"<<endl;
    cout<<"From\tto\tDisk Movement"<<endl;
    while(!programs.empty()){
        next=0;
        for (int i=0; i!=(int)programs.size(); i++){
            if(abs(programs[i]-pos)<abs(programs[next]-pos)){
                next=i;
            }
        }
        diff=abs(programs[next]-pos);
        total_movement+=diff;
        cout<<pos<<"\t"<<programs[next]<<"\t"<<diff<<endl;
        pos=programs[next];
        programs.erase(programs.begin()+next);
    }
    return total_movement;
}
int main()
{
    int n,pos,time;
    cout << "Enter number of programs and Initial position of Head"<<endl;
    cin>>n>>pos;
    cout<<"Enter seek time per cilynder"<<endl;
    cin>>time;
    vector<int> programs(n);
    cout<<"Enter programs"<<endl;
    for (int i=0; i<n;i++){
        cin>>programs[i];
    }
    int total_movements=algo(programs,pos);
    total_movements=(float)total_movements;
    cout<<"Total seek Time: "<<total_movements*time<<endl;
    return 0;
}
