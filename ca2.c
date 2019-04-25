#include<stdio.h>
#include<stdlib.h>

void print_op (int a[][20], int p, int q)
{
	int f;
	int e;
	for(f=0;f<p;f++)
	{
		printf("\n\t");
		for(e=0;e<q;e++)
		{
			printf("%d\t",a[f][e]);
		}
	}	
}

//resource request allocation function
void request_r(int allocate[20][20],int need[20][20],int avail[20][20],int p_id,int  q)
{
	int request_m [1][20];
	int g;
	printf ("\n Please enter additional request, if you want :- \n");
	for(g=0 ;g<q;g++)
	{
		printf (" Enter your request for resource_%d : ",g+1);
		scanf ("%d", &request_m[0][g]);
	}
	
	for(g=0;g<q;g++)
		if(request_m[0][g] > need[p_id][g])// Request is more in comparison to need  
		{
			printf("\n Error Found\n");
			exit(0);
		}

	for(g=0;g<q;g++)
		if(request_m[0][g] > avail[0][g])// there is a shortage of resources as available is less and req is more
		{
			printf("\n Resources are not available.\n");
			exit(0);
		}
	
	for(g=0;g<q;g++)  
	{
		avail[0][g]-=request_m[0][g];
		allocate[p_id][g]+=request_m[0][g];
		need[p_id][g]-=request_m[0][g];
	}
}

//safety algorithm function
int s_algo(int allocate[][20],int need[][20],int avail[1][20],int p,int q,int b[])
{

	int s,t,k;
	int x=0;
	int T[20],available[1][20];
	int sf=0,ff=0;
	for(s=0;s<p;s++)
		T[s]=0;
	for(s=0;s<q;s++)
		available[0][s]=avail[0][s];

	for(k=0;k<p;k++)
	{
		for(s=0;s<p;s++)
		{
			if(T[s] == 0)
			{
				ff=0;
				for(t=0;t<q;t++)
				{
					if(need[s][t] > available[0][t])
						ff=1;
				}
				if(ff == 0 && T[s] == 0)
				{
					for(t=0;t<q;t++)
						available[0][t]+=allocate[s][t];
					T[s]=1;
					sf++;
					b[x++]=s;
				}
			}
		}
		if(sf == p)
			return 1;
	}
	return 0;
}



void ip(int allocate[][20],int need[][20],int max[20][20],int available[1][20],int *p,int *q)
{
	int x,y;
	printf("\n Total no. of processes are required, please enter : ");
	scanf("%d",p);
	printf("\n Total no. of resources are required,please enter: ");
	scanf("%d",q);
	for(x=0;x<*p;x++)
	{
		printf("\n Process %d\n",x+1);
		for(y=0;y<*q;y++)
		{
			printf("Your allocation for resource_%d : ",y+1);
			scanf("%d",&allocate[x][y]);
			printf("Your maximum for resource_%d : ",y+1);
			scanf("%d",&max[x][y]);
		}
	}
	printf("\nNo. of available resources : \n");
	for(x=0;x<*q;x++){
		printf(" Resource_%d : ",x+1);
		scanf("%d",&available[0][x]);
	}

	for(x=0;x<*p;x++)
		for(y=0;y<*q;y++)
			need[x][y]=max[x][y]-allocate[x][y];

	printf("\n Here is your allocation matrix");
	print_op(allocate,*p,*q);
	printf("\n Your Maximum Requirement Matrix");
	print_op(max,*p,*q);
	printf("\n Your Need Matrix");
	print_op(need,*p,*q);

}


//banker's algorithm
int bk_algo(int allocate[][20],int need[][20],int available[1][20],int p,int q)
{
	int j,i,b[10];
	j=s_algo(allocate,need,available,p,q,b);
	if(j != 0 )
	{
		printf("\n\n");
		printf("\n Safety sequence found and the sequence is :");
		for(i=0;i<p-1;i++)
		     printf(" P%d -> ",b[i]);
		printf("P%d",b[p-1]);
		return 1;
	}
	else
	{
		printf("\n !!Deadlock occured!!\n");
		return 0;
	}
}


int main(){
	int op;
	int allocate[20][20];
	int max[20][20];
	int need[20][20];
	int available[1][20];
	int p,q,p_id,ch;
	printf("\n \t ********************* BANKER'S ALOGORITHM **************************\n");
	ip(allocate,need,max,available,&p,&q);
	op=bk_algo(allocate,need,available,p,q);
	if(op !=0 ){
		printf("\n\n Do you want make additional request ? (1=yes|0=no)");
		scanf("%d",&ch);
		if(ch == 1)
		{
			printf("\n Please enter your process no. : ");
			scanf("%d",&p_id);
			request_r(allocate,need,available,p_id-1,q);
			op=bk_algo(allocate,need,available,p,q);
			if(op == 0 )
				exit(0);
		}
	}
	else
		exit(0);
	return 0;
}


