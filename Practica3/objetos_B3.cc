//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B3.h"
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
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
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
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
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
	if (i%2==0) glColor3f(r1,g1,b1);
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
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  
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
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
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

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
int i,j;
_vertex3f vertice_aux, vertice_auxB, vertice_auxC;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();

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

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
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
if (fabs(perfil[0].x)>0.0 && tapa==1)
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
 if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1)
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

//************************************************************************
// clase esfera
//************************************************************************

_esfera::_esfera(float radio, int n, int num)
{
 
	_vertex3f v_aux;
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

	parametros(perfil,num,0);
}


//************************************************************************
// clase semi-esfera
//************************************************************************

_semiEsfera::_semiEsfera(float radio, int n, int num)
{
	_vertex3f v_aux;
	perfil.push_back(v_aux);
	for (int i = 1; i <= n; i++)
	{
		v_aux.x = radio * cos(1 * M_PI / 2 + (M_PI * i / n)/2);
		v_aux.y = radio * sin(1 * M_PI / 2 + (M_PI * i / n)/2);
		perfil.push_back(v_aux);
	}
	parametros(perfil,num,1);
}

//************************************************************************
// clase cilindro
//************************************************************************

_cilindro::_cilindro(float alt, float anch, int num)
{
	_vertex3f v_aux;
	v_aux.x=anch;v_aux.y=0.0;v_aux.z=0.0;
	perfil.push_back(v_aux);
	
	v_aux.x=anch;v_aux.y=-alt;v_aux.z=0.0;
	perfil.push_back(v_aux);

	parametros(perfil,num,1);
}

//************************************************************************
// clase cono truncado
//************************************************************************

_conoT::_conoT(float alt, float anchInf, float anchSup, int num)
{
	_vertex3f v_aux;
	v_aux.x = anchInf; v_aux.y = 0; v_aux.z = 0.0;
	perfil.push_back(v_aux);

	v_aux.x = anchSup; v_aux.y = alt; v_aux.z = 0.0;
	perfil.push_back(v_aux);

	parametros(perfil,num,1);
}

//************************************************************************
// clase cono truncado
//************************************************************************

_tetraedro::_tetraedro(float lado)
{
	_vertex3f v_aux;
	_vertex3i cara_aux;
	float h = sqrt(pow(lado,2)-pow(lado/2,2));

	v_aux.x = 0.0; v_aux.y = lado*sqrt(6)/3; v_aux.z = h/3;
	vertices.push_back(v_aux);
	v_aux.y = 0.0; v_aux.z = 0.0; 
	v_aux.x = lado/2;
	vertices.push_back(v_aux);
	v_aux.x = -lado/2;
	vertices.push_back(v_aux);
	v_aux.x = 0.0; v_aux.z = h;
	vertices.push_back(v_aux);

	cara_aux._0 = 0; cara_aux._1 = 3; cara_aux._2 = 1;
	caras.push_back(cara_aux);
	cara_aux._1 = 2;
	caras.push_back(cara_aux);
	cara_aux._2 = 3;
	caras.push_back(cara_aux);
	cara_aux._0 = 3; cara_aux._2 = 1;
	caras.push_back(cara_aux);

}


//************************************************************************
// objeto articulado: Robot Pilaf
//************************************************************************

_central::_central()
{
}

void _central::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
		glScalef(2.0,2.0,2.0);
		esfera.draw(modo, r1-0.1,g1-0.1,b1-0.1, r2-0.1,g2-0.1,b2-0.1, grosor);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,0.25,0.75);
		glScalef(1.2,1.75,1.5);
		esfera.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,0.55,1.75);
		glScalef(0.75,0.75,0.75);
		esfera.draw(modo, r2,g2,b2, r1,g1,b1, grosor);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-1.8,0.0,0.0);
		glScalef(0.8,0.8,0.8);
		esfera.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1.8,0.0,0.0);
		glScalef(0.8,0.8,0.8);
		esfera.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
	glPopMatrix();
}

/****************************************************************************************************************/

_mano::_mano()
{
}

void _mano::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
		glScalef(0.2,0.2,0.2);
		
		glPushMatrix();
			antebrazo.draw(modo, r1-0.1,g1-0.1,b1-0.1, r2-0.1,g2-0.1,b2-0.1, grosor);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0,4.8,0.0);
			glScalef(2.7,2.2,2.7);
			puno.draw(modo, r2,g2,b2, r1,g1,b1, grosor);
		glPopMatrix();
	glPopMatrix();

}

/****************************************************************************************************************/

_pie::_pie()
{
}

void _pie::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
		glScalef(0.5,0.5,0.5);
		art.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,-2.5,0.2);
		glRotatef(-5.0,1,0,0);	
		glScalef(0.7,0.8,0.6);	
		pant.draw(modo, r1-0.1,g1-0.1,b1-0.1, r2-0.1,g2-0.1,b2-0.1, grosor);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,-3.5,0.9);
		glScalef(1.5,1.2,2.3);
		jaba.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
	glPopMatrix();
}

/****************************************************************************************************************/

_Pilaf::_Pilaf()
{
	rebote = 0.0;
	giroCuerpo = 0.0;
	giroBrazoDerX = giroBrazoDerY = giroBrazoDerZ = 0.0;
	giroBrazoIzqX = giroBrazoIzqY = giroBrazoIzqZ = 0.0;
    giroManoIzqZ = giroManoIzqY = 0.0;
	giroManoDerZ = giroManoDerY = 0.0;
	giroPieDerX = giroPieIzqX = 0.0;
	giroPiernaDerX = giroPiernaIzqX = 0.0;
}

