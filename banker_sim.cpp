#include <iostream>
using namespace std;

int main(){
	int t=0, p, r, R, Time;
	cout<<"Enter number of process(p) to simulate\n";
	cin>>p;
	cout<<"Enter number(r) of resources\n";
	cin>>r;
	cout<<"Enter the resource(R) vector\n"
	cin>>R;
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