#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"

#define sqr(x) ((x)*(x))
using namespace std;
GLfloat a=0.3,t=0,turn1=0,p=0;
GLfloat dx=10.0,dz=0,dy = -8.0;
GLdouble modelviewMatrix[16];
bool b=false,turn=false,open=false,op=false,op2=false,op3=false,op4=false,hou=false,pr=true,p1=false;
GLdouble px=0,py=0,pz=100,refx=0,refy=0,refz=-60;
double windowHeight=1000, windowWidth=800;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0,mov=0,mov2=0,mov3=0,mov4=0,m1=0,m2=0,m3=0,m4=0;
float temp=0,openn=0;
bool light0 = true,light1=false, light2 =false,light3 =false,light4=false,light5=false,light6=false,light7=false,off=false;
bool a1=true,s1=true,d1=true, a2=true,s2=true,d2=true,a3=true,s3=true,d3=true,e3=false,e2=false,e1=false,e4=false,e5=false,e6=false,e7=false;
GLboolean bRotate = false, aRotate = false,boatmov=false;
unsigned int ID[40];
map<string, unsigned int> tex;

void swingBezier(int L, int start);
void para(int col);
void tree2();
void swing();
void slide();
void coco();
void balloon(int col);
void surf();
void waterslide();

GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info
void scsToWcs(float sx,float sy, float wcsv[3] );
void processMouse(int button, int state, int x, int y);
void showControlPoints(GLfloat L);

int clikd=0;
double ex=0, ey=0, ez=15, lx=0,ly=0,lz=0, hx=0,hy=1,hz=0;

int flag=0;
float wcsClkDn[3],wcsClkUp[3];
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
} clkpt[2];

void scsToWcs(float sx,float sy, float wcsv[3] )
{

    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    //glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = sx;
    winY = (float)viewport[3] - (float)sy;
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    wcsv[0]=worldX;
    wcsv[1]=worldY;
    wcsv[2]=worldZ;


}
void processMouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(flag!=1)
        {
            flag=1;
            clkpt[0].x=x;
            clkpt[0].y=y;
        }


        scsToWcs(clkpt[0].x,clkpt[0].y,wcsClkDn);
        std::cout<<"\nD: "<<x<<" "<<y<<" wcs: "<<wcsClkDn[0]<<" "<<wcsClkDn[1];
    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (flag==1)
        {
            clkpt[1].x=x;
            clkpt[1].y=y;
            flag=0;
        }
        float wcs[3];
        scsToWcs(clkpt[1].x,clkpt[1].y,wcsClkUp);
        std::cout<<"\nU: "<<x<<" "<<y<<" wcs: "<<wcsClkUp[0]<<" "<<wcsClkUp[1];

        clikd=!clikd;
    }
}


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //
}

GLfloat A[1][4],B[1][4],output[1][4];

static GLfloat colors[5][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0}
};

static GLfloat v_pyramid[8][3] =
{
    {-1.0,-1.0,1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},
    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {-1.0, 1.0, -1.0}
};

static GLubyte quadIndices[6][4] =
{
    {0,1,2,3},
    {0,4,5,1},
    {1,5,6,2},
    {0,3,7,4},
    {4,7,6,5},
    {3,2,6,7}

};

static GLfloat v_triangle[6][3] =
{
    {0,0,0},//0
    {2,0,0},//1
    {2,2,0},//2
    {0,0,2},//3
    {2,0,2},//4
    {2,2,2}//5
};
static GLfloat v_triangle2[6][3] =
{
    {0,0,0},//0
    {1,1,0},//1
    {2,2,0},//2
    {0,0,2},//3
    {1,2,2},//4
    {2,2,2}//5
};
static GLubyte p_Indices[2][3] =
{
  //  {0,1,2},
 //   {5,4,3}
        {3,4,5},
      {0,2,1}
};

static GLubyte q_Indices[3][4] =
{
    {1,2,4,5},
    {0,1,4,3},
    {0,2,5,3}
};



static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
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

    glNormal3f(Nx,Ny,Nz);
}

void light()
{
    //GLfloat light_ambient[4];
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat light_ambient[]  = {0.7, 0.7, 0.7, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffusenight[]  = {0.2,0.2,0.2, 1.0 };
    GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_position[] = { -70,49,22.5,41.0 ,1};//-70,9,-22.5
glEnable( GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);///position
   if(a1 ) {
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);}///ambient
    else {glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);}

    if(d1){
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);}///diffuse
    else {glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);}

    if(s1){
    glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);}///specular
    else {glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);}
    if(light0){ glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  }///LIGHT0
    else{  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);  }
    if(off) {glDisable(GL_LIGHT0);}



///BEDROOM LIGHT

    GLfloat light_ambient1[]  = {1,1,1, 1.0};
    GLfloat light_diffuse1[]  = { 1.0, 01.0, 01.0, 1.0 };
    GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position1[] = {30,9,-22.52, 1.0 };


    glLightfv( GL_LIGHT1, GL_POSITION, light_position1);///position
    if(a1) {glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient1);}///ambient
    else {glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);}

    if(d1){ glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);}///diffuse
    else {glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);}

    if(s1){glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular1);}///specular
    else {glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);}

///FIREPLACE LIGHT

    GLfloat light_ambient5[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse5[]  = { 1.0, 1.0, 01.0, 1.0 };
    GLfloat light_specular5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position5[] = {-31.5,13,21, 1.0 };


    glLightfv( GL_LIGHT5, GL_POSITION, light_position5);///position
    if(a1) {glLightfv( GL_LIGHT5, GL_AMBIENT, light_ambient5);}///ambient
    else {glLightfv( GL_LIGHT5, GL_AMBIENT, no_light);}

    if(d1){ glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse5);}///diffuse
    else {glLightfv(GL_LIGHT5, GL_DIFFUSE, no_light);}

    if(s1){glLightfv( GL_LIGHT5, GL_SPECULAR, light_specular5);}///specular
    else {glLightfv( GL_LIGHT5, GL_SPECULAR, no_light);}


///KITCHEN LIGHT

    GLfloat light_ambient6[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse6[]  = { 01.0, 01.0, 01.0, 1.0 };
    GLfloat light_specular6[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position6[] = {24,4.1+1,-1};


    glLightfv( GL_LIGHT6, GL_POSITION, light_position6);///position
    if(a1) {glLightfv( GL_LIGHT6, GL_AMBIENT, light_ambient6);}///ambient
    else {glLightfv( GL_LIGHT6, GL_AMBIENT, no_light);}

    if(d1){ glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse6);}///diffuse
    else {glLightfv(GL_LIGHT6, GL_DIFFUSE, no_light);}

    if(s1){glLightfv( GL_LIGHT6, GL_SPECULAR, light_specular6);}///specular
    else {glLightfv( GL_LIGHT6, GL_SPECULAR, no_light);}

/// FOODLAMP
    GLfloat light_ambient2[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position2[] = {40,13,85};//18,8,-3  (20,-10.5,55
    GLfloat spot_direction2[] = {0,-1,0};
    //GLfloat spot_direction2[] = { 0.0, -1.0, 0.0 };
    if(light2){glEnable( GL_LIGHT2); e2=true;} //std::cout<<"e4"<<light4x<<" "<<light4y<<" "<<light4z<<" "; }///LIGHT2
    else{  glDisable(GL_LIGHT2); e2=false;   }

    glLightfv( GL_LIGHT2, GL_POSITION, light_position2);///position
    if(a1) {glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient2);}///ambient
    else {glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);}

    if(d1){ glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);}///diffuse
    else {glLightfv(GL_LIGHT2, GL_DIFFUSE, no_light);}

    if(s1){glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular2);}///specular
    else {glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);}

    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);


/// DINING LAMP
    GLfloat light_ambient3[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse3[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular3[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position3[] = {44.5 ,17.3 ,-3,1};//18,8,-3
    GLfloat spot_direction3[] = {0,-1,0};
    //GLfloat spot_direction3[] = { 0.0, -1.0, 0.0 };
    if(light3){glEnable( GL_LIGHT3); e3=true; }//std::cout<<"e4"<<light4x<<" "<<light4y<<" "<<light4z<<" "; }///LIGHT3
    else{  glDisable(GL_LIGHT3); e3=false;   }

    glLightfv( GL_LIGHT3, GL_POSITION, light_position3);///position
    if(a1) {glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient3);}///ambient
    else {glLightfv( GL_LIGHT3, GL_AMBIENT, no_light);}

    if(d1){ glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse3);}///diffuse
    else {glLightfv(GL_LIGHT3, GL_DIFFUSE, no_light);}

    if(s1){glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular3);}///specular
    else {glLightfv( GL_LIGHT3, GL_SPECULAR, no_light);}

    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction3);
    glLightf( GL_LIGHT3, GL_SPOT_CUTOFF, 20.0);


