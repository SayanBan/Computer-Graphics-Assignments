//Coded by Sayan Bandyopadhyay - 181001001040
#include<stdio.h>
#include<graphics.h>
#include<math.h>

int a[20][2]; //array for storing input coords

void rotate(int n, int p, int q)
{
    double angle, c, s;
    printf("Enter rotation angle: ");  
    scanf("%lf", &angle);
    c = cos(angle*3.14/180);
    s = sin(angle*3.14/180);

    //use   x'= xp+ (x-xp)cos - (y-yp)sin
    //      y'= yp+ (x-xp)sin + (y-yp)cos

    for(int i=0; i<=n; i++)
    {
        a[i][0] =   floor(p + (a[i][0]-p) * c - (a[i][1]-q) * s);
        a[i][1] =   floor(q + (a[i][0]-p) * s + (a[i][1]-q) * c);
    }
    setcolor(RED);
    //drawpoly(n+1, *a);

}

void scale(int n)
{
    int s;
    printf("Enter scaling factor: ");
    scanf("%d", &s);

    for(int i=0; i<=n; i++)
    {
        a[i][0] =   a[i][0]*s;
        a[i][1] =   a[i][1]*s;
    }
    //drawpoly(n+1, *a);
}

void translate(int n, int p, int q)
{
    int tx, ty;
    printf("Enter coordinate to shift to: ");
    scanf("%d %d", &tx, &ty);
    setfillstyle(SOLID_FILL, 5);

    printf("Original Centroid: %d, %d\n", p, q);
    printf("Shifted Centroid: %d, %d\n", tx, ty);

    int xdist = abs(tx-p);
    int ydist = abs(ty-q);
    if(tx>p && ty>q)
    {
        //shifting done here
        for(int i=0; i<=n; i++)
        {
            a[i][0] =   a[i][0] + xdist;
            a[i][1] =   a[i][1] + ydist;
        }
    }
    else if(tx<p && ty>q)
    {
        //shifting done here
        for(int i=0; i<=n; i++)
        {
            a[i][0] =   (a[i][0] - xdist);
            a[i][1] =   a[i][1] + ydist;
        }
    }
    else if(tx>p && ty<q)
    {
        //shifting done here
        for(int i=0; i<=n; i++)
        {
            a[i][0] =   a[i][0] + xdist;
            a[i][1] =   (a[i][1] - ydist);
        }
    }
    else if(tx<p && ty<q)
    {
        //shifting done here
        for(int i=0; i<=n; i++)
        {
            a[i][0] =   (a[i][0] - xdist);
            a[i][1] =   (a[i][1] - ydist);
        }
    }
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillpoly(n+1, *a);
    setcolor(WHITE);
    circle(tx, ty, 2);
}

int main()
{
	int n,i;
	//
	
	printf("\tEnter the no. of edges of polygon : ");
	scanf("%d",&n);
	printf("\n\tEnter the cordinates of polygon :\n ");
	for(i=0;i<n;i++)
	{
    	printf("\tX%d Y%d : ",i,i);
    	scanf("%d %d",&a[i][0],&a[i][1]);
	}
    a[n][0]=a[0][0];
    a[n][1]=a[0][1]; //set the last x and y coords as 1st input
	
    //code to init a window and draw the polygon
    int wid1 = initwindow(1000,1000);
	setcurrentwindow(wid1);
    
    //Original Polygon drawn here:-
    setlinestyle(SOLID_LINE, 1, 3);
    setcolor(GREEN);
    drawpoly(n+1, *a); //n+1 because last vertex = intial vertex (a[n][0], a[n][1])
    
    //Code snippet for finding out center of polygon:-
    int p=0, q=0;
	for(i=0;i<n;i++)
	{	
		p = p + a[i][0];
		q = q + a[i][1];
	}
    
    //ROTATION DONE HERE:-
    rotate(n, p/n, q/n); // p/n, q/n is the center 
    
    //SCALING DONE HERE:-
    scale(n);
    
    //TRANSLATION DONE HERE:-
      //Centroid shifted due to scaling, recalculating centroid:
	p=0, q=0;
    for(i=0;i<n;i++)
	{	
		p = p + a[i][0];
		q = q + a[i][1];
	}
    translate(n, p/n, q/n);

    getch();
    return 0;
}
