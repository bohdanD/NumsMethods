/*
 * lab1.c
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

long double f(long double x)
{
	return x*sin(x*M_PI/180.0);
}
void tabul()
{
	int N = 0, i=0;long double x0=0.0, xn=0.0;
	printf("Введіть кількість вузлів:");
	scanf("%i",&N);
	printf("Введіть значення абсциси першого вузла:");
	scanf("%Lf",&x0);
	printf("Введіть значення абсциси останнього вузла:");
	scanf("%Lf",&xn);
	long double x[N+1],y[N+1],h[N+1];
	long double tmp_h = (xn-x0)/(N-1);
	//табулювання функції
	for (i = 1;i <= N; i++)
	{
		x[i] = x0;
		h[i] = tmp_h;
		y[i] = f(x[i]);
		x0+=tmp_h;
	}
	//запис протабульованих даних у файл inputL.txt
	FILE *finput = fopen("input.txt","w");
	for(i=1;i<=N;i++)
	{
		fprintf(finput,"%Le\t%Le\t%Le\n",x[i],y[i],h[i]);
	}
	printf("Дані записано в input.txt");
	fclose(finput);
	return;
}

//розв’язання тридіагональної матриці - знаходження коеф. с
void tridiagonal_matrix_solve(long double * y,long double *h,const int N,long double *c)
{
	FILE *fch = fopen("check.txt","w");//файл для запису похибки матриці
	int i = 0,n=N-1;//N - к-сть вузлів, n - номер останнього вузла
	long double alfa[N+1],beta[N+1],hamma[N+1],delta[N+1],A[N+1],B[N+1],eps[N+1];
	//визначення коефіцієнтів alfa,beta,hamma,delta
	alfa[1]=0.0;beta[1]=1.0;hamma[1]=0.0;delta[1]=0.0;
	for(i=2;i<=n;i++)
	{
		alfa[i]=h[i-1];
		beta[i]=2*(h[i-1]+h[i]);
		hamma[i]=h[i];
		delta[i]=3*(((y[i]-y[i-1])/h[i])-((y[i-1]-y[i-2])/h[i-1]));
	}
	hamma[n]=0.0;
	//прямий хід
	//визначення коефіцієнтів A,B
	A[1]=-hamma[1]/beta[1];
	B[1]=delta[1]/beta[1];
	for(i=2;i<=n;i++)
	{
		A[i]=-hamma[i]/(alfa[i]*A[i-1]+beta[i]);
		B[i]=(delta[i]-alfa[i]*B[i-1])/(alfa[i]*A[i-1]+beta[i]);
	}
	//зворотній хід
	c[n]=(delta[n]-alfa[n]*B[n-1])/(alfa[n]*A[n-1]+beta[n]);
	for(i=n;i>1;i--)
	{
		c[i-1]=A[i-1]*c[i]+B[i-1];
	}	
	//обчислення різниці між правою і лівою частинами системи рівнянь
	eps[1]=fabs(beta[1]*c[1]+hamma[1]*c[2]-delta[1]);	
	for (i=2;i<n;i++)
	{
		eps[i]=fabs(alfa[i]*c[i-1]+beta[i]*c[i]+hamma[i]*c[i+1]-delta[i]);
	}
	eps[n]=fabs(alfa[n]*c[n-1]+beta[n]*c[n]-delta[n]);
	//обчислення різниці в файл
	for (i=1;i<=N;i++)
	{
		fprintf(fch,"%i-%Le\n",i,eps[i]);
	}
	fclose(fch);
}

int main()
{
	tabul();
	FILE * fdata = fopen("input.txt","r");
	int N = 0, i = 0;
	long double x0=0.0;
	//визначення кількості вузлів
	while (fscanf(fdata,"%Le\t%Le\t%Le",&x0,&x0,&x0)!=EOF)
	{
		N++;
	}
	long double x[N+1],y[N+1],xm[20*N+1],ym[20*N+1],h[N+1],a[N+1],b[N+1],c[N+1],d[N+1];
	//зчитування вхідних даних
	rewind(fdata);
	for(i=0;i<N;i++)
	{
		fscanf(fdata,"%Le\t%Le\t%Le",&x[i],&y[i],&h[i]);
		//printf("[%i] %Le\t%Le\t%Le\n",i,x[i],y[i],h[i]);
	}
	x0=x[0];
	long double tmp_h = h[0];
	//функція обчислення коеф. с (метод прогонки)
	tridiagonal_matrix_solve(y,h,N,c);
	//знаходження коеф. a,b,d;
	for(i=1;i<N;i++)
	{
		a[i]=y[i-1];
		b[i]=(y[i]-y[i-1])/h[i]-(h[i]/3)*(c[i+1]+2*c[i]);
		d[i]=(c[i+1]-c[i])/(3*h[i]);
	};
	b[N-1]=(y[N-1]-y[N-2])/h[N-1]-(2.0/3)*h[N-1]*c[N-1];
	d[N-1]=-c[N-1]/(3*h[N-1]);
	//знаходення значень проміжних вузлів сплайна та 
	//запис вихідних даних у файл output.txt
	FILE *foutput = fopen("output.txt","w");
	//табулювання функції з кількістю кроків 20n
	tmp_h /= 20.0;
	for (i = 0; i < 20*N; i++)
	{
		xm[i] = x0+i*tmp_h;
		ym[i] = f(xm[i]);
	}
	//обчислення значень сплайна у проміжних точках та похибки
	long double s = 0,eps = 0; 
	int j=1;
	for (i = 0; i <= 20*(N-1); i++)
	{
		s=a[j]+b[j]*(xm[i]-x[j-1])+c[j]*(xm[i]-x[j-1])*(xm[i]-x[j-1])+
					d[j]*(xm[i]-x[j-1])*(xm[i]-x[j-1])*(xm[i]-x[j-1]);
		eps  = fabs(s-ym[i]);
		//запис проінтерпольованої функції та похибки у файл
		fprintf(foutput,"%Lf\t%Lf\t%Lf\t%Le\n",xm[i],ym[i],s,eps); 
		if ((i!=0)&&((i)%20)==0) {j++;}
	}
	printf("Результат інтерполяції та похибка записані у файл output.txt");
	fclose(foutput);
	return 0;
}
