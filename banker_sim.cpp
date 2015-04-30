#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define SUSPENDED	0
#define ACTIVE		1
#define TERMINATED	2

struct state
{
	int resource[100];
	int claim[100][100];
	int alloc[100][100];
	int available[100];
}real,temp, temp2;



struct Processes{
	int state;
//	int time;
} allProcesses[100];



bool exceedsAvailable(int request[], int available[], int r){

 	for (int j = 0; j < r; ++j)
 	{
 	//	cout<<request[j]<<" "<<available[j]<<endl;
 		if(request[j] > available[j])
 			return true;
 	}
 	return false;
}

int performRequest(int r, int p){
	//cout<<"Perform request"<<endl;
	/*generation of the request*/
	//choose one od the processes
	cout<<"( [";
	int	randomP = rand()%p;
	cout<<randomP<<"], ";
	int request[r]; 	//request generated by the randomly choosen process
	for (int j = 0; j < r; ++j)
	{
		if(real.claim[randomP][j] - real.alloc[randomP][j] != 0)
			request[j] = rand()%(real.claim[randomP][j] - real.alloc[randomP][j])+ 1;
		else
			request[j] = 0;
		cout<<request[j]<<", ";
	}
	cout<<")"<<endl;
	/**************************/	



	if(exceedsAvailable(request, real.available, r)){
		allProcesses[randomP].state = SUSPENDED;
		cout<<"SUSPENDED1"<<endl;
	}else{
		for (int j = 0; j < r; ++j)
		{
			real.alloc[randomP][j] += request[j];
			real.available[j] -= request[j];
		}
	}
	return randomP;
}

void saveState(int r, int p)
{
	//cout<<"saving state"<<endl;
	for(int i=0;i<r;i++)
	{	
		temp.resource[i]=real.resource[i];
		temp.available[i]=real.available[i];
	}	
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<r;j++)
		{
			temp.alloc[i][j]=real.alloc[i][j];
			temp.claim[i][j]=real.claim[i][j];

		}
	}
}

bool isSafe(int r, int p){
//	cout<<"Checking if current state is safe"<<endl;
	int count = p;
	bool picked[p];

	for (int i = 0; i < p; ++i)
	{
		picked[i] = false;
	}
	while(count!=0){
		bool safe = false;
		//check if the next step is possible
		for (int i = 0; i < p; ++i)
		{
			if(picked[i] != true){
				int resRequired[r];
				for (int j = 0; j < r; ++j)
				{
					resRequired[j] = real.claim[i][j] - real.alloc[i][j];
				}
				if(! exceedsAvailable(resRequired, real.available, r)){
					safe = true;
					picked[i] = true;
					for (int j = 0; j < r; ++j)
					{
						real.available[j] += real.alloc[i][j];
					} 
					count--;
					break;
				}

			}	
		}
		if(!safe){
			return false;
		}
	}
	return true;
}


void saveState2(int r, int p){
	//cout<<"saving state"<<endl;
	for(int i=0;i<r;i++)
	{	
		temp2.resource[i]=real.resource[i];
		temp2.available[i]=real.available[i];
	}	
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<r;j++)
		{
			temp2.alloc[i][j]=real.alloc[i][j];
			temp2.claim[i][j]=real.claim[i][j];

		}
	}
}

void restoreState(int r,int p)
{

	for(int i=0;i<r;i++)
	{	
		real.resource[i]=temp.resource[i];
		real.available[i]=temp.available[i];
	}	
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<r;j++)
		{
			real.alloc[i][j]=temp.alloc[i][j];
			real.claim[i][j]=temp.claim[i][j];

		}
	}

}


void restoreState2(int r,int p)
{

	for(int i=0;i<r;i++)
	{	
		real.resource[i]=temp2.resource[i];
		real.available[i]=temp2.available[i];
	}	
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<r;j++)
		{
			real.alloc[i][j]=temp2.alloc[i][j];
			real.claim[i][j]=temp2.claim[i][j];

		}
	}

}

void initialState(int r, int p){
	for (int i = 0; i < p; ++i)
	{
		allProcesses[i].state = ACTIVE;
	}
	cout<<"Enter the resource(R) vector\n";
	for(int i=0;i<r;i++)
		cin >> real.resource[i];
	
	cout<<"Enter Claim(C) matrix\n";
	for(int i=0;i<p;i++){
		for (int j = 0; j < r; ++j)
		{
			cin>>real.claim[i][j];
		}
	}
	for (int i = 0; i < p; ++i)
	{
		for (int j = 0; j < r; ++j)
		{
			real.alloc[i][j] = 0;
		}
	}

	for (int j = 0; j < r; ++j)
	{
		real.available[j] = real.resource[j];
	}
}

bool satisfied(int pid, int r){
	for (int j = 0; j < r; ++j)
	{
		if(real.alloc[pid][j] != real.claim[pid][j])
		{
			return false;
		}
	}
	return true;
}

int main(){
	srand(time(NULL));
	int t=0, p, r, Time;
	cout<<"Enter the amount of time to simulate\n";
	cin>>Time;
	cout<<"Enter number of process(p) to simulate\n";
	cin>>p;
	cout<<"Enter number(r) of resources\n";
	cin>>r;
	
	initialState(r,p);
	int pid;
	int StateData[p][Time];
	while(t<Time){
		
		saveState(r,p);
		pid  = performRequest(r, p);
		saveState2(r,p);
		if(!isSafe(r,p)){
			allProcesses[pid].state = SUSPENDED;
			cout<<"SUSPENDED2"<<endl;
			restoreState(r,p);
		}else{
			restoreState2(r,p);
			if(satisfied(pid,r)){
				for (int j = 0; j < r; ++j)
				{
					real.available[j] += real.claim[pid][j];
				}
				allProcesses[pid].state = TERMINATED;
				cout<<"TERMINATED"<<endl;
			}
			cout<<"ALLOWED"<<endl;
		}
		t++;
		for (int i = 0; i < p; ++i)
		{
			StateData[i][t] = allProcesses[i].state; 			
		}
	}
	for (int i = 0; i < p; ++i)
	{
		for (int j = 1; j < Time; ++j)
		{
			cout<<StateData[i][j];
		}	
		cout<<endl;			
	}
	return 0;
}