#include <stdio.h>
#include <math.h>
long double f(long double x)
{
	return x*sinl(x)+x*cosl(x)-0.5;
}

void tabul(){
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
		fprintf(finput,"%Le\t%Le\t%Le\t%d\n",x[i],y[i],h[i],0);
	}
	printf("Дані записано в input.txt");
	fclose(finput);
	return;
} 

long double fp(long double x)
{
	return sinl(x)+x*cosl(x)+cosl(x)-x*sinl(x);
}
long double fp2(long double x)
{
	return -(x+2)*sinl(x)-(x-2)*cosl(x);
}
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
int main()
{
	//tabul();
	//задання початкових даних
	//long double x_appr=-4.7;	//перший корінь
	//long double x_appr=-1.7;	//другий корінь
	//long double x_appr=0;		//третій корінь
	long double x_appr= 2.222222e+00;   //2.7;	//четвертий корінь
	long double x_appr2=0;
	long double x_appr3=0;
	long double eps=1e-10;
	long double x0,x1,x2,x3,delta,delta1,rr0,rr1,rr2;
	long double tau=-1/fp(x_appr);
	int k=0,kmax=1e+5;
	//метод простої ітерації
	printf("Метод простої ітерації\n");
	x1=x_appr;
	for (k=1;k<=kmax;k++)
	{
		x0=x1;
		x1=x0+tau*f(x0);
		if(fabsl(x1-x0)<=eps && fabsl(f(x1))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
		
	}
	if(k>=kmax)
	printf("Метод простої ітерації не збігається\n");
	//метод Ньютона
	printf("Метод Ньютона\n");
	k=0;
	x1=x_appr;
	for (k=1;k<=kmax;k++)
	{
		x0=x1;
		x1=x0-f(x0)/fp(x0);
		if(fabsl(x1-x0)<=eps && fabsl(f(x1))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
		
	}
	if(k>=kmax)
	printf("Метод Ньютона не збігається\n");
	//метод Чебишева
	printf("Метод Чебишева\n");
	k=0;
	x1=x_appr;
	for (k=1;k<=kmax;k++)
	{
		x0=x1;
		x1=x0-f(x0)/fp(x0)-0.5*power(f(x0),2)*fp2(x0)/power(fp(x0),3);
		if(fabsl(x1-x0)<=eps && fabsl(f(x1))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
		
	}
	if(k>=kmax)
	printf("Метод Чебишева не збігається\n");
	//метод хорд
	printf("Метод хорд\n");
	k=0;
	x_appr2 = x_appr - f(x_appr)/fp(x_appr);
	x1=x_appr;
	x2=x_appr2;
	for (k=1;k<=kmax;k++)
	{
		x0=x1;
		x1=x2;
		x2=x1-f(x1)*(x1-x0)/(f(x1)-f(x0));
		if(fabsl(x2-x1)<=eps && fabsl(f(x2))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
	}
	if(k>=kmax)
	printf("Метод хорд не збігається\n");
	//метод парабол
	printf("Метод парабол\n");
	k=0;
	x_appr2 = x_appr - f(x_appr)/fp(x_appr);
	x_appr3 = x_appr2 - f(x_appr2)/fp(x_appr2);
	x1=x_appr;
	x2=x_appr2;
	x3=x_appr3;
	long double root=0;
	for (k=1;k<=kmax;k++)
	{
		x0=x1;
		x1=x2;
		x2=x3;
		rr0 = (f(x1)-f(x0))/(x1-x0);
		rr1 = (f(x2)-f(x1))/(x2-x1);
		rr2 = ( rr1 - rr0 )/(x2-x0);
		root=sqrtl(power((x2-x1)*rr2+rr1,2)-4*rr2*f(x2));
		delta=(-((x2-x1)*rr2+rr1) + root)/(2*rr2);
		delta1=(-((x2-x1)*rr2+rr1) - root)/(2*rr2);
		delta=(fabsl(delta)<fabsl(delta1))?delta:delta1;
		x3=x2+delta;
		if(fabsl(x3-x2)<=eps && fabsl(f(x3))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
	}
	if(k>=kmax)
	printf("Метод парабол не збігається\n");
	//метод зворотньої інтерполяції
	printf("Метод зворотньої інтерполяції\n");
	k=0;
	x_appr2 = x_appr - f(x_appr)/fp(x_appr);
	x1=x_appr;
	x2=x_appr2;
	for (k=1;k<=kmax;k++)
	{
		x0=x1;
		x1=x2;
		x2=-x0*f(x1)/(f(x0)-f(x1)) - x1*f(x0)/(f(x1)-f(x0));
		if(fabsl(x2-x1)<=eps && fabsl(f(x2))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
		
	}
	if(k>=kmax)
	printf("Метод зворотньої інтерполяції не збігається\n");
	//метод Ейткена
	printf("Метод Ейткена\n");
	k=0;
	x_appr2 = x_appr - f(x_appr)/fp(x_appr);
	x_appr3 = x_appr2 - f(x_appr2)/fp(x_appr2);
	x1=x_appr;
	for (k=1;k<=kmax;k++)
	{
		x0=x1;
		x1=x0+tau*f(x0);
		if(fabsl(x1-x0)<=eps && fabsl(f(x1))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
		x2=x1+tau*f(x1);
		if(fabsl(x2-x1)<=eps && fabsl(f(x1))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
		x3=x2+power(x2-x1,2)/(2*x1-x2-x0);
		if(fabsl(x3-x2)<=eps && fabsl(f(x3))<=eps) {printf("Корінь = %Lf\t кількість ітерацій %d\n",x1,k);break;}
		x1=x3;
	}
	if(k>=kmax)
	printf("Метод Ейткена не збігається\n");
	return 0;
}
