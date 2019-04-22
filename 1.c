

#include<stdio.h>
#include<stdlib.h>
void print(int a[][20],int p, int q)
{
	int i;
	int j;
	for(i=0;i<p;i++)
	{
		printf("\n\t");
		for(j=0;j<q;j++)
		{
			printf("%d\t",a[i][j]);
		}
	}
}
void resource(int allocation[20][20],int need[20][20],int avail[20][20],int p_id,int q)
{
	int request_m [1][20];
	int i;
	printf("\nEnter additional request,if you want:-\n");
	for(i=0;i<q;i++)
	{
		printf("Request for resource,if necessary %d:-",i+1);
		scanf("%d",&request_m[0][i]);
	}
	for(i=0;i<q;i++)
	if(request_m[0][i]>need[p_id][i]);
	{
		printf("\nError Encountered\n");
		exit(0);
	}
	for(i=0;i<q;i++)
	if(request_m[0][i]>avail[0][i])
	{
		printf("Resources are unavailable\n");
		exit(0);
	}
