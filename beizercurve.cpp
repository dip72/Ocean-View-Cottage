#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"

extern int wired=0;

const int dgre=0;
//int ncpt=L+1;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;

const double PI = 3.14159265389;

GLfloat ctrlpoints[87+1][3] =
{
    {9.37, 0.28,0},{8.6, 1.275,0},{ 7.75, 1.8,0},
    { 6.45, 1.925,0},{5.5, 1.85,0},
    {4.35, 1.75,0},{ 3.1, 1.475,0},
    {1.925, 0.8,0},{1.25, 0.075,0},
    ///body 9
     { 0.0, 0.0, 0.0}, { -0.3, 0.5, 0.0},
    { 0.1, 1.7, 0.0},{ 0.5, 1.5, 0.0},
    {1.0, 1.5, 0.0}, {1.4, 1.4, 0.0},
    {1.8, 0.4, 0.0},{2.2, 0.4, 0.0},
    {2.6, 1.5, 0.0}, {3.0, 1.4, 0.0},
    {3.4, 1.4, 0.0},{3.8, 1.4, 0.0},
    {4.2, 1.0, 0.0},{4.6, 1.0, 0.0},
    {5.0, 1.0, 0.0},{5.4, 1.0, 0.0},
    {5.9,1.2, 0.0},{6.5, 1.6, 0.0},
    {6.8, 1.05, 0.0},
    ///coconut 28
   {0,0,0},{0.52381, 0.552381,0},{1.05714, 1.31429,0},
    {1.93333, 1.79048,0},{2.6381 ,1.9619,0},{3.60952, 1.69524,0},
    {3.95238 ,0.971428,0},{4.35238, 0.323809,0},{ 4.33333 ,-0.495238,0},
    {4.04762, -0.8,0},{3.49524, -0.914286,0},
    ///balloon 39
    {-0.0775, 0.34,0}, {-0.0775, 0.41,0}, {-0.14, 0.475, 0},
    {-0.2325, 0.55,0}, {-0.2775, 0.64,0}, {-0.27, 0.7275, 0},
    { -0.24, 0.81,0}, {-0.1725, 0.85,0}, {-0.0775, 0.8875, 0},{ 0.0175, 0.9,0},
   /* {-0.2 ,-0.3875,0}, {-0.115 ,-0.3425,0}, {0.075 ,-0.255 , 0},
    {0.1075 ,-0.12,0}, {  -0.07 ,-0.02 ,0}, {-0.21 ,0.0425 , 0},
    {-0.3075 ,0.1775 ,0}, {-0.3325, 0.3475,0}, {  -0.2525, 0.4625 , 0},
    { -0.115 ,0.53,0},{  0.0875 ,0.5675 ,0},{0.255,0 0.5775,0}*/
    ///49
    { 0.0, 0.0, 0.0},{0.325, 1.575,0},
    { 0.85 ,2.55,0},{1.625 ,2.875,0},
    {2.85, 3.1,0},{ 3.725 ,2.325,0},
    {4.225, 1.3,0},{4.55 ,-0.3,0},
    {4.85 ,0.625,0},{5.5 ,0.55,0},{  5.95, 0.45,0},
    ///surfing board 60
    {8.925 ,0,0},{8.3, .45,0},{  7.6 ,.9,0},
    { 6.5, 1.5,0},{5.5, 1.4,0},
    {4.35, 1.35,0},{ 3.1, .975,0},
    {1.925, 0.8,0},{1.25, 0.75,0},
    ///slide 69
   /*  { 6.5, 1.5,0},{5.5, 1.4,0},
    {4.35, 1.35,0},{ 3.6, -.15,0},
    {2.6, -0.825,0},{0.8 ,-1.525,0},
    {-0.55, -0.525,0},{-1.075, 2.925,0}*/
    {8.75, -4.45,0},{8.75, -3.45,0},{8.75, -2.45,0},
   {8.75, -1.45,0},{8.325 ,-0.325,0},{  7.6 ,.9,0},
    { 6.5, 1.5,0},{5.5, 1.4,0},
    {4.35, 1.35,0},{ 3.6, -.15,0},
    {2.6, -0.825,0},{0.8 ,-1.525,0},
    {-0.55, -0.525,0},{-1.075, 2.925,0},
    {-0.15 ,4.85,0},{ 0.95, 5.8,0},
    { 0.675 ,6.8,0},{-1.075, 6.8,0},{ -2.1, 6.8,0}
};



