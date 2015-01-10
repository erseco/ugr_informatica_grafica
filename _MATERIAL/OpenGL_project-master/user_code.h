//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#define GL_GLEXT_PROTOTYPES

#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <cstdlib>
#include <math.h>
#include <string.h>
#include "vertex.h"
#include "file_ply_stl.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"

using namespace std;


typedef GLfloat Real ;

typedef GLuint Natural ;

const unsigned int X=0, Y=1, Z=2 ;	// indices enteros de los ejes

struct Tupla2r	// tupla con dos reales
{
	Real coo[2] ;
} ;

struct Tupla3r		// tupla con 3 valores reales que representan coordenas
{
	Real coo[3];
} ;

struct Tupla3n		// tupla de 3 entero no negativos (naturales)
{
	Natural ind[3];
} ;

struct CVerTri		// Coordenadas de los 3 vertices de un triangulo
{
	Tupla3r ver[3];
} ;

struct MallaTVT		// Malla con tabla de vertices y triangulos
{
	Natural num_ver ;	//numero de vertices
	Natural num_tri	;	//numero de triangulos
	Tupla3r * ver ;		//tabla de vertices (num_ver entradas)
	Tupla3n * tri ;		//tabla de triangulos (num_tri entradas)
				//Atributos
	Tupla3r * nor_tri ;	//normales de triangulos (num_tri entradas)
	Tupla3r * nor_ver ;	//normales de vertices (num_ver entradas)
	Tupla3r * col_tri ; 	//colores de triangulos(num_tri entradas)
	Tupla3r * col_ver ;	//colores de vertices (num_ver entradas)

	GLuint id_vbo_ver ; 	//identificador del VBO con la tabla de vertices
	GLuint id_vbo_tri ; 	//identificador del VBO con la tabla de triangulos

	GLuint id_vbo_col_ver;
	GLuint id_vbo_nor_ver;
	GLuint id_vbo_nor_tri;

	unsigned int tam_ver ; 	//tamano en bytes de la table de vertices
	unsigned int tam_tri ;	//tamano en bytes de la tabla de triangulos

	Tupla2r * cte_ver;	// puntero a tabla de coord. de textura
				// (con un total de num_ver entradas)
	Natural tam_ctv ;	// tamano en bytes de la tabla de cc.tt.
	GLuint id_vbo_cte_ver ;	//identificador del VBO con las coord. de textura
} ;

struct NodoGE ;		// nodo del grafo e escena

struct ParTransformacion	// parametros de una transformacion
{
	unsigned char tipo ;		//0=rotaction, 1=escalado, 2=traslacion
	Real par[3] ; 	// si tipo==0 -> eje de rotacion
			//	    1 -> vector de desplazamiento
			// 	    2 -> factores de escala
	Real angulo ;	// si tipo==0 -> angulo de rotacion
} ;

struct EntradaNGE	// entrada del nodo del grafo de escena
{
	unsigned char tipo ;	//0=malla, 1-sub-escena, 2=transformacion

	union
	{
		MallaTVT * malla; 	//ptr. a una malla tvt
		NodoGE * subesc ;	//ptr. a un sub-arbol
		ParTransformacion * transf ;	//ptr. a transformacion
	} ;
} ;

struct NodoGE 	// nodo del grafo de escena
{
	std::vector<EntradaNGE> entrada ; 	//vector de entradas
} ;

struct FuenteLuz
{
	int tipo;	//0=dirreccional 1=posicional
	float col[4];	//color de la fuente

	//para fuentes posicionales
	GLfloat posf[4];

	//para fuentes direccionales
	GLfloat alpha;
	GLfloat beta;
};

struct Textura
{
	const char* nombre_fichero;
	unsigned char* texels;	//puntero a los pixels en memoria dinamica
	GLuint idTex ;	//identificador de textura OpenGL
	bool genAuto;	// 0 = se usa la tabla de coordenadas de textura
			// 1= generación automática de coordenadas de textura

	//parametros para la generación automática de texturas
	GLfloat coefsS[4];
	GLfloat coefsT[4];
};

struct Material
{
	GLfloat colorA[4];	//reflectividad ambiental
	GLfloat colorD[4];	//reflectividad difusa
	GLfloat colorS[4];	//reflectividad especular
	GLfloat e;		//exponente de brillo

	Textura* textura;	//textura asociada (puede ser puntero nulo)
};




//****************************************************************************
// Funciones para generar una malla (leer ply y generar atributos de la malla)
//****************************************************************************

void leer_ply(const char* nombre_fichero, bool revolucion, vector<float> &vertices, vector<int> &caras, int N);

void generar_malla(MallaTVT* malla, const char* nombre_fichero, bool revolucion, int N);


//****************************************************************************************
// Funciones para generar y almacenar los vertices y caras (malla generada por revolucion)
//****************************************************************************************

void generate_vertices( vector<float> vertices, vector<float> &vertices_final, int N, char eje);

void generate_faces(vector<int> &caras, int N, int M);


//*******************************************************************************************************
// Funciones para generar y almacenar los normales a los vertices y caras (malla generada por revolucion)
//*******************************************************************************************************

void calculate_normales_tri(MallaTVT* malla);

void calculate_normales_ver(MallaTVT * malla);


//***************************************************************************************
// Funcion para generar y almacenar los coord. de textura (malla generada por revolucion)
//***************************************************************************************

void calculate_coord_textura_revolucion(MallaTVT * malla, int N);


//********************************************************************
// Funciones para dibujar una malla (creacion y visualizacion de VBOs)
//*********************************************************************

void draw_malla(MallaTVT* malla, int modo);

void MTVT_Visualizar_VA(MallaTVT * pm);

GLuint VBO_Crear(GLuint tipo, GLuint tamanio, GLvoid * puntero);

void MTVT_Crear_VBOs(MallaTVT * pm);

void MTVT_Visualizar_VBOs(MallaTVT *pm);

void MTVT_Visualizar_VBOs_AV(MallaTVT *pm);


//*****************************************************************************************
// Funciones para inicializar la entrada de una malla/una transformacion con sus atributos
//*****************************************************************************************

EntradaNGE malla(const char* nombre_fichero, bool revolucion);

EntradaNGE transformacion(char tipo, Real x, Real y, Real z, Real angulo);


//**************************************************************************
// Funciones para visualizar un nodo de entradas (mallas y transformaciones)
//**************************************************************************

void NGE_Visualizar(NodoGE *nodo);

void ComponerTrans(ParTransformacion *pt);



//******************************************************
// Funciones para inicializar los objetos de la escena 3
//******************************************************

EntradaNGE pesa(Real alpha, Real d);

EntradaNGE brazo(Real alpha1, Real alpha2, Real d);

NodoGE* escena3(Real alpha1, Real alpha2, Real d);



//******************************************************
// Funciones para inicializar los objetos de la escena 4
//******************************************************

EntradaNGE lata();

NodoGE* escena4();


