/*
 * lab4.c
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
#define  m 8
#define N m+1
#define N1 N+1


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

double pow(double x, int n){
	double res = 1;
	if(n != 0){
		for(int i = 0; i < n; i++) 
			res *= x;
	}
	return res;
} 

double quad(double x, double a[])
{
	double res = 0;
	for(int i = 1; i <= m; i++)
	{
		res += a[i]*pow(x, i);
	}
	return res+a[0]; 
}

void Gauss(double b[N][N],double c[N],double xx[N])
{
	int k;
	double r;

	for(int i = 0; i <= m - 1; i++){
		k = i;
		r = fabs(b[i][i]);
		for(int j = i + 1; j <= m; j++)
		{
			if(fabs(b[j][i]) >= r){
				k = j;
				r = fabs(b[j][i]);
			}
		}
		if(k != i){
			r = c[k];
			c[k] = c[i];
			c[i] = r;
			for(int j = i; j <= m; j++){
				r = b[k][j];
				b[k][j] = b[i][j];
				b[i][j] = r;
			}
		}
		r = b[i][i];
		c[i] = c[i] / r;
		for(int j = 1; j <= m; j++)
			b[i][j] = b[i][j] / r;
		for(k = i + 1; k <= m; k++){
			r = b[k][i];
			c[k] = c[k] - r * c[i];
			b[k][i] = 0;
			for(int j = i + 1; j <= m; j++)
				b[k][j] = b[k][j] - r * b[i][j];
		}
	}
	xx[m] = c[m] / b[m][m];
	for(int i = m - 1; i >= 1; i--){
		r = c[i];
	for(int j = i + 1; j <= m; j++) r = r - b[i][j] * xx[j];
	xx[i] = r;
	}
} 


int main(int argc, char **argv)
{
	char file[]="f(x).txt";
	//int n =30;
	double x[N];
	double y[N];
	writef(file, N);
	read(file, x, y ,N);
	
	
	return 0;
}

