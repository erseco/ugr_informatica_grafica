/******************************************************************************
 *
 * IG - Informática Gráfica
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Práctica 5 - Interacción
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
Model * lata_sup = new Model();
Model * lata_cue = new Model();
Model * lata_inf = new Model();
Model * peon1 = new Model();
Model * peon2 = new Model();
Model * peon3 = new Model();



float light_alpha = 0.0;
float light_beta = 0.0;


int xant;
int yant;

bool model1_color_orig = true;
bool model2_color_orig = true;


GLint rendermode;

Model * model2 = new Model(); // Aqui guardamos la figura cargada


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


	// // posicion del observador
 //   glMatrixMode(GL_MODELVIEW);
 //   glLoadIdentity();
 //   escena.camaras[camaraActiva].setObservador();


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

	// // Dibujamos el punto para depurar
	// glBegin(GL_POINTS);

	// glColor3f(1, 0, 0);
	// glPointSize(20);

	// glVertex3f(light_alpha, light_beta, 1);


	// glEnd();






	//glTranslatef(0.0,-0.4,1.0);
	glPushMatrix();
	glTranslatef(0.0,0.8,0.0);

	// if (rendermode==GL_SELECT)
	// {
		glLoadName(1);
		cout << "Hola1" << endl;
	//}

	model1->draw(mode);

	// se cambia el color cuando se selecciona
	//draw_solido(piramide1,piramide1->r,piramide1->g,piramide1->b,2);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.5,0.0,-1.5);

	if (rendermode==GL_SELECT)
	{
		glLoadName(2);
		// cout << "Hola2" << endl;

	}

	model2->draw(mode);

	// se cambia el color cuando se selecciona
	//draw_solido(piramide1,piramide1->r,piramide1->g,piramide1->b,2);
	glPopMatrix();



	// glPushMatrix();
	// glTranslatef(0.5,0.0,-0.5);
	// if (modo==GL_SELECT)
	// 	glLoadName(5);
	// draw_solido(piramide5,0.2,0.2,0.8,1);
	// draw_solido(piramide5,piramide5->r,piramide5->g,piramide5->b,2);
	// glPopMatrix();





	// // Si el model1 no es nulo lo pintamos
	// if (model1 != NULL)
	// 	model1->draw(mode);
	// else // Si no pintaremos los elementos de la practica 4
	// {
	// 	lata_sup->draw(mode);
	// 	lata_cue->draw(mode);
	// 	lata_inf->draw(mode);
	// 	peon1->draw(mode);
	// 	peon2->draw(mode);
	// 	peon3->draw(mode);
	// }

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

void changeSpotlight()
{

	cout << "Alfa: " << light_alpha << ", Beta: " << light_beta << endl;

	GLfloat _light_position[4] = { };
	GLfloat _spotlight_direction[3] = { };

    GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	_light_position[0] =  0.0;
	_light_position[1] = 1.0;
	_light_position[2] = 0.0;
	_light_position[3] = 0.0;

	// _spotlight_direction[0] = 0.0;
	// _spotlight_direction[1] = -1.0;



	_spotlight_direction[0] = light_alpha;
	_spotlight_direction[1] = light_beta;
	_spotlight_direction[2] = 0.0;

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);



	glDisable(GL_LIGHT0);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, _light_position);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,_spotlight_direction);





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


			model1->setCenter(1.0,0.0,0.0);
			model2 = new Model_Cube(0.5);
			model2->setCenter(-1.0,0.0,0.0);


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
		case '\'':
		{

			// Asignamos el model1 como nulo para poder saber que estamos en la practica 4
			model1 = NULL;

			// Cargamos los valores
			Model_Ply model_temp = Model_Ply("data/lata-psup.ply");
			lata_sup = new Model_Revolution(model_temp.getVertices(), 50);
			lata_sup->setColor(0.184314, 0.309804, 0.309804, 1.0);

			model_temp = Model_Ply("data/lata-pcue.ply");
			lata_cue = new Model_Revolution(model_temp.getVertices(), 50);
			lata_cue->loadImage("data/text-lata-1.jpg");
			// lata_cue->setZoom(2);

			model_temp = Model_Ply("data/lata-pinf.ply");
			lata_inf = new Model_Revolution(model_temp.getVertices(), 50);
			lata_inf->setColor(0.184314, 0.309804, 0.309804, 1.0);

			model_temp = Model_Ply("data/perfil.ply");
			peon1 = new Model_Revolution(model_temp.getVertices(), 60); //Madera
			peon1->loadImage("data/text-madera.jpg");


			peon2 = new Model_Revolution(model_temp.getVertices(), 50);
			peon2->setColor(0.0, 0.0, 1.0, 1.0);

			peon3 = new Model_Revolution(model_temp.getVertices(), 50);
			peon3->setColor(0.0, 1.0, 0.0, 1.0);

			// Movemos los peones
			peon1->setCenter(3.0,0.0,0.0);
			peon2->setCenter(1.0,0.0,0.0);
			peon3->setCenter(-2.0,0.0,0.0);

		}


	}

	// Llamamos a la sobrecarga de cada modelo de las teclas, por si se quisiera
	// extender el comportamiento dependiendo del modelo
	if (model1 != NULL)
		model1->process_key(Tecla1);
	else
	{
		lata_sup->process_key(Tecla1);
		lata_cue->process_key(Tecla1);
		lata_inf->process_key(Tecla1);
		peon1->process_key(Tecla1);
		peon2->process_key(Tecla1);
		peon3->process_key(Tecla1);


		switch (toupper(Tecla1))
		{
			case 'A': // aumentar el valor de β
				light_beta +=0.1;
				changeSpotlight();
				break;
			case 'Z': // disminuir el valor de β
				light_beta-=0.1;
				changeSpotlight();
				break;
			case 'X': // aumentar el valor de α
				light_alpha+=0.1;
				changeSpotlight();
				break;
			case 'C': // disminuir el valor de α
				light_alpha-=0.1;
				changeSpotlight();
				break;
		}

	}

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

void procesar_hits(GLint hits, GLuint *names)
{
	//...
	// mostrar contenido de la pila
	cout << "Hits: " << hits << endl;

	for (int i = 0; i < hits; i++)
	{
		cout << "Numero: " << names[i * 4] << endl;

		cout << "Min Z: " << names[i * 4 + 1] << endl;
		cout << "Max Z: " << names[i * 4 + 2] << endl;
		cout << "Nombre en la pila: " << names[i * 4 + 3] << endl;
	}

	cout << endl;

	if (hits > 0)
	{

		if (names[0 + 3] == 1)
		{
			if (model1_color_orig)
			{
				model1->setColor(0,0,1,1);
				model1_color_orig = false;
			}
			else
			{
				model1->setColor(0,1,0,1);
				model1_color_orig = true;
			}

		}

		else if (names[0 + 3] == 2)
		{
			if (model2_color_orig)
			{
				model2->setColor(1,0,0,1);
				model2_color_orig = false;
			}
			else
			{
				model2->setColor(0,1,0,1);
				model2_color_orig = true;
			}
		}


		//glColor3f(0,0,1);
	}

	// switch (names[0+3])
	// {
	// 	case 1:
	// 	{
	// 		cout << "hola" << endl;
	// 		glColor3f(0,0,1);
	// 		break;
	// 	}
	// }
	//....
	// procesar el cambio de color
	//...

}


void pick (int x, int y)
{
	cout << "PICK x=" << x << ",y=" << y << endl;



	GLuint selectBuf[100]={0};
	GLint viewport[4], hits=0;

	// Declarar buffer de selección
	glSelectBuffer(100, selectBuf);

	// Obtener los parámetros del viewport
	glGetIntegerv (GL_VIEWPORT, viewport);

	// Pasar OpenGL a modo selección
	rendermode = GL_SELECT;
	glRenderMode (GL_SELECT);
	glInitNames();
	glPushName(0);

	// Fijar la transformación de proyección para la selección
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix (x,(viewport[3] - y),5.0, 5.0, viewport);
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

	// Dibujar la escena
	draw_scene();

	// Pasar OpenGL a modo render
	hits = glRenderMode (GL_RENDER);

	// Restablecer la transformación de proyección
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

	// Procesar el contenido del buffer de selección
	procesar_hits(hits, selectBuf);

	// Dibujar la escena para actualizar cambios
	draw_scene();
}





// void dibujar_escena(int modo)
// {


// 	if (modo==GL_SELECT)
// 		glLoadName(1);
// 	dibujar_objeto1();
// 	if (modo==GL_SELECT)
// 		glLoadName(2);
// 	dibujar_objeto2();

// }

#define tam_buffer 100

// int pick2( int x, int y)
// {

// 	GLuint selectBuf[tam_buffer]={0};
// 	Glint hits;
// 	GLint Viewport[4];

// 	cout << "PICK x=" << x << ",y=" << y << endl;



// 	// 1. Declarar buffer de selección
// 	glSelectBuffer(tam_buffer, selectBuf);

// 	// 2. Obtener los parámetros del viewport
// 	glGetIntegerv (GL_VIEWPORT, Viewport);

// 	// 3. Pasar OpenGL a modo selección
// 	glRenderMode (GL_SELECT)

// 	glInitNames();
// 	glPushName(0);

// 	// 4. Fijar la transformación de proyección para la seleccion
// 	glMatrixMode (GL_PROJECTION);
// 	glLoadIdentity ();
// 	gluPickMatrix (x,(viewport[3] - y),5.0, 5.0, viewport);

// 	//gluPickMatrix ( x, Viewport[3] - y, ancho, alto, Viewport);
// 	glFrustum(Min_x,Max_y,Min_y,Max_y,Front_plane,Back_plane);

// 	MatrizProyeccion(); // SIN REALIZAR LoadIdentity !

// 	// 5. Dibujar la escena con Nombres
// 	// dibujarConNombres();

// 	// 6. Pasar OpenGL a modo render
// 	hits = glRenderMode (GL_RENDER);

// 	// 7. Restablecer la transformación de proyección (sin gluPickMatrix)

// 	// 8. Analizar el contenido del buffer de selección

// 	// 9. Devolver el resultado


// }

void clickRaton( int boton, int estado, int x, int y )
{
	if ( boton == GLUT_LEFT_BUTTON )
	{

		pick(x, y);

		//  if ( estado == GLUT_DOWN )
		// ￼￼￼￼￼￼￼￼// Entrar en el estado "moviendo cámara"
		// 	else
		// 		// Salir del estado "moviendo cámara"


	}
}

void ratonMovido( int x, int y )
{

	pick(x, y);
	cout << "Movido";

	// if ( estadoRaton==MOVIENDO_CAMARA_FIRSTPERSON)
	// {
	//       escena.camaras[camaraActiva].girar(x-xant, y-yant);
	//       xant=x;
	//       yant=y;
	// }
  	//glutPostRedisplay();

}


//***************************************************************************
// Activa la iluminación (light 0)
//***************************************************************************
void EnableLighting(void)
{

	GLfloat light_ambient[] = { .5, .5, .5, 1.0 };
	GLfloat light_diffuse[] = { .9, .9, .9, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 20.0, 10.0, 30.0, 1.0 };
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	float shininess = 20;

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);



	GLfloat emision[] = {0.3, 0.3, 0.3, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);

	glEnable(GL_SMOOTH);     // enable smooth shading
	glEnable(GL_LIGHTING);   // enable lighting
	glEnable(GL_LIGHT0);     // enable light 0
	glEnable(GL_DEPTH_TEST);   //Activa el buffer de profundidad.
	glShadeModel(GL_SMOOTH);


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
  	EnableLighting();

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


	glutMouseFunc(clickRaton);
	// glutMotionFunc(ratonMovido);
	// glutPassiveMotionFunc(ratonMovido);



	// funcion de inicialización
	initialize();

	// Forzamos una llamada a la función normal_keys para cargar un modelo

	normal_keys('6', 0, 0); // Figura cubo
	//normal_keys('7', 0, 0); // Figura ply
	//normal_keys('8', 0, 0); // Figura por rotación
	//normal_keys('9', 0, 0); // Figura jerárquica
	//normal_keys('\'', 0, 0); // Lata y peones

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
