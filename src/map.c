#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>
#include "map.h"
#include "graphe.h"






void dissin_chemin(int height,int width,int ** int_map_buffer,int * pred,char** map_buffer,int **    map){
  int row,i;
  for (row = 0;row<height;row++){
    for(i = 0;i<width;i++){
      map[row][i] = 1;}
  }
 
  for (row = 0;row<height;row++){
     for (i = 0;i<width;i++){
        if (int_map_buffer[row][i] != -1){
        if(pred[int_map_buffer[row][i]] <= -5){
              map_buffer[row][i] = '$';
              map[row][i] = pred[int_map_buffer[row][i]];
             
               /* remplir_colone(row,i,height,width,map_buffer);*/
                }
         }
         
         fprintf(stderr,"%d ",map[row][i]);
     }
 /*    fputs(map_buffer[row],stderr);*/
     fprintf(stderr,"\n");
  }
}



void trace_chemin(int* tab,int arrivee,int depart, int counter){
  int j = arrivee;
  int i = j;
  while (i != depart){
    i = tab[j];
    tab[j] = counter;
    counter--;
    j = i;}
    tab[depart] = counter;
}

int suivre_chemin(int ** map,int x,int y){
  int me = map[y][x]+1;
  if (y>0) if (map[y-1][x] == me) return 0;
  if (y>0) if (map[y-1][x+1] == me) return 1;
  if (map[y][x+1] == me) return 2;
  if (map[y+1][x+1] == me) return 3;
  if (map[y+1][x] == me) return 4;
  if (map[y+1][x-1] == me) return 5;
  if (map[y][x-1] == me) return 6;
  if (y>0) if (map[y-1][x-1] == me) return 7;
 return -1;}








void charge_matrice(int height,int width,float ** matrice_adj,int** int_map_buffer,char** map_buffer)
{
 int i,j;

 for (i=0;i<height;i++){
   for(j=0;j<width;j++){
    matrice_adj[i][j] = 0.0;}
 }
 
 for (i = 0; i<height - 1; i++){
   for (j = 1; j<width-1; j++){
 
     if ((map_buffer[i][j] != '~')&&(map_buffer[i][j+1] != '~')&&(map_buffer[i][j] != '.')&&        (map_buffer[i][j+1] != '.')){
        matrice_adj[int_map_buffer[i][j]][int_map_buffer[i][j+1]] = 1;
        matrice_adj[int_map_buffer[i][j+1]][int_map_buffer[i][j]] = 1;}
     if ((map_buffer[i][j] != '~')&&(map_buffer[i+1][j] != '~')&&(map_buffer[i][j] != '.')&&        (map_buffer[i+1][j] != '.')){
       matrice_adj[int_map_buffer[i][j]][int_map_buffer[i+1][j]] = 1;
       matrice_adj[int_map_buffer[i+1][j]][int_map_buffer[i][j]] = 1;}
 
     if ((map_buffer[i][j] == '~')&&(map_buffer[i][j+1] == '~')){
       matrice_adj[int_map_buffer[i][j]][int_map_buffer[i][j+1]] = 2;
       matrice_adj[int_map_buffer[i][j+1]][int_map_buffer[i][j]] = 2;}
     if ((map_buffer[i][j] == '~')&&(map_buffer[i+1][j] == '~')){
       matrice_adj[int_map_buffer[i][j]][int_map_buffer[i+1][j]] = 2;
       matrice_adj[int_map_buffer[i+1][j]][int_map_buffer[i][j]] = 2;}
 
     if ((map_buffer[i][j] != '~')&&(map_buffer[i+1][j+1] != '~')&&(map_buffer[i][j] != '.')&&    (map_buffer[i+1][j+1] != '.')){
       matrice_adj[int_map_buffer[i][j]][int_map_buffer[i+1][j+1]] = sqrt(2);
       matrice_adj[int_map_buffer[i+1][j+1]][int_map_buffer[i][j]] = sqrt(2);}
     if ((map_buffer[i][j] != '~')&&(map_buffer[i+1][j-1] != '~')&&(map_buffer[i][j] != '.')&&    (map_buffer[i+1][j-1] != '.')){
       matrice_adj[int_map_buffer[i][j]][int_map_buffer[i+1][j-1]] = sqrt(2);
       matrice_adj[int_map_buffer[i+1][j-1]][int_map_buffer[i][j]] = sqrt(2);}
 
      
   }
 }
}



