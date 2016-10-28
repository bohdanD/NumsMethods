



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int n = 100;


void tabul(){
FILE *fA = fopen("A.txt","w");
	FILE *fB = fopen("B.txt","w");
	int N = 100, n=N++, i=0, j=0;
	long double a=1.0, b=9.0, x=8.5L, r_numb = 0.0, sum = 0.0;
	srand(time(NULL));
	//генерування матриці А
	for (i = 1;i <= n; i++)
	{
		sum=0;
		for (j=1;j<=n;j++)
		{
			r_numb = a+b*(long double)rand()/RAND_MAX;
			sum+=r_numb;
			fprintf(fA,"%10.10Le\n",r_numb);
		}
		fprintf(fB,"%10.10Le\n",sum*x);
	}
	printf("Дані записано в A.txt та B.txt");
	fclose(fA);
	fclose(fB);
	return;
}

long double norma(long double *x)
{
	long double res = 0.0L,max = 0;
	int i = 0;
	for (i=1;i<=n;i++)
	{
		res = fabsl(x[i]);
		if (res > max) 	max = res;
	}
	return res;
}
void LU_solve(long double L[n+1][n+1], long double U[n+1][n+1], long double *B,
long double *X)
{
	long double Z[n+1],sum=0;
	int k = 0,j=0;
	Z[1]=B[1]/L[1][1];
	for (k=2;k<=n;k++)
	{
		sum=0.0;
		for(j=1;j<=k-1;j++)
		{
			sum+=L[k][j]*Z[j];
		}
		Z[k]=(B[k]-sum)/L[k][k];
	}
	X[n]=Z[n];
	for (k=n-1;k>=1;k--)
	{
		sum=0.0;
		for(j=k+1;j<=n;j++)
		{
			sum+=U[k][j]*X[j];
		}
		X[k]=Z[k]-sum;
	}
}
void new_B(long double A[n+1][n+1], long double *B, long double *X,
long double *nB)
{
	int i, j;
	long double sum;
	for(i=1;i<=n;i++)
	{
		nB[i]=B[i];
		sum=0;
		for(j=1;j<=n;j++)
		sum+=A[i][j]*X[j];
		nB[i]-=sum;
	}
}
int main()
{
	tabul();
	FILE *fA = fopen("A.txt","r");
	FILE *fAformat = fopen("A_formatted.txt","w");
	FILE *fB = fopen("B.txt","r");
	FILE *fL = fopen("L.txt","w");
	FILE *fU = fopen("U.txt","w");
	int N=n+1,i=0,j=0,k=0, kmax = 1e+5;
	long double sum = 0.0, x_accur = 8.5L,eps = 1e-14, r_eps=0;
	long double A[N][N],B[N],L[N][N],U[N][N],X[N],X_accur[N],dX[N];//Z[N]
	//Зчитування матриць A та стовпця B
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
		{
			fscanf(fA,"%Le",&A[i][j]);
			fprintf(fAformat,"%Lf\t",A[i][j]);
		}
		fprintf(fAformat,"\n");
		fscanf(fB,"%Le",&B[i]);
		//printf("%lf\n",B[i]);
	}
	//Ініціалізація матриць U та L нулями, діагональ одиницями
	for (i = 1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
		{
			L[i][j]=0.0;
			U[i][j]=0.0;
			if (i==j)
			{
				U[i][j] = 1.0;
			}
		}
	}
	//Знаходження LU-розкладу матриці A
	for (k=1;k<=n;k++)
	{
		for (i=k;i<=n;i++)
		{
			sum=0.0;
			for (j=1;j<=k-1;j++)
			{
				sum+=L[i][j]*U[j][k];
			}
			L[i][k]=A[i][k]-sum;
			sum=0.0;
			for (j=1;j<=k-1;j++)
			{
				sum+=L[k][j]*U[j][i];
			}
			U[k][i]=(A[k][i]-sum)/L[k][k];
		}
	}
	//Вивід матриць L та U
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
		{
			fprintf(fL,"%Lf\t",L[i][j]);
			fprintf(fU,"%Lf\t",U[i][j]);
		}
		fprintf(fL,"\n");
		fprintf(fU,"\n");
	}
	//Розв’язання СЛАР
	LU_solve(L,U,B,X);
	//Вектор розв’язку СЛАР
	for (i=1;i<=n;i++)
	{
		//printf("%Lf\n",X[i]);
	}
	printf("\n");
	//Вектор похибок
	
	for (i=1;i<=n;i++)
	{
		r_eps += fabsl(X[i]-x_accur);
		
	}
	printf("Початковий розв’язок %Le\n",r_eps/(long double)n);
	//Знаходження уточненого розв’язку СЛАР
	k=1;
	for(;;)
	{
		new_B(A,B,X,X_accur);
		LU_solve(L,U,X_accur,dX);
		for (i=1;i<=n;i++)
		{
			X[i] += dX[i];
			//printf("%Le\n",dX[i]);
		}
		if (norma(dX)<eps)
		{
			long double neweps=norma(dX);
			printf("Для знаходження розв’язку з точністю %Le потрібно %d ітерацій\n", neweps,k);
			break;
		}
		if (k==kmax) 
		{
			printf("Перевищена максимальна кількість ітерацій\n");
			break;
		}
		++k;
	}
	fclose(fA);
	fclose(fAformat);
	fclose(fB);
	fclose(fL);
	fclose(fU);
	return 0;
}
