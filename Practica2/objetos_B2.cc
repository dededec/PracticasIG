//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"
#include <algorithm>

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		if(i%2 == 0) glColor3f(r1,g1,b1);
		else glColor3f(r2,g2,b2);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
float alt = tam*2;
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;

vertices[4].x=-tam;vertices[4].y=alt;vertices[4].z=tam;
vertices[5].x=tam;vertices[5].y=alt;vertices[5].z=tam;
vertices[6].x=tam;vertices[6].y=alt;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=alt;vertices[7].z=-tam;
// triangulos
caras.resize(12);

caras[0]._0=4;caras[0]._1=0;caras[0]._2=5;
caras[1]._0=0;caras[1]._1=1;caras[1]._2=5;
caras[2]._0=1;caras[2]._1=2;caras[2]._2=5;
caras[3]._0=5;caras[3]._1=2;caras[3]._2=6;
caras[4]._0=3;caras[4]._1=2;caras[4]._2=7;
caras[5]._0=7;caras[5]._1=2;caras[5]._2=6;

caras[6]._0=4;caras[6]._1=0;caras[6]._2=7;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=0;caras[8]._1=1;caras[8]._2=3;
caras[9]._0=3;caras[9]._1=1;caras[9]._2=2;
caras[10]._0=4;caras[10]._1=5;caras[10]._2=6;
caras[11]._0=4;caras[11]._1=6;caras[11]._2=7;
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
for(int i=0; i<n_ver;++i){
	ver_aux.x = ver_ply[i*3];
	ver_aux.y = ver_ply[i*3+1];
	ver_aux.z = ver_ply[i*3+2];
	vertices[i] = ver_aux;
}

_vertex3i car_aux;
for(int i=0; i<n_car; ++i){
	car_aux.x = car_ply[i*3];
	car_aux.y = car_ply[i*3+1];
	car_aux.z = car_ply[i*3+2];
	caras[i] = car_aux;
}


