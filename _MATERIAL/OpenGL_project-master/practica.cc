//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <ctype.h>
#include "user_code.h"
#include "vertex.h"
#include <string.h>

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//variables que determinan lo que dibujar (fichero ply, objeto por revolucion, modelo jerarquico)
int dibujar = 4;
char* fichero = "ply/ant.ply";
int modo = 2;

//variables que contienen las mallas de los modos 1 y 2
MallaTVT malla1;
MallaTVT malla2;

//variables de los grados de libertad
Real alpha1 = 90.0;
Real alpha2 = 0.0;
Real d = 0.0;

//variables de los coordenadas polares de los angulos de las fuentes de luz
Real c_alpha = 0.0;
Real c_beta = 0.0;

//variables que contienen los nodos de escena
NodoGE* grafoEscena3 = new NodoGE();
NodoGE* grafoEscena4 = new NodoGE();

//boolean que indica si hay que redibujar (puesto a true cuando hay rotaciones/translaciones, etc)
bool redibujar = false;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	glPointSize(3.0);

	switch (modo)
	{
		case 1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);//Puntos
			break;
		case 2:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Aristas
			break;
		case 3:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Solido
			break;
		case 4:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Ajedrez
			break;
	}

	switch (dibujar)
	{
		case 1:
			if(malla1.num_ver == 0)
				generar_malla(&malla1, fichero, false, 0); //, 0.17, 0.37, 0.38);
			MTVT_Visualizar_VBOs_AV(&malla1);
			break;
		case 2:
			if(malla2.num_ver == 0)
				generar_malla(&malla2, "ply/peon.ply", true, 50); //NGE_Visualizar, 0.17, 0.37, 0.38);
			MTVT_Visualizar_VBOs_AV(&malla2);
			break;
		case 3:
			if(grafoEscena3->entrada.empty() || redibujar == true)
				grafoEscena3 = escena3(alpha1, alpha2, d);

			NGE_Visualizar(grafoEscena3); //, 0);
			break;
		case 4:
			if(grafoEscena4->entrada.empty() || redibujar == true)
				grafoEscena4 = escena4(); //c_alpha, c_beta, d);

			NGE_Visualizar(grafoEscena4); //, 2);
			break;
	}
}



//**************************************************************************
//
//***************************************************************************

void draw_scene()
{

clear_window();
change_observer();
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

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
if (toupper(Tecla1)=='Q') exit(0);

switch (Tecla1)
{
	case 'p':
		modo = 1;
		break;
	case 'l':
		modo = 2;
		break;
	case 's':
		modo = 3;
		break;
	case 'a':
		modo = 4;
		break;
	case '1':
		dibujar = 1;
		break;
	case '2':
		dibujar = 2;
		break;
	case '3':
		dibujar = 3;
		break;
	case '4':
		dibujar = 4;
		break;
	case 'Z':
		if(dibujar==3)
			if(alpha1 > 60)
			{
				alpha1 = alpha1 - 1;
				redibujar = true;
			}
		if(dibujar==4)
		{
			c_beta-=10;
			redibujar = true;
		}
		break;
	case 'z':
		if(dibujar==3)
			if(alpha1 < 120)
			{
				alpha1 = alpha1 + 1;
				redibujar = true;
			}
		break;
	case 'X':
		if(dibujar==3)
		{
			if(alpha2 <= 0)
				alpha2 = 360;
			else
				alpha2 = alpha2 - 1;
			redibujar = true;
		}
		if(dibujar==4)
		{
			c_alpha+=10;
			redibujar = true;
		}
		break;
	case 'x':
		if(dibujar==3)
			alpha2 = alpha2 + 1;
			redibujar = true;
		break;
	case 'c':
		if(dibujar==3)
			if(d>=-0.3)
				d = d-0.05;
			redibujar = true;
		break;
	case 'C':
		if(dibujar==3)
		{
			if(d<=0.3)
				d = d+0.05;
			redibujar = true;
		}
		if(dibujar==4)
		{
			c_alpha-=10;
			redibujar = true;
		}
		break;
	case 'A':
		if(dibujar==4)
		{
			c_beta+=10;
			redibujar = true;
		}
		break;
	case '-':Observer_distance*=1.2;break;
	case '+':Observer_distance/=1.2;break;
}

draw_scene();

}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=20*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
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
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 1");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
