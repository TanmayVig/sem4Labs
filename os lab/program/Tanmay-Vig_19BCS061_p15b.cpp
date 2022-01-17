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


int left_move(vector<int> programs, int from, int to, int pos){
    int sum=0;
    for(int i=from; i>=to; i--){
        sum+=abs(programs[i]-pos);
        cout<<pos<<"\t"<<programs[i]<<"\t"<<abs(programs[i]-pos)<<endl;
        pos=programs[i];
    }
    return sum;
}

int right_move(vector<int> programs, int from , int to, int pos){
    int sum=0;
    for(int i=from+1;i<=to;i++){
        sum+=abs(programs[i]-pos);
        cout<<pos<<"\t"<<programs[i]<<"\t"<<abs(programs[i]-pos)<<endl;
        pos=programs[i];
    }
    return sum;
}

int algo(vector<int> programs,int pos,int dir,int disk){
    int sum=0,diff, n=(int)programs.size();

    sort_(programs,0,n-1); //sorting 
    int ind=search_(programs,0,n-1,pos); //searching nearest index(0 based)
    if(programs[ind]>pos) ind-=1;
    cout<<"Disk Movement:-"<<endl;
    cout<<"From\tto\tDisk Movement"<<endl;

    if(dir==0){
        // for left side
        sum+=left_move(programs,ind, 0, pos);
        sum+=left_move(programs,n-1,ind+1,programs[0]);
    }else{
        // for left side
        sum+=right_move(programs,ind,n-1,pos);
        sum+=right_move(programs,0,ind,programs[n-1]);
    }
    return sum;
}
int main()
{
    int n,pos,dir,disk;
    cout << "Enter number of programs\tInitial position of Head\tTotal number of disks"<<endl;
    cin>>n>>pos>>disk;
    cout << "Enter direction of head movement **1 = Right and 0 = Left**"<<endl;
    cin>>dir;
    vector<int> programs(n);
    cout<<"Enter programs"<<endl;
    for (int i=0; i<n;i++){
        cin>>programs[i];
    }
    int total_movements=algo(programs,pos,dir,disk);
    total_movements=(float)total_movements;
    cout<<"Average disk movement: "<<total_movements/(float)n<<endl;
    return 0;
}
