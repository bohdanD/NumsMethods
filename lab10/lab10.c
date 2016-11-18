

#include <stdio.h>
#include <math.h>
const int n = 2;
long double power(long double x, int a)
{
	long double mult = 1;
	int i = 0;
	for (i=0;i<a;i++)
	{
		mult*=x;
	}
	return mult;
}
long double F(long double x, long double *a)
{
	long double result = 0;
	int i = 0;
	for (i = 0;i<=n;i++)
	{
		result += a[i]*power(x,i);
	}
	return result;
}
int main()
{

	int i=0, k=0, N = n+1, kmax=1e+5;
	long double a[N],b[N],c[N];
	a[0] = 2.0L; a[1] = 4.0L; a[2] = -1.0L; 
	
	long double x0, x1 = 5, eps = 1e-12;
	//метод Ньютона з використанням схеми Горнера
	do
	{
		x0=x1;
		b[n]=a[n];
		for (i=n-1;i>=0;i--)
		{
			b[i] = a[i] +x0*b[i+1];
		}
		c[n]=b[n];
		for (i=n-1;i>=0;i--)
		{
			c[i] = b[i] +x0*c[i+1];
		}
		x1=x0-b[0]/c[1];	
		if (k>kmax) 
		{
			printf("Перевищена кількість ітерації\n");
			break;
		}
		else {k++;}
	}	while ((fabsl(x1-x0)>=eps)&&(fabsl(F(x1,a))>=eps));
	printf("Дійсний корінь: x0=%20.20Lf. Знайдено за %d ітерацій\n",x0,k);
	//метод Ліна
	long double alpha, alpha1=1, beta,beta1=-1, p,p1, q1;//,q1;
	k=0;
	do
	{
		alpha=alpha1;
		beta=beta1;
		p=-2*alpha;
		//q=power(alpha,2)+power(beta,2);
		b[n]=a[n];
		b[n-1]=a[n-1]-p*b[n];
		q1=a[0]/b[2];
		p1=(a[1]*b[2]-a[0]*b[3])/(b[2]*b[2]);	
		alpha1=-p1/2.0L;
		beta1=sqrtl(q1-alpha1*alpha1);
		if (k>kmax) 
		{
			printf("Перевищена кількість ітерації\n");
			break;
		}
		else {k++;}
		}	while ((fabsl(alpha1-alpha)>=eps)&&(fabsl(beta1-beta)>=eps));
		printf("Комплексний корінь: x1=%Lf-%Lfi. Знайдено за %d ітерацій\n",alpha1,beta1,k);
		printf("Комплексний корінь: x2=%Lf+%Lfi. Знайдено за %d ітерацій\n",alpha1,beta1,k);
	//fclose(fcoef);
	return 0;
}
