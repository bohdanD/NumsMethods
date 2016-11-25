#include <stdio.h>
#include <math.h>

long double fx(long double x)
{
	return 1.5L*(1-expl(-x*x));
}

long double f(long double x,long double y)
{
	return 3*x-2*y*x;
}

int main()
{
	FILE *fdata = fopen("epsf.txt","w");
	FILE *fepsr = fopen("epsr.txt","w");
	FILE *fepsh = fopen("epsh.txt","w");
	int i=0;
	long double a=0,b=4,h=1e-4,k1=0,k2=0,k3=0,k4=0,eps=1e-6;
	int n=(b-a)/h+1;
	long double y[n+1],x[n+1],y2[2*n+2],x2[2*n+2],psi=0;
	x[0]=a;y[0]=0.0L;
	for (i=0;i<=n;i++)//обчислення з точністю h
	{
		x[i]=a+i*h;
		k1=f(x[i],y[i]);
		k2=f(x[i]+h*0.5L,y[i]+h*k1*0.5L);
		k3=f(x[i]+h*0.5L,y[i]+h*k2*0.5L);
		k4=f(x[i]+h,y[i]+h*k3);
		y[i+1]=y[i]+h*(k1+2*k2+2*k3+k4)/6.0L;
	}
	h=h/2.0L;
	for (i=0;i<=2*n;i++)//обчислення з точністю h/2
	{
		x2[i]=a+i*h;
		k1=f(x2[i],y2[i]);
		k2=f(x2[i]+h*0.5L,y2[i]+h*k1*0.5L);
		k3=f(x2[i]+h*0.5L,y2[i]+h*k2*0.5L);
		k4=f(x2[i]+h,y2[i]+h*k3);
		y2[i+1]=y2[i]+h*(k1+2*k2+2*k3+k4)/6.0L;
	}
	for (i=0;i<=n;i++)//обчислення похибки за точним значенням
	{
		fprintf(fdata,"%Lf\t%Lf\t%Lf\t%Le\n",x[i],fx(x[i]),y[i],fabsl(fx(x[i])-y[i]));
	}
	for (i=0;i<=2*n;i++)//обчислення похибки за методом Рунге
	{
		if ((i%2)==0)
		fprintf(fepsr,"%Lf\t%Lf\t%Lf\t%Lf\t%Le\n",x[i/2],x2[i],y[i/2],y2[i],15*fabsl(y[i/2]-y2[i])/16.0L);
	}
	long double t = 0,t1=0,yn=y[0],yn1=0;
	h=1e-4;long double eps32 = eps/32.0L;
	//int k=0,kmax=1e+5;
	for (t=a;t<=b;t+=h)//обчислення з автоматичним вибором кроку h
	{
		k1=f(t,yn);
		k2=f(t+h*0.5L,yn+h*k1*0.5L);
		k3=f(t+h*0.5L,yn+h*k2*0.5L);
		k4=f(t+h,yn+h*k3);
		yn1=yn+h*(k1+2*k2+2*k3+k4)/6.0L;
		yn=yn1;
		t1=t+h;
		psi=fabsl(fx(t1)-yn1);
		if (psi>eps) 
		{
			h=h*0.5L; 
			//printf("divided :: psi>eps %Le > %Le h= %Le\n\n",psi,eps,h);
		} 
		if (psi<=eps32)  
		{
			h=h*2.0L; 
			//printf("multyplied :: psi<=eps/32 %Le > %Le h= %Le\n\n",psi,eps32,h);
		}
		fprintf(fepsh,"%Le\t%Le\t%Le\t%Le\n",t1,h,psi,eps);
	}
	//printf("%Le\n",eps32);
	printf("Дані записано  в output.txt");
	fclose(fdata);
	fclose(fepsr);
	fclose(fepsh);
	return 0;
}
