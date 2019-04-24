


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
		if(sf==p)
		return 1;
	}
	return 0;
}
void input_information(int allocation[][20],int need[][20],int max[20][20],int available[1][20],int *p,int *q)
{
	int i,j;
	printf("\nWrite the number of processes you want: ");
	scanf("%d",p);
	printf("\nWrite the number of resources you want: ");
	scanf("%d",q);
	for(i=0;i<*p;i++)
	{
		printf("\nProcess_number\t %d\n",i+1);
		for(j=0;j<*q;j++)
		{
			printf("Enter the allocation for resource_%d :",j+1);
			scanf("%d",&allocation[i][j]);
			printf("Enter the maximum for resource_%d :",j+1);
			scanf("%d",&max[i][j]);
		}
	}
	printf("\n Enter the number of available resources below:-\n");
	for(i=0;i<*q;i++)
	{
		printf("Resource %d:",i+1);
		scanf("%d",&available[0][i]);
	}
	for(i=0;i<*p;i++)
	   for(j=0;j<*q;j++)
	       need[i][j]=max[i][j]-allocation[i][j];
	printf("\nHere is our Allocation matix");
	print(allocation,*p,*q);
	printf("\nMaximum requirement matrix is as follows");
	print(max,*p,*q);
	printf("\nAnd the Need matrix is as follows");
	print(need,*p,*q);
}
	int b_algo(int allocation[][20],int need[][20],int available[1][20],int p, int q)
	{
		int i,j,a[20];
		j=s_algo(allocation,need,available,p,q,a);
		if(j!=0)
		{
			printf("\n\n");
			printf("\n Safety sequence found and sequence is:-");
			for(i=0;i<p-1;i++)
			  printf("P%d->",a[i]);
			printf("P%d",a[p-1]);
			return 1;
		}
		else
		{
			printf("\nDeadlock Occured!!!!\n");
			return 0;
		}
	}
	int main()
	{
		int op;
		int allocation[20][20];
		int max[20][20];
		int need[20][20];
		int available[1][20];
		int p,q;
		int p_id,ch;
		printf("\n\t\t\t\t\t\t\tBANKER's ALGORITHM\n");
		printf("\n\t\t***************************************************************************************************************\n");
		input_information(allocation,need,available,max,&p,&q);
		op=b_algo(allocation,need,available,p,q);
		if(op!=0)
		{
			printf("\n\nDo you want to make additional request? (1=yes|0=no)");
			scanf("%d",ch);
			if(ch==1)
			{
				printf("\n Enter process no.:-");
				scanf("%d",&p_id);
				resource(allocation,need,available,p_id-1,q);
				op=b_algo(allocation,need,available,p,q);
				if(op==0)
				 exit(0);
			}
		}
		else
		 exit(0);
		return 0;
	}

