

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

const int n = 100;
const int kmax = 1e+4;

void tabul()
{
	FILE *fA = fopen("A.txt","w");
	FILE *fB = fopen("B.txt","w");
	int N = 100, n=N++, i=0, j=0, scale = n*10;
	long double a=1.0, b=9.0, x=8.5L, r_numb = 0.0, sum = 0.0;
	srand(time(NULL));
	//генерування матриці А
	for (i = 1;i <= n; i++)
	{
		sum=0;
		for (j=1;j<=n;j++)
		{
			r_numb = a+b*(long double)rand()/RAND_MAX;
			sum = (i==j)?sum + r_numb*scale:sum + r_numb;
			if (i==j) fprintf(fA,"%10.10Le\n",r_numb*scale);
			else fprintf(fA,"%10.10Le\n",r_numb);
		}
		fprintf(fB,"%10.10Le\n",sum*x);
	}
	printf("Дані записано в A.txt та B.txt");
	fclose(fA);
	fclose(fB);
}	


long double norma_vector(long double *Y,long double *X)
{
	long double max = 0;
	int i = 0;
	//printf("%lf\t",max);
	for(i=2;i<=n;i++)
	{
		if (fabs(Y[i]-X[i])>max) max=fabs(Y[i]-X[i]);
		
	}
	//printf("%lf\n",max);
	return max;
}
long double norma_matrix(long double X[n+1][n+1])
{
	long double max = fabs(X[1][1]), sum = 0;
	int i = 0, j = 0;
	for(i=1;i<=n;i++)
	{
		sum = 0;
		for (j=1;j<=n;j++)
		{
			sum+=fabs(X[i][j]);
		}
		if (sum>max) max = sum;
	}
	return max;
}
int main()
{
	tabul();
	FILE *fA = fopen("A.txt","r");
	FILE *fB = fopen("B.txt","r");
	FILE *fAformat = fopen("A_formatted.txt","w");
	int N=n+1,i=0,j=0,k=0;
	long double sum = 0.0, sum1 = 0, tau = 0.01, eps = 1e-12;
	long double A[N][N],B[N],X[N],Y[N];
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
		{
			fscanf(fA,"%Le",&A[i][j]);
			fprintf(fAformat,"%Lf\t",A[i][j]);
		}
		fprintf(fAformat,"\n");
		fscanf(fB,"%Le",&B[i]);
	}
	for(i=1;i<=n;i++)
	{
		X[i]=1.0;
		Y[i]=1.0;
	}
	tau = 1/norma_matrix(A);//знаходження значення тау
	printf("Tau=%Lf\n",tau);
	//метод простої ітерації
	printf("Метод простої ітерації\n");
	for(k=1;k<=kmax;k++)
	{
		for(i=1;i<=n;i++)
		{
			sum = 0;
			for(j=1;j<=n;j++)
			{
				sum+=A[i][j]*X[j];
			}
			Y[i] = X[i] - tau*sum+tau*B[i];
		}
		if(norma_vector(Y,X)<=eps) break;
		//printf("%lf\t%lf\n",norma_vector(Y,X),X[1]);
		for (i=1;i<=n;i++)
		{
			X[i]=Y[i];
		}
		
		if (k==kmax)
		printf("Метод розбігається\n");
	}
	printf("Корінь %Lf знайдено за %d ітерацій\n",X[1],k);
	//метод Якобі
	for(i=1;i<=n;i++)
	{
		X[i]=1.0;
		Y[i]=1.0;
	}
	printf("Метод Якобі\n");
	for(k=1;k<=kmax;k++)
	{
		for(i=1;i<=n;i++)
		{
			sum = 0;
			for(j=1;j<=n;j++)
			{
				if (i!=j)
				sum+=X[j]*A[i][j]/A[i][i];
			}
			Y[i] = -sum + B[i] / A[i][i];
		}
		if(norma_vector(Y,X)<=eps) break;
		//printf("%lf\t%lf\n",norma_vector(Y,X),X[1]);
		for (i=1;i<=n;i++)
		{
			X[i]=Y[i];
		}
		
		if (k==kmax)
		printf("Метод розбігається\n");
	}
	printf("Корінь %Lf знайдено за %d ітерацій\n",X[1],k);
	//метод Гауса-Зейделя
	for(i=1;i<=n;i++)
	{
		X[i]=1.0;
		Y[i]=1.0;
	}
	printf("Метод Гауса-Зейделя\n");
	for(k=1;k<=kmax;k++)
	{
		for(i=1;i<=n;i++)
		{
			sum = 0,sum1=0;
			for(j=1;j<=n;j++)
			{
				if (j<i)
				sum+=Y[j]*A[i][j]/A[i][i];
				if (j>i)
				sum1+=X[j]*A[i][j]/A[i][i];
			}
			Y[i] = B[i] / A[i][i] - sum - sum1;
		}
		if(norma_vector(Y,X)<=eps) break;
		//printf("%lf\t%lf\n",norma_vector(Y,X),X[1]);
		for (i=1;i<=n;i++)
		{
			X[i]=Y[i];
		}
		
		if (k==kmax)
		printf("Метод розбігається\n");
	}	
	printf("Корінь %Lf знайдено за %d ітерацій\n",X[1],k);
	fclose(fA);
	fclose(fB);
	fclose(fAformat);
	return 0;
}
