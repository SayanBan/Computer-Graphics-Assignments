/***********************************************************************
Course: Computer Graphics and Multimedia Systems Lab
Class/Section BCS3A
Introduction: Graphics visualization of a set of pixels
Problem: Given a set of pixels (i.e., integer points in 2D plane), 
         write a C program    to create a .svg image to visualize them.
         Also export the SVG image in an HTML file containing the SVG
         image, so that you can use your internet browser to visualize it.
Author: Piyush K. Bhunre, Dept of CSE, Techno India University, WB, India
email: pkbhunre@gmail.com Date: 19/08/2020                
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Export2SVG_HTML(int **p, int n, int width, int height)
{
  int i; //float stroke_width=1,  stroke_opacity =0.98, float fill_opacity =0.8; 
  FILE *fp = fopen("Sayan.html", "w");
  fprintf(fp, "<!DOCTYPE html>\n<html>\n<body>\n");   //add deader to html
  //add SVG image  canvas
  fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">", 
                width,height,width,height);
  for(i=0; i<n; i++)
  {
   fprintf(fp, "\n<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" style=\"fill:yellow;stroke:red;stroke-width:1.0;fill-opacity:0.8;stroke-opacity:1.0\"/>", p[i][0], p[i][1]);
//fprintf(fp, "\n<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" stroke=\"green\" stroke-width=\"4\" fill=\"yellow\"/>",p[i][0],p[i][1]);
   }
   fprintf(fp, "\n </svg>\n");
   fprintf(fp, "\n</body>\n</html>\n");
   fclose(fp);
   return;
}


void Export2SVG(int **p, int n, int width, int height)
{
  int i;
  //float stroke_width=1;
  //float stroke_opacity =0.98; 
  //float fill_opacity =0.8; 
  FILE *fp = fopen("Sayan.svg", "w");

  //add deader to SVG image  with canvas size 
  fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",
               width,height,width,height);
  for(i=0; i<n; i++)
  {
   fprintf(fp, "\n<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" style=\"fill:yellow;stroke:red;stroke-width:1.0;fill-opacity:0.8;stroke-opacity:1.0\"/>", p[i][0], p[i][1]);
  //fprintf(fp, "\n<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" stroke=\"green\" stroke-width=\"4\" fill=\"yellow\"/>", 
  //               p[i][0], p[i][1]);
 }
  fprintf(fp, "\n </svg>\n");
  fclose(fp);
  return;
}


int main(int argc, char *argv[]){
  int  **p;
  int i, n;
  printf("\nEnter number of points: ");
  scanf("%d",&n);
  p=(int**)malloc(n*sizeof(int*));
  if(!p){printf("\nError: malloc failed for p...\n\n"); return 0;}
  printf("\nEnter the pixel coordinates:\n");
  for(i=0; i<n; i++){
    p[i]=(int*)malloc(2*sizeof(int));
    if(!p[i]){ printf("\n Error: malloc failed for p[%d]...\n\n", i); return 0;}
    scanf("%d%d",&p[i][0],&p[i][1]);
    p[i][0]*=10;      p[i][1]*=10;  // Make 10 unit for lebgth of a side of each  pixel
  }
  //Find the bounding rectangle
  int x1,x2,y1,y2;
  x1=x2=p[0][0];   y1=y2=p[0][1];
  for(i=1; i<n; i++){
    if(x1>p[i][0]) x1=p[i][0];     if(x2<p[i][0]) x2=p[i][0];
    if(y1>p[i][1]) y1=p[i][1];     if(y2<p[i][1]) y2=p[i][1];
  }
  //Determine the canvas dimension with margin :  add margin of 20 unit to all 4 sides
  x1 -=20;    x2 +=20;  y1 -=20;  y2 +=20;
  int height =  y2-y1; // vertically downwars
  int width =   x2-x1; // horizontally toeards right
  for(i=0; i<n; i++){ 
      p[i][0] -= x1;   p[i][1] -= y1; // Shift the points inside the canvas [0, width]x[0,height]
  }
  Export2SVG(p, n, width, height);  
  Export2SVG_HTML(p, n, width, height);
  for(i=0; i<n; i++)  free(p[i]);
  free(p);
  return 1;
}
