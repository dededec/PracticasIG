//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"

using namespace std;

// tipos
typedef enum
{
        CUBO,
        PIRAMIDE,
        OBJETO_PLY,
        ROTACION,
        ARTICULADO,
        ESFERA,
        PILAF
} _tipo_objeto;

_tipo_objeto t_objeto = PILAF;
_modo modo = SOLID_ILLUMINATED_GOURAUD;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 450, Window_high = 450;

//Variables para editar materiales
float material1[] = {0.0, 0.0, 0.0};
float material2[] = {0.0, 0.0, 0.0};
float* materialEditar = material1;

int seleccionMaterial1 = 0;
int seleccionMaterial2 = 0;
int* colorEditar = &seleccionMaterial1;

string parteEditar = "";

//Variable para rotar la luz
int alfa = 60;

// objetos
_cubo cubo;
_piramide piramide(0.85, 1.3);
_objeto_ply ply;
_rotacion rotacion;
_tanque tanque;

_esfera esfera;
_semiEsfera semiEsfera;
_cilindro cilindro;

_Pilaf pilaf;

// _objeto_ply *ply1;
void luces(float alfa)
{
        GLfloat light1_position[4] = {20, 20, 0, 1},
                light1_ambient[4] = {0.0, 0.0, 0.0, 0.1},
                light1_intensity[4] = {0.9, 0.9, 0.9, 1};

        glDisable(GL_LIGHT0);

        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_intensity);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1_intensity);

        glEnable(GL_LIGHT1);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glRotatef(alfa, 0, 1, 0);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glPopMatrix();
}
void funcion_moverPiernaDerAdelante(int a);
void funcion_moverPiernaDerAtras(int a);
void funcion_moverPiernaIzqAdelante(int a);
void funcion_moverPiernaIzqAtras(int a);
void funcion_moverCuerpo(int a);

bool aumentando = true;
bool comenzado = false;
float saltos = 0;
bool saltando = false;
float objetivo1[3] = {2.1, 2.5, 1.3}; 
float objetivo2[3] = {2.5, 1.4, 1.3};

void funcion_moverCuerpo(int a)
{
        alfa = (alfa + 10) % 360;
        if(aumentando)
        {
                for(int i=0;i<3;++i)
                {
                        if(material1[i] < objetivo1[i])
                        {
                                material1[i] += 0.1;
                                material2[i] -= 0.1;
                        }
                        else if(material1[i] > objetivo1[i]) 
                        {
                                material1[i] -= 0.1;
                                material2[i] += 0.1;
                        }
                        if(material1[i] < objetivo1[i] && material1[i]+0.1 >= objetivo1[i])
                        {
                                material1[i] = objetivo1[i];
                                material2[i] = 2.5 - objetivo1[i];
                        }
                }

                bool conseguido = true;
                for(int i=0; i<3; ++i)
                {
                        if(material1[i] != objetivo1[i])
                        {
                                conseguido=false;
                                break;
                        }
                }
                if(conseguido) aumentando = false;
        }
        else
        {
               
                for (int i = 0; i < 3; ++i)
                {
                        if (material1[i] < objetivo2[i])
                        {
                                material1[i] += 0.1;
                                material2[i] -= 0.1;
                        }
                        else if (material1[i] > objetivo2[i])
                        {
                                material1[i] -= 0.1;
                                material2[i] += 0.1;
                        }
                        if (material1[i] < objetivo2[i] && material1[i] + 0.1 >= objetivo2[i])
                        {
                                material1[i] = objetivo2[i];
                                material2[i] = 2.5 - objetivo2[i];
                        }
                }

                bool conseguido = true;
                for (int i = 0; i < 3; ++i)
                {
                        if (material1[i] != objetivo2[i])
                        {
                                conseguido = false;
                                break;
                        }
                }
                if (conseguido) aumentando = true;
        }
        

        if (saltando)
        {
                if (a == 10)
                {
                        saltando = false;
                        pilaf.rebote = -0.05;
                }
                else
                {
                        a++;
                        if (pilaf.rebote > -0.1)
                                pilaf.rebote += -0.02;
                }
        }
        else
        {
                if (a == 0)
                {
                        pilaf.rebote = 0.05;
                        saltando = true;
                }
                else
                {
                        a--;
                        if (pilaf.rebote < 0.1)
                                pilaf.rebote += 0.02;
                }
        }
        glutPostRedisplay();
        glutTimerFunc(20, funcion_moverCuerpo, a);
}
void funcion_moverPiernaDerAtras(int a)
{
        pilaf.giroPiernaDerX += 4.25;
        if (pilaf.giroPieDerX > -25)
                pilaf.giroPieDerX -= 5;
        glutPostRedisplay();
        if (a < 71) // < 300/aumento
        {
                glutTimerFunc(10, funcion_moverPiernaDerAtras, a + 4);
        }
        else
        {
                glutTimerFunc(30, funcion_moverPiernaDerAdelante, a);
        }
}

