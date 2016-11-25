

#include <stdio.h>
#include <math.h>
const int m = 2;
long double f1(long double x, long double y)
{
	return x*x+y*y-16;
}
long double f2(long double x, long double y)
{
	return y-x*x+2;
}
long double df1dx(long double x)
{
	return 2*x;
}
long double df1dy(long double y)
{
	return 2*y;
}
long double df2dx(long double x)
{
	return -2*x;
}
long double df2dy(long double x)
{
	return 1;
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
int main()
{
	long double x0=0.0,y0=0.0,x1,y1,x_appr=4.0, y_appr=4.0, tau = 0.1, eps = 1e-10;
	int kmax=1000,k=0;
	//метод релаксації
	printf("Метод релаксації\n");
	x1=x_appr;
	y1=y_appr;
	do
	{
		x0=x1;
		y0=y1;
		x1= x0 - tau*f1(x0,y0);
		y1= y0 - tau*f2(x0,y0);	
		//printf("x1=%20.20Lf\n",x1);
		//printf("y1=%Lf\n",y1);
		if (k>kmax) 
		{
			printf("Перевищена кількість ітерації\n");
			break;
		}
		else {k++;}
	}	while ((fabsl(x1-x0)>=eps)||(fabsl(y1-y0)>=eps)||(fabsl(f1(x1,y1))>=eps)||(fabsl(f2(x1,y1))>=eps));
	printf("x=%20.20Lf\n",x1);
	printf("y=%Lf\n",y1);
	printf("k=%i\n\n",k);
	//метод Ньютона
	printf("Метод Ньютона\n");
	k=0;x1=x_appr;y1=y_appr;tau=-0.1;
	long double A[m][m],B[m],X[m];
	do
	{
		x0=x1;
		y0=y1;
		A[0][0]=df1dx(x0);
		A[0][1]=df1dy(y0);
		A[1][0]=df2dx(x0);
		A[1][1]=df2dy(y0);
		B[0]=f1(x0,y0);
		B[1]=f2(x0,y0);
		gauss(A,B,X,m);
		x1 = x0 + tau*X[0];
		y1 = y0 + tau*X[1];
		if (k>kmax) 
		{
			printf("Перевищена кількість ітерації\n");
			break;
		}
		else {k++;}
	}	while (fabsl(X[0]) >= eps && fabsl(X[1]) >= eps);
	printf("x=%20.20Lf\n",x1);
	printf("y=%Lf\n",y1);
	printf("k=%i\n\n",k);
	return 0;
} 
