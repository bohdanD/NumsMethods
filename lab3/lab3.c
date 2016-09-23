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
#include <math.h>

void writef()
{
	FILE *fp;
	fp = fopen("res.txt", "w+");
	int iter = 100;
	double step = 0.1;
	double x = 0;
	double y;
	char s1[50];
	char s2[50];
	for(int i=0; i<iter; i++)
	{
		y = sin(x);
		sprintf(s1, "%f", x);
		sprintf(s2, "%f", y);
		fputs(s1, fp);
		fputs("\t", fp);
		fputs(s2, fp);
		fputs("\n", fp);
		x += step;
	}
	fclose(fp);
}

void readx(double y[])
{
	FILE *fp;
	char buff[255];
	char buff2[255];
	fp = fopen("res.txt", "r");
	for(int i=0; i<100; i++)
	{
		if((i % 2) > 0)
			fscanf(fp, "%s", buff);
		else
			fscanf(fp, "%s", buff2);
		sscanf(buff, "%lf", &y[i]);	
		//printf("%lf", y[i]);
	}
}

double omega(double x, double arr[])
{
	static double res = 1;
	for(int i= 0; i< 100; i++)
	{
		if(x!=arr[i])
			res = res * (x - arr[i]);
	}
	return res;
}

double newton(double x[], double y[])
{
	static double res=0;
	for(int i=0; i<100; i++)
	{
		double t = omega(x[i], x); 
		printf("\n%lf", t);
		res+=y[i]/ t;
	}
	return res;
}



int main(int argc, char **argv)
{
	
	double x[100];
	x[0]=0;
	for(int i=1; i<100; i++)
		x[i]= x[i-1]+0.1;
	double y[100];
	writef();
	readx(y);
	printf("%s", "\n");
	printf("%lf", omega(1, x));
	printf("%s", "\n");
	printf("%lf", newton(x, y));
	return 0;
}