///BEDLAMP
    GLfloat light_ambient4[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse4[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular4[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position4[] = {51.5 ,10.3 ,-24,1};//18,8,-3
    GLfloat spot_direction4[] = {0,-1,0};
    //GLfloat spot_direction4[] = { 0.0, -1.0, 0.0 };
    if(light4){glEnable( GL_LIGHT4); e4=true;}// std::cout<<"e4"<<light4x<<" "<<light4y<<" "<<light4z<<" "; }///LIGHT4
    else{  glDisable(GL_LIGHT4); e4=false;   }

    glLightfv( GL_LIGHT4, GL_POSITION, light_position4);///position
    if(a1) {glLightfv( GL_LIGHT4, GL_AMBIENT, light_ambient4);}///ambient
    else {glLightfv( GL_LIGHT4, GL_AMBIENT, no_light);}

    if(d1){ glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse4);}///diffuse
    else {glLightfv(GL_LIGHT4, GL_DIFFUSE, no_light);}

    if(s1){glLightfv( GL_LIGHT4, GL_SPECULAR, light_specular4);}///specular
    else {glLightfv( GL_LIGHT4, GL_SPECULAR, no_light);}

    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction4);
    glLightf( GL_LIGHT4, GL_SPOT_CUTOFF, 10.0);

   /* GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);*/

    /// sofaLAMP
    GLfloat light_ambient7[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse7[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular7[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position7[] = {33,3,7};//18,8,-3  (-65,15,-17
    GLfloat spot_direction7[] = {0,-1,0};
    //GLfloat spot_direction7[] = { 0.0, -1.0, 0.0 };
    if(light7){glEnable( GL_LIGHT7); e7=true; }//<<light4x<<" "<<light4y<<" "<<light4z<<" "; }///LIGHT7
    else{  glDisable(GL_LIGHT7); e7=false;   }

    glLightfv( GL_LIGHT7, GL_POSITION, light_position7);///position
    if(a1) {glLightfv( GL_LIGHT7, GL_AMBIENT, light_ambient7);}///ambient
    else {glLightfv( GL_LIGHT7, GL_AMBIENT, no_light);}

    if(d1){ glLightfv(GL_LIGHT7, GL_DIFFUSE, light_diffuse7);}///diffuse
    else {glLightfv(GL_LIGHT7, GL_DIFFUSE, no_light);}

    if(s1){glLightfv( GL_LIGHT7, GL_SPECULAR, light_specular7);}///specular
    else {glLightfv( GL_LIGHT7, GL_SPECULAR, no_light);}

    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spot_direction7);
    glLightf( GL_LIGHT7, GL_SPOT_CUTOFF, 15.0);
}


void drawtriangle(GLfloat a,GLfloat b,GLfloat c,bool e=false)
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5*a, 0.5*b, 0.5*c, 1.0 };
    GLfloat mat_diffuse[] = { a,b,c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};
    GLfloat mat_emision[] = {1,1,1,1};

    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    if(e == true) {glMaterialfv(GL_FRONT, GL_EMISSION, mat_diffuse);}
;

       glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <2; i++)
    {
       // glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_triangle[p_Indices[i][0]][0], v_triangle[p_Indices[i][0]][1], v_triangle[p_Indices[i][0]][2],
                    v_triangle[p_Indices[i][1]][0], v_triangle[p_Indices[i][1]][1], v_triangle[p_Indices[i][1]][2],
                    v_triangle[p_Indices[i][2]][0], v_triangle[p_Indices[i][2]][1], v_triangle[p_Indices[i][2]][2]);

        glVertex3fv(&v_triangle[p_Indices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_triangle[p_Indices[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_triangle[p_Indices[i][2]][0]);glTexCoord2f(1,1);
    }
    glEnd();

   glBegin(GL_QUADS);
    for (GLint i = 0; i <3; i++)
    {
    //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_triangle[q_Indices[i][0]][0], v_triangle[q_Indices[i][0]][1], v_triangle[q_Indices[i][0]][2],
                    v_triangle[q_Indices[i][1]][0], v_triangle[q_Indices[i][1]][1], v_triangle[q_Indices[i][1]][2],
                    v_triangle[q_Indices[i][2]][0], v_triangle[q_Indices[i][2]][1], v_triangle[q_Indices[i][2]][2]);

        glVertex3fv(&v_triangle[q_Indices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_triangle[q_Indices[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_triangle[q_Indices[i][2]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_triangle[q_Indices[i][3]][0]);glTexCoord2f(1,0);
    }
    glEnd();

}


void drawtriangle2(GLfloat a,GLfloat b,GLfloat c,bool e=false)
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5*a, 0.5*b, 0.5*c, 1.0 };
    GLfloat mat_diffuse[] = { a,b,c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};
    GLfloat mat_emision[] = {1,1,1,1};

    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    if(e == true) {glMaterialfv(GL_FRONT, GL_EMISSION, mat_diffuse);}
;

       glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <2; i++)
    {
       // glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_triangle2[p_Indices[i][0]][0], v_triangle2[p_Indices[i][0]][1], v_triangle2[p_Indices[i][0]][2],
                    v_triangle2[p_Indices[i][1]][0], v_triangle2[p_Indices[i][1]][1], v_triangle2[p_Indices[i][1]][2],
                    v_triangle2[p_Indices[i][2]][0], v_triangle2[p_Indices[i][2]][1], v_triangle2[p_Indices[i][2]][2]);

        glVertex3fv(&v_triangle2[p_Indices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_triangle2[p_Indices[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_triangle2[p_Indices[i][2]][0]);glTexCoord2f(1,1);
    }
    glEnd();

   glBegin(GL_QUADS);
    for (GLint i = 0; i <3; i++)
    {
    //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_triangle[q_Indices[i][0]][0], v_triangle[q_Indices[i][0]][1], v_triangle[q_Indices[i][0]][2],
                    v_triangle[q_Indices[i][1]][0], v_triangle[q_Indices[i][1]][1], v_triangle[q_Indices[i][1]][2],
                    v_triangle[q_Indices[i][2]][0], v_triangle[q_Indices[i][2]][1], v_triangle[q_Indices[i][2]][2]);

        glVertex3fv(&v_triangle[q_Indices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_triangle[q_Indices[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_triangle[q_Indices[i][2]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_triangle[q_Indices[i][3]][0]);glTexCoord2f(1,0);
    }
    glEnd();

}


void color(GLfloat a,GLfloat b,GLfloat c,bool e=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5*a, 0.5*b, 0.5*c, 1.0 };
    GLfloat mat_diffuse[] = { a,b,c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};
    GLfloat mat_emision[] = {1,1,1,1};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    if(e == true) {glMaterialfv(GL_FRONT, GL_EMISSION, mat_diffuse);}
}
void drawcube(GLfloat a,GLfloat b,GLfloat c,bool e=false, GLfloat t=1)
{
    color(a,b,c,e);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_pyramid[quadIndices[i][0]][0], v_pyramid[quadIndices[i][0]][1], v_pyramid[quadIndices[i][0]][2],
                    v_pyramid[quadIndices[i][1]][0], v_pyramid[quadIndices[i][1]][1], v_pyramid[quadIndices[i][1]][2],
                    v_pyramid[quadIndices[i][2]][0], v_pyramid[quadIndices[i][2]][1], v_pyramid[quadIndices[i][2]][2]);

        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);glTexCoord2f(0,t);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);glTexCoord2f(t,1);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);glTexCoord2f(t,0);
    }
    glEnd();


}
void LoadTexture(const char*filename,int a)
{
    glGenTextures(1, &ID[a]);
    glBindTexture(GL_TEXTURE_2D, ID[a]);
    //std::cout<<ID[a]<<" ";
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[a]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void trees()
{
    int n=0;
    for (int i=0;i<5;i++){
    glPushMatrix();
    glTranslatef(30,5,-50+n);
    tree2();
    glPopMatrix();
    n+=-20;
    }
    n=0;
    for (int i=0;i<5;i++){
    glPushMatrix();
    glTranslatef(10,5,-60+n);
    tree2();
    glPopMatrix();
    n+=-20;
    }
}


void roundhouse()
{

    color(1,1,1);//0.486, 0.988, 0.000);
    glBindTexture(GL_TEXTURE_2D, ID[14]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();///cone
    glTranslatef(-53.3,21.8,170);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *objj = gluNewQuadric();
    gluQuadricTexture(objj,TRUE);
    gluCylinder(objj, 0.1, 15, 15, 100, 100);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[0]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();///ceilingfloor long porch
    glTranslatef(-72.8,-10.5,75);
    glScalef(10,.3,41.6);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();///ceilingfloor long porch
    glTranslatef(-72.8+17.5,-10.5,132);
    glScalef(8.5,.3,25.6);
    drawcube(1,1,0);
    glPopMatrix();

    glPushMatrix();///center
    glTranslatef(-53.3,-9.5,170);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 15.0, 15, 2, 30, 30);
    glEnd();
    glPopMatrix();
    color(1,1,1);


    int n=0;
    for(int i=0;i<2;i++)//upper leg
     {
         int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-59.5,1,n+162.5);
                glScalef(0.3,10.5,0.3);
                drawcube(1.000, 0.549, 0.000);
                glPopMatrix();
                m=m+12.5;
         }
         n=n+12.5;
     }


    glPushMatrix();
    glTranslatef(-53.3,-9.5,170);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,15,70,60);
    glEnd();
    glPopMatrix();

glDisable(GL_TEXTURE_2D);
}

void beachchair()
{
    glBindTexture(GL_TEXTURE_2D, ID[11]); ///w4
glEnable(GL_TEXTURE_2D);
    int j=0;
   for (int i =0; i<19;i++)///body
    {
       glPushMatrix();
    glTranslatef(0,0,0+j);
    glScalef(5,.3,.3);
    drawcube(0.957, 0.643, 0.376);
    glPopMatrix();
    j=j+1.5;
    }
    glPushMatrix();
    glTranslatef(-5,0,9);
    glScalef(.3,.3,9.3);
    drawcube(0.957, 0.643, 0.376);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,0,9);
    glScalef(.3,.3,9.3);
    drawcube(0.957, 0.643, 0.376);
    glPopMatrix();

    j=0;///slide
    for (int i =0; i<8;i++)
    {
       glPushMatrix();
       glRotatef( 50, 1, 0, 0.0 );
    glTranslatef(0,5,-4+j);
    glScalef(5,.3,.3);
    drawcube(0.957, 0.643, 0.376);
    glPopMatrix();
    j=j+1.5;
    }
    glPushMatrix();
    glRotatef( 50, 1, 0, 0.0 );
    glTranslatef(-5,5,-3.7+3.7);
    glScalef(.3,.3,4.2);
    drawcube(0.957, 0.643, 0.376);
    glPopMatrix();
    glPushMatrix();
    glRotatef( 50, 1, 0, 0.0 );
    glTranslatef(5,5,-3.7+3.7);
    glScalef(.3,.3,4.2);
    drawcube(0.957, 0.643, 0.376);
    glPopMatrix();

    j=0;///leg
    for (int i =0; i<2;i++)
    {
    glPushMatrix();
    //glRotatef( 50, 1, 0, 0.0 );
    glTranslatef(-4.2,-1.5,0.7+j);
    glScalef(.5,1,.5);
    drawcube(0.957, 0.643, 0.376);
    glPopMatrix();

    glPushMatrix();
    //glRotatef( 50, 1, 0, 0.0 );
    glTranslatef(4.2,-1.5,0.7+j);
    glScalef(.5,1,.5);
    drawcube(0.957, 0.643, 0.376);
    glPopMatrix();
    j=j+16.7;
    }
    glDisable(GL_TEXTURE_2D);

}

void beach()
{
glBindTexture(GL_TEXTURE_2D, ID[12]);///beach
     glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(129,-10,-105);
    glScalef(170,.3,300);
    drawcube(1,1,1);//0.957, 0.643, 0.376);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[2]);///ocean
     glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-141,-10,-105);
    glScalef(100,.3,300);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void boat()
{
    glBindTexture(GL_TEXTURE_2D, ID[26]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();///body
    glTranslatef(-3,0.5,0.5);
    glScalef(1,1,0.5);
    glRotatef( 180, 1, 0, 0.0 );
    drawtriangle(1,1,1);
    glPopMatrix();


     glPushMatrix();
    glTranslatef(3,0.5,-0.5);
    glScalef(1,1,0.5);
    glRotatef( 180,0,1, 0.0 );
    glRotatef( -180, 1, 0, 0.0 );
    drawtriangle(01,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-0.5,0);
    glScalef(1,1,0.5);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);

 /*   glPushMatrix();///sail
    glTranslatef(0,3,0);
    glScalef(.051,2,.1);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8,2.5,0);
    //glRotatef( 180,0,01, 0.0 );
    glScalef(.31,2,0.1);

    //glRotatef( -180, 1, 0, 0.0 );
    drawtriangle(1,0,0);
    glPopMatrix();*/

    glPushMatrix();///UPPER PART
    glTranslatef(0,0.6,0);
    glScalef(3,0.1,0.5);
    drawcube(1,0,0);
    glPopMatrix();
glBindTexture(GL_TEXTURE_2D, ID[27]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();///UPPER box
    glTranslatef(0.5,0.87,0);
    glScalef(1.6,0.2,0.5);
    drawcube(1,1,1);//0.000, 0.000, 0.545);
    glPopMatrix();
    glPushMatrix();///UPPER box2
    glTranslatef(0.8,1.3,0);
    glScalef(1.3,0.3,0.5);
    drawcube(1,1,1);//0,0,1);
    glPopMatrix();
    glPushMatrix();///UPPER box
    glTranslatef(1.3,1.9,0);
    glScalef(0.8,0.3,0.5);
    drawcube(1,1,1);//0.118, 0.565, 1.000);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}

void boat2()
{
    glBindTexture(GL_TEXTURE_2D, ID[33]);
    glEnable(GL_TEXTURE_2D);
   glPushMatrix();///body
    glTranslatef(-15,2,5);
    glScalef(3,4,5);
    glRotatef( 180, 1, 0, 0.0 );
    drawtriangle(1,1,1); //0.627, 0.322, 0.176);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(15,2,-5);
    glScalef(3,4,5);
    glRotatef( 180,0,1, 0.0 );
    glRotatef( -180, 1, 0, 0.0 );
    drawtriangle(1,1,1); //0.627, 0.322, 0.176);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2,0);
    glScalef(9,4,5);
    drawcube(1,1,1); //0.6, 0.322, 0.176);
    glPopMatrix();
int k=-1;
  for(int i=0;i<2;i++){
    glPushMatrix();///borderlong
    glTranslatef(0,3.1,5*k);
    glScalef(15.25,1.2,0.5);
    drawcube(1,1,1); //0.6, 0.322, 0.176);
    glPopMatrix();

    glPushMatrix();///borderwidth
    glTranslatef(14*k,3.1,0);
    glScalef(2,1.2,5);
    drawcube(1,1,1); //0.6, 0.322, 0.176);
    glPopMatrix();
    k=1;
    }

    glDisable(GL_TEXTURE_2D);
    k=5;
for(int i=0;i<7;i++){ ///slides
    glPushMatrix();
    glTranslatef(-15+k,2.3,0);
    glScalef(0.8,.5,4.8);
    drawcube(1,1,1);
    glPopMatrix();
    k=k+3;
    }
glBindTexture(GL_TEXTURE_2D, ID[13]);
    glEnable(GL_TEXTURE_2D);
int n=-1;
    for(int i=0;i<2;i++)//upper leg
     {
         int m=-1;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m*12.5,9.5,n*3.5);
                glScalef(0.3,5.5,0.3);
                drawcube(0.722, 0.525, 0.043);
                glPopMatrix();
                m=1;
         }
         n=1;
     }
 glDisable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, ID[13]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();///roof
    glTranslatef(0,14.8,0);
    glScalef(13.5,0.2,4.5);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}


