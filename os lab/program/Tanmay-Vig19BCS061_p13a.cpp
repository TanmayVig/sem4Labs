#include <iostream>
#include <vector>
#include <cmath>
/*
fcfs
1. detail about each disk movement
2. average head movement
*/
using namespace std;
int algo(vector<int> programs,int pos){
    cout<<"Disk Movement:-"<<endl;
    cout<<"From\tto\tDisk Movement"<<endl;
    int sum=0,diff;
    for (int i=0; i<(int)programs.size();i++){
        diff=abs(pos-programs[i]);
        sum+=diff;
        cout<<pos<<"\t"<<programs[i]<<"\t"<<diff<<endl;
        pos=programs[i];
    }
    return sum;
}
int main()
{
    int n,pos;
    cout << "Enter number of programs and Initial position of Head"<<endl;
    cin>>n>>pos;
    vector<int> programs(n);
    cout<<"Enter programs"<<endl;
    for (int i=0; i<n;i++){
        cin>>programs[i];
    }
    int total_movements=algo(programs,pos);
    total_movements=(float)total_movements;
    cout<<"Average disk movement: "<<total_movements/(float)n<<endl;
    return 0;
}
