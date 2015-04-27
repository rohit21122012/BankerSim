#include <iostream>
using namespace std;

struct state
{
	int resource[100];
	int claim[100][100];
	int alloc[100][100];
	int available[100];
}real,temp;

void saveState(int r, int p)
{
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

bool isSafe(int r,int p)
{
	bool check = false;
	for(int i=0;i<p;i++)
	{
			for(int j=0;j<r;j++)
			{
				if(real.claim[i][j]-real.alloc[i][j]<=real.available[j])
					check=true;
				else{
					check=false;
					break;
				}
			}
			if(check)
				return check;
	}

	return false;
}

int main(){
	
	int t=0, p, r, Time;
	
	cout<<"Enter number of process(p) to simulate\n";
	cin>>p;
	cout<<"Enter number(r) of resources\n";
	cin>>r;

	cout<<"Enter the resource(R) vector\n";
	for(int i=0;i<r;i++)
		cin >> real.resource[i];
	cout<<"Enter the amount of time to simulate\n";
	cin>>Time;
	
	while(t<Time){
		saveState(r,p);
		//generateRequest();
		if(!isSafe(r,p)){
		//	restoreState();
		}
		t++;
	}
	return  0;
}