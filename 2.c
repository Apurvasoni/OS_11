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
	for(i=0;i<q;i++)
	{
		avail[0][i]-=request_m[0][i];
		allocation[p_id][i]+=request_m[0][i];
		need[p_id][i]-=request_m[0][i];
	}
}
int s_algo(int allocation[][20],int need[][20],int avail[1][20],int p, int q,int x[])
{
	int i,j,k;
	int w=0;
	int F[20],available[1][20];
	int sf=0,ff=0;
	for(i=0;i<p;i++)
	F[i]=0;
	for(i=0;i<q;i++)
	available[0][i]=avail[0][i];
	for(k=0;k<p;k++)
	{
		for(i=0;i<p;i++)
		{
			if(F[i]==0)
			{
				ff=0;
				for(j=0;j<q;j++)
				{
					if(need[i][j]>available[0][j])
					ff=1;
				}
				if(ff==0&&F[i]==0)
				{
					for(j=0;j<q;j++)
					available[0][j]+=allocation[i][j];
					F[i]=1;
					sf++;
					x[w++]=i;
				}
			}
		}
