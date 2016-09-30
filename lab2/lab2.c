/*
 * lab2.c
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
	fp = fopen("f(x)n=20.txt", "w+");
	int iter = 2000;
	double step = 0.01;
	double x = 0;
	double y;
	char s1[50];
	char s2[50];
	for(int i=0; i<=iter; i++)
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
//zrobutu double
int fact(int k)
{
	int res = 1;
	if(k==0 || k==1)
	{
		return 1;
	}else
	{
		res = fact(k-1) * k;
	}
	return res;
}

int cnk(int n, int k)
{
	static int res = 0;
	int nk = n - k;
	res = fact(n)/(fact(k)*fact(nk));
	return res;
}

double delta(int k)
{
	double result = 0;
	for(int i=0; i<=k; i++)
	{
		result += pow(-1, i) * cnk(k, i) * sin(k-i);
	}
	return result;
}

double factPolynom(double t, int n)
{
	double res = 1;
	for(int i=0; i<n; i++)
	{
		res *= t-i;
	}
	return res;
	
}

double fAppr(double t, int n)
{
	double sum = 0;
	for(int i=0; i<=n; i++)
	{
		sum += delta(i) / fact(i) * factPolynom(t, i);
	}
	return sum;
}

double eps(double f, double fappr)
{
	return fabs(f-fappr);
}
 
 void writeAppr(char file[], double x[], double yarr[], int n)
 {
	 FILE *fp;
	fp = fopen(file, "w+");

	double y, e;
	char s1[50];
	char s2[50];
	char s3[50];
	int k = n/100;
	for(int i=0; i<=n; i++)
	{
		y = fAppr(x[i], k);
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
	//writef();
	char fileF[] = "f(x)n=10.txt";
	char fileFappr[] = "fAppr(x)n=10.txt";
	int n = 1000;
	double x[2001];
	double y[2001];
	read(fileF, x, y, n);
	writeAppr(fileFappr, x, y, n);
	/*double pol  = factPolynom(2.1, 20);
	double appr = fAppr(2.1, 5);
	printf("%lf\n", appr);
	printf("%lf\n", y[200]);
	printf("%lf\n", eps(y[200], appr));
	
	printf("%lf\n", delta(10));
	printf("%lf\n", pol);
	* */
	return 0;
}

