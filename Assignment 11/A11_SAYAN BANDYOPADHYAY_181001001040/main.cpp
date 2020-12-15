/*
Name - Sayan Bandyopadhyay
Id - 181001001040
Batch - BCS3A
*/

/*
Parameters which are need to be included :
	-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
    */

#include<stdio.h> 
#include<string.h>
#include<graphics.h>
using namespace std; 
  
const int MAX_POINTS = 20; 
int clip_poly_size;

  
// Returns x-value of point of intersectipn of two 
// lines 
int x_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4) 
{ 
    int num = (x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4); 
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4); 
    return num/den; 
} 
  
// Returns y-value of point of intersectipn of 
// two lines 
int y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4) 
{ 
    int num = (x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4); 
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4); 
    return num/den; 
} 
  
// This functions clips all the edges w.r.t one clip 
// edge of clipping area 
void clip(int poly_points[][2], int &poly_size,int x1, int y1, int x2, int y2) 
{ 
    int new_points[MAX_POINTS][2], new_poly_size = 0; 
  
    // (ix,iy),(kx,ky) are the co-ordinate values of 
    // the points 
    for (int i = 0; i < poly_size; i++) 
    { 
        // i and k form a line in polygon 
        int k = (i+1) % poly_size; 
        int ix = poly_points[i][0], iy = poly_points[i][1]; 
        int kx = poly_points[k][0], ky = poly_points[k][1]; 
  
        // Calculating position of first point 
        // w.r.t. clipper line 
        int i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1); 
  
        // Calculating position of second point 
        // w.r.t. clipper line 
        int k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1); 
  
        // Case 1 : When both points are inside 
        if (i_pos < 0  && k_pos < 0) 
        { 
            //Only second point is added 
            new_points[new_poly_size][0] = kx; 
            new_points[new_poly_size][1] = ky; 
            new_poly_size++; 
        } 
  
        // Case 2: When only first point is outside 
        else if (i_pos >= 0  && k_pos < 0) 
        { 
            // Point of intersection with edge 
            // and the second point is added 
            new_points[new_poly_size][0] = x_intersect(x1,y1, x2, y2, ix, iy, kx, ky); 
            new_points[new_poly_size][1] = y_intersect(x1,y1, x2, y2, ix, iy, kx, ky); 
            new_poly_size++; 
  
            new_points[new_poly_size][0] = kx; 
            new_points[new_poly_size][1] = ky; 
            new_poly_size++; 
        } 
  
        // Case 3: When only second point is outside 
        else if (i_pos < 0  && k_pos >= 0) 
        { 
            //Only point of intersection with edge is added 
            new_points[new_poly_size][0] = x_intersect(x1,y1, x2, y2, ix, iy, kx, ky); 
            new_points[new_poly_size][1] = y_intersect(x1,y1, x2, y2, ix, iy, kx, ky); 
            new_poly_size++; 
        } 
  
        // Case 4: When both points are outside 
        else
        { 
            //No points are added 
        } 
    } 
  
    // Copying new points into original array 
    // and changing the no. of vertices 
    poly_size = new_poly_size; 
    for (int i = 0; i < poly_size; i++) 
    { 
        poly_points[i][0] = new_points[i][0]; 
        poly_points[i][1] = new_points[i][1]; 
    } 
} 
  
// Implements Sutherland–Hodgman algorithm 
void suthHodgClip(int poly_points[][2], int poly_size,int clipper_points[][2], int clipper_size) 
{ 
    //i and k are two consecutive indexes 
    for (int i=0; i<clipper_size; i++) 
    { 
        int k = (i+1) % clipper_size; 
  
        // We pass the current array of vertices, it's size 
        // and the end points of the selected clipper line 
        clip(poly_points, poly_size, clipper_points[i][0],clipper_points[i][1], clipper_points[k][0],clipper_points[k][1]); 
    } 
    clip_poly_size=poly_size;
} 
  