void drawcube(GLfloat a,GLfloat b,GLfloat c,bool e=false,GLfloat t=1);
void color(GLfloat a,GLfloat b,GLfloat c,bool e=false);

void showControlPoints(GLfloat L,GLfloat st)
{
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = st; i <=L; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
}


void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(-Nx,-Ny,-Nz);
}


//control points
long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve ( double t,  float xy[2],int endd,int start)
{
    double y=0;
    double x=0,y1=0;
    t=t>1.0?1.0:t;
    int L =endd-start;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[start][0];
        y+=coef*ctrlpoints[start][1];
        start++;

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //std::cout<<"xy"<<xy[0]<<" "<<xy[1]<<std::endl;

    //return y;
}


void leafBezier(GLint N)
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[8][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy,8,0);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy,8,0);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= N; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void leaves()
{

    color(	0.133, 0.545, 0.133);
    glPushMatrix();
    glTranslatef(0.87,5.5,-1.4);
    glRotatef(-45,0,0,1);
    glScalef(0.8,0.5,0.5);
    leafBezier(4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.5,-1.4);
    glScalef(0.7,0.5,0.5);
    leafBezier(5);
    glPopMatrix();


glPushMatrix();///4th
glTranslatef(10,5,0);
glRotatef(180,0,1,0);
glRotatef(-45,0,0,1);
glScalef(0.8,0.5,0.5);
leafBezier(4);
glPopMatrix();


glPushMatrix();///5th
glTranslatef(10,.5,0);
glRotatef(180,0,1,0);
//glRotatef(-45,0,0,1);
glScalef(0.6,0.5,0.5);
leafBezier(4);
glPopMatrix();

glPushMatrix();
glTranslatef(5.5,7,-1.5);
glRotatef(-90,0,0,1);
glScalef(0.7,0.5,0.5);
leafBezier(5);
glPopMatrix();


}

void trunkBezier()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 9, endx = ctrlpoints[27][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy,26,8);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy, 26, 8);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= 40; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void tree()
{
    glPushMatrix();
    glTranslatef(7,-1.5,5);
    glRotatef(90,0,01,0);
    //glRotatef(180,0,01,0);
    leaves();
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,-1.5,0);
    leaves();
    glPopMatrix();

    color(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(5.8,0,-0.5);
    glScalef(.5,2,0.5);
    glRotatef(-90,0,0,01);
    trunkBezier();
    glPopMatrix();
}


void lineBezier(int L, int start)
{
    int i, j;
    float x, y, z, r,s,x1,r1;
    float t=0;
    float dt=0.5/80;
    float xy[3];
    BezierCurve( t,  xy,L,start);//9,0
    x = xy[0];
    r = xy[1];


    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < 150; ++i )
    {
      /*  glPointSize(5);
        glBegin( GL_POINTS );
        glVertex2f(x,r);
        glEnd();

        t+=dt;
        BezierCurve( t,  xy,L,start);
        x = xy[0];
    r = xy[1];*/
    t+=dt;
        BezierCurve( t,  xy,L,start);
        x1 = xy[0];
        r1 = xy[1];
        glLineWidth(5);
        glBegin( GL_LINES );
        glVertex2f(x,r);
        glVertex2f(x1,r1);
        glEnd();
        x=x1;
        r=r1;
    }
}

