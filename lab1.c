/*
 * lab1.c
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
/*
double * sin_tabulation(double step, double interval)
{
	int array_length = (int) interval / step;
	double* result = (double*)malloc(sizeof(double) * array_length);
	double arg = 0;
	for(int i=0; i<array_length; i++)
	{
		result[i] = sin(arg);
		arg += step; 
	}
	return result;
}
*/	

void writef()
{
	FILE *fp;
	fp = fopen("res.txt", "w+");
	int iter = 100;
	double step = 0.06;
	double x = -3;
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

int main(int argc, char **argv)
{
	writef();
	return 0;
	
}

