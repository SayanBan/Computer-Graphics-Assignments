#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
using namespace std;


typedef float Matrix4 [4][4];

Matrix4 theMatrix;

static GLfloat input[8][3], original[8][3];

float output[8][3];
int tx,ty,tz,sx,sy,sz,angle;


void multiplyM()
{
//We Don't require 4th row and column in scaling and rotation
//[8][3]=[8][3]*[3][3] //4th not used
for(int i=0;i<8;i++)
 {
    for(int j=0;j<3;j++)
    {
        output[i][j]=0;
        for(int k=0;k<3;k++)
        {
            output[i][j]=output[i][j]+input[i][k]*theMatrix[k][j];
        }
    }
}
}

void Export2OBJ()
{
  	FILE *fp = fopen("obj.obj", "w");
  	
	fprintf(fp,"o Mesh\nv %f %f %f\nv %f %f %f\nv %f %f %f\nv %f %f %f\nv %f %f %f\nv %f %f %f\nv %f %f %f\nv %f %f %f\nvn 0 -1 0\nvn 0 1 0\nvn -1 0 0\nvn 1 0 0\nvn 0 0 1\nvn 0 0 -1\nvt 0 0\nvt 1 0\nvt 0 1\nvt 1 1\nf 1 2 3 4\nf 2 1 5 6\nf 3 2 6 7\nf 6 5 8 7\nf 4 3 7 8\nf 4 8 5 1\n",output[0][0],output[0][1],output[0][2],output[1][0],output[1][1],output[1][2],output[2][0],output[2][1],output[2][2],output[3][0],output[3][1],output[3][2],output[4][0],output[4][1],output[4][2],output[5][0],output[5][1],output[5][2],output[6][0],output[6][1],output[6][2],output[7][0],output[7][1],output[7][2],output[8][0],output[8][1],output[8][2]);

	
	
  	printf("obj.obj created successfully!\n");
    fclose(fp);
}

void draw(float a[8][3])
{


    glBegin(GL_QUADS);
     glColor3f(0.0f, 0.0f, 1.0f);//Blue //behind
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);

   glColor3f(1.0f, 0.5f, 0.0f);//Orange  //bottom
   glVertex3fv(a[0]);
   glVertex3fv(a[1]);
   glVertex3fv(a[5]);
   glVertex3fv(a[4]);

   glColor3f(0.5f, 0.5f, 0.5f);//Violet //left
  glVertex3fv(a[0]);
  glVertex3fv(a[4]);
  glVertex3fv(a[7]);
  glVertex3fv(a[3]);

  	glColor3f(0.1f, 0.1f, 0.1f);//Dark grey//right
	glVertex3fv(a[1]);
	glVertex3fv(a[2]);
	glVertex3fv(a[6]);
	glVertex3fv(a[5]);

 	glColor3f(0.0f, 0.5f, 1.0f);//baby Blue //up
	glVertex3fv(a[2]);
	glVertex3fv(a[3]);
	glVertex3fv(a[7]);
	glVertex3fv(a[6]);

	glColor3f(0.5f, 1.0f, 1.0f);//cyan
	glVertex3fv(a[4]);
	glVertex3fv(a[5]);
	glVertex3fv(a[6]);
	glVertex3fv(a[7]);

	glEnd();
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0); 
    glOrtho(-454.0,454.0,-250.0,250.0,-250.0,250.0);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glColor3f(0.0,0.0,0.0);

draw(original);
draw(output);


glFlush();
}
void scale()
{
	printf("Enter scaling factors");
	scanf("%d %d %d", &sx,&sy,&sz);
	theMatrix[0][0]=sx;
    theMatrix[1][1]=sy;
    theMatrix[2][2]=sz;
    multiplyM();
}

void translate()
{
	printf("Enter translation factors");
	scanf("%d %d %d", &tx,&ty,&tz);
	for(int i=0;i<8;i++)
	{
		output[i][0]=input[i][0]+tx;
output[i][1]=input[i][1]+ty;
output[i][2]=input[i][2]+tz;
	}
	
}	

void rotate()
{
	int x1,y1,x2,y2,o;
	printf("Enter rotating angle along x-axis");
	scanf("%d",&angle);

 angle = angle*3.142/180;
  theMatrix[1][1] = cos(angle);
 theMatrix[1][2] = -sin(angle);
 theMatrix[2][1] = sin(angle);
 theMatrix[2][2] = cos(angle);


	
	
	multiplyM();
}		

int main(int argc, char** argv)
{
	float co;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("Enter coordinate ");
			scanf("%f",&co);
			input[i][j]=co;
			original[i][j]=co;
		}
	}
	
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1362,750);
    glutInitWindowPosition(0,0);
    glutCreateWindow("3D TRANSFORMATIONS");
    init();
  
    translate();
	scale();
	rotate();
	Export2OBJ();
	glutDisplayFunc(display);
	
    glutMainLoop();
	return 0;
}
