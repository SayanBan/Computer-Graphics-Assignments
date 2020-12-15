
/*
Parameters which are need to be included :
	-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
*/

#include <stdio.h> 
#include<Math.h>
#include <graphics.h> 
using namespace std; 
  
// Global Variables 
int xmin, xmax, ymin, ymax; 
static int count=0;
  
// Lines where co-ordinates are (x1, y1) and (x2, y2) 
struct lines { 
    int x1, y1, x2, y2; 
}; 
  
// This will return the sign required. 
int sign(int x) 
{ 
    if (x > 0) 
        return 1; 
    else
        return 0; 
} 
  
// CohenSutherLand LineClipping Algorith As Described in theory. 
// This will clip the lines as per window boundries. 
void clip(struct lines mylines) 
{ 
    // arrays will store bits 
    // Here bits impiles initial Point whereas bite implies end points 
    int bits[4], bite[4], i, var; 
    
  
    // Finding Bits 
    bits[0] = sign(xmin - mylines.x1); 
    bite[0] = sign(xmin - mylines.x2); 
    bits[1] = sign(mylines.x1 - xmax); 
    bite[1] = sign(mylines.x2 - xmax); 
    bits[2] = sign(ymin - mylines.y1); 
    bite[2] = sign(ymin - mylines.y2); 
    bits[3] = sign(mylines.y1 - ymax); 
    bite[3] = sign(mylines.y2 - ymax); 
  
    // initial will used for initial coordinates and end for final 
    string initial = "", end = "", temp = ""; 
  
    // convert bits to string 
    for (i = 0; i < 4; i++) { 
        if (bits[i] == 0) 
            initial += '0'; 
        else
            initial += '1'; 
    } 
    for (i = 0; i < 4; i++) { 
        if (bite[i] == 0) 
            end += '0'; 
        else
            end += '1'; 
    } 
  
    // finding slope of line y=mx+c as (y-y1)=m(x-x1)+c 
    // where m is slope m=dy/dx; 
  
    float m = (mylines.y2 - mylines.y1) / (float)(mylines.x2 - mylines.x1); 
    float c = mylines.y1 - m * mylines.x1; 

	// setting color of graphics to be WHITE 
    setcolor(YELLOW); 
  
    // if both points are inside the Accept the line and draw 
    if (initial == end && end == "0000") { 
        // inbuild function to draw the line from(x1, y1) to (x2, y2) 
        line(mylines.x1, mylines.y1, mylines.x2, mylines.y2); 
        return; 
    } 
  
    // this will contain cases where line maybe totally outside for partially inside 
    else
	{ 
        // taking bitwise end of every value 
        for (i = 0; i < 4; i++) 
		{   
            int val = (bits[i] & bite[i]); 
            if (val == 0) 
                temp += '0'; 
            else
                temp += '1'; 
        } 
        // as per algo if AND is not 0000 means line is completely outside hence draw nothing and retrurn 
        if (temp != "0000") 
		{
			printf("Line %d Completly outside.\n",count);
            return; 
		}
  
        // Here contain cases of partial inside or outside 
        // So check for every boundary one by one 
        for (i = 0; i < 4; i++) 
		{ 
            // if boths bit are same hence we cannot find any intersection with boundary so continue 
            if (bits[i] == bite[i]) 
                continue; 
            // Otherwise there exist a intersection 
  
            // Case when initial point is in left xmin 
            if (i == 0 && bits[i] == 1) 
			{ 
                var = round(m * xmin + c); 
                mylines.y1 = var; 
                mylines.x1 = xmin; 
            } 
            // Case when final point is in left xmin 
            if (i == 0 && bite[i] == 1) 
			{ 
                var = round(m * xmin + c); 
                mylines.y2 = var; 
                mylines.x2 = xmin; 
            } 
            // Case when initial point is in right of xmax 
            if (i == 1 && bits[i] == 1) 
			{ 
                var = round(m * xmax + c); 
                mylines.y1 = var; 
                mylines.x1 = xmax; 
            } 
            // Case when final point is in right of xmax 
            if (i == 1 && bite[i] == 1) 
			{ 
                var = round(m * xmax + c); 
                mylines.y2 = var; 
                mylines.x2 = xmax; 
            } 
            // Case when initial point is in top of ymin 
            if (i == 2 && bits[i] == 1) 
			{ 
                var = round((float)(ymin - c) / m); 
                mylines.y1 = ymin; 
                mylines.x1 = var; 
            } 
            // Case when final point is in top of ymin 
            if (i == 2 && bite[i] == 1) 
			{ 
                var = round((float)(ymin - c) / m); 
                mylines.y2 = ymin; 
                mylines.x2 = var; 
            } 
            // Case when initial point is in bottom of ymax 
            if (i == 3 && bits[i] == 1) 
			{ 
                var = round((float)(ymax - c) / m); 
                mylines.y1 = ymax; 
                mylines.x1 = var; 
            } 
            // Case when final point is in bottom of ymax 
            if (i == 3 && bite[i] == 1) 
			{ 
                var = round((float)(ymax - c) / m); 
                mylines.y2 = ymax; 
                mylines.x2 = var; 
            } 
            // Updating Bits at every point 
            bits[0] = sign(xmin - mylines.x1); 
            bite[0] = sign(xmin - mylines.x2); 
            bits[1] = sign(mylines.x1 - xmax); 
            bite[1] = sign(mylines.x2 - xmax); 
            bits[2] = sign(ymin - mylines.y1); 
            bite[2] = sign(ymin - mylines.y2); 
            bits[3] = sign(mylines.y1 - ymax); 
            bite[3] = sign(mylines.y2 - ymax); 
        } // end of for loop 
        // Inialize initial and end to NULL 
        initial = "", end = ""; 
        // Updating strings again by bit 
        for (i = 0; i < 4; i++) 
		{ 
            if (bits[i] == 0) 
                initial += '0'; 
            else
                initial += '1'; 
        } 
        for (i = 0; i < 4; i++) 
		{ 
            if (bite[i] == 0) 
                end += '0'; 
            else
                end += '1'; 
        } 
        // If now both points lie inside or on boundary then simply draw the updated line 
        if (initial == end && end == "0000") 
		{ 
            line(mylines.x1, mylines.y1, mylines.x2, mylines.y2); 
            return; 
        } 
        // else line was completely outside hence rejected 
        else
		{
			printf("Line %d Completly outside.\n",count);
            return; 
		}
    } 
} 
  
