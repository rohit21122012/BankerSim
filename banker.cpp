#include <iostream>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int process,resource;
	printf("Enter the number of processes\n");
	scanf("%d",&process);
	printf("Enter the number of resources\n");
	scanf("%d",&resource);
	int claim[process][resource];
	int allocate[process][resource];
	int resource_max[resource];
	int avail[resource];
	for(int i=1;i<=resource;i++)
	{
		printf("Enter the max resource for %d\n",i );
		scanf("%d",&resource_max[i]);


	}
	for(int i=0;i<process;i++)
	{
		printf("Enter the resources for process %d\n", i);
		for(int j=0;j<resource;j++)
		{	

			printf("Enter the max requirement for resource %d\n", j);
			scanf("%d",&claim[i][j]);

		}

	}

	return 0;
}
