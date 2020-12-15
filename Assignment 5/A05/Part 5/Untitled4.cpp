#include<stdio.h>
#include<graphics.h>
#include<conio.h>
int n=0,size,interior=0,exterior=0;
int x1,y1,x2,y2,x3,y3;
int *pixels=NULL;
static int m=0;
void ExportPixels()
{
	FILE *fp = fopen("Pixels.txt", "w");
    for(int i=0; i<n; i++)
	{
		if(i>0 && i<exterior)
		{
   			fprintf(fp, "%d, %d\n", pixels[2*i+0], pixels[2*i+1]);
   		}
   		else if(i==0)
   		{
   			fprintf(fp,"Exterior Coordinates :\n");
   			fprintf(fp,"Coordinate A ( %d, %d)\n", x1,y1);
   			fprintf(fp,"Coordinate B ( %d, %d)\n", x2,y2);
   			fprintf(fp,"Coordinate C ( %d, %d)\n", x3,y3);
   			fprintf(fp,"Coordinate of Centroid ( %d, %d)\n", (x1+x2+x3)/3,(y1+y2+y3)/3);
   			fprintf(fp,"Number of Exteriror pixels : %d\n",exterior);
   			fprintf(fp, "Coordinates(Including A,B and C also) : \nX, Y\n%d, %d\n",x1,y1);
		}
		else if(i==exterior)
		{
			fprintf(fp,"\nInterior Coordinates :\n");
   			fprintf(fp,"Seed Point ( %d, %d)\n", ((x1+x2+x3)/3)+1,((y1+y2+y3)/3)+1);
   			fprintf(fp,"Number of Interiror pixels : %d\n",interior);
   			fprintf(fp, "Interior Coordinates : \nX, Y\n%d, %d\n",pixels[2*i+0], pixels[2*i+1]);
		}
		else if(i>exterior)
		{
			fprintf(fp, "%d, %d\n", pixels[2*i+0], pixels[2*i+1]);	
		}
	}	
  	fclose(fp);
  	printf("Number of pixels : %d\n",n);
 	printf("Pixels.txt created successfully!\n");
}
void Export2SVG(int width, int height)
{
    int scale = 10;
    int margin = 100;
    int i;
    int a1 = pixels[0], a2 = pixels[0];
    int b1 = pixels[1], b2 = pixels[1];
    for(i=1; i<n; i++)
	{
        if(a1>pixels[2*i+0])
        {
			a1=pixels[2*i+0]; 
		}
        if(a2<pixels[2*i+0])
		{
			a2=pixels[2*i+0];
		}
        if(b1>pixels[2*i+1]) 
		{
			b1=pixels[2*i+1];
		}
        if(b2<pixels[2*i+1])
		{	
			b2=pixels[2*i+1];
		}
    }
    a1 *=scale; a2 *=scale;
    b1 *=scale; b2 *=scale;
  	FILE *fp = fopen("svg.svg", "w");
  	fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",width,height,width,height);
     for(i=0; i<n; i++)
    {
    	if(pixels[2*i+0]==x1 && pixels[2*i+1]==y1)
    	{
    		fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:red;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
    	}
    	else if(pixels[2*i+0]==x2 && pixels[2*i+1]==y2)
    	{
    		fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:blue;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
    	}
    	else if(pixels[2*i+0]==x3 && pixels[2*i+1]==y3)
    	{
    		fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:green;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
    	}
    	else if(i<exterior)
    	{
        	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:#FFD700;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
        }
        else
    	{
        	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:yellow;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
        }
    } 
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:red;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*((x1+x2+x3)/3)-a1+100, scale*((y1+y2+y3)/3)-b1+100, scale, scale);  
  	fclose(fp);
  	printf("svg.svg created successfully!\n");
}
void Export2HTML(int width, int height)
{
  	int scale = 10;
    int margin = 100;
    int i;
    int a1 = pixels[0], a2 = pixels[0];
    int b1 = pixels[1], b2 = pixels[1];
    for(i=1; i<n; i++)
	{
        if(a1>pixels[2*i+0])
        {
			a1=pixels[2*i+0]; 
		}
        if(a2<pixels[2*i+0])
		{
			a2=pixels[2*i+0];
		}
        if(b1>pixels[2*i+1]) 
		{
			b1=pixels[2*i+1];
		}
        if(b2<pixels[2*i+1])
		{	
			b2=pixels[2*i+1];
		}
    }
    a1 *=scale; a2 *=scale;
    b1 *=scale; b2 *=scale;
  	FILE *fp = fopen("html.html", "w");
  	fprintf(fp, "<!DOCTYPE html>\n<html>\n<body>\n"); 
	fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",width,height,width,height);
    for(i=0; i<n; i++)
    {
    	if(pixels[2*i+0]==x1 && pixels[2*i+1]==y1)
    	{
    		fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:red;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
    	}
    	else if(pixels[2*i+0]==x2 && pixels[2*i+1]==y2)
    	{
    		fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:blue;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
    	}
    	else if(pixels[2*i+0]==x3 && pixels[2*i+1]==y3)
    	{
    		fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:green;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
    	}
    	else if(i<exterior)
    	{
        	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:#FFD700;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
        }
        else
    	{
        	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:yellow;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*pixels[2*i+0]-a1+100, scale*pixels[2*i+1]-b1+100, scale, scale);
        }
    } 
	fprintf(fp,"\n<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:red;stroke:black;stroke-width:.30;fill-opacity:0.76;stroke-opacity:0.90\"/>", scale*((x1+x2+x3)/3)-a1+100, scale*((y1+y2+y3)/3)-b1+100, scale, scale);  
    fprintf(fp, "\n </svg>\n");
    fprintf(fp, "\n</body>\n</html>\n");
    fclose(fp);
  	printf("html.html created successfully!\n");
}

