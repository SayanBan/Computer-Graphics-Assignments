//Sayan Bandyopadhyay
// 181001001040 - BCS3A
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ncolor;
int color[20][4];

void read_offcolor()
{
    printf("Color is being read shhhh\n");
    FILE *fc = fopen("offcolor.mtl", "r");

    fscanf(fc, "%d", &ncolor); //Scans "OFF"
    //printf("%d\n", ncolor);
    for(int i=0;i<ncolor;i++)
    {
        fscanf(fc, "%d", &color[i][0]);
        fscanf(fc, "%d", &color[i][1]);
        fscanf(fc, "%d", &color[i][2]);
        fscanf(fc, "%d", &color[i][3]);
    }
    /*
    for(int i=0;i<ncolor;i++)
    {   
        printf("%d %d %d %d\n", color[i][0], color[i][1], color[i][2], color[i][3]);
    }
    */
    fclose(fc);
}

int vertex_count=0, face_count=0, edge_count=0, a;
double v[50000][3], f[50000][4], e[50000][3]; //v holds vertex, f holds face, e holds edges
char c[10]; //Holds "OFF"

int ExportToOFF(double v[8][3], double f[6][4])
{
    FILE *fp = fopen("outputOFF.off", "w");
    fprintf(fp, "OFF\n%d %d %d", vertex_count, face_count, edge_count );
    
    //For Vertices
    for(int i=0; i<vertex_count; i++)
    {
        fprintf(fp, "\n %0.7lf %0.7lf %0.7lf", v[i][0], v[i][1], v[i][2]);
    }
    
    //For Faces, with color information
    int j=0;            //marker for color start (denotes array index 0)
    for(int i=0; i<face_count; i++)
    {
        if(j==ncolor)    //marker for total number of colors used (stored in array)
            j=0;
        fprintf(fp, "\n %0.1lf %0.1lf %0.1lf %0.1lf %d %d %d %d", f[i][0], f[i][1], f[i][2], f[i][3], color[j][0], color[j][1], color[j][2], color[j][3]);
        j++;
    }

    //For edges
    for(int i=0; i<edge_count; i++)
    {
        fprintf(fp, "\n %0.7lf %0.7lf %0.7lf", e[i][0], e[i][1], e[i][2]);
    }
    printf("OFF File exported successfully!\n");
}

void readOFF()
{
    printf("File is being read\n");
    FILE* fd= fopen("inputOFF.off", "r");
    fscanf(fd, "%[^\n]", c); //Scans "OFF"
    //printf("%s", c);
    fscanf(fd, "%d", &vertex_count);
    fscanf(fd, "%d", &face_count);
    fscanf(fd, "%d", &edge_count);
    //printf("\n%d %d %d\n", vertex_count, face_count, edge_count);
    for(int i=0; i<vertex_count; i++)
    {
        fscanf(fd, "%lf", &v[i][0]);
        fscanf(fd, "%lf", &v[i][1]);
        fscanf(fd, "%lf", &v[i][2]);
    }

    for(int i=0; i<face_count; i++)
    {
        fscanf(fd, "%lf", &f[i][0]);
        fscanf(fd, "%lf", &f[i][1]);
        fscanf(fd, "%lf", &f[i][2]);
        fscanf(fd, "%lf", &f[i][3]);
    }

    for(int i=0; i<edge_count; i++)
    {
        fscanf(fd, "%lf", &e[i][0]);
        fscanf(fd, "%lf", &e[i][1]);
        fscanf(fd, "%lf", &e[i][2]);
    }
    //Debug printf statement:-
    /*
    for(int i=0; i<vertex_count; i++)
    {
        printf("%0.7lf %0.7lf %0.7lf\n", v[i][0], v[i][1], v[i][2]);
    }

    for(int i=0; i<face_count; i++)
    {
        printf("%0.1lf %0.1lf %0.1lf %0.1lf\n", f[i][0], f[i][1], f[i][2], f[i][3]);
    }
    */
    ExportToOFF(v, f);
    fclose(fd);
}


//CODE FOR OBJ FILE:-
double v2[10000][3];
int f2[10000][3], vertex_count2, face_count2, ncolor_obj;
char c2, color2[20][10], colortrash[50];

int read_objcolor()
{
    printf("Color is being read shhhh\n");
    FILE *fc = fopen("objcolor.mtl", "r");

    int eof=0;
    for(int i=0; i<100; i++)
    {
        fscanf(fc, "%s", &colortrash); //Scans "newmtl"
        fscanf(fc, "%s\n", &color2[i]);
        ncolor_obj++;

        for(int j=0; j<16; j++)
        {
            fscanf(fc, "%s", &colortrash);
        }

        eof = fgetc(fc);
        if(eof == EOF)
            break;
    }
    ncolor_obj-=1;
    printf("%d colors:\n", ncolor_obj);

    for(int i=0; i<20; i++)
    {
        printf("%s\n", color2[i]);
    }

    fclose(fc);
}

int ExportToOBJ()
{
    FILE *fp = fopen("outputOBJ.obj", "w");
    //fprintf(fp, "OFF\n%d %d %d", vertex_count2, face_count2);

    fprintf(fp, "mtllib objcolor.mtl\n");

    //For Vertices
    for(int i=0; i<vertex_count2; i++)
    {
        fprintf(fp, "v %0.7lf %0.7lf %0.7lf\n", v2[i][0], v2[i][1], v2[i][2]);
    }
    
    int j=0;
    for(int i=0; i<face_count2; i++)
    {

        if(j==ncolor_obj) //no. of colours to be repeated
            j=0;

        fprintf(fp, "usemtl %s\n", color2[j]);
        j++;
        
        fprintf(fp, "f %d %d %d\n", f2[i][0], f2[i][1], f2[i][2]);
    }

    printf("OBJ File exported successfully!\n");
    fclose(fp);
}


void readOBJ()
{
    printf("File is being read\n");
    FILE* fd2= fopen("inputOBJ.obj", "r");
    fscanf(fd2, "%d", &vertex_count2);
    fscanf(fd2, "%d", &face_count2);
    printf("%d %d\n", vertex_count2, face_count2);
    
    for(int i=0; i<vertex_count2; i++)
    {
        fscanf(fd2, "\n%c", &c2);

        //printf("Loop %d, char: %c\n", i+1, c2);
        fscanf(fd2, "%lf", &v2[i][0]);
        fscanf(fd2, "%lf", &v2[i][1]);
        fscanf(fd2, "%lf", &v2[i][2]);
    }

    for(int i=0; i<face_count2; i++)
    {
        fscanf(fd2, "\n%c", &c2);
        fscanf(fd2, "%d", &f2[i][0]);
        fscanf(fd2, "%d", &f2[i][1]);
        fscanf(fd2, "%d", &f2[i][2]);
    }

    //Debug printf statement:-
    /*
    for(int i=0; i<vertex_count2; i++)
    {
        printf("v %0.7lf %0.7lf %0.7lf\n", v2[i][0], v2[i][1], v2[i][2]);
    }

    for(int i=0; i<face_count2; i++)
    {
        printf("f %d %d %d\n", f2[i][0], f2[i][1], f2[i][2]);
    }
    */
    ExportToOBJ();
    fclose(fd2);
}

int main()
{
    read_offcolor();    //reads color from color.mtl file
    readOFF();     //reads a triangle mesh from input.off
    
    read_objcolor();
    readOBJ();
}
