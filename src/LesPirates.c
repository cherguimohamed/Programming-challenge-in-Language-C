#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe.h"
#include "map.h"
#define MAX_LINE_LENGTH 1024
#define BOOSTS_AT_START 5

/**
 * @brief Compute the gas consumption of a requested acceleration
 *
 * CAUTION: Even an illegal move will result in gas consumption. Producing
 * illegal moves should be prevented as much as possible!
 *
 * @param accX Acceleration x component
 * @param accY Acceleration y component
 * @param speedX Speed x component
 * @param speedY Speed y component
 * @param inSand (boolean)
 * @return Number of gas units consumed
 */


int gasConsumption(int accX, int accY, int speedX, int speedY, int inSand)
{
  int gas = (accX * accX) + (accY * accY);
  gas += (int)(sqrt(speedX*speedX + speedY * speedY) * 1.5);
  if (inSand) {
    gas += 1;
  }
  return -gas;
}


/* gasneeded */
int gasNeeded(int** map, int x,int y,int arrivee){
/*  int me = map[y][x] + 1;*/
  int speedX,speedY;
  int gas_Reste = 0;
  int i = map[y][x];
  int j = 0;
  int* accX = calloc(1,sizeof(int));
  int *accY  = calloc(1,sizeof(int));
  speedX = 0;
  speedY = 0;
  do {
    j = suivre_chemin(map,x,y);
    getMinAcceleration(j,accX,accY);
    (*accX) -= speedX;
    (*accY) -= speedY;
    gas_Reste += gasConsumption(*accX,*accY,speedX,speedY,0);
    speedX += *accX;
    speedY += *accY;
    x += speedX;
    y += speedY;
    i = map[y][x];
  } while (i != arrivee);

  return gas_Reste;
}