void umbrella(GLfloat a, GLfloat b, GLfloat c, GLfloat d ,GLfloat e, GLfloat f,int o,int p)
{


    color(1,1,1);//0.486, 0.988, 0.000);
    glBindTexture(GL_TEXTURE_2D, ID[p]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();///cone
    glTranslatef(0,11,0);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *objj = gluNewQuadric();
    gluQuadricTexture(objj,TRUE);
    if(open){gluCylinder(objj, 0.1, 15, 7, 200, 200);}
    else { gluCylinder(objj, 0.1, 3, 7, 200, 200); }
    glEnd();
    glPopMatrix();

glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[o]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();///rod
    glTranslatef(0,-1,0);
    glScalef(0.4,12,0.4);
    drawcube(d,e,f);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void stair(GLfloat a=1, GLfloat b=0, GLfloat c=0)
{
    for(int i=0;i<2;i++)//leg
     {
    glPushMatrix();
    glTranslatef(i*7,0,0);
    glScalef(.5,12,.5);
    drawcube(a,b,c);
    glPopMatrix();
     }
int n=0;
     for(int i=0;i<6;i++)// leg
     {
    glPushMatrix();
    glTranslatef(3.2,-8+n,0);
    glScalef(4,.5,2);
    drawcube(1,1,1);
    glPopMatrix();
    n=n+3;
     }

}
void tower()
{


     ///rod
     int n=0;
    for(int i=0;i<2;i++)//upper leg
     {
         int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m,0,n);
                glScalef(0.5,8,0.5);
                drawcube(1,1,1);
                glPopMatrix();
                m=m+15;
         }
         n=n+15;
     }
glPushMatrix();//middle
    glTranslatef(5,0,15);
    glScalef(0.5,8,0.5);
    drawcube(1,1,1);
    glPopMatrix();
glPushMatrix();//ceilling
    glTranslatef(7.6,7.6,7.6);
    glScalef(9,0.5,9);
    drawcube(1,0,0);
    glPopMatrix();
glPushMatrix();
    glTranslatef(7.6,-7.6,7.6);//floor
    glScalef(9,0.5,9);
    drawcube(1,0,0);
    glPopMatrix();
    n=0;
for(int i=0;i<2;i++)//leg
     {
         int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m,-19,n);
                glScalef(0.5,11,0.5);
                drawcube(1,1,1);
                glPopMatrix();
                m=m+15;
         }
         n=n+15;
     }

glPushMatrix();//railing
    glTranslatef(0,0,7.6);
    glScalef(0.5,0.5,7);
    drawcube(1,0,0);
    glPopMatrix();
    n=0;
glPushMatrix();
    glTranslatef(15,0,7.6);
    glScalef(0.5,0.5,7);
    drawcube(1,0,0);
    glPopMatrix();
    n=0;
glPushMatrix();
    glTranslatef(7.6,0,0);
    glScalef(7,0.5,0.5);
    drawcube(1,0,0);
    glPopMatrix();
    n=0;
glPushMatrix();
    glTranslatef(2.6,0,15);
    glScalef(2,0.5,0.5);
    drawcube(1,0,0);
    glPopMatrix();
    n=0;

glPushMatrix();
    glRotatef(-35,1,0,0);
    glTranslatef(7.0,-26.8,7);
    stair();
    glPopMatrix();

}

void fridge()
{
    glPushMatrix();///body
    glTranslatef(-8,-2.5,-22);
    glScalef(3,7,2);
    drawcube(	0.000, 0.000, 0.545);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[39]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();///frontdown
    glTranslatef(-8,-5.6,-19.9);
    glScalef(3,4,0.3);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[39]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();///front
    glTranslatef(-8,1.8,-19.9);
    glScalef(3,2.7,0.3);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();///handle
    glTranslatef(-6.5,-2.5,-19.7);
    glScalef(1,0.2,0.3);
    drawcube(0.098, 0.098, 0.439);
    glPopMatrix();
    glPushMatrix();///handle
    glTranslatef(-5.8,.5,-19.7);
    glScalef(0.2,1,0.3);
    drawcube(0.098, 0.098, 0.439);
    glPopMatrix();
}

void cabinet()
{
    glPushMatrix();
    glTranslatef(11.4,-7,-9.5);
    glScalef(3,3,13);
    drawcube(0.251, 0.878, 0.816);
    glPopMatrix();

glBindTexture(GL_TEXTURE_2D, ID[17]);    ///ocean
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(11.4,-3.7,-9.5);
    glScalef(3,.3,13);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);

glPushMatrix();
    glTranslatef(8,-6.8,-13.5);
    glScalef(.1,2.5,2);
    drawcube(0.000, 1.000, 1.000);
    glPopMatrix();
glPushMatrix();
    glTranslatef(8,-6.8,-8.5);
    glScalef(.1,2.5,2);
    drawcube(0.400, 0.804, 0.667);
    glPopMatrix();
glPushMatrix();
    glTranslatef(8,-6.8,-3.5);
    glScalef(.1,2.5,2);
    drawcube(0.000, 1.000, 1.000);
    glPopMatrix();
glPushMatrix();
    glTranslatef(8,-6.8,1.5);
    glScalef(.1,2.5,2);
    drawcube(0.400, 0.804, 0.667);
    glPopMatrix();

///RACK
glBindTexture(GL_TEXTURE_2D, ID[2]); //ocean
glEnable(GL_TEXTURE_2D);
glPushMatrix();
    glTranslatef(6,1,-20);
    glScalef(8,.2,2);
    drawcube(1,1,1);
    glPopMatrix();
glPushMatrix();
    glTranslatef(6,4,-20);
    glScalef(8,.2,2);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}
void oven()
{
glPushMatrix();
    glTranslatef(4,-7,-19.5);
    glScalef(5,3,3);
    drawcube(0.251, 0.878, 0.816);
    glPopMatrix();

glPushMatrix();
    glTranslatef(4,-7.5,-16.5);
    glScalef(3,1.5,.3);
    drawcube(0.973, 0.973, 1.000);
    glPopMatrix();
glPushMatrix();
    glTranslatef(4,-5,-16.5);
    glScalef(3,0.5,.3);
    drawcube(0,0,0);
    glPopMatrix();
glPushMatrix();///handle
    glTranslatef(4,-7,-16);
    glScalef(1,0.2,0.3);
    drawcube(0.576, 0.439, 0.859);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID[17]);//ocean
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(3.5,-3.7,-19.5);
    glScalef(4.7,.3,3);
    drawcube(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
void glass()
{
    color(1,1,1);//0.486, 0.988, 0.000);
    glBindTexture(GL_TEXTURE_2D, ID[30]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();///cone
    glRotatef(-90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj,TRUE);
    gluCylinder(obj, 0.1, 0.7, 0.8, 60, 60);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.6,0);
    glScalef(0.06,0.6,0.06);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();///cone
    glTranslatef(0,-1,0);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob,TRUE);
    gluCylinder(ob, 0.1, 0.5, 0.3, 60, 60);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void basket()
{
    color(0.863, 0.078, 0.235);
    glPushMatrix();///cone
    glRotatef(-90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 1, 2, 1, 60, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    //glTranslatef(0,2,0);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    //gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,1,70,60);
    glEnd();
    glPopMatrix();

    color(0.000, 0.000, 0.545);
    glPushMatrix();///sphere
    glTranslatef(0,0.7,-0.7);
    glutSolidSphere(0.7,60,60);
    glPopMatrix();
    color(1.000, 0.078, 0.576);
    glPushMatrix();///sphere
    glTranslatef(-0.5,0.5,0);
    glutSolidSphere(0.5,60,60);
    glPopMatrix();
    color(0.678, 1.000, 0.184);
    glPushMatrix();///sphere
    glTranslatef(0.2,0.7,0);
    glutSolidSphere(0.7,60,60);
    glPopMatrix();
    color( 1.000,0.678, 0.184);
    glPushMatrix();///sphere
    glTranslatef(-0.3,0.8,0.8);
    glutSolidSphere(0.6,60,60);
    glPopMatrix();
    color( 0.502, 0.000, 0.502);
    glPushMatrix();///sphere
    glTranslatef(0,0.7,0.8);
    glutSolidSphere(0.6,60,60);
    glPopMatrix();


}

void chairrot(GLfloat a, GLfloat b, GLfloat c)
{
    int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-40,-7.7,.5);
                glScalef(0.2,5.5,0.2);
                drawcube(a,b,c);
                glPopMatrix();
                m=m+4;
         }
     m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(-38,m-1.9,.5);
                glScalef(2.3,0.3,0.2);
                drawcube(a,b,c);
                glPopMatrix();
                m=m-11.7;
         }
}
void diningchair(GLfloat a=0, GLfloat b=0, GLfloat c=0.804)
{
     glPushMatrix();
    glTranslatef(-38,-7.3,-1.4);
    glScalef(2.4,0.3,2.4);
    drawcube(a,b,c);
    glPopMatrix();

    int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-40,-7.3,.5);
                glScalef(0.2,4.18,0.2);
                drawcube(1,1,1);
                glPopMatrix();
                m=m+4;
         }
    glPushMatrix();
    glTranslatef(-38,-11.7,.5);
    glScalef(2.3,0.3,0.2);
    drawcube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,-1.2,1.4);
    glRotatef(35,1,0,0);
    chairrot(a,b,c);
    glPopMatrix();

}

void teaset()
{
    color(0.957, 0.643, 0.376);
    glPushMatrix();///pot
    glTranslatef(-40,-1,-9);
    glutSolidTeapot(1);
    glPopMatrix();

    ///cup
    int n=0;
    for(int i=0;i<2;i++){
    color(00.941, 0.902, 0.549);
    glPushMatrix();///cone
    glTranslatef(-38,-1.7,-8+n);
    glRotatef(-90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 0.4, 0.8, 0.6, 60, 60);
    glEnd();
    glPopMatrix();


    glPushMatrix();///cone
    glTranslatef(-38,-1.8,-8+n);
    glRotatef(-90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluCylinder(ob, 0.1, 1, 0.2, 60, 60);
    glEnd();
    glPopMatrix();

    color(0,0,0);
    glPushMatrix();
    glTranslatef(-38,-1.3,-8+n);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,0.6,70,60);
    glEnd();
    glPopMatrix();
    n=n-2;
    }
}
void diningtb()
{
    glPushMatrix();
    teaset();
    glPopMatrix();

glBindTexture(GL_TEXTURE_2D, ID[15]);
glEnable(GL_TEXTURE_2D);
   glPushMatrix();///body
    glTranslatef(-38,-2.0,-9);
    glScalef(7,.2,7);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);

   glPushMatrix();
    glTranslatef(-38,-2.7,-9);
    glScalef(4,.7,4);
    drawcube(0.000, 0.000, 0.804);
    glPopMatrix();
    int n=0;
    for(int i=0;i<2;i++)///leg
     {
         int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-40,-6.7,n-11.5);
                glScalef(0.3,4.5,0.3);
                drawcube(1,1,1);
                glPopMatrix();
                m=m+4;
         }
         n=n+4;
     }
     glPushMatrix();
    glTranslatef(-38,-6.7,-9.6);
    glScalef(1.9,0.7,1.9);
    drawcube(0.000, 0.000, 0.804);
    glPopMatrix();
}

