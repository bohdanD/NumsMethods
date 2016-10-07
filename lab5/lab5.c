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
	long double x = 0.4;
	printf("sin(x) = %Lf\n", f(x));
	printf("f`(x)=%Lf\n", fp(x));
	long double better=1;
	long double h;
	for(int i=-20; i<=3; i++)
	{
		long double temp = eps1(x, pow(10, i));
		if(temp<better)
		{
			h = pow(10,i);
			better=temp;
		}
		//printf("%Le\n", temp);
	}
	printf("better for y0 =%Le\n", better);
	printf("better for y0 h=%Le\n", h);
	better = 1;
	h= pow(10,-3);
	printf("h=1e-3 y0(h) eps=%Le\n", eps1(x, h));
	printf("h=1e-3 y0(2h) eps=%Le\n", eps1(x, 2*h));
	printf("h=1e-3 yr(h) eps=%Le\n", eps2(x, h));
	printf("h=1e-3 ye(h) eps=%Le\n", eps3(x, h));
	printf("h=1e-3 p=%Le\n", p(x, h));
	return 0;
}