return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, char eje)
{
int i,j;
_vertex3f vertice_aux, vertice_auxB,vertice_auxC;
_vertex3i cara_aux;
int num_aux;



// tratamiento de los vértices

num_aux=perfil.size();

if(eje == 'y')
{

/*********************************
 *********************************
 *********** EJE Y ***************
 *********************************
 *********************************/

	if(perfil[0].y > perfil[num_aux-1].y)
	{
		reverse(perfil.begin(),perfil.end());
	}
	
	vertice_auxB.x = 1.0;
	vertice_auxC.x = 1.0;

	if(perfil[0].x == 0.0)
	{
		vertice_auxB = perfil[0];
		perfil.erase(perfil.begin());
	}

	if(perfil[perfil.size()-1].x == 0.0)
	{
		vertice_auxC = perfil[perfil.size()-1];
		perfil.erase(--perfil.end());	
	}


	num_aux=perfil.size();


	vertices.resize(num_aux*num);

	//ROTAR SOBRE EL EJE Y
	for (j=0;j<num;j++)
  	{for (i=0;i<num_aux;i++)
    	{
		vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    	perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      	vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    	perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      	vertice_aux.y=perfil[i].y;
      	vertices[i+j*num_aux]=vertice_aux;

			}
  	}

	// tratamiento de las caras 
	caras.resize(vertices.size());
	for(j=0; j<num;++j)
		for(i=0; i<num_aux-1;++i){
			cara_aux.x = i+((j+1)%num)*num_aux;
			cara_aux.y = i+1+((j+1)%num)*num_aux;
			cara_aux.z = i+1+j*num_aux;
				
			caras.push_back(cara_aux);

			cara_aux.x = i+1+j*num_aux;
			cara_aux.y = i+j*num_aux;
			cara_aux.z = i+((j+1)%num)*num_aux;
				
			caras.push_back(cara_aux);
			
		}

	//Vértices eliminados
	if(vertice_auxB.x == 0.0){

		perfil.insert(perfil.begin(),vertice_auxB);
		vertices.push_back(vertice_auxB);
		
		cara_aux.y = vertices.size()-1;
		for(j=0;j<num;++j)
		{
			cara_aux.x=j*num_aux;
			cara_aux.z=((j+1)*num_aux)%(vertices.size()-1);
			
			caras.push_back(cara_aux);
		}
	}


	if(vertice_auxC.x == 0.0){ 

		perfil.push_back(vertice_auxC);
		vertices.push_back(vertice_auxC);
	
		cara_aux.y = vertices.size()-1;
		for(j=0;j<num;++j)
		{
			cara_aux.x=num_aux*(j+1)-1;
			cara_aux.z=(num_aux*(j+2)-1)%(num_aux*num);
			
			caras.push_back(cara_aux);
		}
	}

	// tapa inferior
	if (fabs(perfil[0].x)>0.0)
	{

		vertice_aux.x=0;
		vertice_aux.y=perfil[0].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);
		
		cara_aux.y = vertices.size()-1;
		for(j=0;j<num;++j)
		{
			cara_aux.x=j*num_aux;
			cara_aux.z=((j+1)*num_aux)%(vertices.size()-1);
			
			caras.push_back(cara_aux);
		}
	}


 
 	// tapa superior
 	if (fabs(perfil[perfil.size()-1].x)>0.0)
	{

		vertice_aux.x=0;
		vertice_aux.y=perfil[num_aux-1].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);
		
		cara_aux.y = vertices.size()-1;
		for(j=0;j<num;++j)
		{
			cara_aux.x=num_aux*(j+1)-1;
			cara_aux.z=(num_aux*(j+2)-1)%(num_aux*num);
			
			caras.push_back(cara_aux);
		}

	}

}
else if(eje == 'x')
{
/*********************************
 *********************************
 *********** EJE X ***************
 *********************************
 *********************************/


	if(perfil[0].x > perfil[num_aux-1].x)
	{
		reverse(perfil.begin(),perfil.end());
	}
	
	vertice_auxB.z = 1.0;
	vertice_auxC.z = 1.0;

	if(perfil[0].z == 0.0)
	{
		vertice_auxB = perfil[0];
		perfil.erase(perfil.begin());
	}

	if(perfil[perfil.size()-1].z == 0.0)
	{
		vertice_auxC = perfil[perfil.size()-1];
		perfil.erase(--perfil.end());	
	}


	num_aux=perfil.size();


	vertices.resize(num_aux*num);


	//ROTAR SOBRE EL EJE X
	for (j=0;j<num;j++)
  		{for (i=0;i<num_aux;i++)
     		{

      			vertice_aux.z=perfil[i].y*cos(2.0*M_PI*j/(1.0*num))+
                		    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      			vertice_aux.y=-perfil[i].y*sin(2.0*M_PI*j/(1.0*num))+
                		    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      			vertice_aux.x=perfil[i].x;
      			vertices[i+j*num_aux]=vertice_aux;

     		}
  		}


	// tratamiento de las caras 
	caras.resize(vertices.size());
	for(j=0; j<num;++j)
		for(i=0; i<num_aux-1;++i){
			cara_aux.x = i+((j+1)%num)*num_aux;
			cara_aux.y = i+1+((j+1)%num)*num_aux;
			cara_aux.z = i+1+j*num_aux;
				
			caras.push_back(cara_aux);

			cara_aux.x = i+1+j*num_aux;
			cara_aux.y = i+j*num_aux;
			cara_aux.z = i+((j+1)%num)*num_aux;
				
			caras.push_back(cara_aux);
			
		}

	//Vértices eliminados
	if(vertice_auxB.z == 0.0){

		perfil.insert(perfil.begin(),vertice_auxB);
		vertices.push_back(vertice_auxB);
		
		cara_aux.x = vertices.size()-1;
		for(j=0;j<num;++j)
		{
			cara_aux.z=j*num_aux;
			cara_aux.y=((j+1)*num_aux)%(vertices.size()-1);
			
			caras.push_back(cara_aux);
		}
	}


	if(vertice_auxC.z == 0.0){ 

		perfil.push_back(vertice_auxC);
		vertices.push_back(vertice_auxC);
	
		cara_aux.x = vertices.size()-1;
		for(j=0;j<num;++j)
		{
			cara_aux.z=num_aux*(j+1)-1;
			cara_aux.y=(num_aux*(j+2)-1)%(num_aux*num);
			
			caras.push_back(cara_aux);
		}
	}

	// tapa inferior
	if (fabs(perfil[0].z)>0.0)
	{
			vertice_aux.z=0;
			vertice_aux.x=perfil[0].x;
			vertice_aux.y=0;
			vertices.push_back(vertice_aux);
		
			cara_aux.z = vertices.size()-1;
			for(j=0;j<num;++j)
			{
				cara_aux.y=j*num_aux;
				cara_aux.x=((j+1)*num_aux)%(vertices.size()-1);
			
				caras.push_back(cara_aux);
			}
	}


 
 	// tapa superior
 	if (fabs(perfil[perfil.size()-1].z)>0.0)
	{

			vertice_aux.z=0;
			vertice_aux.x=perfil[num_aux-1].x;
			vertice_aux.y=0;
			vertices.push_back(vertice_aux);
		
			cara_aux.z = vertices.size()-1;
			for(j=0;j<num;++j)
			{
				cara_aux.y=num_aux*(j+1)-1;
				cara_aux.x=(num_aux*(j+2)-1)%(num_aux*num);
			
				caras.push_back(cara_aux);
			}

	}
}
else
{
/*********************************
 *********************************
 *********** EJE Z ***************
 *********************************
 *********************************/

	if(perfil[0].z > perfil[num_aux-1].z)
	{
		reverse(perfil.begin(),perfil.end());
	}

	vertice_auxB.x = 1.0;
	vertice_auxC.x = 1.0;

	if(perfil[0].x == 0.0)
	{
		vertice_auxB = perfil[0];
		perfil.erase(perfil.begin());
	}

	if(perfil[perfil.size()-1].x == 0.0)
	{
		vertice_auxC = perfil[perfil.size()-1];
		perfil.erase(--perfil.end());	
	}


	num_aux=perfil.size();


	vertices.resize(num_aux*num);

 
	//ROTAR SOBRE EL EJE Z
	for (j=0;j<num;j++)
	  {for (i=0;i<num_aux;i++)
	     {

	      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
	                    perfil[i].y*sin(2.0*M_PI*j/(1.0*num));
	      vertice_aux.y=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
	                    perfil[i].y*cos(2.0*M_PI*j/(1.0*num));
	      vertice_aux.z=perfil[i].z;
	      vertices[i+j*num_aux]=vertice_aux;

			}
	  }


	// tratamiento de las caras 
	caras.resize(vertices.size());
	for(j=0; j<num;++j)
		for(i=0; i<num_aux-1;++i){
			cara_aux.x = i+((j+1)%num)*num_aux;
			cara_aux.y = i+1+((j+1)%num)*num_aux;
			cara_aux.z = i+1+j*num_aux;
				
			caras.push_back(cara_aux);

			cara_aux.x = i+1+j*num_aux;
			cara_aux.y = i+j*num_aux;
			cara_aux.z = i+((j+1)%num)*num_aux;
				
			caras.push_back(cara_aux);
			
		}

	//Vértices eliminados
	if(vertice_auxB.x == 0.0){

		perfil.insert(perfil.begin(),vertice_auxB);
		vertices.push_back(vertice_auxB);
		
		cara_aux.z = vertices.size()-1;
		for(j=0;j<num;++j)
		{
			cara_aux.x=j*num_aux;
			cara_aux.y=((j+1)*num_aux)%(vertices.size()-1);
			
			caras.push_back(cara_aux);
		}
	}


	if(vertice_auxC.x == 0.0){ 

		perfil.push_back(vertice_auxC);
		vertices.push_back(vertice_auxC);
	
		cara_aux.z = vertices.size()-1;
		for(j=0;j<num;++j)
		{
			cara_aux.x=num_aux*(j+1)-1;
			cara_aux.y=(num_aux*(j+2)-1)%(num_aux*num);
			
			caras.push_back(cara_aux);
		}
	}

	// tapa inferior
	if (fabs(perfil[0].x)>0.0)
	{

			vertice_aux.x=0;
			vertice_aux.z=perfil[0].z;
			vertice_aux.y=0;
			vertices.push_back(vertice_aux);
		
			cara_aux.y = vertices.size()-1;
			for(j=0;j<num;++j)
			{
				cara_aux.x=j*num_aux;
				cara_aux.z=((j+1)*num_aux)%(vertices.size()-1);
			
				caras.push_back(cara_aux);
			}
	}


 
 	// tapa superior
 	if (fabs(perfil[perfil.size()-1].x)>0.0)
	{

			vertice_aux.x=0;
			vertice_aux.z=perfil[num_aux-1].z;
			vertice_aux.y=0;
			vertices.push_back(vertice_aux);
		
			cara_aux.z = vertices.size()-1;
			for(j=0;j<num;++j)
			{
				cara_aux.x=num_aux*(j+1)-1;
				cara_aux.y=(num_aux*(j+2)-1)%(num_aux*num);
			
				caras.push_back(cara_aux);
			}

	}
}

}