void funcion_moverPiernaDerAdelante(int a)
{

        pilaf.giroPiernaDerX -= 4.25;
        if (pilaf.giroPieDerX < 90)
        {
                if (pilaf.giroPieDerX < 60)
                        pilaf.giroPieDerX += 5;
                else
                        pilaf.giroPieDerX += 10;
        }

        if (a > -36) //-150/aumento
        {
                if (a >= -3.5 && !comenzado)
                {
                        comenzado = true;
                        glutTimerFunc(120, funcion_moverCuerpo, 0);
                        glutTimerFunc(60, funcion_moverPiernaIzqAtras, 0);
                }
                if (comenzado && (pilaf.giroBrazoDerZ < 100))
                {
                        pilaf.giroBrazoDerZ += 5;
                        pilaf.giroBrazoIzqZ += -5;
                        pilaf.giroManoIzqY += -4.5;
                        pilaf.giroManoDerY += 4.5;
                }
                glutTimerFunc(10, funcion_moverPiernaDerAdelante, a - 4);
        }
        else
                glutTimerFunc(30, funcion_moverPiernaDerAtras, a);

        glutPostRedisplay();
}

void funcion_moverPiernaIzqAtras(int a)
{
        pilaf.giroPiernaIzqX += 4.25; // 300/aumento
        if (pilaf.giroPieIzqX > -25)
                pilaf.giroPieIzqX -= 10;
        glutPostRedisplay();
        if (a < 71)
        {
                glutTimerFunc(10, funcion_moverPiernaIzqAtras, a + 4);
        }
        else
        {
                glutTimerFunc(30, funcion_moverPiernaIzqAdelante, a);
        }
}

void funcion_moverPiernaIzqAdelante(int a)
{
        pilaf.giroPiernaIzqX -= 4.25; // 5*-30 = -150
        if (pilaf.giroPieIzqX < 90)
                pilaf.giroPieIzqX += 10;
        glutPostRedisplay(); //-150/aumento
        if (a > -36)
        {
                glutTimerFunc(10, funcion_moverPiernaIzqAdelante, a - 4);
        }
        else
                glutTimerFunc(30, funcion_moverPiernaIzqAtras, a);
}

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
        //  plano_delantero>0  plano_trasero>PlanoDelantero)
        glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

        // posicion del observador
        change_projection();
        glMatrixMode(GL_PROJECTION);
        //glLoadIdentity();
        glTranslatef(0, 0, -Observer_distance);
        glRotatef(Observer_angle_x, 1, 0, 0);
        glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

        glDisable(GL_LIGHTING);
        glLineWidth(2);
        glBegin(GL_LINES);
        // eje X, color rojo
        glColor3f(1, 0, 0);
        glVertex3f(-AXIS_SIZE, 0, 0);
        glVertex3f(AXIS_SIZE, 0, 0);
        // eje Y, color verde
        glColor3f(0, 1, 0);
        glVertex3f(0, -AXIS_SIZE, 0);
        glVertex3f(0, AXIS_SIZE, 0);
        // eje Z, color azul
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, -AXIS_SIZE);
        glVertex3f(0, 0, AXIS_SIZE);
        glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

        switch (t_objeto)
        {
        case CUBO:
                cubo.draw(modo, material1[0], material1[1], material1[2], material2[0], material2[1], material2[2], 2);
                break;
        case PIRAMIDE:
                piramide.draw(modo, material1[0], material1[1], material1[2], material2[0], material2[1], material2[2], 2);
                break;
        case OBJETO_PLY:
                ply.draw(modo, material1[0], material1[1], material1[2], material2[0], material2[1], material2[2], 2);
                break;
        case ROTACION:
                rotacion.draw(modo, material1[0], material1[1], material1[2], material2[0], material2[1], material2[2], 2);
                break;
        case ESFERA:
                esfera.draw(modo, material1[0], material1[1], material1[2], material2[0], material2[1], material2[2], 2);
                break;
        case PILAF:
                pilaf.draw(modo, material1[0], material1[1], material1[2], material2[0], material2[1], material2[2], 2);
                break;
        }
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{

        clean_window();
        change_observer();
        luces(alfa);
        draw_axis();
        draw_objects();
        glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
        float Aspect_ratio;

        Aspect_ratio = (float)Alto1 / (float)Ancho1;
        Size_y = Size_x * Aspect_ratio;
        change_projection();
        glViewport(0, 0, Ancho1, Alto1);
        glutPostRedisplay();
}

//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void mostrarColorEditado(int seleccionMaterial1)
{
        string color = "";
        if (seleccionMaterial1 == 0)
                color = " ROJO";
        else if (seleccionMaterial1 == 1)
                color = " VERDE";
        else
                color = " AZUL";

        cout << "Se esta editando el color " << color << endl;
}