void flood(int x, int y, int new_col, int old_col) 
{ 
    if (getpixel(x, y) == old_col)
	{ 
        putpixel(x, y, new_col); 
        
		pixels[2*m+0]=x;
		pixels[2*m+1]=y;
	    m++;	
        flood(x + 1, y, new_col, old_col); 
        
       
        flood(x - 1, y, new_col, old_col); 
        
       
        flood(x, y + 1, new_col, old_col); 
        
        
        flood(x, y - 1, new_col, old_col); 
    } 
}

void lineBres(int xa, int ya, int xb, int yb)
{
    int k,twoDx,twoDy,twoDyMinusDx,dx,dy,p,slope;
    if(xa<xb)
    {
    	dx = xb - xa;
    	if(ya<yb)
    	{
    		dy = yb - ya;
    	}
    	else
    	{
    		dy=ya-yb;
		}
    }
    else
    {
    	dx = xa - xb;
    	if(ya<yb)
    	{
    		dy = yb - ya;
    	}
    	else
    	{
    		dy=ya-yb;
		}
	}
	slope=dy/dx;
	if(slope>=1)
	{
    	p = 2 * dx - dy;
    }
    else
    {
    	p = 2 * dy - dx;
	}
	twoDx = 2 * dx;
    twoDy = 2 * dy;
    twoDyMinusDx = 2*dy-2*dx;
    int x, y;

    if (xa > xb)
    {
	    x = xb;
	    y = yb;
	    xb = xa;
    }
    else
    {
	    x = xa;
	    y = ya;
    }
    if(m==0)
    {
    	pixels = (int*)malloc(60*(size+1)*sizeof(int));
    }
       
    pixels[2*m+0]=x;
    pixels[2*m+1]=y;
   
    m++;
    if(slope<1)
    {
	    for (k = 0; k <= dx-1; k++)
	    {
		    x++;
		    if (p < 0)
		        p = p + twoDy;
		    else
		    {
		        y++;
		        p = p + twoDyMinusDx;
		    }
	        
	        pixels[2*m+0]=x;
		    pixels[2*m+1]=y;
	        m++;
	    }
	}
	else
	{
		for (k = 0; k <= dy-1; k++)
	    {
		    y++;
		    if (p < 0)
		        p = p + twoDx;
		    else
		    {
		        x++;
		        p = p + twoDyMinusDx;
		    }
	        
	        pixels[2*m+0]=x;
		    pixels[2*m+1]=y;
	        m++;
	    }
	}
    n=m;
        
}

void display()
{
    for(int i=0;i<n;i++)
    {
    	if(pixels[2*i+0]==x1 && pixels[2*i+1]==y1)
    	{
    		putpixel(pixels[2*i+0],pixels[2*i+1],4);
		}
		else if(pixels[2*i+0]==x2 && pixels[2*i+1]==y2)
    	{
    		putpixel(pixels[2*i+0],pixels[2*i+1],1);
		}
		else if(pixels[2*i+0]==x3 && pixels[2*i+1]==y3)
    	{
    		putpixel(pixels[2*i+0],pixels[2*i+1],2);
		}
		else
		{
        	putpixel(pixels[2*i+0],pixels[2*i+1],14);
        }
    }
    putpixel((x1+x2+x3)/3,(y1+y2+y3)/3,4);
    printf("Done...\n");
}
int makepositive(int x)
{
	if(x<0)
	{
		x=x*(-1);
	}
	return x;
}
int main()
{

    int gd=DETECT,gm;
    
    printf("Enter the A coordinates: ");
    scanf("%d%d",&x1,&y1);
    printf("Enter the B coordinates: ");
    scanf("%d%d",&x2,&y2);
    printf("Enter the C coordinates: ");
    scanf("%d%d",&x3,&y3);
	int a1,b1,c1,a2,b2,c2;
	a1=x2-x1;
	b1=x3-x2;
	c1=x3-x1;
	a2=y2-y1;
	b2=y3-y2;
	c2=y3-y1;
	
	a1=makepositive(a1);
	b1=makepositive(b1);
	c1=makepositive(c1);
	a2=makepositive(a2);
	b2=makepositive(b2);
	c2=makepositive(c2);
	
    if(a1>=a2 && b1>=b2 && c1>=c2)
    {
    	if(x1>x2 && x2>x3)
    	{
	    	size=x3;
	    }
	    else if(x2>x1 && x2>x3)
	    {
	    	size=x2;
		}
		else
		{
			size=x3;
		}
    	initgraph(&gd,&gm,NULL);
    	lineBres(x1,y1,x2,y2);
	    lineBres(x2,y2,x3,y3);	    
	    lineBres(x1,y1,x3,y3);
	    exterior=n;
	    display();	    
		flood(((x1+x2+x3)/3)+1,((y1+y2+y3)/3)+1,3,0);
		n=m;
		interior=m-exterior;
		ExportPixels();    
    	Export2HTML(5000,5000);
		Export2SVG(5000,5000);
		
    	getch();
    }
    else
    {
    	printf("Wrong coordinates.");
	}
    return 0;
}
