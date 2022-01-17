// Request sequence = {176, 79, 34, 60, 92, 11, 41, 114} #8
// Initial head position = 50
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int search_(vector<int> programs,int lo, int hi, int x){// find point where arr[mid]<=head && arr[mid+1]>head
if(lo<hi){
    int mid=(hi-lo)/2;
    if(programs[mid]==x){
        return mid;
    }else if(programs[mid]<x){
        if((mid+1)==(int)programs.size() || programs[mid+1]>x) return mid;
        else search_(programs,lo,mid-1,x);
    }else{
        if((mid)==0 || programs[mid-1]<x) return mid;
        else search_(programs,mid+1,hi,x);
    }
}
return -1;
}

int piv(vector<int> &arr, int lo, int hi){
    int i=lo, p=arr[hi];
    for (int j=lo; j<=hi;j++){
        if(arr[j]<p){
            swap(arr[j],arr[i]);
            i+=1;
        }
    }
    swap(arr[hi],arr[i]);
    return i;
}

void sort_(vector<int> &arr,int lo, int hi){
    if(lo<hi){
        int p=piv(arr,lo,hi);
        sort_(arr,lo,p-1);
        sort_(arr,p+1,hi);
    }
}

int left_move(vector<int> programs,int ind,int pos){
    int sum=0;
    for(int i=ind;i>=0;i--){
        sum+=abs(programs[i]-pos);
        cout<<pos<<"\t"<<programs[i]<<"\t"<<abs(programs[i]-pos)<<endl;
        pos=programs[i];
    }
    return sum;
}
int right_move(vector<int> programs, int ind, int pos){
    int sum=0;
    for(int i=ind+1;i<programs.size();i++){
        sum+=abs(programs[i]-pos);
        cout<<pos<<"\t"<<programs[i]<<"\t"<<abs(programs[i]-pos)<<endl;
        pos=programs[i];
    }
    return sum;
}

int algo(vector<int> programs,int pos, int dir){
    int sum=0,diff, n=(int)programs.size();

    cout<<"Disk Movement:-"<<endl;
    cout<<"From\tto\tDisk Movement"<<endl;

    sort_(programs,0,n-1); //sorting 
    int ind=search_(programs,0,n-1,pos); //searching nearest index(0 based)
    if(programs[ind]>pos) ind-=1;

    if(dir==0){
        // for left side
        sum += left_move(programs,ind,pos);
        //for right
        sum+= right_move(programs,ind,programs[0]);
    }else{
        //for right
        sum+= right_move(programs,ind,pos);
        // for left side
        sum += left_move(programs,ind,programs[n-1]);
    }
    return sum;
}
int main()
{
    int n,pos,dir;
    cout << "Enter number of programs and Initial position of Head"<<endl;
    cin>>n>>pos;
    cout << "Enter direction of head movement **1 = Right and 0 = Left**"<<endl;
    cin>>dir;
    vector<int> programs(n);
    cout<<"Enter programs"<<endl;
    for (int i=0; i<n;i++){
        cin>>programs[i];
    }
    int total_movements=algo(programs,pos,dir);
    total_movements=(float)total_movements;
    cout<<"Average disk movement: "<<total_movements/(float)n<<endl;
    return 0;
}