//Driver code 
int main() 
{ 
    int a[50],poly_points[20][2];
    int poly_size,xmin,ymin,xmax,ymax; 
    int clipper_size = 4; 

    int clipper_points[4][2]; 
    printf("Enter xmin ymin : ");
    scanf("%d %d",&xmin,&ymin);

    printf("Enter xmax ymax : ");
    scanf("%d %d",&xmax,&ymax);
    
    
        clipper_points[0][0]=xmin;
        clipper_points[0][1]=ymin; 

        clipper_points[1][0]=xmin;
        clipper_points[1][1]=ymax; 

        clipper_points[2][0]=xmax;
        clipper_points[2][1]=ymax; 

        clipper_points[3][0]=xmax;
        clipper_points[3][1]=ymin; 
    

    int npoly,nedge;

    char filename[50];

    printf("Enter the filename from where the coordinates are to be taken ");
    scanf("%s",&filename);

    initwindow(800,600);
    

    FILE* fd= fopen(filename, "r");
    fscanf(fd, "%d", &npoly);
    int p;
    for(int i=0; i<npoly; i++)
    {
        fscanf(fd, "%d", &poly_size);
        p=0;
        for(int j=0; j<poly_size; j++)
        {
            fscanf(fd, "%d", &poly_points[j][0]);
            fscanf(fd, "%d", &poly_points[j][1]); 
            
            a[2*p+0]=poly_points[j][0];
            a[2*p+1]=poly_points[j][1]; 
            p++;
        }

        a[2*p+0]=poly_points[0][0];
        a[2*p+1]=poly_points[0][1];

        setcolor(15);
        drawpoly(poly_size+1,a);
    }
    fclose(fd);
    setcolor(RED);
    rectangle(xmin,ymin,xmax,ymax);

    printf("\n Press Enter to see the clipping window \n");

    getch();    

    //After Clipping

    initwindow(800,800);

    fd= fopen(filename, "r");
    fscanf(fd, "%d", &npoly);
    
    for(int i=0; i<npoly; i++)
    {
        fscanf(fd, "%d", &poly_size);
        p=0;
        for(int j=0; j<poly_size; j++)
        {
            fscanf(fd, "%d", &poly_points[j][0]);
            fscanf(fd, "%d", &poly_points[j][1]); 
            
            a[2*p+0]=poly_points[j][0];
            a[2*p+1]=poly_points[j][1]; 
            p++;
        }

        a[2*p+0]=poly_points[0][0];
        a[2*p+1]=poly_points[0][1];

        if(i==0)
        {
            setcolor(COLOR(255,51,153));
        }
        else if(i==1)
        {
            setcolor(COLOR(153,204,255));
        }
        else if(i==2)
        {
            setcolor(COLOR(204,255,153));
        }

        else if(i==3)
        {
            setcolor(COLOR(255,255,153));
        }

        drawpoly(poly_size+1,a);

        suthHodgClip(poly_points, poly_size, clipper_points,clipper_size); 
    
        p=0;
        for (int k=0; k < clip_poly_size; k++) 
        {
            a[2*p+0]=poly_points[k][0];
            a[2*p+1]=poly_points[k][1]; 
            p++;
        }
        a[2*p+0]=poly_points[0][0];
        a[2*p+1]=poly_points[0][1];

        if(i==0)
        {
            setcolor(COLOR(153,0,76));
        }
        else if(i==1)
        {
            setcolor(COLOR(0,0,204));
        }
        else if(i==2)
        {
            setcolor(COLOR(0,153,0));
        }
        else if(i==3)
        {
            setcolor(COLOR(255,255,0));
        }
        drawpoly(clip_poly_size+1,a);
    }
    fclose(fd);

    setcolor(RED);
    rectangle(xmin,ymin,xmax,ymax);
	
    getch();
    closegraph();
    return 0; 
} 
