/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Práctica 1 - Carga de ficheros PLY
 *
 *  Permitimos la carga de ficheros PLY así como la creación fija de un cubo y
 *  una pirámide, se permite el cambio de modo de visualización con las teclas
 *  1 = Puntos | 2 = Alambre | 3 = Solido | 4 = Ajedrez
 *
 *  Tambien se permite cambiar el tipo de figura con las teclas
 *  A = PLY (defeto) | C = Cubo | P = Piramide...
 *
 *  Notese que se debe variar el zoom (AvPag) para visualizar algunas figuras
 *
 ******************************************************************************/

#include <stdlib.h> // pulls in declaration of malloc, free
#include "stdio.h"
#include <iostream>
#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include <ctype.h>

#include <model_cube.h>
#include <model_pyramid.h>
#include <model_ply.h>


// Atributos
int modo;           // Aqui almacenaremos el modo de visualización

Model model; // Aqui guardamos la figura cargada
Model_Ply model_ply;
Model_Cube model_cube(0.5);
Model_Pyramid model_pyramid(0.5);
Model_Ply model_beethoven(0.5, "data/beethoven.ply");
Model_Ply model_dodge(0.5, "data/big_dodge.ply");
Model_Ply model_porsche(0.5, "data/big_porsche.ply");
Model_Ply model_helicopter(0.5, "data/chopper.ply");
Model_Ply model_cow(0.5, "data/cow.ply");

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

	// Solucion para el ratio al maximizar
	const GLfloat ratio = GLfloat(UI_window_height) / GLfloat(UI_window_width);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	// glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glFrustum(-Window_width,Window_width,-Window_height * ratio,Window_height * ratio,Front_plane,Back_plane);
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
	// Pintamos el objeto seleccionado dependiendo del modo
	switch (modo)
	{
		case 1: //Puntos
			model.draw(Model::POINTS);
			break;
		case 2: //Aristas
			model.draw(Model::LINES);
			break;
		case 3: //Solido
			model.draw(Model::SOLID);
			break;
		case 4: //Ajedrez
			model.draw(Model::CHESS);
			break;
	}

}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
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
	UI_window_width = Ancho1;
	UI_window_height = Alto1;

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

	if (toupper(Tecla1)=='Q')
		exit(0);

	else if (Tecla1 == '1' || Tecla1 == '2' || Tecla1 == '3' || Tecla1 == '4')
	{
		cout << "Cambiado a modo " << (int)Tecla1 - 48 << endl;
		modo = (int)Tecla1 - 48; // le restamos la diferencia al valor ascii

	}
	else if (toupper(Tecla1)=='C')
		model = model_cube;
	else if (toupper(Tecla1)=='P')
		model = model_pyramid;
	else if (toupper(Tecla1)=='A')
		model = model_ply;
	else if (toupper(Tecla1)=='B')
		model = model_beethoven;
	else if (toupper(Tecla1)=='D')
		model = model_dodge;
	else if (toupper(Tecla1)=='S')
		model = model_porsche;
	else if (toupper(Tecla1)=='H')
		model = model_helicopter;
	else if (toupper(Tecla1)=='V')
		model = model_cow;
	// Repintamos
	glutPostRedisplay();
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
	Observer_distance=3*Front_plane;
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

	// Comprobamos que se le pasen los parametros correctos al programa
	if (argc != 3)
	{
		cout << "Uso del programa: " << argv[0] << " <modo> <fichero.ply>" << endl << endl;
		cout << "Modos: 1: puntos | 2: alambre | 3: sólido | 4: ajedrez" << endl << endl;
		exit(2); // Salimos con error 2
	}

	// Asignamos el modo y el fichero ply
	modo = atoi(argv[1]);

	// Cargamos las figuras (se pueden cambiar con el teclado)
	model_ply = Model_Ply(0.5, argv[2]);
	// model_cube = Model_Cube(0.5);
	// model_pyramid = Model_Pyramid(0.5);

	// Por defecto mostramos la ply
	model = model_ply;

	// Ayuda:
	cout << "Ayuda: " << endl;
	cout << "\t C = Cubo" << endl;
	cout << "\t P = Piramide" << endl;
	cout << "\t A = Archivo cargado" << endl;
	cout << "\t B = Beethoven" << endl;
	cout << "\t D = Coche (Dodge)" << endl;
	cout << "\t S = Coche (Porsche)" << endl;
	cout << "\t H = Helicoptero" << endl;
	cout << "\t V = Vaca" << endl;
	cout << "--------" << endl;



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
	glutCreateWindow("Practica 1");

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