_cono::_cono(float abs, float alt, int num, char eje)
{
	_vertex3f v_aux;

	if(eje == 'y')
	{
		v_aux.x=abs;v_aux.y=0.0;v_aux.z=0.0;
		perfil.push_back(v_aux);
	
		v_aux.x=0.0;v_aux.y=alt;v_aux.z=0.0;
		perfil.push_back(v_aux);
	}
	else if(eje == 'x')
	{
		v_aux.z=0.0;v_aux.x=alt;v_aux.y=0.0;
		perfil.push_back(v_aux);

		v_aux.z=abs;v_aux.x=0.0;v_aux.y=0.0;
		perfil.push_back(v_aux);
	
		
	}
	else
	{
		v_aux.x=abs;v_aux.z=0.0;v_aux.y=0.0;
		perfil.push_back(v_aux);
	
		v_aux.x=0.0;v_aux.z=alt;v_aux.y=0.0;
		perfil.push_back(v_aux);
	}
	

	parametros(perfil,num,eje);
}

_cilindro::_cilindro(float abs, float alt, int num, char eje)
{
	_vertex3f v_aux;

	if(eje == 'y')
	{
		v_aux.x=abs;v_aux.y=alt;v_aux.z=0.0;
		perfil.push_back(v_aux);
	
		v_aux.x=abs;v_aux.y=0.0;v_aux.z=0.0;
		perfil.push_back(v_aux);
	}
	else if(eje == 'x')
	{
		v_aux.z=abs;v_aux.x=alt;v_aux.y=0.0;
		perfil.push_back(v_aux);
	
		v_aux.z=abs;v_aux.x=0.0;v_aux.y=0.0;
		perfil.push_back(v_aux);
	}
	else
	{
		v_aux.x=abs;v_aux.z=alt;v_aux.y=0.0;
		perfil.push_back(v_aux);
	
		v_aux.x=abs;v_aux.z=0.0;v_aux.y=0.0;
		perfil.push_back(v_aux);
	}

	

	parametros(perfil,num,eje);
}

