/*
Name - Sayan Bandyopadhyay
ID - 181001001040
Batch - BCS3A
*/

//National flag

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<Math.h>
void Export2SVG(int width, int height)
{
  	FILE *fp = fopen("1040.svg", "w");
  	fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",width,height,width,height);
  	
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(253,153,51);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 400, 100, 1200, 200);
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(253,255,255);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 400, 300, 1200, 200);
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(18,136,7);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 400, 500, 1200, 200);
    fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(211,211,211);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 360, 60, 20, 690);
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(211,211,211);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 320, 750, 100, 50);	
    fprintf(fp,"\n<line style=\"stroke:black;stroke-width:2\" x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"></line>",380,60,400,100);
	fprintf(fp,"\n<line style=\"stroke:black;stroke-width:2\" x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"></line>",380,750,400,700);	
	fprintf(fp,"\n<circle style=\"stroke:RGB(0,0,136);stroke-width:2\" r=\"80\" cx=\"900\" cy=\"400\"></circle>");
    int x,y,a=900,b=400,r=80;
	float PI=3.14;
	
	
	for(int i=0;i<=360;i=i+15)
	{
		x=r*cos(i*PI/180);
		y=r*sin(i*PI/180);
		fprintf(fp,"\n<line style=\"stroke:RGB(0,0,136);stroke-width:2\" x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"></line>",a,b,a+x,b-y);
	}
	
  	printf("1040.svg created successfully!\n");
  	fprintf(fp, "\n </svg>\n");
    fclose(fp);
}

void Export2HTML(int width, int height)
{
  	
  	FILE *fp = fopen("1040.html", "w");
  	fprintf(fp, "<!DOCTYPE html>\n<html>\n<body>\n"); 
	fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",width,height,width,height);
  	
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(253,153,51);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 400, 100, 1200, 200);
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(253,255,255);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 400, 300, 1200, 200);
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(18,136,7);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 400, 500, 1200, 200);
    fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(211,211,211);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 360, 60, 20, 690);
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:RGB(211,211,211);stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", 320, 750, 100, 50);	
    fprintf(fp,"\n<line style=\"stroke:black;stroke-width:2\" x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"></line>",380,60,400,100);
	fprintf(fp,"\n<line style=\"stroke:black;stroke-width:2\" x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"></line>",380,750,400,700);	
    fprintf(fp,"\n<circle style=\"stroke:RGB(0,0,136);stroke-width:2\" r=\"80\" cx=\"900\" cy=\"400\"></circle>");
    int x,y,a=900,b=400,r=80;
	float PI=3.14;
	
	
	for(int i=0;i<=360;i=i+15)
	{
		x=r*cos(i*PI/180);
		y=r*sin(i*PI/180);
		fprintf(fp,"\n<line style=\"stroke:RGB(0,0,136);stroke-width:2\" x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"></line>",a,b,a+x,b-y);
	}
	
    fprintf(fp, "\n </svg>\n");
    fprintf(fp, "\n</body>\n</html>\n");
    fclose(fp);
  	printf("1040.html created successfully!\n");
}


int main()
{
	initwindow(1400,1200);
	
	//Flag Top Part
	rectangle(400,100,1200,300);
	
	//Flag Middle Part
	rectangle(400,300,1200,500);
	
	//Flag Bottom Part
	rectangle(400,500,1200,700);
	
	//Coloring the Flag
	setfillstyle(SOLID_FILL,COLOR(253,153,51));
	floodfill(401,101,15);
	
	setfillstyle(SOLID_FILL,COLOR(253,255,255));
	floodfill(401,301,15);
	
	setfillstyle(SOLID_FILL,COLOR(18,136,7));
	floodfill(401,501,15);
	
	//Ashok Chakra
	setcolor(COLOR(0,0,136));
	circle(800,400,80);
	
	//Spokes
	int x,y,a=800,b=400,r=80;
	float PI=3.14;
	
	
	for(int i=0;i<=360;i=i+15)
	{
		x=r*cos(i*PI/180);
		y=r*sin(i*PI/180);
		line(a,b,a+x,b-y);
	}
	
	setcolor(15);
	//Stick
	rectangle(360,60,380,750);
	
	setfillstyle(SOLID_FILL,7);
	floodfill(361,61,15);
	
	//Base
	rectangle(320,750,420,800);
	
	setfillstyle(SOLID_FILL,7);
	floodfill(321,751,15);
	
	//Flag holding rope
	line(380,60,400,100);
	line(380,750,400,700);
	
	Export2SVG(1400,1000);
	Export2HTML(1400,1000);
	
	getch();
	closegraph();
	return 0;
}
