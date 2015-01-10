/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Práctica 3 - Modelos jerárquicos
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
#include <model_robot.h>
#include <model_lanzadera.h>
#include <model_revolution.h>


// Atributos
int modo;           // Aqui almacenaremos el modo de visualización

Model * model1 = new Model(); // Aqui guardamos la figura cargada
// Model * model2 = new Model(); // Aqui guardamos la figura cargada


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

	Model::DrawMode mode;

	// Pintamos el objeto seleccionado dependiendo del modo
	switch (modo)
	{
		case 1: //Puntos
			mode = Model::POINTS;
			break;
		case 2: //Aristas
			mode = Model::LINES;
			break;
		case 3: //Solido
			mode = Model::SOLID;
			break;
		case 4: //Ajedrez
			mode = Model::CHESS;
			break;
	}

	model1->draw(mode);
	// model2->draw(mode);

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

	switch (Tecla1)
	{
		case 'q':
			exit(0);
		case '1':
		case '2':
		case '3':
		case '4':
		{
			modo = (int)Tecla1 - 48; // le restamos la diferencia al valor ascii
			//cout << "Cambiado a modo " <<  modo << endl;
			break;
		}
		case '6':
			model1 = new Model_Cube(0.5);
			break;

		case '7':
			model1 = new Model_Ply("data/beethoven.ply");
			break;

		case '8':
		{
			Model_Ply model_temp("data/perfil.ply");
			model1 = new Model_Revolution(model_temp.getVertices(), 20);
		}
			break;

		case '9':
		{
			model1 = new Model_Lanzadera();
			// model1->setCenter(1.0,0.0,0.0);
			// model2 = new Model_Lanzadera();
			// model2->setCenter(-1.0,0.0,0.0);
			break;
		}
		case '0':
		{
			model1 = new Model_Robot();
			break;
		}
	}

	// Llamamos a la sobrecarga de cada modelo de las teclas, por si se quisiera
	// extender el comportamiento dependiendo del modelo
	model1->process_key(Tecla1);
	// model2->process_key(Tecla1);

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
// Activa la iluminación (light 0)
//***************************************************************************
void EnableLighting(void) {
  /* Control material properties */
  GLfloat mat_specular[] = { 0.7, 0.0, 0.0, 1.0 };
  GLfloat mat_diffuse[] = { 0.5, 0.0, 0.0, 1.0 };
  GLfloat mat_ambient[] = { 0.5, 0.0, 0.0, 1.0 };
  GLfloat mat_shininess = { 7.0 };

  /* Control lighting properties */
  GLfloat light_ambient[] = { .5, .0, .0, 1.0 };
  GLfloat light_diffuse[] = { .5, .0, .0, 1.0 };
  GLfloat light_specular[] = { .7, .0, .0, 1.0 };
  GLfloat light_position[] = { 100.0, 80.0, 120.0, 1.0 };

  /* set up ambient, diffuse, and specular components for light 0 */
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  /* define material properties for front face of all polygons */
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

  glEnable(GL_SMOOTH);     // enable smooth shading
  glEnable(GL_LIGHTING);   // enable lighting
  glEnable(GL_LIGHT0);     // enable light 0
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

	// Activamos la iluminacion
  	//EnableLighting();

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
	if (argc != 2)
	{
		cout << "Uso del programa: " << argv[0] << " <modo>" << endl << endl;
		cout << "Modos: 1: puntos | 2: alambre | 3: sólido | 4: ajedrez" << endl << endl;
		exit(2); // Salimos con error 2
	}

	cout << "Modos:" << endl;
	cout << "------" << endl;
	cout << "6 = Cubo" << endl;
	cout << "7 = Beethoven" << endl;
	cout << "8 = Peon" << endl;
	cout << "9 = Lanzadera" << endl;
	cout << "0 = Robot" << endl;

	// Asignamos el modo y el fichero ply
	modo = atoi(argv[1]);


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
	glutCreateWindow("Informatica Grafica");

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


	// Forzamos una llamada a la función normal_keys para cargar un modelo

	//normal_keys('6', 0, 0); // Figura cubo
	//normal_keys('7', 0, 0); // Figura ply
	//normal_keys('8', 0, 0); // Figura por rotación
	normal_keys('9', 0, 0); // Figura jerárquica



	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