void diningset()
{
    glPushMatrix(); ///table
    //glRotatef( theta, 0, 01, 0.0 );
    glTranslatef(0,1,0);
    diningtb();
    glPopMatrix();
   glPushMatrix(); ///chair
    //glRotatef( theta, 0, 01, 0.0 );
    glTranslatef(0,2.6,-1);///2.6
    //glScalef(1,1.0,1);
    diningchair();
    glPopMatrix();

    glPushMatrix(); ///chair2
    //glRotatef( theta, 0, 01, 0.0 );
    glRotatef( 90, 0, 01, 0.0 );
    glTranslatef(47,2.6,-29);
    //glScalef(1,1.0,1);
    diningchair();
    glPopMatrix();

    glPushMatrix(); ///chair3
    //glRotatef( theta, 0, 01, 0.0 );
    glRotatef( 180, 0, 01, 0.0 );
    glTranslatef(75,2.6,18);
    //glScalef(1,1.0,1);
    diningchair();
    glPopMatrix();

    glPushMatrix(); ///chair4
    //glRotatef( theta, 0, 01, 0.0 );
    glRotatef( 270, 0, 01, 0.0 );
    glTranslatef(28,2.6,46.5);
    //glScalef(1,1.0,1);
    diningchair();
    glPopMatrix();

}
void pillow()
{
    int m=0;
    for(int i=0;i<3;i++)
    {
glBindTexture(GL_TEXTURE_2D, ID[16]);
glEnable(GL_TEXTURE_2D);
     glPushMatrix();///pillow
    glTranslatef(-19,-10.5,31-m);
    glScalef(-.5,2.7,2.7);
    drawcube(1,1,1);
    glPopMatrix();
    m=m+6;
glDisable(GL_TEXTURE_2D);
    }

}
void sofa()
{
glBindTexture(GL_TEXTURE_2D, ID[36]);
glEnable(GL_TEXTURE_2D);
   glPushMatrix();///body
    glTranslatef(-22,-7,25);
    glScalef(4,1,10);
    drawcube(1,1,1);
    glPopMatrix();

   glPushMatrix();///back
    glTranslatef(-19,-3.5,25);
    glScalef(1,2.5,10);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();///side
    glTranslatef(-22,-6.5,14);
    glScalef(4,3,1);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();///side
    glTranslatef(-22,-6.5,36);
    glScalef(4,3,1);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);

    glPushMatrix();///pillow
    glRotatef(-20,0,0,01);
    pillow();
    glPopMatrix();


    color(0.118, 0.565, 1.000);
    glPushMatrix();///centertable
    glTranslatef(-32,-5.6,24);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 3.0, 3, 7, 30, 30);
    glEnd();
    glPopMatrix();
    color(1,1,1);
glBindTexture(GL_TEXTURE_2D, ID[17]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-32,-5.6,24);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,5,70,60);
    glEnd();
    glPopMatrix();

glDisable(GL_TEXTURE_2D);

glPushMatrix();///basket

    glTranslatef(-32,-5.46,24);
    glScalef(0.8,0.8,0.8);
    basket();
    glPopMatrix();
}

void clockfire()
{
    glBindTexture(GL_TEXTURE_2D, ID[23]);
glEnable(GL_TEXTURE_2D);
 glPushMatrix();///body
    glTranslatef(-1,-0.5,0.5);
    glScalef(1,1,0.3);
    glRotatef( 180, 1, 0, 0.0 );
    drawtriangle(1,1,1);
    glPopMatrix();


     glPushMatrix();
    glTranslatef(3,-0.5,-0.1);
    glScalef(1,1,0.3);
    glRotatef( 180,0,1, 0.0 );
    glRotatef( -180, 1, 0, 0.0 );
    drawtriangle(01,1,1);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(1,2,0);
    glScalef(1,3,0.3);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();///HANDLE
    glTranslatef(1,1.8,1);
    glScalef(0.1,0.5,0.05);
    drawcube(0.545, 0.271, 0.075);
    glPopMatrix();
    glPushMatrix();///HANDLE
    glTranslatef(1.45,2.2,1);
    glRotatef(90,0,0,1);
    glScalef(0.1,0.5,0.05);
    drawcube(0.545, 0.271, 0.075);
    glPopMatrix();


color(1,1,1);
    glPushMatrix();///mirror
    glTranslatef(1,2.2,.5);
    glRotatef(90,0,0,01);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 1, 1.7, 0.3, 110, 110);
    //gluDisk(obj,3.4,3.4,30,30);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[32]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1,2.2,.8);
    glRotatef(90,0,0,01);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob,TRUE);
    gluDisk(ob,0,1.7,70,60);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void firelight()
{
    glPushMatrix();
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-52,13,21);
    glScalef(0.2,0.6,3.6);
    //glRotatef(90,0,1,0);
    drawcube(0.647, 0.165, 0.165);
    glPopMatrix();

    glPushMatrix();
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-51.5,13,21);
    glScalef(0.2,0.4,3.2);
    //glRotatef(90,0,1,0);
    drawcube(1.000, 1, 1.000,e5);
    glPopMatrix();
}
void sofalamp()
{
     color(0.498, 1.000, 0.831,e7);
    glPushMatrix(); ///cone
    glTranslatef(-22,3.6,10);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 2, 2, 2.4, 60, 60);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22,2.2,10);//light
    glScalef(0.2,.2,0.2);
    drawcube(1,1,1,e7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22,-4.5,10);
    glScalef(0.2,6.5,0.2);
    drawcube(0.737, 0.561, 0.561);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22,-9.50,10);
    glScalef(0.8,.3,0.8);
    drawcube(0.737, 0.561, 0.561);
    glPopMatrix();
}

void dininglamp()
{
     color(0.604, 0.804, 0.196);
    glPushMatrix(); ///cone
    glTranslatef(-38,8,-9);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, .3, 2.8, 1.6, 60, 60);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-38,7.8,-9);//light
    glScalef(0.2,.2,0.2);
    drawcube(0.678, 1.000, 0.184,e3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-38,15.7,-9);
    glScalef(0.17,7.4,0.17);
    drawcube(0.502, 0.502, 0.000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-38,8.1,-9);
    glScalef(0.4,.3,0.4);
    drawcube(	0.000, 0.392, 0.000);
    glPopMatrix();
}

void fire()
{
    glPushMatrix();///fireplace
    glTranslatef(-58,-4,22);
    glScalef(.3,6,5);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-57.5,0.5,22);
    glScalef(0.8,1.5,5);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();//low
    glTranslatef(-57.5,-9.2,21.5);
    glScalef(1.2,.5,6);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();//marble
    glTranslatef(-57.5,2,21.5);
    glScalef(1.2,.4,6);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();//side
    glTranslatef(-57.5,-5,18.5);
    glScalef(0.8,5,1.5);
    drawcube(1,1,1);
    glPopMatrix();

     glPushMatrix();//side
    glTranslatef(-57.5,-5,25.5);
    glScalef(0.8,5,1.5);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();///fire
    glTranslatef(-57,-6,22);
    glScalef(.1,3,2.5);
    drawcube(0,0,0);
    glPopMatrix();
}

void bed()
{
glBindTexture(GL_TEXTURE_2D, ID[38]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-1.7,0);
    glScalef(5,1,14);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glTranslatef(-85,-8.5,-6);
    glScalef(7,0.6,14);
    drawcube(1,1,1);
    glPopMatrix();

///stand
    glPushMatrix();
    //glTranslatef(-85.2,-2.6,-19);
    glTranslatef(0,3,-13);
    glScalef(7,2.5,1);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glTranslatef(-85.2,-2.6,-19);
    glTranslatef(0,7,-13);
    glScalef(7,0.6,1);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(-85.2,-2.6,-19);
    glTranslatef(5,6,-13);
    glScalef(0.6,0.6,1);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glTranslatef(-85.2,-2.6,-19);
    glTranslatef(-5,6,-13);
    glScalef(0.6,0.6,1);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);

glBindTexture(GL_TEXTURE_2D, ID[18]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //glTranslatef(-85,-6,-6);
    glTranslatef(0,1.50,02);
    glScalef(6.4,1,12);
    drawcube(01,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, ID[20]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();///blanket
    //glTranslatef(-85,-4.8,0);
    glTranslatef(0,2.8,9);
    glScalef(6.4,.1,4);
    drawcube(01,1,1);
    glPopMatrix();

    glPushMatrix();///pillow
    //glTranslatef(-88.5,-4,-13);
    glTranslatef(03,2.8,-5);
    glScalef(2.5,-.5,2.5);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///pillow
    //glTranslatef(-82,-4,-13);
    glTranslatef(-03,2.8,-5);
    glScalef(2.5,-.5,2.5);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}
void tv()
{
    glPushMatrix();
    glTranslatef(-55,4,17);
    glScalef(.5,3,4);
    drawcube(0,0,0);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[29]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-55.9,4,17);
    glScalef(.005,2.5,3.5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void almirah()
{
    glBindTexture(GL_TEXTURE_2D, ID[38]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(1.5,6,2);
    glTranslatef(0,0,0);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3,6,2);
    glTranslatef(6.15,0,0);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.5,6,2);
    glTranslatef(2.4,0,0);
    drawcube(1,1,1);
    glPopMatrix();
    //handle2
    int a=0;
    for(int i=0;i<2;i++)
    {
      glPushMatrix();
    glScalef(0.07,0.6,0.1);
    glTranslatef(11+a,0,23);
    drawcube(0,0.4,0.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.07,0.15,0.3);
    glTranslatef(11+a,-5,7);
    drawcube(0,0.4,0.4);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.07,0.15,0.3);
    glTranslatef(11+a,3.5,7);
    drawcube(0,0.4,0.4);
    glPopMatrix();
    a=a+28;
    }

    glDisable(GL_TEXTURE_2D);
}

void sidetable()
{
glBindTexture(GL_TEXTURE_2D, ID[38]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-68,-5,-17);
    glScalef(2,1.6,2);
    drawcube(1,1,1);//0.275, 0.510, 0.706);
    glPopMatrix();

     int n=0;
    for(int i=0;i<2;i++)///leg
     {
         int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-69,-8,n-18);
                glScalef(0.2,2,0.2);
                drawcube(1,1,1);
                glPopMatrix();
                m=m+2;
         }
         n=n+2;
     }

     glPushMatrix();//handle
    glTranslatef(-68,-5.2,-15);
    glScalef(.7,.3,.2);
    drawcube(0.0, 0.000, 01.00);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}

void dressingtable()
{
glBindTexture(GL_TEXTURE_2D, ID[38]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-57,-3,20);
    glScalef(2,1.5,5);
    drawcube(1,1,1);
    glPopMatrix();

     int n=0;
    for(int i=0;i<2;i++)///leg
     {
         int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-58,-7,n+18);
                glScalef(0.3,3,0.3);
                drawcube(0.545, 0.000, 0.00);
                glPopMatrix();
                m=m+2;
         }
         n=n+4;
     }
    glPushMatrix();//handle
    glTranslatef(-59,-2.8,20);
    glScalef(.2,.3,.7);
    drawcube(0, 0.000, 1.00);
    glPopMatrix();



color(1,1,1);
     glPushMatrix();///mirror
    glTranslatef(-56,2.4,20);
    glRotatef(90,0,01,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    gluCylinder(obj, 4, 4, 1, 110, 110);
    //gluDisk(obj,3.4,3.4,30,30);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55,2.4,20);
    glRotatef(90,0,01,0);
    glBegin(GL_POLYGON);
    obj = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    gluDisk(obj,0,4,70,60);
    glEnd();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[10]);
    glEnable(GL_TEXTURE_2D);
    color(1,1,1);
    glPushMatrix();
    glTranslatef(-56,2.4,20);
    glRotatef(90,0,01,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,4,70,60);
    glEnd();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);




}

void bedlamp()
{
     color(0.933, 0.510, 0.933);
    glPushMatrix(); ///cone
    glTranslatef(-68,1.5,-17);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, .8, 2, 2, 60, 60);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68,0.5,-17);//light
    glScalef(0.2,.2,0.2);
    drawcube(1,1,1,e4);
//        glGetDoublev (GL_MODELVIEW_MATRIX, modelviewMatrix);
//light3x = modelviewMatrix[12];
//light3y = modelviewMatrix[13];
//light3z = modelviewMatrix[14];
    //std::cout<<"fghffjgftyfut"<<light3x<<" "<<light3y<<" "<<light3z<<"p";
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68,-2,-17);
    glScalef(0.2,2,0.2);
    drawcube(0.545, 0.000, 0.545);
    glPopMatrix();

    color(0.294, 0.000, 0.510);
    glPushMatrix(); ///cone
    glTranslatef(-68,-3,-17);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *o = gluNewQuadric();
    gluCylinder(o, 0.5, 0.5, 0.5, 60, 60);
    glEnd();
    glPopMatrix();
}

void bedlight()
{
    glPushMatrix();
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-70,9,-23);
    glScalef(2.6,0.8,.2);
    //glRotatef(90,0,1,0);
    drawcube(0.000, 0.000, 0.545);
    glPopMatrix();

    glPushMatrix();
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-70,9,-22.5);
    glScalef(2,0.4,.2);
    //glRotatef(90,0,1,0);
    drawcube(1.000, 1, 1.000,e1);
    glPopMatrix();

    /*color(0.000, 0.000, 0.545);
    glPushMatrix();///sphere
    glTranslatef(-70,10,-22);
    glutSolidSphere(0.7,60,60);
    glPopMatrix();*/
}

