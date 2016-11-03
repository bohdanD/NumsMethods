/*
 * lab4.c
 * 
 * Copyright 2016 fei34dorosh <fei34dorosh@class>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
const int m = 1;

long double f(long double x)
{
	return x*sinl(x*M_PI/180.0L);
}

void tabul()
{
	int N = 0, i=0;long double x0=0.0L, xn=0.0L;
	printf("Введіть кількість вузлів:");
	scanf("%i",&N);
	printf("Введіть значення абсциси першого вузла:");
	scanf("%Lf",&x0);
	printf("Введіть значення абсциси останнього вузла:");
	scanf("%Lf",&xn);
	long double x[N+1],y[N+1];
	long double h = (xn-x0)/(N-1);
	//h*=5;
	//табулювання функції
	for (i = 1;i <= N; i++)
	{
		x[i] = x0+(i-1)*h;
		y[i] = f(x[i]);
	}
	//запис протабульованих даних у файл inputL.txt
	FILE *finput = fopen("input.txt","w");
	for(i=1;i<=N;i++)
	{
		fprintf(finput,"%i)\t%10.22Le\t%10.22Le\n",i,x[i],y[i]);
	}
	printf("Дані записано в input.txt");
	fclose(finput);
	return;
}

long double power(long double x, int a)
{
	long double result = 1;int i=0;
	for (i=0;i<a;i++)
	{
		result*=x;
	}
	return result;
}

long double dysp(long double *phi, long double *y, int n)
{
	long double sum = 0;
	int i = 0;
	for (i=0;i<=n;i++)
	{
		sum += power(phi[i]-y[i],2);
	}
	sum /= n+1;
	return sqrtl(sum);
}

void gauss(long double a[][m], long double *b, long double *x, int m){
	int k, max, i, j;
	long double prom, t, mmax;
	for(k=0;k<m;k++){
		max=k;
		mmax=fabsl(a[k][k]);
		for(i=k+1;i<m;i++)
			if(fabsl(a[i][k])>mmax){
				max=i;
				mmax=fabsl(a[i][k]);
			}
			
		if(max!=k){
			for(i=0;i<m;i++){
				prom=a[k][i];
				a[k][i]=a[max][i];
				a[max][i]=prom;
			}
			prom=b[k];
			b[k]=b[max];
			b[max]=prom;
		}
		
		for(i=k+1;i<m;i++){
			t=-a[i][k]/a[k][k];
			for(j=k+1;j<m;j++) a[i][j]+=t*a[k][j];
			b[i]+=t*b[k];
		}	
	}
	
	x[m-1]=b[m-1]/a[m-1][m-1];
	for(k=m-2;k>=0;k--){
		x[k]=b[k];
		for(i=k+1;i<m;i++)x[k]-=x[i]*a[k][i];
		x[k]/=a[k][k];
	}
}

int main(int argc, char **argv)
{
	tabul();
	int i=0,j=0,k=0,n=0,N=0;//,max=0;//
	//long double mmax = 0.0L,prom = 0.0L,t = 0.0L;
	FILE * fdata = fopen("input.txt","r");
	FILE * foutput = fopen("output.txt","w");
	FILE * fdysp = fopen("dysp1.txt","a");
	char one_char;
	//визначення кількості вузлів
	while((one_char = fgetc(fdata)) != EOF)
    if (one_char == '\n') ++N;
    n=N-1;
	long double x[N],y[N],phi[N],c[N];
	//зчитування вхідних даних
	rewind(fdata);
	for(i=0;i<N;i++)
	{
		fscanf(fdata,"%i\t%*c\t%Le\t%Le",&j,&x[i],&y[i]);
		//printf("%i)\t%Le\t%Le\n",j,x[i],y[i]);
	}
	
	//int m=nn;
	//printf("Введіть значення m:");
	//scanf("%i",&m);
	
	long double a[m][m],b[m],sum=0;
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			sum=0;
			for (k=0;k<N;k++)
			{
				sum+=power(x[k],i+j);
			}
			a[i][j]=sum;
			//printf("%Lf\n",a[i][j]);
		}
		sum=0;
		for (k=0;k<N;k++)
		{
			sum+=power(x[k],i)*y[k];
		}
		b[i]=sum;
		//printf("%Lf\n",b[i]);
	}
	//Обчислення коефіцієнтів за методом Гауса
	gauss(a,b,c,m);
	//Інтерполяція зі знайденими коефіцієнтами
	for (i = 0; i < N; i++)
	{
		sum=0;
		for (j=0;j<m;j++)
		{
			sum+=c[j]*power(x[i],j);
		}
		phi[i]=sum;
	}
	for (i=0;i<N;i++)
	{
		fprintf(foutput,"%Le\t%Le\t%Le\t%Le\n",x[i],y[i],phi[i],fabsl(phi[i]-y[i]));
	}
	//Обчислення дисперсії
	printf("Дисперсія = %Le\n",dysp(phi,y,n));
	fprintf(fdysp,"%i\t%Le\n",m,dysp(phi,y,n));
	printf("Дані записано в output.txt, dysp.txt");
	fclose(fdata);
	fclose(foutput);
	fclose(fdysp);
	return 0;
}