void lineleafBezier()
{
    int i, j;
    float x, y, z, r,s,x1,r1;
    float t=0;
    float dt=0.5/50;
    float xy[3];
    BezierCurve( t,  xy,4,0);
    x = xy[0];
    r = xy[1];


    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < 60; ++i )
    {
        t+=dt;
        BezierCurve( t,  xy,4,0);
         x1 = xy[0];
        r1 = xy[1];
        glLineWidth(3);
        glBegin( GL_LINES );
        glVertex2f(x,r);
        glVertex2f(x1,r1);
        glEnd();
        x=x1;
        r=r1;
        //glLineWidth(4);
        //glBegin( GL_LINES );
     /*   glPointSize(3);
        glBegin( GL_POINTS );
        glVertex2f(x,r);
        //glVertex2f(x1,r1);
        glEnd();*/
        //x=x1;
        //r=r1;


    }
}

void leaf2()
{
    glPushMatrix();
    lineBezier(9,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(03.5,4.75,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(03,5,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(02.5,5.4,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
glPushMatrix();
    glTranslatef(02,5.6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(01.5,6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();

glPushMatrix();
    glTranslatef(01,6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
 glPushMatrix();
    glTranslatef(0.5,6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
 glPushMatrix();
    glTranslatef(-0.5,6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.5,6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,5.8,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.5,5.8,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
///
    glPushMatrix();
    glTranslatef(-3,5.6,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
glPushMatrix();
    glTranslatef(-3.5,5,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4,5,0);
    glRotatef(180,0,0,1);
    glRotatef(130,0,0,01);
    lineleafBezier();
    glPopMatrix();

}

void leavesall()
{
    color(	0.133, 0.545, 0.133);
    glPushMatrix();
    glTranslatef(5,0,0);
    glRotatef(-45,0,0,1);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,0);
    glRotatef(-15,0,0,1);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-1,0);
    glRotatef(15,0,0,1);
    leaf2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,-1,0);
    glRotatef(45,0,0,1);
    leaf2();
    glPopMatrix();
    ///rotate
     glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-45,01,0,0);
    glRotatef(-45,0,0,1);
    leaf2();
    glPopMatrix();
     glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-45,0,01,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();


     glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-105,0,01,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();
     glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(65,01,0,0);
    glRotatef(-165,0,01,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();
     glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-90,0,01,0);
    glRotatef(-165,0,01,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();
     glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-90,0,01,0);
    glRotatef(165,0,01,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(90,0,01,0);
    glRotatef(265,01,0,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();
 glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-215,0,01,0);
    glRotatef(65,0,0,1);
    leaf2();
    glPopMatrix();
glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-215,0,01,0);
    glRotatef(45,0,0,1);
    leaf2();
    glPopMatrix();
///color(1,0,0);
 glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-215,0,01,0);
    glRotatef(25,0,0,1);
    leaf2();
    glPopMatrix();

color(	0.133, 0.545, 0.133);
     glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(-155,0,01,0);
    glRotatef(95,0,0,1);
    leaf2();
    glPopMatrix();


     glPushMatrix();
    glTranslatef(5,0,1);
    glRotatef(-275,0,01,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(5,0,1);
    glRotatef(-330,0,01,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,0);
    glRotatef(-45,0,0,1);
    glRotatef(-330,0,01,0);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,0);
    //glRotatef(95,0,0,1);
    glRotatef(-330,0,01,0);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(45,0,0,1);
    //glRotatef(-155,0,01,0);
    //glRotatef(-95,0,0,1);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,01);
    //glRotatef(45,0,0,1);
    glRotatef(-280,0,01,0);
    glRotatef(95,0,0,1);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,01);
    //glRotatef(45,0,0,1);
    glRotatef(-280,0,01,0);
    glRotatef(45,0,0,1);
    leaf2();
    glPopMatrix();

    color(1,0,0);
    glPushMatrix();
    glTranslatef(5,0,01);
    glRotatef(45,0,0,1);
    //glRotatef(-280,0,01,0);
    //glRotatef(45,0,0,1);
    leaf2();
    glPopMatrix();
}

void tree2()
{
    color(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(5.2,02.5,0.5);
    glScalef(.7,3.5,0.7);
    glRotatef(-90,0,0,01);
    trunkBezier();
    glPopMatrix();

    glPushMatrix();
    leavesall();
    glPopMatrix();


}


void swingBezier(int L, int start)
{
    int i, j;
    float x, y, z, r,s,x1,r1;
    float t=0;
    float dt=0.5/80;
    float xy[3];
    BezierCurve( t,  xy,L,start);//9,0
    x = xy[0];
    r = xy[1];


    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < 100; ++i )
    {
        t+=dt;
        BezierCurve( t,  xy,L,start);
        x1 = xy[0];
        r1 = xy[1];
        glLineWidth(5);
        glBegin( GL_LINES );
        glVertex2f(x,r);
        glVertex2f(x1,r1);
        glEnd();
        x=x1;
        r=r1;

    }
}

void slide()
{
    color(0,1,1);
    float n=0;
for(int k=0;k<15;k++)
{
    glPushMatrix();
    glRotatef(180,0,0,01);
    glScalef(1.5,1,1);
    glTranslatef(-5.5,2,0-n);
    swingBezier(9,0);
    glPopMatrix();
    n+=0.25;
}


}

void cocoBezier(int L, int start)
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;
	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=0.5/80;;
    float xy[2];
    BezierCurve( t,  xy,L,0);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < 26; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy,L,0);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= 40; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}


void coco()
{
    //showControlPoints(28+9,30);
    color(	0.000, 0.502, 0.000);
    glPushMatrix();
    glRotatef( -90, 0.0, 0.0, 1.0);
    //  glPolygonMode( GL_FRONT, GL_LINE ) ;
    //glPolygonMode( GL_BACK, GL_LINE ) ;
    //glTranslatef(0.5,2-n,0);
    //glRotatef(90,01,0,0);
    glScalef(0.5,0.8,1);
    cocoBezier(38,28);
    glPopMatrix();

    color(0.961, 0.871, 0.702);
    glPushMatrix();
    glTranslatef(0,-1.58,0);
    glScalef(1.25,.9,1.6);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob,TRUE);
    gluDisk(ob,0.3,0.77,70,60);
    glEnd();
    glPopMatrix();

    ///umbrella

color(1,0,0);
glPushMatrix();///cone
    glTranslatef(0,-0.1,-0.5);
    glRotatef(-25,01,0,0);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 0.01, 0.7, 0.6, 60, 60);
    glEnd();
    glPopMatrix();
color(0.780, 0.082, 0.522);
glPushMatrix();///rod
    glTranslatef(0,-0.2,-0.5);
    glRotatef(-25,01,0,0);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    obj = gluNewQuadric();
    gluCylinder(obj, 0.06, 0.06, 2.2, 60, 60);
    glEnd();
    glPopMatrix();
}