_esfera::_esfera(float radio, int n, int num, char eje)
{
 
	_vertex3f v_aux;
	if(eje == 'y')
	{
		v_aux.x = 0.0;
		v_aux.y = -radio;
		v_aux.z = 0.0;
		perfil.push_back(v_aux);
		for (int i = 1; i < n; i++)
		{
			v_aux.x = radio * cos(3 * M_PI / 2 + M_PI * i / n);
			v_aux.y = radio * sin(3 * M_PI / 2 + M_PI * i / n);
			perfil.push_back(v_aux);
		}
		v_aux.x = 0.0;
		v_aux.y = radio;
		perfil.push_back(v_aux);
	}
	else if(eje == 'x')
	{
		v_aux.z = 0.0;
		v_aux.x = -radio;
		v_aux.y = 0.0;
		perfil.push_back(v_aux);
		for (int i = 1; i < n; i++)
		{
			v_aux.z = radio * cos(3 * M_PI / 2 + M_PI * i / n);
			v_aux.x = radio * sin(3 * M_PI / 2 + M_PI * i / n);
			perfil.push_back(v_aux);
		}
		v_aux.z = 0.0;
		v_aux.x = radio;
		perfil.push_back(v_aux);
	}
	else if(eje == 'z')
	{
		v_aux.x = 0.0;
		v_aux.z = -radio;
		v_aux.y = 0.0;
		perfil.push_back(v_aux);
		for (int i = 1; i < n; i++)
		{
			v_aux.x = radio * cos(3 * M_PI / 2 + M_PI * i / n);
			v_aux.z = radio * sin(3 * M_PI / 2 + M_PI * i / n);
			perfil.push_back(v_aux);
		}
		v_aux.x = 0.0;
		v_aux.z = radio;
		perfil.push_back(v_aux);
	}

	parametros(perfil,num,eje);
}

_rotacionPLY::_rotacionPLY()
{
}


void _rotacionPLY::leer(char* archivo, int num)
{
	int n_ver;
	vector<float> ver_ply;
	vector<int> car_ply;

	_file_ply::read(archivo, ver_ply, car_ply );

	n_ver=ver_ply.size()/3;

	_vertex3f ver_aux;
	for(int i=0; i<n_ver;++i){
		ver_aux.x = ver_ply[i*3];
		ver_aux.y = ver_ply[i*3+1];
		ver_aux.z = ver_ply[i*3+2];
		perfil.push_back(ver_aux);
	}
	
	parametros(perfil,num,'y');
}



