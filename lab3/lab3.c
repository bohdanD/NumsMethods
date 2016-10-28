/*
 * безіменний.c
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
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

long double f(long double x)
{
	return x*sinl(x*M_PI/180.0L);
}
int tabul(){
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
	return 0;
}

long double w(int k, long double user_x, const long double *x)
{
	int i = 0;
	long double mult=1;
	for (i=0;i<=k;i++)
	{
		mult*=(user_x-x[i]);
	}
	return mult;
}

long double rr(int n, const long double *x, const long double *y)
{
	int i = 0,j=0; long double sum=0,mult=1;
	for (i=0;i<=n;i++)
	{
		mult=1;
		for(j=0;j<=n;j++)
		{
			if (j!=i)
			{
				mult*=(x[i]-x[j]);
				
			}
		}
		sum+=(y[i]/mult);
	}
	return sum;
}

long double Nn(int n, long double tmp_x, const long double *x, const long double *y)
{
	int k=0;
	long double result = 0;
	for(k=1;k<=n;k++)
	{
		result+=(w(k-1,tmp_x,x)*rr(k,x,y));
	}
	result+=y[0];
	return result;
}

long double Feps(int n, long double tmp_x, const long double *x, const long double *y)
{
	return fabsl(f(tmp_x)-Nn(n,tmp_x,x,y));
}


int main(int argc, char **argv)
{
	tabul();
	FILE * fdata = fopen("input.txt","r");
	FILE * fdata_out = fopen("output.txt","w");
	int N = 0, n = 0, i = 0, j = 0;
	long double xc=0,a=0,b=0,l=0,h=0;
	char one_char;
	//визначення кількості вузлів
	while((one_char = fgetc(fdata)) != EOF)
    if (one_char == '\n') ++N;
	long double x[N+1],y[N+1];//,xm[20*N+1],ym[20*N+1],h[N+1];
	//зчитування вхідних даних
	rewind(fdata);
	for(i=0;i<N;i++)
	{
		fscanf(fdata,"%i\t%*c\t%Le\t%Le",&j,&x[i],&y[i]);
		//printf("%i)\t%Le\t%Le\n",j,x[i],y[i]);
	}
	n=N-1;
	a=x[0];
	b=x[n];
	//printf("Введіть x для обчислення значення інтерполяційного многочлена Ньютона:");
	//scanf("%Lf",&xc);
	//printf("Nn(xc=%Lf)=%Lf\n",xc,Nn(n,xc,x,y));
	//printf("Табуляція 6\n");
	h=(b-a)/(long double)(20*n);
	b=a+360*h/4.0;
	for (l = a;l<=b;l+=h)
	{
		xc = l;
		fprintf(fdata_out,"%Le\t%Le\t%Le\t%Le\t%Le\n",xc,f(xc),Nn(n,xc,x,y),Feps(n,xc,x,y),w(n,xc,x));
		//printf("%Le\t%Le\t%Le\t%Le\t%Le\n",xc,f(xc),Nn(n,xc,x,y),Feps(n,xc,x,y),w(n,xc,x));
	}
	printf("Дані записано в output.txt");
	fclose(fdata);
	fclose(fdata_out);
	return 0;
}

