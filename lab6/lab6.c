

#include<stdio.h>
#include<math.h>

const long double a = 0.0L, b= 2.0L;
long double int_ac = 0.0L;
long int iter = 0;

long double f(long double x) //експериментальна функція
{
	iter++;
	return x*expl(x);
}

long double F(long double x) //первісна експериментальної фунції
{
	return (x-1)*expl(x);
}

long double I(int N)
{
	long double sum=f(a)+f(b), h=(b-a)/N,x=0;
	long int i = 0;
	for (i=1;i < N;i++)
	{
		x=a+i*(b-a)/N;
		if (i%2==1)
		{
			sum+=4*f(x);
		}
		else
		{
			sum+=2*f(x);
		}
	}
	return sum*h/3.0;
}
long double Ip(int N,long double a,long double b)
{
	long double sum=f(a)+f(b), h=(b-a)/N,x=0;
	long int i = 0;
	for (i=1;i < N;i++)
	{
		x=a+i*(b-a)/N;
		if (i%2==1)
		{
			sum+=4*f(x);
		}
		else
		{
			sum+=2*f(x);
		}
	}
	return sum*h/3.0;
}
long double I_adaptation(int N, long double delta){
	long double res=0, h=(b-a)/N, x, x1, I0, I1;
	int i, k, kmax=10000;
	
	for(i=1;i<=N;i++){
		x=a+h*i;
		x1=a+h*(i-1);
		k=2;
		I1=Ip(k, x1, x);
		while(k<kmax){
			k*=2;
			I0=I1;
			I1=Ip(k, x1, x);
			if(fabsl(I0-I1)<=delta) break;
		}
		res+=I1;
	}
	return res;
}
int main()
{
	
	FILE * fdata = fopen("output.txt","w");
	FILE * fr = fopen("r.txt","w");
	int_ac = expl(2.0L) + 1.0L;
	long int N = 100;
	long double eps_t=0,eps_opt=1e-12,E0,E1,E2;
	printf("точне знач. інтегралу %Lf\n",int_ac);
	printf("приблизне знач. інтегралу %Lf\n",I(N));

	for (N=8000;N<1e+5;N+=1000)
	{
		fprintf(fdata,"%li\t%Le\n",N,fabsl(I(N)-int_ac));
	}
	N=1000;
	while ((eps_t=fabs(I(N)-int_ac))>eps_opt)
	{
		//fprintf(fdata,"%i\t%Le\n",N,eps_e);
		N+=1;
	}
	printf("Nopt=%li\n",N);
	printf("Eps=%Le\n", eps_t);
	printf("При N=7208\n");
	N=7208;
	//N=8192;
	E0=fabsl(I(N)-int_ac);
	printf("E0=%Le\n",E0);
	E1=fabsl(I(N)+((I(N)-I(N/2))/15.0L)-int_ac);
	E2=fabsl((I(N/2)*I(N/2)-I(N)*I(N/4))/(2.0L*I(N/2)-(I(N)+I(N/4)))-int_ac);

	printf("E1=%Le\n",E1);
	printf("E2=%Le\n",E2);
	//printf("ch=%Le\n",I(N/2)*I(N/2)-I(N)*I(N/4));
	//printf("zn=%Le\n",2.0L*I(N/2)-(I(N)+I(N/4)));
	printf("p=%Le\n", 1/logl(2.0L)*logl((I(N/4) - I(N/2))/(I(N/2) - I(N))));
	printf("Iadapt=%Lf\n",I_adaptation(N,1e-5));
	N=100;
	for (eps_t=1e-10;eps_t>=1e-15;eps_t/=10.0L)
	{
		iter=0;
		fprintf(fr,"%Le\t%Le",eps_t,fabsl(I_adaptation(N,eps_t)-int_ac));
		fprintf(fr, "\t%li\n", iter);
	}
	fclose(fdata);
	fclose(fr);
	return 0;
}