void normal_key(unsigned char Tecla1, int x, int y)
{
        switch (toupper(Tecla1))
        {
        case 'Q':
                exit(0);

        case '+':
                if (materialEditar[*colorEditar] < 5.2) materialEditar[*colorEditar] += 0.2;
                break;
        case '-':
                if (materialEditar[*colorEditar] > -4.0) materialEditar[*colorEditar] -= 0.2;
                break;
        
        case 'T':
                (*colorEditar)--;
                if (*colorEditar < 0) *colorEditar = 0;
                mostrarColorEditado(*colorEditar);
                break;
        case 'Y':
                *colorEditar = ( (*colorEditar) + 1) % 3;
                mostrarColorEditado(*colorEditar);
                break;
        
        case 'G':
                parteEditar = " CUERPO";
                colorEditar = &seleccionMaterial1;
                if(materialEditar == material1)
                {
                        parteEditar = " OJOS Y MANOS";
                        materialEditar = material2;
                        colorEditar = &seleccionMaterial2;
                }
                else materialEditar = material1;
                cout << "----------------- EDITANDO: " << parteEditar << " -----------------" << endl;
                mostrarColorEditado(*colorEditar);
                break;

        

        case '1':
                modo = POINTS;
                break;
        case '2':
                modo = EDGES;
                break;
        case '3':
                modo = SOLID;
                break;
        case '4':
                modo = SOLID_CHESS;
                break;
        case '5':
                modo = SOLID_ILLUMINATED_FLAT;
                break;
        case '6':
                modo = SOLID_ILLUMINATED_GOURAUD;
                break;

        case '7':
                t_objeto = CUBO;
                break;
        case '8':
                t_objeto = PIRAMIDE;
                break;
        case '9':
                t_objeto = OBJETO_PLY;
                break;
        case '0':
                t_objeto = ROTACION;
                break;
        case '\'':
                if(t_objeto == ESFERA) t_objeto = PILAF;
                else t_objeto = ESFERA;
                break;

        case 'R':
                pilaf.giroBrazoDerX += 5;
                break;
        case 'W':
                pilaf.giroBrazoDerX -= 5;
                break;
        case 'F':
                if (pilaf.giroBrazoDerY < 80)
                        pilaf.giroBrazoDerY += 5;
                break;
        case 'S':
                if (pilaf.giroBrazoDerY > -80)
                        pilaf.giroBrazoDerY -= 5;
                break;
        case 'A':
                if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
                {
                        alfa -= 10;
                }
                break;
        case 'D':
                if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
                {
                        alfa += 10;
                }
                else
                {
                        if (pilaf.giroBrazoDerZ < 100)
                                pilaf.giroBrazoDerZ += 5;
                }
                break;
        case 'E':
                if (pilaf.giroBrazoDerZ > -30)
                        pilaf.giroBrazoDerZ -= 5;
                break;

        case 'O':
                pilaf.giroBrazoIzqX -= 5;
                break;
        case 'U':
                pilaf.giroBrazoIzqX += 5;
                break;
        case 'J':
                if (pilaf.giroBrazoIzqY > -80)
                        pilaf.giroBrazoIzqY -= 5;
                break;
        case 'L':
                if (pilaf.giroBrazoIzqY < 80)
                        pilaf.giroBrazoIzqY += 5;
                break;
        case 'K':
                if (pilaf.giroBrazoIzqZ > -100)
                        pilaf.giroBrazoIzqZ -= 5;
                break;
        case 'I':
                if (pilaf.giroBrazoIzqZ < 30)
                        pilaf.giroBrazoIzqZ += 5;
                break;

        case 'Z':
                if (pilaf.giroPieDerX < 90)
                        pilaf.giroPieDerX += 5;
                break;
        case 'X':
                if (pilaf.giroPieDerX > -25)
                        pilaf.giroPieDerX -= 5;
                break;
        case 'C':
                if (pilaf.giroPieIzqX < 90)
                        pilaf.giroPieIzqX += 5;
                break;
        case 'V':
                if (pilaf.giroPieIzqX > -25)
                        pilaf.giroPieIzqX -= 5;
                break;

        case 'B':
                if (pilaf.giroPiernaDerX < 90)
                        pilaf.giroPiernaDerX += 5;
                break;
        case 'N':
                if (pilaf.giroPiernaDerX > -40)
                        pilaf.giroPiernaDerX -= 5;
                break;
        case 'M':
                if (pilaf.giroPiernaIzqX < 90)
                        pilaf.giroPiernaIzqX += 5;
                break;
        case ',':
                if (pilaf.giroPiernaIzqX > -40)
                        pilaf.giroPiernaIzqX -= 5;
                break;
        case 'P':
                material2[0] = 2.5;
                material2[1] = 2.5;
                material2[2] = 2.5;
                funcion_moverPiernaDerAtras(0);
                break;
        }
        glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{

        switch (Tecla1)
        {
        case GLUT_KEY_LEFT:
                Observer_angle_y--;
                break;
        case GLUT_KEY_RIGHT:
                Observer_angle_y++;
                break;
        case GLUT_KEY_UP:
                Observer_angle_x--;
                break;
        case GLUT_KEY_DOWN:
                Observer_angle_x++;
                break;
        case GLUT_KEY_PAGE_UP:
                Observer_distance *= 1.2;
                break;
        case GLUT_KEY_PAGE_DOWN:
                Observer_distance /= 1.2;
                break;

        case GLUT_KEY_F1:
                pilaf.giroCuerpo -= 5;
                break;
        case GLUT_KEY_F2:
                pilaf.giroCuerpo += 5;
                break;

        case GLUT_KEY_F5:
                if (pilaf.giroManoDerZ < 0)
                        pilaf.giroManoDerZ += 5;
                break;
        case GLUT_KEY_F6:
                if (pilaf.giroManoDerZ > -90)
                        pilaf.giroManoDerZ -= 5;
                break;
        case GLUT_KEY_F7:
                if (pilaf.giroManoDerY < 120)
                        pilaf.giroManoDerY += 5;
                break;
        case GLUT_KEY_F8:
                if (pilaf.giroManoDerY > 0)
                        pilaf.giroManoDerY -= 5;
                break;

        case GLUT_KEY_F9:
                if (pilaf.giroManoIzqZ > 0)
                        pilaf.giroManoIzqZ -= 5;
                break;
        case GLUT_KEY_F10:
                if (pilaf.giroManoIzqZ < 90)
                        pilaf.giroManoIzqZ += 5;
                break;
        case GLUT_KEY_F11:
                if (pilaf.giroManoIzqY > -120)
                        pilaf.giroManoIzqY -= 5;
                break;
        case GLUT_KEY_F12:
                if (pilaf.giroManoIzqY < 0)
                        pilaf.giroManoIzqY += 5;
                break;
        }
        glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
        cout << "----------------- EDITANDO:  CUERPO -----------------" << endl;
        mostrarColorEditado(seleccionMaterial1);
        
        // se inicalizan la ventana y los planos de corte
        Size_x = 0.5;
        Size_y = 0.5;
        Front_plane = 1;
        Back_plane = 1000;

        // se incia la posicion del observador, en el eje z
        Observer_distance = 4 * Front_plane;
        Observer_angle_x = 0;
        Observer_angle_y = 0;

        // se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
        // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
        glClearColor(1, 1, 1, 1);

        // se habilita el z-bufer
        glEnable(GL_DEPTH_TEST);
        change_projection();
        glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

        // creación del objeto ply

        ply.parametros(argv[1]);

        // perfil

        vector<_vertex3f> perfil2;
        _vertex3f aux;
        aux.x = 1.0;
        aux.y = -1.4;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 1.0;
        aux.y = -1.1;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.5;
        aux.y = -0.7;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.4;
        aux.y = -0.4;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.4;
        aux.y = 0.5;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.5;
        aux.y = 0.6;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.3;
        aux.y = 0.6;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.5;
        aux.y = 0.8;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.55;
        aux.y = 1.0;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.5;
        aux.y = 1.2;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.3;
        aux.y = 1.4;
        aux.z = 0.0;
        perfil2.push_back(aux);
        rotacion.parametros(perfil2, 6, 1);

        // se llama a la inicialización de glut
        glutInit(&argc, argv);

        // se indica las caracteristicas que se desean para la visualización con OpenGL
        // Las posibilidades son:
        // GLUT_SIMPLE -> memoria de imagen simple
        // GLUT_DOUBLE -> memoria de imagen doble
        // GLUT_INDEX -> memoria de imagen con color indizado
        // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
        // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
        // GLUT_DEPTH -> memoria de profundidad o z-bufer
        // GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

        // posicion de la esquina inferior izquierdad de la ventana
        glutInitWindowPosition(Window_x, Window_y);

        // tamaño de la ventana (ancho y alto)
        glutInitWindowSize(Window_width, Window_high);

        // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
        // al bucle de eventos)
        glutCreateWindow("PRACTICA - 3");

        // asignación de la funcion llamada "dibujar" al evento de dibujo
        glutDisplayFunc(draw);
        // asignación de la funcion llamada "change_window_size" al evento correspondiente
        glutReshapeFunc(change_window_size);
        // asignación de la funcion llamada "normal_key" al evento correspondiente
        glutKeyboardFunc(normal_key);
        // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
        glutSpecialFunc(special_key);

        // funcion de inicialización
        initialize();

        // inicio del bucle de eventos
        glutMainLoop();
        return 0;
}
