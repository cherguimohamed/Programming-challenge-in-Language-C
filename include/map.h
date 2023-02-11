#ifndef map_h
#define map_h
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graphe.h"



void dissin_chemin(int,int,int **,int *,char**,int **);
void trace_chemin(int*,int,int, int);

int suivre_chemin(int **,int,int);

void charge_matrice(int,int,float **,int**,char**);
int gasNeeded(int**,int,int,int);




































#endif
