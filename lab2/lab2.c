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

int fact(int k)
{
	static int res = 1;
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
	res = (int)fact(n)/(fact(k)*fact(nk));
	return res;
}

int main(int argc, char **argv)
{
	//writef();
	int i = cnk(4, 2);
	printf("%i", i);
	return 0;
}