// Driver Function 
int main() 
{ 
    // Setting values of Clipping window 
  /*  xmin = 400; 
    xmax = 1000; 
    ymin = 100; 
    ymax = 300;*/

	int n;
	printf("Enter the clipping window coordinates\n");
	printf("Enter xmin xmax ");
	scanf("%d %d",&xmin,&xmax);
	printf("Enter ymin ymax ");
	scanf("%d %d",&ymin,&ymax);
	printf("Enter the number of lines to be drawn ");
	scanf("%d",&n);

	struct lines mylines[n]; 

	for (int i = 0; i < n; i++) 
	{ 
		printf("Enter the coordinates for line %d \n",(i+1));
		printf("Enter x1 and y1 ");
		scanf("%d %d",&mylines[i].x1,&mylines[i].y1);
		printf("Enter x2 and y2 ");
		scanf("%d %d",&mylines[i].x2,&mylines[i].y2);
	}
  
    initwindow(1400,1200);
	
	setcolor(RED);
	rectangle(xmin,ymin,xmax,ymax);

    setcolor(GREEN);
    for (int i = 0; i < n; i++) 
	{ 
        line(mylines[i].x1, mylines[i].y1,mylines[i].x2, mylines[i].y2); 
    } 
    for (int i = 0; i < n; i++) 
	{ 
		count=count+1;
        clip(mylines[i]); 
    }  
    getch(); 
    closegraph(); 
    return 0; 
} 
