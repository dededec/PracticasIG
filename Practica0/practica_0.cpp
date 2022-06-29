#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>



void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo)
{
	int i;
	if (modo==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (modo==GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glBegin( GL_POLYGON );
		for (i=0;i<n;i++)
			glVertex2f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
	glEnd();
}

void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);

       glColor3f(0.0,1.0,0.0); //Al trabajar con GL_FLAT, se coje el último color definido para la línea que vas a hacer. Con GL_SMOOTH hace lo que quieres que haga
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Monigote ()
{
  
		glLineWidth(1);
  glColor3f(1.0,0.8,0.35);
		Circle(0.3, 0.0, 0.3, 1000, GL_FILL); //radio, x, y, puntos, relleno
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
			glVertex3f(-0.2,0.4,0.0);
			glVertex3f(-0.25,0.7,0.0);
			glVertex3f(-0.05,0.5,0.0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(0.2,0.4,0.0);
			glVertex3f(0.25,0.7,0.0);
			glVertex3f(0.05,0.5,0.0);
		glEnd();

		glColor3f(1.0,1.0,1.0);
		Circle(0.1, -0.11, 0.35, 1000, GL_FILL); //radio, x, y, puntos, relleno
		Circle(0.1, 0.11, 0.35, 1000, GL_FILL); //radio, x, y, puntos, relleno

		glColor3f(0.0,0.0,0.0);
		glLineWidth(2);
	 glBegin(GL_LINES);
			glVertex3f(-0.11,0.45,0.0);
			glVertex3f(-0.11,0.25,0.0);
			
			glVertex3f(0.11,0.45,0.0);
			glVertex3f(0.11,0.25,0.0);

			//Linea nariz hacia abajo
			glVertex3f(0.0,0.15,0.0);
			glVertex3f(0.0,0.05,0.0);

			//Bigotillos
			glVertex3f(0.05,0.2,0.0);
			glVertex3f(0.37,0.22,0.0);

			glVertex3f(-0.05,0.2,0.0);
			glVertex3f(-0.37,0.22,0.0);

			glVertex3f(0.04,0.18,0.0);
			glVertex3f(0.23,0.15,0.0);

			glVertex3f(-0.04,0.18,0.0);
			glVertex3f(-0.23,0.15,0.0);

			glVertex3f(0.03,0.16,0.0);
			glVertex3f(0.15,0.1,0.0);

			glVertex3f(-0.03,0.16,0.0);
			glVertex3f(-0.15,0.1,0.0);
		glEnd();
		
		glBegin(GL_POLYGON);
			glVertex3f(-0.07,0.25,0.0);
			glVertex3f(0.07,0.25,0.0);
			glVertex3f(0.0,0.15,0.0);
		glEnd();
/* cara
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 glBegin(GL_POLYGON);
     glVertex3f(-0.3,0.2,0.0);
     glVertex3f(-0.2,0.2,0.0);
     glVertex3f(-0.2,0.35,0.0);
		 glVertex3f(-0.3,0.35,0.0);
   glEnd();
	glBegin(GL_POLYGON);
     glVertex3f(0.2,0.2,0.0);
     glVertex3f(0.3,0.2,0.0);
     glVertex3f(0.3,0.35,0.0);
     glVertex3f(0.2,0.35,0.0);
   glEnd();
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      //glColor3f(1.0,0.4,0.6);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 


   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 
		/*glBegin(GL_POLYGON);
     glVertex3f(-0.5,0.1,0.0);
     glVertex3f(0.5,0.1,0.0);
     //glColor3f(1.0,0.4,0.6);
     glVertex3f(0.5,0.25,0.0);
     glVertex3f(-0.5,0.25,0.0);
   glEnd();*/
   
}


static void Init( )
{

   glShadeModel( GL_FLAT );
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);
  glClear( GL_COLOR_BUFFER_BIT );
   
  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
		exit(0);
		
	if(key == 'a'){
		glShadeModel( GL_SMOOTH);
		Display();
	}
 		
	if(key == 'b'){
		glShadeModel(GL_FLAT);
		Display();
	}

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 );
   glutInitWindowSize(500, 500 );
   glutCreateWindow("Practica 0 IG");


   Init();

   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop( );

   return 0;
}

