//------------------------------------------------------------------
// Demo Program 2 (LineDDA_OpenGL_v1.c): Computer Graphics Lab 
// Author: Piyush K. Bhunre, CSE Dept., TIU, WEst Bengal, INDIA
// email: pkbhunre@gmail.com
// C program to demonstrate  drawing a Line Segment using DDA Algorithm and 
//                           visualizing the pixel set using OpenGL utility
// For Compilation use: cc mainOpenGL.c -lglut -lGLU -lGL -lm
//                  or: gcc mainOpenGL.c -lglut -lGLU -lGL -lm
//                  or: g++ mainOpenGL.c -lglut -lGLU -lGL -lm
// Updated on: 25-08-2020
// Tested on Ubuntu 18.04 LTS and gcc/g++ compiler
// -------------------------------------------------------------------------------
// OpenGL Installation (In UBUNTU)
// With internet connection ON, just execute the following statements in sequence:
// sudo apt-get update
// sudo apt-get install build-essential
// sudo apt-get install freeglut3 freeglut3-dev
// sudo apt-get install libXi-dev
// sudo apt-get install libXmu-dev
//------------------------------------------------------------------

#include<stdio.h> 
#include<GL/glut.h> 
#include<math.h> 
#define pi 3.142857 
#define ROUND(x) ( (int)(x+0.5) )

//Global variables ---- to accessed in OpenGL display function
//Endpoint of a line segments
int p[2] = {-100, -100};
int q[2] = {150, 130};
int n=0;          // number of pixels of DDA Line
int *pixels=NULL; // array of pixels

//This function compute the pixel set for a line segment using DDA algorithm
int *LineDDA(int xa, int ya, int xb, int yb, int *n)
{
   int dx = xb - xa;
   int dy = yb - ya;
   int steps, k,m;
   float xIncr, yIncr, x=xa, y=ya;

   if( abs(dx) > abs(dy) ) steps = abs(dx);
   else steps = abs(dy);
   int *pixels = (int*)malloc(2*(steps+1)*sizeof(int));
   if(!pixels){ printf("\n\nError: malloc failed in LineDDA()...\n\n"); return pixels;}   
   xIncr = dx/(float)steps;
   yIncr = dy/(float)steps;
   m=0;
   pixels[2*m+0]=(int)ROUND(x);
   pixels[2*m+1]=(int)ROUND(y);
   m++;
   for(k=0; k<steps; k++)
   {
        x += xIncr;
        y += yIncr;
        pixels[2*m+0]=(int)ROUND(x);
        pixels[2*m+1]=(int)ROUND(y);
        m++;
   }
   *n=m;
   printf("\nNumber of DDA Line pixels = %d\n", *n);
   return pixels;
}

// function to initialize the OpenGL window
void myInit (void) 
{ 
    // making background color black as first 3 arguments all are 0.0 
    glClearColor(0.0, 0.0, 0.0, 1.0);       
    //making picture color green (in RGB mode), as middle argument is 1.0 
    //glColor3f(0.0, 1.0, 0.0); 
      
    //breadth of picture boundary is 1 pixel 
    glPointSize(2.0); //set pixel size as 2
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
      
    // setting window dimension in X- and Y- direction 
    gluOrtho2D(-780, 780, -420, 420); 
} 

//This a callback function called in the main() before updating the windows.
//So, if you need to show something, insert your code in this function.
//For example, the pixels corresponding to the DDA Line  are drawn.
//The diplay part is taken care off by the OpenGL 
void display (void)  
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
    glPointSize(2.0);
    glBegin(GL_POINTS);   // begining of drawing pixel  on the openGl window
  
    float x, y;
    int i; 
    glColor3f( 1, 1, 1 ); // set pixel color as white
    // Draw DDA Line
    if(pixels)
    for ( i = 1; i < n-1; i++) 
    {
       glVertex2i( (float)pixels[2*i+0], (float)pixels[2*i+1]); 
    }
    glEnd(); // ending of drawing pixel  on the openGl window 
  
    //Draw the end points
    glPointSize(8.0);
    glBegin(GL_POINTS);
    glColor3f( 1, 0, 0 );
      glVertex2i( (float)pixels[0], (float)pixels[1]); 
      glVertex2i( (float)pixels[2*(n-1)+0], (float)pixels[2*(n-1)+1]); 
    glEnd(); 


   //This should called otherwise the openGL window will not be updated
   //Actually this function swap the openGL buffers, otherwise no change will be shown in the window
    glFlush(); 

} 
  
int main (int argc, char** argv) 
{ 
    //Compute the pixel set for the line segment and store in an array
    pixels = LineDDA(p[0], p[1], q[0], q[1], &n);

    //Initialize OpenGL
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(1366, 768); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to the window 
    glutCreateWindow("DDA Line Deawing with OpenGL: PKB"); 
    myInit(); 

    glutDisplayFunc(display); //The call back routine is called here

    glutMainLoop(); //make sure the display routine runs for ever
    
    return 1;
} 
