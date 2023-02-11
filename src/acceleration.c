#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe.h"
#include "map.h"



int norme(int x, int y){
  int a = x * x + y * y;
  a = sqrt(a);
  return a;
}




int accelerationValid(int x,int y, int boost){
  if (boost>4){
    if (x<-1 || x>1 || y<-1 || y>1) return 0;}
  else{
    if (x<-2 || x>2 || y<-2 || y>2) return 0;}
  return 1;
}

int longDirection(int **map, int x, int y){
  int *accx = calloc(1,sizeof(int));
  int *accy = calloc(1,sizeof(int));
  int longe = 1;
  int j = suivre_chemin(map,x,y);
  while (j == suivre_chemin(map,x,y)){
    getMinAcceleration(j,accx,accy);
    x += *accx;
    y += *accy;
    longe++;
  }
  return longe;
}



void getAccelerations(int** map,int x,int y,int spdX, int spdY,int* acX, int* acY,int levelAcc,int* counter){

  int j = suivre_chemin(map,x,y);
  getMinAcceleration(j,acX,acY);
  if (levelAcc == 0){
    getMinAcceleration(j,acX,acY);
    *acX -= spdX;
    *acY -= spdY;
  }
  if (levelAcc == 1){
    if (*acX == spdX && *acY == spdY) (*counter)++;
    if (*counter == 0){
     getMinAcceleration(j,acX,acY);
     *acX -= spdX;
     *acY -= spdY;}

    if ((*counter)  == 1) getMinAcceleration(j,acX,acY);
    if ((*counter) == 2) {getMinAcceleration(j,acX,acY);*acX = -*acX;*acY = -*acY;*counter = -1;}
    (*counter)++;
  }
  if (levelAcc == 2){
    if (*acX == spdX && *acY == spdY) (*counter)++;
    if (*counter == 0){
      getMinAcceleration(j,acX,acY);
      *acX -= spdX;
      *acY -= spdY;}


    if ((*counter) == 2) getMinAcceleration(j,acX,acY);
    if ((*counter) == 1) getMinAcceleration(j,acX,acY);
    if ((*counter) == 3) {getMinAcceleration(j,acX,acY);*acX = -*acX;*acY = -*acY;}
    if ((*counter) == 4) {getMinAcceleration(j,acX,acY);*acX = -*acX;*acY = -*acY;*counter = -1;}
    (*counter)++;
  }
  if (levelAcc == 3){
    if (*acX == spdX && *acY == spdY) (*counter)++;

    if (*counter == 0){
      getMinAcceleration(j,acX,acY);
      *acX -= spdX;
      *acY -= spdY;}

    if ((*counter) == 3) getMinAcceleration(j,acX,acY);
    if ((*counter) == 1) getMinAcceleration(j,acX,acY);
    if ((*counter) == 2) {*acX = 0;*acY = 0;}
    if ((*counter) == 5) {*acX = 0;*acY = 0;}
    if ((*counter) == 4) {getMinAcceleration(j,acX,acY);*acX = -*acX;*acY = -*acY;}
    if ((*counter) == 6) {getMinAcceleration(j,acX,acY);*acX = -*acX;*acY = -*acY;*counter = -1;}
    (*counter)++;  
  }


  if (levelAcc == 4){
    if (*acX == spdX && *acY == spdY) (*counter)++;
    if (*counter == 0){
      getMinAcceleration(j,acX,acY);
      *acX -= spdX;
      *acY -= spdY;}


    if ((*counter) == 1) {getMinAcceleration(j,acX,acY);*acX *= 2;*acY *=2;}
    if ((*counter) == 2) {*acX =0;*acY = 0;}
    if ((*counter) == 3) {*acX = 0;*acY = 0;}
    if ((*counter) == 4) {getMinAcceleration(j,acX,acY);*acX = -*acX*2;*acY = -*acY*2;*counter = -1;}
    (*counter)++;
  }
}


/*
int suivre_chemin(int ** map,int x,int y){
   int me = map[y][x]+1;
   if (map[y-1][x] == me) return 0;
   if (map[y-1][x+1] == me) return 1;
   if (map[y][x+1] == me) return 2;
   if (map[y+1][x+1] == me) return 3;
   if (map[y+1][x] == me) return 4;
   if (map[y+1][x-1] == me) return 5;
   if (map[y][x-1] == me) return 6;
   if (map[y-1][x-1] == me) return 7;
return 0;}

*/


 

void getMinAcceleration(int direction,int* accX,int* accY){

  int j = direction;


  if (j==0){
    *accX = 0;
    *accY = -1;}
  
  if (j==1){
    *accX = 1;
    *accY = -1;}
  
  if (j==2){
    *accX = 1;
    *accY = 0;}
  
  if(j==3){
    *accX = 1;
    *accY = 1;}
  
  if (j==4){
    *accX = 0;
    *accY = 1;}
  
  if(j==5){
    *accX = -1;
    *accY = 1;}
  
  if (j==6){
    *accX = -1;
    *accY = 0;}
  
  if (j==7){
    *accX = -1;
    *accY = -1;} 
}



void getAcceleration(int * acX,int * acY,int speedX,int speedY,int myX,int myY,int** map,int gasLevel,int round,int countVit,int levelAcc)
{
  
   int n,gasUtile;
   if ((norme(speedX,speedY) <= sqrt(2))) {
     n = longDirection(map,myX,myY);
   
   gasUtile = gasLevel + gasNeeded(map,myX,myY,-5);
   countVit = 0;
   levelAcc = 0;
   if (n>4 && n<10 && gasUtile>9) levelAcc = 1;
   if (n>10 && n<18 && gasUtile>16) {
     levelAcc = 2;
     if (round == 1) levelAcc = 4;}
   if (n>18 && gasUtile>30) {
     levelAcc = 3;
     if (round == 1) levelAcc = 4;}
   getAccelerations(map,myX,myY,speedX,speedY,acX,acY,levelAcc,&countVit);
   }
   else {
     getAccelerations(map,myX,myY,speedX,speedY,acX,acY,levelAcc,&countVit);}
}
