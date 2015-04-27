#include <iostream>
using namespace std;

struct state
{
	int resource[100];
	int claim[100][100];
	int alloc[100][100];
	int available[100];
}intitial,temp;

void saveState()
{


}

bool isSafe()
{

	return true;
}

int main(){
	
	int t=0, p, r, Time;
	
	cout<<"Enter number of process(p) to simulate\n";
	cin>>p;
	cout<<"Enter number(r) of resources\n";
	cin>>r;

	cout<<"Enter the resource(R) vector\n";
	for(int i=0;i<r;i++)
		cin >> intitial.resource[i];
	cout<<"Enter the amount of time to simulate\n";
	cin>>Time;
	
	while(t<Time){
		saveState();
		//generateRequest();
		if(!isSafe()){
		//	restoreState();
		}
		t++;
	}
	return  0;
}