GLfloat colorpoints[12][3] =
{
    {0.000, 1.000, 0.000},{0.000, 0.502, 0.000},{0.486, 0.988, 0.000},
    {	0.545, 0.000, 0.545},{0.196, 0.804, 0.196},{0.502, 0.502, 0.0},
    {1.000, 0.271, 0.000},{0.541, 0.169, 0.886},{	0.000, 0.000, 0.804},
    {	0.196, 0.804, 0.196},{0.255, 0.412, 0.882},{0.604, 0.804, 0.196}
};
void balloonBezier(int L, int start,int col)
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;
	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=0.5/100;;
    float xy[2];
    BezierCurve( t,  xy,L,0);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    int c=col-1;
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < 36; ++i )  			//step through x
    {

        if(c==col+5) c=col;
        else c++;
        color(colorpoints[c][0],colorpoints[c][2],colorpoints[c][2]);
        //std::cout<<c<<colorpoints[c][0]<<colorpoints[c][2]<<colorpoints[c][2]<<std::endl;
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy,L,0);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= 40; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void balloon(int col)
{
    //showControlPoints(48,40);
    color(	0.000, 0.502, 0.000);
    glPushMatrix();
    glRotatef( 90, 0.0, 0.0, 1.0);
    glScalef(0.5,0.8,1.3);
    balloonBezier(48,39,col);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.1,0);
    glScalef(0.45,0.45,0.45);
    drawcube(1,0,0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.2,0.5,0.3);
    glScalef(0.05,0.7,0.05);
    drawcube(1,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.2,0.5,0.3);
    glScalef(0.05,0.7,0.05);
    drawcube(1,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.2,0.5,-0.3);
    glScalef(0.05,0.7,0.05);
    drawcube(1,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.2,0.5,-0.3);
    glScalef(0.05,0.7,0.05);
    drawcube(1,0,0);
    glPopMatrix();
}