void _Pilaf::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

	//PARTE SUPERIOR
	glPushMatrix();
		glTranslatef(0.0,rebote,0.0);
		glRotatef(giroCuerpo,0,1,0);


		glPushMatrix(); //Cabina
		glScalef(0.5,0.5,0.5);
		cabina.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
		glPopMatrix();


		glPushMatrix(); //Brazo izquierdo
			glTranslatef(1.0,0.0,0.0);
			glRotatef(giroBrazoIzqX,1,0,0);
			//if(giroBrazoIzqY < 80 && giroBrazoIzqY > -80) 
			glRotatef(giroBrazoIzqY,0,1,0);
			//if(giroBrazoIzqZ < 30 && giroBrazoIzqZ > -100) 
			glRotatef(giroBrazoIzqZ,0,0,1);

			glTranslatef(0.78,0.78,0.0); //Con esto se deja en el eje

			glPushMatrix();
				glRotatef(-45.0,0,0,1);
				glScalef(0.15,0.55,0.15);
				cilindro.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
			glPopMatrix();


			glPushMatrix();
				//if(giroManoIzqZ < 90 && giroManoIzqZ > 0) 
				glRotatef(giroManoIzqZ,0,0,1);
				//if(giroManoDerY < 0 && giroManoDerY > -120
				glRotatef(giroManoIzqY,-1,1,0);
				glRotatef(-45.0,0,0,1);
				mano.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
			glPopMatrix();


		glPopMatrix();


		glPushMatrix(); //Brazo derecho
			glTranslatef(-1.0,0.0,0.0);
			glRotatef(giroBrazoDerX,1,0,0);
			//if(giroBrazoDerY < 80 && giroBrazoDerY > -80) 
			glRotatef(giroBrazoDerY,0,1,0);
			//if(giroBrazoDerZ < 100 && giroBrazoDerZ > -30)
			glRotatef(giroBrazoDerZ,0,0,1);

			glTranslatef(-0.78,0.78,0.0); //Con esto se deja en el eje

			glPushMatrix();
				glRotatef(45.0,0,0,1);
				glScalef(0.15,0.55,0.15);
				cilindro.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
			glPopMatrix();

			glPushMatrix();
				//if(giroManoDerZ < 0 && giroManoDerZ > -90) 
				glRotatef(giroManoDerZ,0,0,1);
				//if(giroManoDerY < 120 && giroManoDerY > 0) 
				glRotatef(giroManoDerY,1,1,0);
				glRotatef(45.0,0,0,1);
				mano.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
			glPopMatrix();		
		glPopMatrix();

	glPopMatrix();


	//PARTE INFERIOR
	glPushMatrix();//Pierna Derecha
		glTranslatef(0.0,0.1,0.0);
		//if(giroPiernaDerX < 90 && giroPiernaDerX > -40) 
		glRotatef(giroPiernaDerX,1,0,0);

		glPushMatrix();
			glTranslatef(-0.55,-0.68,0.1);
			glRotatef(55.0,0,1,0);
			glRotatef(-35.0,0,0,1);
			glScalef(0.15,0.40,0.15);
			cilindro.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
		glPopMatrix();

		glPushMatrix();

			glTranslatef(-0.8,-1.35,0.5);
			glRotatef(-20.0,0,1,0);
			//if(giroPieDerX < 90 && giroPieDerX > -25) 
			glRotatef(giroPieDerX,1,0,0);
			glScalef(0.35,0.35,0.35);
			pie.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
		glPopMatrix();
		

	glPopMatrix();

	glPushMatrix();//Pierna Izquierda
		glTranslatef(0.0,0.1,0.0);
		//if(giroPiernaIzqX < 90 && giroPiernaIzqX > -40) 
		glRotatef(giroPiernaIzqX,1,0,0);

		glPushMatrix();
			glTranslatef(0.55,-0.68,0.1);
			glRotatef(-55.0,0,1,0);
			glRotatef(35.0,0,0,1);
			glScalef(0.15,0.40,0.15);
			cilindro.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
		glPopMatrix();

		glPushMatrix();

			glTranslatef(0.8,-1.35,0.5);
			glRotatef(20.0,0,1,0);
			//if(giroPieIzqX < 90 && giroPieIzqX > -25) 
			glRotatef(giroPieIzqX,1,0,0);
			glScalef(0.35,0.35,0.35);
			pie.draw(modo, r1,g1,b1, r2,g2,b2, grosor);
		glPopMatrix();
		

	glPopMatrix();

	
}

//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
rodamiento.parametros(perfil,12,1);
altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
altura=0.18;
anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.04;aux.y=-0.4;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.04;aux.y=0.4;aux.z=0.0;
perfil.push_back(aux);
tubo_abierto.parametros(perfil,12,0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.4,0,0);
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tuboV=2.0;
giro_tuboH=0.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glTranslatef(0.0,(chasis.altura)/2.0,0.0);
chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glRotatef(giro_torreta,1,1,1);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tuboV,0,0,1);
glRotatef(giro_tuboH,0,1,0);
tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
glPopMatrix();

};
