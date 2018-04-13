// optimization.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
using namespace std;

static void  input_data(void);

#define N 30  // number of cities
#define TYPE -1 // 1=max;-1=min
#define GEN 600 // maximum generation number
#define POP_SIZE 30
#define P_MUTATION 0.2
#define P_CROSSOVER 0.3

int  CHROMOSOME[POP_SIZE + 1][N + 1];
double  OBJECTIVE[POP_SIZE + 1];
double  d[N + 1][N + 1];
double  q[POP_SIZE + 1];

static void  input_data(void)
{
	double x[N + 1], y[N + 1];
	int i, j;
	float read1, read2;
	FILE *fp;

	fopen_s(&fp, "DATA30.dat", "r");
	for (i = 1; i <= N; i++) {
		fscanf_s(fp, "%f %f", &read1, &read2);
		x[i] = read1; y[i] = read2;
	}
	fclose(fp);

	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			d[i][j] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));

}


int main()
{

	int i, j;
	double a;

	srand((unsigned)time(NULL));
	q[0] = 0.05; a = 0.05;
	for (i = 1; i <= POP_SIZE; i++) { a = a*0.95; q[i] = q[i - 1] + a; }
	input_data();
	for (i = 1; i <= GEN; i++) {
		selection();
		crossover();
		mutation();
		evaluation(i);
		printf("\nGeneration NO.%d,  ", i);
		printf("Distance=%3.4f\n", OBJECTIVE[0]);
	}
	printf("\nBest Route is: ");
	for (j = 1; j <= N; j++) {
		if (j<N) printf("%d->", CHROMOSOME[0][j]);
		else printf("%d", CHROMOSOME[0][j]);
	}
	printf("\n Best Distance=%3.4f\n", OBJECTIVE[0]);

	FILE *fp;

	fopen_s(&fp, "RESULT30.dat", "a");
	fprintf(fp, "\nBest Route is: ");
	for (j = 1; j <= N; j++) {
		if (j<N) fprintf(fp, "%d->", CHROMOSOME[0][j]);
		else fprintf(fp, "%d", CHROMOSOME[0][j]);
		if (j % 10 == 0) fprintf(fp, "\n");
	}
	fprintf(fp, "\nBest Distance=%3.4f\n", OBJECTIVE[0]);
	fclose(fp);

	printf("\n");
	system("pause");
	return 1;
}