void kitlight()
{
   glPushMatrix();
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(5,05+2,4);
    glScalef(0.4,0.3,1.4);
    //glRotatef(90,0,1,0);
    drawcube(0.000, 1.000, 0.545);
    glPopMatrix();

  /*  glPushMatrix();
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-70,9,-22.5);
    glScalef(2,0.4,.2);
    //glRotatef(90,0,1,0);
    drawcube(1.000, 1, 1.000,e1);
    glPopMatrix(); */
    color(0.000, 0.000, 0.545,e6);
    glPushMatrix();///sphere
    glTranslatef(5,4.1+2,3);
    glutSolidSphere(0.7,60,60);
    glPopMatrix();
}
void housewall()
{
    //glDisable(GL_LIGHT6);
    //cout<<ID[7];
    glBindTexture(GL_TEXTURE_2D, ID[0]); ///wood
glEnable(GL_TEXTURE_2D);
    glPushMatrix();///floor
    glTranslatef(-36.7,-10.5,7.5);
    glScalef(53,.5,33);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

glBindTexture(GL_TEXTURE_2D, ID[3]); ///wood
glEnable(GL_TEXTURE_2D);

if(light6){glEnable( GL_LIGHT6);e6=true;  }///LIGHT6
    else if(!light6){  glDisable(GL_LIGHT6); e6=false;  }
   glPushMatrix();///floorkitchen
    glTranslatef(0,-10,-10);
    glScalef(15,.3,15);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_LIGHT6);
if(light5){glEnable( GL_LIGHT5);e5=true;  }///LIGHT5
    else if(!light5){  glDisable(GL_LIGHT5); glDisable(GL_LIGHT6); e5=false;  }
    glPushMatrix();///floor2dining
    glTranslatef(-35.4,-10,7);
    glScalef(20.5,.3,32);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_LIGHT5);
if(light1){glEnable( GL_LIGHT1);e1=true;  }///LIGHT1
    else if(!light1){  glDisable(GL_LIGHT1); e1=false;  }
    glPushMatrix();///floor3bed
    glTranslatef(-71.8,-10,7);
    glScalef(16.2,.3,32);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_LIGHT1);
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[9]); ///wall
glEnable(GL_TEXTURE_2D);
if(light6){glEnable( GL_LIGHT6);e6=true;  }///LIGHT6
    else if(!light6){  glDisable(GL_LIGHT1); e6=false;  }
    ///kitchen
    glPushMatrix();///wall
    glTranslatef(15,-0.3,0);
    glScalef(.3,10,5);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();///kitchenwall
    glTranslatef(15,-0.3,-20);
    glScalef(.3,10,5);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///downwall
    glTranslatef(15,-5.35,-10);
    glScalef(.3,5,5);
    drawcube(1,1,1);
    glPopMatrix();
//    glPushMatrix();///windowbody
//    glTranslatef(15,1,-10);
//    glScalef(.3,4.5,4);
//    drawcube(1, 1,1);
//    glPopMatrix();
    glPushMatrix();///windowlow
    glTranslatef(15,0,-10);
    glScalef(.3,0.5,5);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
    glPushMatrix();///windowhigh
    glTranslatef(15,6,-10);
    glScalef(.3,0.5,5);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
    glPushMatrix();///window
    glTranslatef(15,3,-14.57);
    glScalef(.3,3,.52);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
    glPushMatrix();///window
    glTranslatef(15,3,-5.5);
    glScalef(.3,3,.52);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
    glPushMatrix();///upwall
    glTranslatef(15,8.1,-10);
    glScalef(.3,1.6,5);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///backwallofkitchen
    glTranslatef(0,0,-25);
    glScalef(15,9.6,0.3);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///frontwallkitchen
    glTranslatef(5,0,5.2);
    glScalef(10,9.6,0.3);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///frontwall2kitchen
    glTranslatef(-10,7.3,5.2);
    glScalef(5,1.8,0.3);
    drawcube(1,01,01);
    glPopMatrix();
glDisable(GL_LIGHT6);

    ///dining
 if(light5){glEnable( GL_LIGHT5);e5=true;  }///LIGHT5
    else if(!light5){  glDisable(GL_LIGHT5); e5=false;  }

    glPushMatrix();///frontwallofdiningdoor
    glTranslatef(-19.4,0,39);
    glScalef(4.3,9.6,0.3);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///backwallofdining
    glTranslatef(-30,0,-25);
    glScalef(15,9.6,0.3);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///sofawall
    glTranslatef(-15,0,22);
    glScalef(.3,10,17);
    drawcube(1,1,1);
    glPopMatrix();
    ///bedroom
if(light1){glEnable( GL_LIGHT1);e1=true;  }///LIGHT1
    else if(!light1){  glDisable(GL_LIGHT1); e1=false;  }
    glPushMatrix();///fireplacewall
    glTranslatef(-54,5,17);
    glScalef(.3,15,22);
    drawcube(1,1,1);
    glPopMatrix();

glDisable(GL_LIGHT5);



    glPushMatrix();///backwallofbedroom
    glTranslatef(-72,0,-25);
    glScalef(16,9.6,0.3);
    drawcube(1,1,1);
    glPopMatrix();
     glPushMatrix();///bedroomwall
    glTranslatef(-88,-0.3,-17.5);
    glScalef(.3,10,8);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///downwindowwall
    glTranslatef(-88,-7.7,1.3);
    glScalef(.3,3,11);
    drawcube(1,1,1,t=10);
    glPopMatrix();
    glPushMatrix();///upwindowwall
    glTranslatef(-88,8.3,1.3);
    glScalef(.3,1.5,11);
    drawcube(1,1,1,t=5);
    glPopMatrix();
    glPushMatrix();///windowlow
    glTranslatef(-88,-3.7,1.4);
    glScalef(.3,1,11);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
    glPushMatrix();///windowhigh
    glTranslatef(-88,5.8,1.4);
    glScalef(.3,1,11);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
    glPushMatrix();///window
    glTranslatef(-88,1,-8.85);
    glScalef(.3,5,.7);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
    glPushMatrix();///window
    glTranslatef(-88,1,0.5);
    glScalef(.3,5,.7);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
    glPushMatrix();///window
    glTranslatef(-88,1,11.5);
    glScalef(.3,5,.7);
    drawcube(0.184, 0.310, 0.310);
    glPopMatrix();
     glPushMatrix();///bedroomwall
    glTranslatef(-88,-0.3,25.7);
    glScalef(.3,10,13.5);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///frontwallofbedroom
    glTranslatef(-60,0,39);
    glScalef(6,9.6,0.3);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///frontwallofbedroom2
    glTranslatef(-83.3,0,39);
    glScalef(5,9.6,0.3);
    drawcube(1,1,1);
    glPopMatrix();
 glDisable(GL_LIGHT6);

glDisable(GL_TEXTURE_2D);
}
void roof()
{
 if(light1){glEnable( GL_LIGHT1);e1=true;  }///LIGHT1
    else if(!light1){  glDisable(GL_LIGHT1); e1=false;  }
glBindTexture(GL_TEXTURE_2D, ID[9]); ///wood
glEnable(GL_TEXTURE_2D);
    glPushMatrix();///frontwallofbedroom
    glTranslatef(-89,9.6,38.8);
    glScalef(17.7,10.6,0.25);
    drawtriangle(1,1,1);
    glPopMatrix();
    glPushMatrix();///backtwallofbedroom
    glTranslatef(-89,9.6,-25.3);
    glScalef(17.7,10.6,0.25);
    drawtriangle(1,1,1);
    glPopMatrix();
 glDisable(GL_LIGHT1);

  if(light5){glEnable( GL_LIGHT5);e5=true;  }///LIGHT5
    else if(!light5){  glDisable(GL_LIGHT5); e5=false;  }
    glPushMatrix();///frontwallodiningroom
    glTranslatef(-14,9.6,39.2);
    glScalef(20,10.6,0.25);
    glRotatef(180,0,1,0);
    drawtriangle(1,1,1);
    glPopMatrix();
    glPushMatrix();///backwallofdining
    glTranslatef(-14,9.6,-24.8);
    glScalef(20,10.6,0.25);
    glRotatef(180,0,1,0);
    drawtriangle(1,1,1);
    glPopMatrix();
    glDisable(GL_LIGHT5);
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[7]); ///roof
glEnable(GL_TEXTURE_2D);
    glPushMatrix();///ceiling3
    glTranslatef(-72.8,19.8,8);
    glRotatef(30.5,0,0,1);
    glScalef(22,.7,33);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///ceiling2
    glTranslatef(-33.4,20.5,8);
    glRotatef(-28,0,0,1);
    glScalef(24,.7,33);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///ceiling
    glTranslatef(2,10,-9);
    glScalef(17,.7,17);
    drawcube(1,1,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);

glBindTexture(GL_TEXTURE_2D, ID[0]); ///wood2
glEnable(GL_TEXTURE_2D);
   glPushMatrix();///ceiling3
    glTranslatef(-75.8,13.5,47);
    glRotatef(28,0,0,1);
    glScalef(6.4,.7,7);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();///ceiling2
    glTranslatef(-65.4,13.5,47);
    glRotatef(-28,0,0,1);
    glScalef(6.4,.7,7);
    drawcube(1,1,1);
    glPopMatrix();
  /*  glPushMatrix();///ceilingmiddle
    glTranslatef(-53,19,47);
    glScalef(10.5,.7,7);
    drawcube(1,1,0);
    glPopMatrix();*/
glPushMatrix();///ceilingfloor
    glTranslatef(-70.8,-10.5,47);
    glScalef(10,.3,7);
    drawcube(1,1,1);
    glPopMatrix();
    int m=0;
    for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-78.5,01,52);
                glScalef(0.5,11,0.5);
                drawcube(1.000, 1,1);
                glPopMatrix();
                m=m+16.5;
         }

glDisable(GL_TEXTURE_2D);
}

void door()
{
    glBindTexture(GL_TEXTURE_2D, ID[8]); ///glass
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();///dining
    glTranslatef(-25.1,0,39);
    glScalef(8.5,8.4,0.3);
    drawcube(1,1,1);
    glPopMatrix();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glPushMatrix();///border
    glTranslatef(-25,9,39);
    glScalef(9.5,.6,0.3);
    drawcube(0.545, 0.271, 0.075);
    glPopMatrix();
    glPushMatrix();///b
    glTranslatef(-25,-9,39);
    glScalef(9.5,.6,0.3);
    drawcube(0.545, 0.271, 0.075);
    glPopMatrix();
    glPushMatrix();///b
    glTranslatef(-16,0,39);
    glScalef(0.6,9.6,0.3);
    drawcube(0.545, 0.271, 0.075);
    glPopMatrix();
     glPushMatrix();///b
    glTranslatef(-34.2,0,39);
    glScalef(0.6,9.6,0.3);
    drawcube(0.545, 0.271, 0.075);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void frame(int a)
{
 glPushMatrix();
    glScalef(4,3,0.2);
    drawcube(1,1,1);
    glPopMatrix();
glBindTexture(GL_TEXTURE_2D, ID[a]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,.2);
    glScalef(3,2,0.2);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void rot(GLfloat a)
{

    B[0][0]-=A[0][0];
    B[0][1]-=A[0][1];
    B[0][2]-=A[0][2];
    B[0][3]=1;

    GLfloat rotation_mat[4][4] = {
        {cos(a*3.14/180.0), 0, sin(a*3.14/180.0), 0},
        {0, 1, 0, 0},
        {-sin(a*3.14/180.0), 0, cos(a*3.14/180.0), 0},
        {0, 0, 0, 1}
        };

    for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++)
                output[j][k] = 0;
    }
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 4; j++) {
            output[i][j] = 0;
            for (int k = 0; k < 4; k++)
                output[i][j] += B[i][k] * rotation_mat[k][j];

        }
   }


    B[0][0]=output[0][0]+A[0][0];
    B[0][1]=output[0][1]+A[0][1];
    B[0][2]=output[0][2]+A[0][2];


}