void paraBezier(int l,int s,int col)
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy,l,s);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    int c=col-1;
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        if(c==col+4) c=col;
        else c++;
        color(colorpoints[c][0],colorpoints[c][2],colorpoints[c][2]);
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy,l,s);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= 40; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void para(int col)
{
    color(0,0,1);
    glPushMatrix();
    glTranslatef(0,6.6,0);
    glRotatef(-90,0,0,1);
    paraBezier(59,49,col);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,-0.1,0);
    glScalef(0.4,0.4,0.4);
    drawcube(0.824, 0.412, 0.118);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.2,0.5,0.3);
    glScalef(0.05,0.5,0.05);
    drawcube(0.824, 0.412, 0.118);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.2,0.5,0.3);
    glScalef(0.05,0.5,0.05);
    drawcube(0.824, 0.412, 0.118);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.2,0.5,-0.3);
    glScalef(0.05,0.5,0.05);
    drawcube(0.824, 0.412, 0.118);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.2,0.5,-0.3);
    glScalef(0.05,0.5,0.05);
    drawcube(0.824, 0.412, 0.118);
    glPopMatrix();

}


void pBezier(int l,int s)
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy,l,s);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < 40; ++i )  			//step through x
    {
        if(i<=10) color(1.000, 0.271, 0.000);
        else if(i>10 && i<=20) color(1.000, 0.498, 0.314);
        else if(i>20 && i<=30) color(	1.000, 0.843, 0.000);
        else color(0.941, 0.902, 0.549);

        t+=dt;
        BezierCurve( t,  xy,l,s);
        x1 = xy[0];
        r1 = xy[1];

        glBegin( GL_POLYGON );
        glVertex3f (x, r, 1);
        glVertex3f (x1, r1, 01);
        glVertex3f (x1, -r1, 01);
        glVertex3f (x, -r, 01);
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void surf()
{
    glPushMatrix();
    pBezier(68,60);
    glPopMatrix();
}

void circleBezier(int l,int s)
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;



    float t=0;
    float dt=1.0/450;
    float xy[2];
    BezierCurve( t,  xy,l,s);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < 600; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy,l,s);
        x1 = xy[0];
        r1 = xy[1];

        glPointSize(3);
        glBegin(GL_LINES);
        //for(int l=0;l<1;l=l+0.3){
        for(int k =0;k<50;k=k+3)
        {
            theta =k*3.142/180;
            glVertex3f(x1+1.2*cos(theta),r1+1.2*sin(theta),1);
            glVertex3f(x1+1.2*cos(theta),r1+1.2*sin(theta),3);

        }

        glEnd();
       /* glBegin(GL_LINES);
        for(int k =0;k<50;k=k+3)
        {
            theta =k*3.142/180;
            glVertex3f(x1+1.2*cos(theta),r1+1.2*sin(theta),3);

        }
        glEnd();*/
        x = x1;
        r = r1;
    } //for i

}


void waterslide()
{
    color(0,0,1);
    glPushMatrix();
    //glRotatef( 290, 0.0, 0.0, 1.0);
         //glRotatef(-190,0,01,0);

    circleBezier(87,69);
    glPopMatrix();
}
