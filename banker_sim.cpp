#include <iostream>
using namespace std;

int main(){
	int t=0, p, r, Time;
	int R[r];
	cout<<"Enter number of process(p) to simulate\n";
	cin>>p;
	cout<<"Enter number(r) of resources\n";
	cin>>r;
	cout<<"Enter the resource(R) vector\n"
	for(int i=0;i<r;i++)
		cin >> R[i];
	cout<<"Enter the amount of time to simulate\n";
	cin>>Time;
	
	while(t<Time){
		saveState();
		generateRequest();
		if(!isSafe()){
			restoreState();
		}
		t++;
	}
	return  0;
}