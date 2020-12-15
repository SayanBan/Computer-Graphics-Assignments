Name - Sayan Bandyopadhyay
Id - 181001001040
Batch - BCS3A

Sutherland-Hodgman polygon clipping algorithm 
-- C language 

Sutherland-Hodgman polygon clipping algorithm has been implemented in the CPP file "1039.cpp".

The program has been done with the "graphics.h" header file, hence it can be run in Dev c++,Visual Studio Code etc like IDE's.
Parameters which are need to be included :
	-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

Functions used:
int x_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4) 
int y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4) 
void clip(int poly_points[][2], int &poly_size,int x1, int y1, int x2, int y2) 
void suthHodgClip(int poly_points[][2], int poly_size,int clipper_points[][2], int clipper_size) 

Output : There will be two window, one for before clipping and one for after clicking.
	 After seeing the before clipping window then hit enter once for after clipping window. 

Samples input 1:
4
3 40 40 80 60 60 80
4 0 0 100 0 100 100 0 100
4 -20 -20 80 20 70 50 10 20
7 120 40 200 200 120 320 80 280 40 160 120 200 40 80

	Clipping window:
	a) 50 50 100 95

Enter xmin ymin : 50 50
Enter xmax ymax : 100 95
Enter the filename from where the coordinates are to be taken input_1.txt

	b) -10 -20 60 100


Enter xmin ymin : -10 -20
Enter xmax ymax : 60 100
Enter the filename from where the coordinates are to be taken input_1.txt

Sample input 2:
3
3 100 400 200 250 300 200
3 200 120 300 120 250 160
4 300 250 300 450 500 450 500 250

	Clipping window:
	150 100 400 400

Enter xmin ymin : 150 100
Enter xmax ymax : 400 400
Enter the filename from where the coordinates are to be taken input_2.txt