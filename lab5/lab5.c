/*
 * lab5.c
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
#include<math.h>
long double f(long double x)
{
return sinl(x);
}

long double fp(long double x)
{
return cosl(x);
}

long double fn(long double x, long double h)
{
return (f(x+h)-f(x-h))/(2.0*h);
}

long double eps1(long double x, long double h)
{
return fabsl(fp(x)-fn(x,h));
}

long double eps2(long double x, long double h){
return fabsl( fp(x)-( fn(x, h)+(fn(x, h)-fn(x, 2.0L*h))/3.0L ) );
}

long double eps3(long double x, long double h)
{
return fabsl(fp(x)-(fn(x, 2.0L*h)*fn(x, 2.0L*h)-fn(x, h)*fn(x, 4L*h)) / (2.0L*fn(x, 2.0L*h)-(fn(x, h)+fn(x, 4.0L*h))) );
}

long double p(long double x, long double h){
return 1/logl(2)*logl((fn(x, 4.0L*h)-fn(x, 2.0L*h))/(fn(x, 2.0L*h)-fn(x, h)));
}
int main(int argc, char **argv)
{
	FILE * fdata = fopen("output.txt","w");
	FILE * freport = fopen("report.txt","w");
	long double x0=2.25,yp0=0.0, h=1e-4, h0,h1,E0,E1,E2,E3;
	
	while (h>=1e-7)
	{
		fprintf(fdata,"%Le\t%Le\n",h,eps1(x0,h));
		h-=1e-7;
	}
	yp0=fp(x0);
	h0=6.8e-6;
	h1=5e-4;
	E0=eps1(x0,h0);//при оптимальному кроці
	E1=eps1(x0,h1);//при менш точному кроці
	E2=eps2(x0,h1);//уточнення за методом Рунге-Ромберта
	E3=eps3(x0,h1);//уточнення за методом Ейткена
	int pint = (int)roundl(p(x0,h1));//порядок точності
	printf("yp0=%Lf\n",yp0);
	printf("h0=%Le\n",h0);
	printf("h1=%Le\n",h1);
	printf("E0=%Le\n",E0);
	printf("E1=%Le\n",E1);
	printf("E2=%Le\n",E2);
	printf("E3=%Le\n",E3);
	printf("p=%i\n",pint);
	fprintf(freport,"yp0=%Lf\n",yp0);
	fprintf(freport,"h0=%Le\n",h0);
	fprintf(freport,"h1=%Le\n",h1);
	fprintf(freport,"E0=%Le //при оптимальному кроці\n",E0);
	fprintf(freport,"E1=%Le //при менш точному кроці\n",E1);
	fprintf(freport,"E2=%Le //уточнення за методом Рунге-Ромберта\n",E2);
	fprintf(freport,"E3=%Le //уточнення за методом Ейткена\n",E3);
	fprintf(freport,"p=%i //порядок точності\n",pint);
	fclose(fdata);
	fclose(freport);
	return 0;
}

