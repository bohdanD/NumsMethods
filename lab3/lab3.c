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

void writef(char file[], int n)
{
	FILE *fp;
	fp = fopen(file, "w+");
	double step =  5.0/(n);
	double x = 0;
	double y;
	char s1[50];
	char s2[50];
	for(int i=0; i<=n; i++)
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

void read(char file[], double x[], double y[], int n)
{
	FILE *fp;
	char buff[255];
	char buff2[255];
	fp = fopen(file, "r");
	for(int i=0; i<=n; i++)
	{
		
			fscanf(fp, "%s", buff);
		
			fscanf(fp, "%s", buff2);
		sscanf(buff, "%lf", &x[i]);	
		sscanf(buff2, "%lf", &y[i]);	
		//printf("%lf", y[i]);
	}
}

double omega(double x, double arr[], int n)
{
	double res = 1;
	for(int i= 0; i<n; i++)
	{
		if(x!=arr[i])
			res *= (x - arr[i]);
	}
	return res;
}

double newton(double x[], double y[], int n)
{
	double res=0;
	for(int i=0; i<=n; i++)
	{
		//printf("\n%lf", t);
		res+= y[i]/ omega(x[i], x, n); 
	}
	return res;
}

double polynome(double xArg, double x[], double y[], int n)
{
	double res = y[0];
	for(int i=1; i<=n; i++)
	{
		res += omega(xArg, x, i-1)*newton(x, y, i);
	}
	return res;
}

double eps(double y, double pol)
{
	return fabs(y-pol);
}
	
void writePolynome(char file[], double x[], double yarr[], int n)
 {
	 FILE *fp;
	fp = fopen(file, "w+");

	double y, e;
	char s1[50];
	char s2[50];
	char s3[50];
	//int k = n/100;
	for(int i=1; i<=n; i++)
	{
		y = polynome(x[i], x, yarr, 5);
		e = eps(yarr[i], y);
		sprintf(s1, "%f", x[i]);
		sprintf(s2, "%f", y);
		sprintf(s3, "%f", e);
		fputs(s1, fp);
		fputs("\t", fp);
		fputs(s2, fp);
		fputs("\t", fp);
		fputs(s3, fp);
		fputs("\n", fp);
	
	}
	fclose(fp);
 }

int main(int argc, char **argv)
{
	int n = 100;
	char file[] = "res.txt";
	double x[n+1];
	double y[n+1];
	writef(file, n);
	read(file, x, y, n);
	writePolynome("polynome.txt", x, y, n);
	return 0;
}

