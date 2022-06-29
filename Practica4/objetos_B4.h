//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD} _modo;

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
void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave(float r, float g, float b);

void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void	calcular_normales_caras();
void 	calcular_normales_vertices();

vector<_vertex3i> caras;

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

bool b_normales_caras;
bool b_normales_vertices;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
float brillo;                  //exponente del brillo 

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
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);
_vertex3f rotateY(_vertex3f p, float alpha);

vector<_vertex3f> perfil; 
int num;
};

//************************************************************************
// clase esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
	_esfera(float radio = 1.0, int n = 15, int num = 17);
       void calcular_normales_vertices( );
};

//************************************************************************
// clase semiesfera
//************************************************************************

class _semiEsfera: public _rotacion
{
       public:
       _semiEsfera(float radio = 1.0, int n = 15, int num = 17);
       void calcular_normales_vertices( );
       
};

//************************************************************************
// clase cilindro
//************************************************************************

class _cilindro: public _rotacion
{
       public:
       _cilindro(float alt = 2.0, float anch = 1.0, int num=17);
};


//************************************************************************
// clase cono truncado
//************************************************************************

class _conoT: public _rotacion
{
       public:
       _conoT(float alt = 3.0, float anchInf= 1.0, float anchSup = 1.5, int  num = 17);
};

//************************************************************************
// clase tetraedro
//************************************************************************

class _tetraedro: public _triangulos3D
{
       public:
       _tetraedro(float lado=1.0);
};

//************************************************************************
// objecto articulado: Robot Pilaf
//************************************************************************
class _central: public _triangulos3D
{
       protected:
       _esfera esfera;

       public:
       _central();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class _mano: public _triangulos3D
{
       protected:
       _conoT antebrazo;
       _esfera puno;

       public:
       _mano();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

class _pie: public _triangulos3D
{
       protected:
       _esfera art;
       _semiEsfera jaba;
       _conoT pant = _conoT(3.0, 1.7, 1.0, 17); // _conoT(float alt = 3.0, float anchInf= 1.0, float anchSup = 1.5, int  num = 17);

       public:
       _pie();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


class _Pilaf: public _triangulos3D
{
       protected:
       _central cabina;
       _cilindro cilindro;
       _mano mano;
       _pie pie;

       public:
       float rebote;
       float giroCuerpo;
       float giroBrazoDerX, giroBrazoDerY, giroBrazoDerZ;
       float giroBrazoIzqX, giroBrazoIzqY, giroBrazoIzqZ;
       float giroManoDerZ, giroManoDerY;
       float giroManoIzqZ, giroManoIzqY;
       float giroPieDerX, giroPieIzqX;
       float giroPiernaDerX, giroPiernaIzqX;

       
       _Pilaf();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

};

//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tuboV, giro_tuboH;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};