void fan()
{

    glPushMatrix();
    drawcube(0.7, 0.6, 0.8);
    glPopMatrix();


    glPushMatrix(); // dot
    glScalef(0.3,0.33,0.3);
    glTranslatef(4,0,0);
    drawcube(0.2, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix(); // pakha
    glScalef(5,0.1,1.2);
    glTranslatef(1.3,0,0);
    drawcube(0.4,0.4,0.8);
    glPopMatrix();

    glPushMatrix(); // dot
    glScalef(0.3,0.33,0.3);
    glTranslatef(-4,0,0);
    drawcube(0.2, 0.2, 0.2);
    glPopMatrix();


    glPushMatrix(); // pakha
    glScalef(5,0.1,1.2);
    glTranslatef(-1.3,0,0);
    drawcube(0.4,0.4,0.8);
    glPopMatrix();

    glPushMatrix(); // dot
    glScalef(0.3,0.33,0.3);
    glTranslatef(0,0,-4);
    drawcube(0.2, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix(); // pakha
    glScalef(1.2,0.1,5);
    glTranslatef(0,0,-1.3);
    drawcube(0.4,0.4,0.8);
    glPopMatrix();

    glPushMatrix(); // dot
    glScalef(0.3,0.33,0.3);
    glTranslatef(0,0,4);
    drawcube(0.2, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix(); // pakha
    glScalef(1.2,0.1,5);
    glTranslatef(0,0,1.3);
    drawcube(0.4,0.4,0.8);
    glPopMatrix();

}

void stool(GLfloat a, GLfloat b, GLfloat c, GLfloat d ,GLfloat e, GLfloat f)
{
    int n=0;
    for(int i=0;i<2;i++)// leg
     {
         int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-1,-2.8,n-1);
                glScalef(0.2,2.3,0.2);
                drawcube(a,b,c);
                glPopMatrix();
                m=m+2.5;
         }
         n=n+2.5;
     }

color(d,e,f);
glPushMatrix();///center
    //glTranslatef(-53.3,-9.5,170);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj, TRUE);
    gluCylinder(obj, 2.0, 2, 2, 30, 30);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(-53.3,-9.5,170);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,2,70,60);
    glEnd();
    glPopMatrix();


}

void frontyard()
{
    glPushMatrix(); ///chair
    glTranslatef(-10,-4,7);
    glRotatef( 180, 0, 01, 0.0 );
    glScalef(0.7,.7,0.5);
    diningchair(	0.604, 0.804, 0.196);
    glPopMatrix();

glPushMatrix(); ///UMBRELLA
    glRotatef( theta, 0, 01, 0.0 );
    glTranslatef(18,-6,12);
    glScalef(0.5,0.5,0.5);
    color(1,1,1);//0.486, 0.988, 0.000);
    glBindTexture(GL_TEXTURE_2D, ID[24]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix();///cone
    glTranslatef(0,11,0);
    glRotatef(90,01,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *objj = gluNewQuadric();
    gluQuadricTexture(objj,TRUE);
    gluCylinder(objj, 0.1, 13, 7, 100, 100);
    glEnd();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[23]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();///rod
    glTranslatef(0,-1,0);
    glScalef(0.4,12,0.4);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //glRotatef(-8,0,0,1);
   // umbrella(1,1,1,	1.000, 1.000, 1,23,24);
    glPopMatrix();

glBindTexture(GL_TEXTURE_2D, ID[24]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix(); ///stool
    glTranslatef(20,-8,14);
    //glRotatef( 180, 0, 01, 0.0 );
    glScalef(0.7,0.8,0.7);
    stool(	0.604, 0.804, 0.196,1,1,1);//0.498, 1.000, 0.831,
    glPopMatrix();
glDisable(GL_TEXTURE_2D);

 glPushMatrix();
    glTranslatef(20,-5,14);
    glScalef(0.7,0.7,0.7);
    coco();
    glPopMatrix();
}

void house()
{
    ///BEDROOM
    if(light1){glEnable( GL_LIGHT1);e1=true;  }///LIGHT1
    else if(!light1){  glDisable(GL_LIGHT1); e1=false;  }

    glPushMatrix(); ///bedlight
    bedlight();
    glPopMatrix();
    glPushMatrix(); ///bedlamp
    bedlamp();
    glPopMatrix();
    glPushMatrix();///bedroomdoor
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(mov2,0,0);
    glTranslatef(-55,0,0.5);
    glScalef(0.67,1,1);
    door();
    glPopMatrix();
    glPushMatrix();///bed
    glTranslatef(-78,-8,-8);
    //glTranslatef(6,1,0);
    bed();
    glPopMatrix();
    glPushMatrix();///tv
    tv();
    glPopMatrix();
    glPushMatrix(); ///ALMIRAH
    glScalef(0.7,1.1,1);
    glTranslatef(-122.8,-3.0,23);
    glRotatef( 90, 0, 1, 0 );
    almirah();
    glPopMatrix();
    glPushMatrix();///dressingtable
    glTranslatef(0,0,10);
    dressingtable();
    glPopMatrix();
    glPushMatrix();///sidetable
    sidetable();
    glPopMatrix();
    glPushMatrix();///bedframe
    glTranslatef(-79,3.5,-24);
    frame(4);
    glPopMatrix();
    glPushMatrix();///fan
    glTranslatef(-70,17,0);
    glRotatef(alpha,0,1,0);

    glScalef(0.6,.6,.6);
    fan();
    glPopMatrix();
    glPushMatrix();///fanrod
    glTranslatef(-70,19.6,0);
    glScalef(0.25,2,.25);
    drawcube(0.545, 0.271, 0.075);
    glPopMatrix();

    glDisable(GL_LIGHT1);

    ///DININGROOM
if(light5){glEnable( GL_LIGHT5);e5=true;  }///LIGHT5
    else if (!light5){  glDisable(GL_LIGHT5); e5=false;  }

     glPushMatrix(); ///clock
glTranslatef(-29,7,-20);
glScalef(0.7,.7,.7);
    clockfire();
    glPopMatrix();
    glPushMatrix(); ///sofalamp
    sofalamp();
    glPopMatrix();
    glPushMatrix(); ///firelight
    firelight();
    glPopMatrix();
    glPushMatrix(); ///dininglamp
    dininglamp();
    glPopMatrix();
    glPushMatrix();///dining1door
    glScalef(.8,1,1);
    //glTranslatef(mov,0,0);
    glTranslatef(-14,0,-0.7);
    door();
    glPopMatrix();
    glPushMatrix();///dining2door
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(mov,0,0);
    glScalef(.8,1,1);
    glTranslatef(-33,0,0);
    door();
    glPopMatrix();
    glPushMatrix();///diningback
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(mov4,0,0);
    glTranslatef(-35.5,0,-64.4);
    glScalef(0.6,1,1);
    door();
    glPopMatrix();
   glPushMatrix();///diningset
    diningset();
    glPopMatrix();
    glPushMatrix();///sofa
    sofa();
    glPopMatrix();
    glPushMatrix();///fire
    glTranslatef(6,0,0);
    fire();
    glPopMatrix();
    glPushMatrix();///sofaframe
    glTranslatef(-16,3,22);
    glRotatef(-90,0,1,0);
    frame(6);
    glPopMatrix();
    glPushMatrix();///sofaframe
    glTranslatef(-16,3,30);
    glScalef(1,1.0,.5);
    glRotatef(-90,0,1,0);
    frame(5);
    glPopMatrix();

    glDisable(GL_LIGHT5);


    ///KITCHEN
    if(light6){glEnable( GL_LIGHT6);e6=true;  }///LIGHT1
    else if(!light6){  glDisable(GL_LIGHT6); e6=false;  }

    glPushMatrix(); ///kitlight
    kitlight();
    glPopMatrix();
    glPushMatrix();///kitchendoor
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(mov3,0,0);
    glTranslatef(2.9,-2,-33);
    glScalef(0.5,0.8,1);
    door();
    glPopMatrix();
    glPushMatrix(); ///fridge
    fridge();
    glPopMatrix();
    glPushMatrix();///cabinet
    cabinet();
    glPopMatrix();
    glPushMatrix();///oven
    oven();
    glPopMatrix();

glDisable(GL_LIGHT6);


    glPushMatrix();///wall
    housewall();
    glPopMatrix();

    glPushMatrix();///roof
    roof();
    glPopMatrix();


}

void foodcorner()
{
       color(1,1,1);///roof
    glPushMatrix();
    glTranslatef(0,7.7,0);
    glRotatef(-90,1,0,0);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
glBindTexture(GL_TEXTURE_2D, ID[13]);
glEnable(GL_TEXTURE_2D);
    glutSolidCone(10,9,10,10);
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


glBindTexture(GL_TEXTURE_2D, ID[13]);
glEnable(GL_TEXTURE_2D);
    glPushMatrix(); ///body
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(0,1,0);
    glScalef(4,2.8,7);
    //glRotatef(90,0,1,0);
    drawcube(0.941, 0.902, 0.549);
    glPopMatrix();


    int n=0;
    for(int i=0;i<2;i++)//upper leg
     {
         int m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-3.5,7.0,n-3.5);
                glScalef(0.3,3.3,0.3);
                drawcube(1.000, 0.549, 0.000);
                glPopMatrix();
                m=m+7.5;
         }
         n=n+9.5;
     }

glPushMatrix(); ///bodyup
    //glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(0,3.7,0);
    glScalef(4.5,0.3,7.5);
    //glRotatef(90,0,1,0);
    drawcube(1.000, 0.549, 0.000);
    glPopMatrix();

n=0;
    for(int i=0;i<2;i++)//lower leg
     {
         int  m=0;
         for(int j=0;j<2;j++)
         {
                glPushMatrix();
                glTranslatef(m-3.5,-2.5,n-3.5);
                glScalef(0.3,1,0.3);
                drawcube(1.000, 0.549, 0.000);
                glPopMatrix();
                m=m+7.0;
         }
         n=n+9.5;
     }


glDisable(GL_TEXTURE_2D);

for (int j=0;j<2;j++)///glass
{
    for(int i=0;i<2;i++)
{

    glPushMatrix();
    glScalef(0.8,0.8,0.8);
    glTranslatef(-2+i*1.5,6.3,1+j*1.5);
    glass();
    glPopMatrix();
}
}
glPushMatrix();///basket
    //glScalef(0.8,0.8,0.8);
    glTranslatef(2,3.9,4);
    basket();
    glPopMatrix();

glBindTexture(GL_TEXTURE_2D, ID[13]);
    glEnable(GL_TEXTURE_2D);
color(0.871, 0.722, 0.529);
glPushMatrix(); ///stool
    glTranslatef(0,3.6,-11.5);
    //glRotatef( 180, 0, 01, 0.0 );
    glScalef(0.9,1.3,0.9);
    stool(0.627, 0.322, 0.176,0.871, 0.722, 0.529);
    glPopMatrix();

color(0.871, 0.722, 0.529);
glPushMatrix(); ///stool
    glTranslatef(-8,3.6,.5);
    glScalef(0.9,1.3,0.9);
    stool(0.627, 0.322, 0.176,0.871, 0.722, 0.529);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

 glPushMatrix();
    glTranslatef(-1,8.1,-1.8);
    glRotatef(10,0,0,01);
    coco();
    glPopMatrix();

}

void umbrellachair()
{

    glPushMatrix(); ///BEACHCHAIR
    glRotatef( theta, 0, 01, 0.0 );
    glTranslatef(-15,-12,18);
    glRotatef(-90,0,1,0);
    glScalef(0.5,0.8,0.9);
    beachchair();
    glPopMatrix();

    glPushMatrix(); ///UMBRELLA
    glRotatef( theta, 0, 01, 0.0 );
    glTranslatef(-21,-8,12);
    glScalef(0.5,0.8,0.5);
    glRotatef(-8,0,0,1);
    umbrella(1,1,1,	1.0, 1.0, 1.000,23,25);
    glPopMatrix();
}

void strings()
{
    glPushMatrix();///string
    glTranslatef(-0.45,-6.67,0);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();///string
    glTranslatef(0.1,-7.1,0);
    glRotatef(-70,0,0,1);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();///string
    glTranslatef(0,-7.78,0);
    glRotatef(-130,0,0,1);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();///string
    glTranslatef(-0.8,-7.78,0);
    glRotatef(-220,0,0,1);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();///string
    glTranslatef(-1.0,-7.2,0);
    glRotatef(-280,0,0,1);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,01);
    glPopMatrix();

    glPushMatrix();///string
    glTranslatef(-7,-6.3,0);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();///string
    glTranslatef(-7.5,-6.7,0);
    glRotatef(60,0,0,1);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();///string
    glTranslatef(0-6.7,-7.3,0);
    glRotatef(-130,0,0,1);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,1);
    glPopMatrix();
    glPushMatrix();///string
    glTranslatef(-6.4,-6.7,0);
    glRotatef(-240,0,0,1);
    glScalef(0.07,0.6,0.07);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();///string
    glTranslatef(-7.4,-7.5,0);
    glRotatef(150,0,0,1);
    glScalef(0.07,0.6,0.07);
    drawcube(1,1,1);
    glPopMatrix();

}