int main()
{
  int row;
  int width, height;
  int i,arrivee,depart,countVit;
  
  
  int gasLevel;
  int boosts = BOOSTS_AT_START;
  int round = 0;
  int j; 
  int ** map;  
  int otherX,otherY;
  int myOldX,myOldY;
  int accelerationX = 1, accelerationY = 0;
  int speedX = 0, speedY = 0;
  char action[100];
  char line_buffer[MAX_LINE_LENGTH];
  char **map_buffer;
  int ** int_map_buffer;
  float ** matrice_adj;
  
  int counter = 1;
  graphe* g;
  tas* t;
  int levelAcc;
  /*int * predd;*/
  int fin_position_x = 0,fin_position_y = 0;
  int* tab_fin;
  int counter_fin_tab = 0;
  
  int * acX = calloc(1,sizeof(int));
  int * acY = calloc(1,sizeof(int));
  myOldX = 0;
  myOldY = 0;
  boosts = boosts;
  fin_position_x =  fin_position_x;
  fin_position_y = fin_position_y;
  tab_fin = calloc(20,sizeof(int));
 
  fgets(line_buffer, MAX_LINE_LENGTH, stdin);      /* Read gas level at Start */
  sscanf(line_buffer, "%d %d %d", &width, &height, &gasLevel);
  /* sauvegarde du map  */
  map_buffer = calloc(height,sizeof(char*));
  int_map_buffer = calloc(height,sizeof(int*));
  map = calloc(height,sizeof(int*));
  for(i=0;i<height;i++){
    map[i] = calloc(width,sizeof(int));
	  map_buffer[i] = calloc(width,sizeof(char));
     int_map_buffer[i] = calloc(width,sizeof(int));
  }


  fprintf(stderr, "=== >Map< ===\n");
  fprintf(stderr, "Size %d x %d\n", width, height);
  fprintf(stderr, "Gas at start %d \n\n", gasLevel);
  
  for (row = 0; row < height; row++) {        /* Read map data, line per line */
    fgets(map_buffer[row], MAX_LINE_LENGTH, stdin);
    for (i = 0;i<width;i++){    
       if (map_buffer[row][i] == '.') int_map_buffer[row][i] = -1;
       else {
          int_map_buffer[row][i] = counter;
          if (map_buffer[row][i] == '='){
            fin_position_x = i;
            fin_position_y = row;
            tab_fin[counter_fin_tab] = counter;
            counter_fin_tab++;
          /*  fprintf(stderr,"tab_fin[%d] = %d\n",counter_fin_tab,counter);*/
          }
          counter++;}
    }
    fputs(map_buffer[row], stderr);
  }

  matrice_adj = calloc(counter+1,sizeof(int*));
  for(i=0;i<counter;i++){
     matrice_adj[i] = calloc(counter+1,sizeof(int));
  }

  fprintf(stderr, "l'affichage a été effeuctue par le map_buffer\n");
 /* l'affichage du map avec des entiers */ 
  for (row = 0; row<height;row++){
     for(i=0;i<width;i++)
     fprintf(stderr,"%d ",int_map_buffer[row][i]);
     fprintf(stderr,"\n");}
  fflush(stderr);
  /* les initialisation de de graphe */



  charge_matrice(height,width,matrice_adj,int_map_buffer,map_buffer);


  g = calloc(1,sizeof(graphe));
  t = calloc(1,sizeof(tas));
  init_tas(counter,t);
  init_graphe(counter,counter,g);
  g->matrice = matrice_adj;
  fprintf(stderr, "\n=== Race start ===\n");
  
/******************************************************************************************/
  levelAcc = 0;
  countVit = 0;
  while (!feof(stdin)) {
    int myX, myY, secondX, secondY, thirdX, thirdY;
    round++;
    fprintf(stderr, "=== ROUND %d\n", round);
    fflush(stderr);
    fgets(line_buffer, MAX_LINE_LENGTH, stdin);   /* Read positions of pilots */
                 
  
  		/* position of pilots */
    sscanf(line_buffer, "%d %d %d %d %d %d",
           &myX, &myY, &secondX, &secondY, &thirdX, &thirdY);

    /* calcule de plus court chemin*/
 /****************************************************************************************/
    if (round == 1){
      depart = int_map_buffer[myY][myX];

      arrivee = calcule_chemin(g,int_map_buffer[myY][myX],tab_fin,counter_fin_tab);

      trace_chemin(g->pred,arrivee,depart,-5);

      dissin_chemin(height,width,int_map_buffer,g->pred, map_buffer,map);
    }

    fprintf(stderr, "    Positions: Me(%d,%d)  A(%d,%d), B(%d,%d)\n",
            myX, myY, secondX, secondY, thirdX, thirdY);
    fflush(stderr);
    	
/* cas où le pilot est bloqué */

  otherX = 0;
  otherY = 0;
  j = suivre_chemin(map,myX,myY);
  getMinAcceleration(j,acX,acY);
  if (norme(speedX,speedY) <= sqrt(2)){
    if ((myX+*acX == secondX)&&(myY + *acY == secondY)){
      otherX = secondX;
      otherY = secondY;}
   if ((myX+*acX == thirdX)&&(myY + *acY == thirdY)){
      otherX = thirdX;
      otherY = thirdY;}
  }

 
  if ((!((myOldX == myX)&&(myOldY == myY))&& myOldY!=0 && myOldX != 0)||(otherX != 0 && otherY !=0))  {
    fprintf(stderr,"\n  \n \n ");
    for (i = 0;i<g->nbsom;i++){
      g->pris[i] = 0;
      g->distance[i] = 0.0;
      g->pred[i] = 0;
    }
    map_buffer[myOldY][myOldX] = '.';
    charge_matrice(height,width,matrice_adj,int_map_buffer,map_buffer);
    if (otherX==0 && otherY == 0){
    for (i=0;i<g->nbsom;i++) {
      matrice_adj[int_map_buffer[myOldY][myOldX]][i] = 0;
      matrice_adj[i][int_map_buffer[myOldY][myOldX]] = 0;}
    }
    else {
      for (i=0;i<g->nbsom;i++) {
      matrice_adj[int_map_buffer[otherY][otherX]][i] = 0;
      matrice_adj[i][int_map_buffer[otherY][otherX]] = 0;}
    }    
    g->matrice = matrice_adj;
    arrivee = calcule_chemin(g,int_map_buffer[myY][myX],tab_fin,counter_fin_tab);
    trace_chemin(g->pred,arrivee,int_map_buffer[myY][myX],-5);
    dissin_chemin(height,width,int_map_buffer,g->pred, map_buffer,map);
 	  
    
  }

  if (!((myOldX == myX)&&(myOldY == myY))){
    speedX = 0;
    speedY = 0;}

    getAcceleration(acX,acY,speedX,speedY,myX,myY,map,gasLevel,round,countVit,levelAcc); 
 
    accelerationX = *acX ;
    accelerationY = *acY ;/* -spped*/

    speedX += accelerationX;
    speedY += accelerationY;
    gasLevel += gasConsumption(accelerationX, accelerationY, speedX, speedY, 0);
    
    myX += speedX;
    myY += speedY;
   
    myOldX = myX;
    myOldY = myY;
   
    /* Write the acceleration request to the race manager (stdout). */
    sprintf(action, "%d %d", accelerationX, accelerationY); /* X  Y*/
    fprintf(stdout, "%s", action);
    fflush(stdout);                           /* CAUTION : This is necessary  */
    fprintf(stderr, "    Action: %s   Gas remaining: %d\n", action, gasLevel);
    fflush(stderr);
    if (0 && round > 4) { /* (DISABLED) Force a segfault for testing purpose */
      int * p = NULL;
      fprintf(stderr, "Good Bye!\n");
      fflush(stderr);
      *p = 0;
    }
  }

  return EXIT_SUCCESS;
}
