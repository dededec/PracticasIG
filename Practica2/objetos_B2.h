//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, char eje = 'y');

vector<_vertex3f> perfil; 
int num;
};

//************************************************************************
// clase cono
//************************************************************************

class _cono: public _rotacion
{
public:
	_cono(float abs = 1.0, float alt = 1.0, int num = 17, char eje = 'y');
};

//************************************************************************
// clase cilindro
//************************************************************************

class _cilindro: public _rotacion
{
public:
	_cilindro(float abs = 1.0, float alt = 1.0, int num = 17, char eje = 'y');
};

//************************************************************************
// clase esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
	_esfera(float radio = 1.0, int n = 5, int num = 17, char eje = 'y');
};

//************************************************************************
// clase rotacion PLY
//************************************************************************

class _rotacionPLY: public _rotacion
{
public:
	_rotacionPLY();
	void leer(char *archivo, int num = 17);
};