void cycle()
{
    color(0,0,0);
    glPushMatrix();///wheel
    glTranslatef(-0.5,-7.29,0);
    glutSolidTorus(.15,1.5,60,60);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7,-7,0);
    glutSolidTorus(.15,1.5,60,60);
    glPopMatrix();
    color(1,1,1);
    glPushMatrix();///wheel
    glTranslatef(-0.5,-7.29,0);
    glutSolidTorus(.18,1.2,60,60);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-7,-7,0);
    glutSolidTorus(.18,1.2,60,60);
    glPopMatrix();


glBindTexture(GL_TEXTURE_2D, ID[39]);
glEnable(GL_TEXTURE_2D);
    strings();

    glPushMatrix();
    glTranslatef(-2.73,-6,0);
    glRotatef(40,0,0,1);
    glScalef(2,0.1,0.1);
    drawcube(1,1,1);
    glPopMatrix();
     glPushMatrix();
    glTranslatef(-4.7,-6,0);
    glRotatef(20,0,0,1);
    glScalef(.1,1.5,0.1);
    drawcube(1,1,1);
    glPopMatrix();
 glPushMatrix();
    glTranslatef(-1.5,-4,0);
    glRotatef(20,0,0,1);
    glScalef(.1,1,0.1);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8,-6,0.3);
    glRotatef(20,0,0,1);
    glScalef(.05,1.5,0.05);
    drawcube(0,0,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.8,-6,-0.3);
    glRotatef(20,0,0,1);
    glScalef(.05,1.5,0.05);
    drawcube(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.2,-5,0);
    glScalef(1.9,0.1,0.1);
    drawcube(1,1,1);
    glPopMatrix();
     glPushMatrix();//paddle
    glTranslatef(-5.6,-7,0.25);
    glScalef(1.3,0.07,0.07);
    drawcube(1,1,1);
    glPopMatrix();
     glPushMatrix();
    glTranslatef(-5.6,-7,-0.25);
    glScalef(1.3,0.07,0.07);
    drawcube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5.76,-6.4,-0.25);
    glRotatef(30,0,0,1);
    glScalef(1.2,0.07,0.07);
    drawcube(0,0,1);
    glPopMatrix();
     glPushMatrix();
    glTranslatef(-5.76,-6.4,0.25);
    glRotatef(30,0,0,1);
    glScalef(1.2,0.07,0.07);
    drawcube(1,1,1);
    glPopMatrix();
glPushMatrix();
    glTranslatef(-1.3,-4.6,0);
    //glRotatef(30,0,0,1);
    glScalef(0.07,0.07,.38);
    drawcube(1,1,1);
    glPopMatrix();

    ///paddle
    glPushMatrix();
    glTranslatef(-4.5,-7,0.4);
    glutSolidTorus(.1,0.3,60,60);
    glPopMatrix();
    glPushMatrix();//handle
    glTranslatef(-4.3,-7.5,0.3);
    //glRotatef(30,0,0,1);
    glScalef(0.07,0.5,0.07);
    drawcube(1,01,01);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.1,-8,0.4);
    //glRotatef(30,0,0,1);
    glScalef(0.26,0.07,.1);
    drawcube(0,0,0);
    glPopMatrix();
    ///wheelcenter
    glPushMatrix();
    glTranslatef(-.38,-7.3,0);
    //glRotatef(30,0,0,1);
    glScalef(0.07,0.07,.3);
    drawcube(01,01,1);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(-6.9,-7,0);
    //glRotatef(30,0,0,1);
    glScalef(0.07,0.07,.3);
    drawcube(01,01,1);
    glPopMatrix();

        ///seat
    color(1,1,1);
    glPushMatrix();
    glTranslatef(-5.3,-4.2,0);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj, TRUE);
    gluCylinder(obj, .7, 1, 0.7, 30, 30);
    glEnd();
    glPopMatrix();
    color(1,1,1);
    glPushMatrix();
    glTranslatef(-5.3,-4.2,0);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,.7,70,60);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.3,-4.7,0);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,0.75,70,60);
    glEnd();
    glPopMatrix();

    ///bell
    glPushMatrix();
    glTranslatef(-1.76,-3,0);
    //glRotatef(30,0,0,1);
    glScalef(0.07,0.07,.6);
    drawcube(01,01,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.74,-2.8,0.6);
    glRotatef(30,0,0,1);
    glScalef(0.07,0.4,.07);
    drawcube(01,01,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.74,-2.8,-0.6);
    glRotatef(30,0,0,1);
    glScalef(0.07,0.4,.07);
    drawcube(01,01,1);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
    glPushMatrix();//handle
    glTranslatef(-2.3,-2.5,0.6);
    //glRotatef(30,0,0,1);
    glScalef(0.4,0.07,0.07);
    drawcube(1.000, 0.894, 0.71);
    glPopMatrix();
    glPushMatrix();//handle
    glTranslatef(-2.3,-2.5,-0.6);
    //glRotatef(30,0,0,1);
    glScalef(0.4,0.07,0.07);
    drawcube(1.000, 0.894, 0.71);
    glPopMatrix();



}

void swing()
{
        glPushMatrix();
    //glTranslatef(-90,-12.6,-3);
    //glRotatef(90,0,0,01);
    //glRotatef(180,01,0,0);
    //glRotatef(45,01,0,00);
    glScalef(2,2,2);
    slide();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.3,-6.7,-3.5);
    glScalef(0.3,0.13,3.8);
    drawcube(0.627, 0.322, 0.176);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-11.7,-4.6,-3.5);
    glScalef(0.3,0.13,3.8);
    drawcube(0.627, 0.322, 0.176);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.5,-5.6,-2.5);
    //glRotatef(40,01,0,0);
    glRotatef(25,0,0,1);
    glScalef(3.3,0.1,.1);
    drawcube(0,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14.5,-3.6,-2.5);
    //glRotatef(40,01,0,0);
    glRotatef(-25,0,0,1);
    glScalef(3.3,0.1,.1);
    drawcube(0,0,1);
    glPopMatrix();
}

void swingtree()
{
    glPushMatrix();
    glTranslatef(-3,-2,13);
    glScalef(0.7,1,1);
    swing();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,3,10);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3,10);
    tree2();
    glPopMatrix();
}

void slidehouse()
{



 glPushMatrix();///slide
 glTranslatef(-80,-11.9,-19);
glRotatef( -53,0,01,0);
//glRotatef(260,0,0,01);
glScalef(1.5,1.5,2);
waterslide();
glPopMatrix();


color(0.275, 0.510, 0.706);

    glPushMatrix();///leg
    glTranslatef(-90,-1.5,-20);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *objj = gluNewQuadric();
    gluCylinder(objj, 2, 2, 19, 100, 100);
    glEnd();
    glPopMatrix();


                glPushMatrix();
                glTranslatef(-76,-12.5,-9);
                //glRotatef( -53,0,01,0);
                glScalef(0.3,3,0.3);
                drawcube(0.275, 0.510, 0.706);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(-79,-12.5,-8);
                //glRotatef( -53,0,01,0);
                glScalef(0.3,3,0.3);
                drawcube(0.275, 0.510, 0.706);
                glPopMatrix();


color(	0.098, 0.098, 0.439);
    glPushMatrix();///center
    glTranslatef(-90,0,-20);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 8.0, 8, 5, 30, 30);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-90,0,-20);
    glRotatef(90,1,0,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluDisk(ob,0,8,70,60);
    glEnd();
    glPopMatrix();

}


void seabeach()
{


glPushMatrix();///trees
trees();
glPopMatrix();
glPushMatrix();
glTranslatef(36,3,40);
tree2();
glPopMatrix();
glPushMatrix();///cycle
glTranslatef(025,-0.3,40);
glRotatef(-30,0,01,0);
glScalef(1.5,1.5,1.5);
cycle();
glPopMatrix();

glPushMatrix();///swing
glTranslatef(40,0,55);
glRotatef(-90,0,1,0);
swingtree();
glPopMatrix();


 glPushMatrix(); ///YARD
    //glRotatef( theta, 0, 01, 0.0 );
    glTranslatef(7,0,16);
    frontyard();
    glPopMatrix();

    glPushMatrix(); ///BEACH
    glRotatef( theta, 0, 01, 0.0 );
    glTranslatef(0,-4,7);
    beach();
    glPopMatrix();


    glPushMatrix();///HOUSE
    glRotatef(theta, 0, 01, 0.0 );
    glTranslatef(40,-5.5,23);
    glScalef(0.7,0.7,0.7);
    glRotatef(-90,0,1,0);
    house();
    glPopMatrix();

     glPushMatrix();///cocout
    glTranslatef(-25,-7.5,48);
    glRotatef(-15,0,0,1);
    coco();
    glPopMatrix();
glPushMatrix(); ///bEACHCHAIR
    glRotatef( theta, 0, 01, 0.0 );
    glTranslatef(-15,-12,7);
    glRotatef(-90,0,1,0);
    glScalef(0.5,0.8,0.9);
    beachchair();
    glPopMatrix();
int nn=0;
for(int i=0;i<2;i++){

    glPushMatrix();///umbrella chair
    umbrellachair();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,nn+15);
    umbrellachair();
    glPopMatrix();
    nn+=15;
}
     nn=0;
for(int i=0;i<5;i++){
    glPushMatrix();///umbrella chair

    glTranslatef(0,0,-70-nn);
    umbrellachair();
    glPopMatrix();
    nn+=15;
}


    glPushMatrix();///stair
glTranslatef(-40,-6,-76);
glRotatef(30,0,0,01);
glRotatef(90,0,01,0);
glScalef(0.5,.7,.5);
stair(	0.098, 0.098, 0.439);
glPopMatrix();

    glPushMatrix(); ///slidehouse
    glTranslatef(-70,3,12);
    glRotatef(-90,0,01,0);
    slidehouse();
    glPopMatrix();

    glPushMatrix(); ///ROUNDhouse
    glRotatef(theta, 0, 01, 0.0 );
    glTranslatef(20,-7.5,10);
    glScalef(0.5,0.5,0.5);
    glRotatef(-90,0,1,0);
    roundhouse();
    glPopMatrix();

glPushMatrix(); ///BOAT
    glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-100,-12,-19+t);
    glScalef(3.5,2,5);
    glRotatef(90,0,1,0);
    boat();
    glPopMatrix();
    glPushMatrix(); ///BOAT2
    glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-47,-13,55);
    glScalef(0.7,0.6,0.6);
    boat2();
    glPopMatrix();
    glPushMatrix(); ///BOAT2
    glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-47,-13,67);
    glScalef(0.7,0.6,0.6);
    boat2();
    glPopMatrix();

    color(1.000, 0.871, 0.678);
     glPushMatrix();
     glTranslatef(-23,-11.7,0);
     glRotatef(80,0,1,0);
    glutSolidTorus(0.5,1.5,20,20);
    glPopMatrix();

   glPushMatrix(); ///TOWER
    glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(-30,.5,-10);
    glScalef(.4,.5,.4);
    //glRotatef(90,0,1,0);
    tower();
    glPopMatrix();


    glPushMatrix(); ///FOODCORNER
    glRotatef( theta, 0, 1, 0.0 );
    glTranslatef(40,-10,85);
    glScalef(1.4,1.4,1.4);
    //glRotatef(90,0,1,0);
    foodcorner();
    glPopMatrix();

    glPushMatrix();///surf
    glTranslatef(30,-18,56.8);
    glRotatef(-15,01,0,0);
    glRotatef(90,0,0,01);
    glScalef(2,2,9);
     surf();
     glPopMatrix();


}

void parachute()
{
    glPushMatrix();
    glTranslatef(p,0,0);
    glTranslatef(-60,15,-25);
    glScalef(1.5,1.5,1.5);
    balloon(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-p,0,0);
    glTranslatef(-5,15,10);
    para(0);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(p,0,0);
    glTranslatef(-25,30,10);
    para(3);
    glPopMatrix();

         glPushMatrix();
     glTranslatef(-p,0,0);
    glTranslatef(10,20,10);
    para(8);
    glPopMatrix();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(px,dy,pz,B[0][0],B[0][1],B[0][2],0,1,0);

    glPushMatrix();///LIGHT
    if(turn){rot(a);}
    if(hou) glTranslatef(dx,-4,dz+76);
    else glTranslatef(dx,-4,dz);//dz+76
    light();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID[34]);
    glEnable(GL_TEXTURE_2D);
    color(1,1,1);
    glPushMatrix();///sphere SKY
    if(turn){rot(a);}
    if(hou) glTranslatef(dx,-4,dz+76);
    else glTranslatef(dx,-4,dz);//dz+76
    glTranslatef(0,150,40);
    glRotatef(180,0,01,0);
    glRotatef(-90,01,00,0);
    glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj, TRUE);
    gluSphere(obj,405,100,100);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

  glPushMatrix();///BEACH
    if(turn)
        {rot(a);}
    if(hou) glTranslatef(dx,-4,dz+76);
    else glTranslatef(dx,-4,dz);//dz+76
    seabeach();
    glPopMatrix();

  glPushMatrix();
    if(turn)
        {rot(a);}
    if(hou) glTranslatef(dx,-4,dz+76);
    else glTranslatef(dx,-4,dz);//dz+76
    parachute();
    glPopMatrix();




    glFlush();
    glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y) {

float r=1.5;

    switch (key) {
        case GLUT_KEY_LEFT :
            turn = !turn;
            a = -r;
            A[0][0]=px;
            A[0][1]=dy;
            A[0][2]=pz;
            A[0][3]=1;
            temp+=1;

            break;
        case GLUT_KEY_RIGHT :
            turn = !turn;
            a = r;
            A[0][0]=px;
            A[0][1]=dy;
            A[0][2]=pz;
            A[0][3]=1;
            temp+=1;
            break;
        case GLUT_KEY_UP :

            if(openn)
            {
                if((dz<6 && dz>=-4) )  dz += 1;
                else if (dz<6 && dz>=-10 && dx<-49) dz += 1;
                else if(  dx>=-40 &&dz<-10 && dz>=-27) dz+=1;
                else if (dx<=-40 && dz<-27 ) dz+=1;

            }
            else dz += 3;
            break;
        case GLUT_KEY_DOWN :
            if(openn)
            {
                if(dz<=6 && dz>-4) dz -= 1;
               else if (dz<=6 && dz>-10 && dx<-49) dz -= 1;
                else if ( dx>=-40 && dz<=-10 && dz>-27)  dz=dz-1;
                 else if ( dx<-40 && dz<=-27 )  dz=dz-1;
            }
            else dz -= 3;
            break;
    }
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {


    case 'j': ///bird's eye
        case 'J':
        pz=40;
        dy=120;
        B[0][0]=0;//106;
        B[0][1]=-100;
        B[0][2]=0;//36;
        B[0][3]=1;
        hou=false;
        break;
    case 'k': ///house
        case 'K':
        pz=50;
        dy=-8;
        B[0][0]=106;
        B[0][1]=dy;
        B[0][2]=36;
        B[0][3]=1;
        hou=true;
        break;
    case 'l': ///normal
        case 'L':
        pz=50;
        dy=-8;
        B[0][0]=0;//106;
        B[0][1]=-dy;
        B[0][2]=-60;//36;
        B[0][3]=1;
        hou=false;
        break;
       case 't':
           case 'T':
           boatmov=!boatmov;
            break;
        case 'g':
             case 'G':

                 if(openn)
                 {
                     if(dz <=-35 && dx<-42 && dx>=-52) {dx = dx + 1; }
                     else if ( dz<-17 && dz>=-25 && dx>=-32 && dx<-22) {dx+=1;  }
                     else  if (dz>=-17 && dx<-12 && dx>=-52){ dx = dx + 1;}

                     else  if (dz<-25 && dz>-35 && dx<-22 && dx>=-52){ dx = dx + 1;  }

                 }
                else dx = dx + 3;

            if(op) {dx=dx+10; openn+=1; op=false; }
             if(op2) {dx=dx+40; openn+=1; op2=false; }
             if(op3) {dx=dx+40; openn+=1; op3=false; }
             if(op4) {dx=dx+40; openn+=1; op4=false; }


            break;
        case 'h':
             case 'H':
                 if(openn)
                 {
                     if(dz <=-35 && dx<=-42 && dx>-52){ dx = dx - 1;  }
                     else if ( dz<=-17 && dz>-25 && dx>-32 && dx<=-22) {dx-=1;  }
                     else if (dz>-17 && dx<=-12 && dx>-52) {dx = dx - 1; }
                     else  if (dz<=-25 && dz>-35 && dx<=-22 && dx>-52){ dx = dx - 1;  }

                 }
            else dx = dx - 3;
            if(op)  {dx=dx-10; openn+=1; op=false;}
            if(op2) {dx=dx-10; openn+=1; op2=false;}
            if(op3) {dx=dx-10; openn+=1; op3=false;}
            if(op4) {dx=dx-10; openn+=1; op4=false;  }

            break;
        case 'b':
        case 'B':
            open = !open;
            break;

    case 'S':
        case 's':
        bRotate = !bRotate;

        break;

    case 'm':
        case 'M':
        m1=m1+1;
        break;
    case 'n':
        case 'N':
        m2=m2+1;
        break;
    case 'o':
        case 'O':
        m3=m3+1;
        break;
    case 'p':
        case 'P':
        m4=m4+1;
        break;

    case 'u':
    case 'U':
        dy+=3;
        break;

    case 'D':
        case 'd':
        dy-=3;
        break;


   case 'r':
       case 'R':
        aRotate = !aRotate;
        break;

    case '0':
        light0=!light0;
        break;
    case '1':
        light1=!light1;
        break;

    case '7':
        light2=!light2;
        break;
    case '3':
        light3=!light3;
        break;
    case '2':
        light4=!light4;
        break;
    case '5':
        light5=!light5;
        break;
    case '6':
        light6=!light6;
        break;
    case '4':
        light7=!light7;
        break;
    case '9':
        off= !off;
        break;

    case 'w':
        case 'W':
        s1=!s1;
        break;

    case 'e':
        case 'E':
        d1=!d1;
        break;

    case 'q':
        case 'Q':
        a1=!a1;

        break;
    case 27:	// Escape key
        exit(1);
    }
}


void animate()
{

        if(pr == true)
    {

        if(p>70) p1=true;
        if (!p1) p = p + .7;
        else  p =p-.7;
        if(p<-70) p1=false;
    }
    if(temp)
    {
       refx= B[0][0];
       refy= B[0][1];
       refz= B[0][2];
       temp=0;
    }
    if(boatmov == true)
    {

        if(t>110) b=true;
        if (!b) t = t + 3;
        else  t =t-3;
        if(t<-140) b=false;
    }
    if (bRotate == true)
    {
        theta += 5.04;
        if(theta >360.0)
            theta -=360.0*floor(theta/360.0);;
    }
    if (aRotate == true)
    {
        alpha += 3.2;
        if(alpha >360.0)
            alpha -=360.0*floor(alpha/360.0);;
    }
    if(m1 ==1)
    {
        mov+=04.5;
        if(mov>13.9)
         {//dx=dx-10;
            m1=m1+1;
            op=true;}
    }
    else if(m1 ==3)
    {
        mov-=04.5;
        if(mov<=0)
          {
              openn-=1;
            m1=0;}
    }
    if(m2==1)
    {
        mov2-=02.5;
        if(mov2<-9)
           {
            m2=m2+1;
            op2=true;}

    }
    else if(m2 ==3)
    {
        mov2+=02.5;
        if(mov2>=-2)
            {openn-=1;
            m2=0;}
    }
    if(m3==1)
    {
        mov3+=02.5;
        if(mov3>7)
            {//dx=dx-10;
            m3=m3+1;
            op3=true;}
    }
    else if(m3 ==3)
    {
        mov3-=02.5;
        if(mov3<=0)
            {m3=0;
            openn-=1;}
    }
    if(m4==1)
    {
        mov4-=02.5;
        if(mov4<-9)
            //dx=dx-10;
           {
            m4=m4+1;
            op4=true;}
    }
    else if(m4 ==3)
    {
        mov4+=02.5;
        if(mov4>-1)
          { m4=0;
            openn-=1;}
    }

  glutPostRedisplay();

}
void console()
{
    std::cout<<"FOR LIGHTS:\n";
    std::cout<<"\tTO OFF GLOBAL LIGHT PRESS 9\n";
    std::cout<<"\tFOR BEDROOM LIGHT PRESS 1\n";
    std::cout<<"\tFOR BEDSIDE LAMP(SPOTLIGHT) PRESS 2\n";
    std::cout<<"\tFOR SPOTLIGHT OVER DINING TABLE PRESS 3\n";
    std::cout<<"\tFOR LAMP BESIDE SOFA PRESS 4\n";
    std::cout<<"\tFOR DINING ROOM LIGHT PRESS 5\n";
    std::cout<<"\tFOR KITCHEN LIGHT PRESS 6\n";
    std::cout<<"\tFOR LIGHT OVER FOOD CORNER PRESS 7\n";
    std::cout<<"\tTO CHECK AMBIENT, DIFFUSE, SPECULAR EFFECT PRESS 'q/Q','e/E','w/W'\n\n";
    std::cout<<"\TO WALK:\n";
    std::cout<<"\tFRONT PRESS FRONT_ARROW\n";
    std::cout<<"\tBACK PRESS BACK_ARROW\n";
    std::cout<<"\tLEFT PRESS 'g/G'\n";
    std::cout<<"\tRIGHT PRESS 'h/H'\n";
    std::cout<<"\tROTATE PRESS LEFT/RIGHT ARROW\n";
    std::cout<<"\tUP PRESS 'u/U'\n";
    std::cout<<"\tDOWN PRESS 'd/D'\n\n";
    std::cout<<"\TO OPEN :\n";
    std::cout<<"\tUMBRELLA PRESS 'b/B'\n";
    std::cout<<"\tBEDROOM DOOR PRESS 'n/N'\n";
    std::cout<<"\tDINING DOOR PRESS 'm/M'\n";
    std::cout<<"\tKITCHEN DOOR PRESS 'o/O'\n";
    std::cout<<"\tBACK DOOR PRESS 'p/P'\n";
    std::cout<<"\tTO MOVE BOAT PRESS 't/T'\n";
    std::cout<<"\tTO CHANGE VIEW:\n";
    std::cout<<"\tTO BIRD'S EYE VIEW PRESS 'j/J'\n";
    std::cout<<"\tHOUSE FRONT PRESS 'k/K'\n";
    std::cout<<"\tBACK TO ORIGINAL VIEW PRESS 'l/L'\n";


}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Project-1607072");
    glutReshapeFunc(resize);
    glutMouseFunc(processMouse);

B[0][0]=0;//106;
B[0][1]=dy;
B[0][2]=-60;//36;
B[0][3]=1;
console();
   LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\oc.bmp",2);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\wood.bmp",3);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\m.bmp",4);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\photo.bmp",5);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\wp1.bmp",6);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\roof2.bmp",7);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\glass2.bmp",8);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\w3.bmp",9);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\w.bmp",0);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\tin.bmp",10);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\W4.bmp",11);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\s1.bmp",12);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\bam.bmp",13);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\bamm.bmp",14);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\table.bmp",15);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\cushions.bmp",16);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\marbel.bmp",17);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\bed4.bmp",18);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\bed6.bmp",20);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\rod.bmp",23);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\umm.bmp",24);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\red.bmp",25);//um
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\tin4.bmp",26);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\win2.bmp",27);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\roof.bmp",28);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\sc2.bmp",29);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\glass.bmp",30);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\cl.bmp",32);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\boat.bmp",33);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\sky7.bmp",34);//4 7* 12 14 yy
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\sofa4.bmp",36);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\wood2.bmp",38);
    LoadTexture("G:\\4.2\\CSE 4208 GRAPHICS LAB\\LAB4\\1607072\\textures\\tin3.bmp",39);
    glClearColor(0,0,0,1);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

glutSpecialFunc(processSpecialKeys);
glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);

    glutMainLoop();

    return 0;
}

