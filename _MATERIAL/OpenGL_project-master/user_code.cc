//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"

#define PI 3.14159265

using namespace std;



//***********************************
// Funciones utiles para los calculos
//***********************************


Tupla3r producto_vectorial(Tupla3r U, Tupla3r V)
{
	Tupla3r W;
	W.coo[0] = U.coo[1]*V.coo[2] - U.coo[2]*V.coo[1];
	W.coo[1] = U.coo[2]*V.coo[0] - U.coo[0]*V.coo[1];
	W.coo[2] = U.coo[0]*V.coo[1] - U.coo[1]*V.coo[0];

	return W;
}


Tupla3r sum_vector(Tupla3r U, Tupla3r V)
{
	Tupla3r W;
	W.coo[0] = U.coo[0] + V.coo[0];
	W.coo[1] = U.coo[1] + V.coo[1];
	W.coo[2] = U.coo[2] + V.coo[2];

	return W;
}

double distancia(Tupla3r a, Tupla3r b)
{
	double x = pow((b.coo[0]-a.coo[0]), 2);
	double y = pow((b.coo[1]-a.coo[1]), 2);

	return sqrt((double)(x+y));
}

//****************************************************************************
// Funciones para generar una malla (leer ply y generar atributos de la malla)
//****************************************************************************


void leer_ply(const char* nombre_fichero, bool revolucion, vector<float> &vertices, vector<int> &caras, int N)
{
	if(revolucion)
	{
		vector<float> vertices_perfil;
		ply::read_vertices(nombre_fichero, vertices_perfil);

		//generamos los otros vertices
	  	 generate_vertices(vertices_perfil, vertices, N, 'Y');

	   	//generamos las caras
	   	generate_faces(caras, N, vertices_perfil.size()/3);
	}
	else
	{
		ply::read(nombre_fichero, vertices, caras);
	}

}


void generar_malla(MallaTVT* malla, const char* nombre_fichero, bool revolucion, int N){

	vector<float> vertices;
	vector<int> caras;

	leer_ply(nombre_fichero, revolucion, vertices, caras, N);

	malla->num_ver = vertices.size()/3;
	malla->num_tri = caras.size()/3;
	malla->ver = (Tupla3r *)malloc(sizeof(Tupla3r) * malla->num_ver);
	malla->tri = (Tupla3n *)malloc(sizeof(Tupla3n) * malla->num_tri);

	malla->tam_ver = sizeof(Real)*3L*malla->num_ver;
	malla->tam_tri = sizeof(Natural)*3L*malla->num_tri;

	malla->nor_ver = (Tupla3r *)malloc(sizeof(Tupla3r) * malla->num_ver);
	malla->nor_tri = (Tupla3r *)malloc(sizeof(Tupla3r) * malla->num_tri);

	unsigned int i=0, j=0;

	while(i<vertices.size())
	{
		Tupla3r vert;
		vert.coo[0] = vertices[i];
		vert.coo[1] = vertices[i+1];
		vert.coo[2] = vertices[i+2];

		//cout << " vert " << j << " : " << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << endl;

		malla->ver[j] = vert;

		i+=3;
		j++;
	}

	i=0;
	j=0;
    	while(i<caras.size())
	{
		Tupla3n tri;
		tri.ind[0] = caras[i];
		tri.ind[1] = caras[i+1];
		tri.ind[2] = caras[i+2];

		//cout << " tri " << i << " : " << caras[i] << " " << caras[i+1] << " " << caras[i+2] << endl;

		malla->tri[j] = tri;

		i+=3;
		j++;
	}

	calculate_normales_tri(malla);
	calculate_normales_ver(malla);

	//generamos las coordenadas de textura
	if(revolucion==true)
	{
		// calcular tamaña de la tabla de cc.tt.
		malla->tam_ctv = sizeof(Real)*2L*malla->num_ver ;

		malla->cte_ver = (Tupla2r *)malloc(sizeof(Real)*2L*malla->num_ver);
		calculate_coord_textura_revolucion(malla, N);
	}
	else
		malla->cte_ver = 0;

	MTVT_Crear_VBOs(malla);
}


//**************************************************************************************
// Funciones para generar y almacenar los vertices y caras (malla generada por revolucion)
//**************************************************************************************

void generate_vertices( vector<float> vertices, vector<float> &vertices_final, int N, char eje)
{
    int i,j;
    double alpha;

    //Insercion del primero perfil en la lista
    for(i=0;i<vertices.size();i++)
	vertices_final.push_back(vertices[i]);

    //Generacion de los vertices con tecnica de revolucion (rotacion sobre el eje)
    for(j=0;j<N-1;j++)
    {
	alpha = j * (2*PI/(N-1));
	for(i=0;i<vertices.size();i+=3)
	{
		float vx, vy, vz;
		if(eje == 'X')
		{
			vx = vertices[i];
			vy = cos(alpha)*vertices[i+1] - sin(alpha)*vertices[i+2];
			vz = sin(alpha)*vertices[i+1] + cos(alpha)*vertices[i+2];
		}
		else if(eje == 'Y')
		{
			vx = cos(alpha)*vertices[i] + sin(alpha)*vertices[i+2];
			vy = vertices[i+1];
			vz = -sin(alpha)*vertices[i] + cos(alpha)*vertices[i+2];
		}
		else
		{
			vx = cos(alpha)*vertices[i] - sin(alpha)*vertices[i+1];
			vy = sin(alpha)*vertices[i] + cos(alpha)*vertices[i+1];
			vz = vertices[i+2];
		}

       	 	vertices_final.push_back(vx);
		vertices_final.push_back(vy);
		vertices_final.push_back(vz);
	}
    }

	//Generacion del ultimo perfil (igual al primero)
	alpha = 0;
	for(i=0;i<vertices.size();i+=3)
	{
	 	float vx, vy, vz;
		if(eje == 'X')
		{
			vx = vertices[i];
			vy = cos(alpha)*vertices[i+1] - sin(alpha)*vertices[i+2];
			vz = sin(alpha)*vertices[i+1] + cos(alpha)*vertices[i+2];
		}
		else if(eje == 'Y')
		{
			vx = cos(alpha)*vertices[i] + sin(alpha)*vertices[i+2];
			vy = vertices[i+1];
			vz = -sin(alpha)*vertices[i] + cos(alpha)*vertices[i+2];
		}
		else
		{
			vx = cos(alpha)*vertices[i] - sin(alpha)*vertices[i+1];
			vy = sin(alpha)*vertices[i] + cos(alpha)*vertices[i+1];
			vz = vertices[i+2];
		}

	 	vertices_final.push_back(vx);
		vertices_final.push_back(vy);
		vertices_final.push_back(vz);
	}

	//Generacion de los 2 ultimos vertices para las tapas inferior y superior
	float vx1, vy1, vz1, vx2, vy2, vz2;
	if(eje == 'X')
	{
		vx1 = vertices[0];
		vy1 = 0;
		vz1 = 0;

		vx2 = vertices[vertices.size()-3];
		vy2 = 0;
		vz2 = 0;
	}
	else if(eje == 'Y')
	{
		vx1 = 0;
		vy1 = vertices[1];
		vz1 = 0;

		vx2 = 0;
		vy2 = vertices[vertices.size()-2];
		vz2 = 0;
	}
	else
	{
		vx1 = 0;
		vy1 = 0;
		vz1 = vertices[2];

		vx2 = 0;
		vy2 = 0;
		vz2 = vertices[vertices.size()-1];
	}

	vertices_final.push_back(vx1);
	vertices_final.push_back(vy1);
	vertices_final.push_back(vz1);

	vertices_final.push_back(vx2);
	vertices_final.push_back(vy2);
	vertices_final.push_back(vz2);
}


void generate_faces(vector<int> &caras, int N, int M)
{
	for(unsigned int i=0;i<N+1;i++)
	{
		int i1, i2, i3, i4, i5, i6 ;
		for(unsigned int j=0;j<M-1;j++)
		{
			//primero triangulo
			i1=M*i+j;
			i2=M*i+j+1;
			i3=(M*(i+1)+j+1)%(M*(N+1));

			//segundo triangulo
			i4=M*i+j;
			i5=(M*(i+1)+j)%(M*(N+1));
			i6=(M*(i+1)+j+1)%(M*(N+1));

			caras.push_back(i1);
			caras.push_back(i2);
			caras.push_back(i3);
			caras.push_back(i4);
			caras.push_back(i5);
			caras.push_back(i6);
	   	}
   	}

	//Generacion de las caras de la tapa superior
	for(unsigned int i=0;i<N;i++)
	{
		int i1, i2, i3;
		i1=M*(N+1);
		i2=M*i;
		i3=(M*(i+1))%(M*(N+1));

		//cout << "i1 = " << i1 << " i2 = " << i2 << " i3 = " << i3 << endl;

		caras.push_back(i1);
		caras.push_back(i2);
		caras.push_back(i3);
	}


	//Generacion de las caras de la tapa inferior
	for(unsigned int i=0;i<N;i++)
	{
		int i1, i2, i3;
		i1=M*(N+1)+1;
		i2=M*(i+1)-1;
		i3=(M*(i+2)-1)%(M*(N+1));

		caras.push_back(i1);
		caras.push_back(i2);
		caras.push_back(i3);
	}
}


//*****************************************************************************************************
// Funciones para generar y almacenar los normales a los vertices y caras (malla generada por revolucion)
//*****************************************************************************************************

void calculate_normales_tri(MallaTVT* malla)
{
	for(unsigned int i=0; i<malla->num_tri; i++)
	{
		//Vectores
		Tupla3r AB, BC, N;

		//Puntos
		Tupla3r A, B, C;

		A = malla->ver[malla->tri[i].ind[0]];
		B = malla->ver[malla->tri[i].ind[1]];
		C = malla->ver[malla->tri[i].ind[2]];

		AB.coo[0] = B.coo[0] - A.coo[0];
		AB.coo[1] = B.coo[1] - A.coo[1];
		AB.coo[2] = B.coo[2] - A.coo[2];
		BC.coo[0] = C.coo[0] - B.coo[0];
		BC.coo[1] = C.coo[1] - B.coo[1];
		BC.coo[2] = C.coo[2] - B.coo[2];

		N = producto_vectorial(AB, BC);

		//cout << "N : x=" << N.coo[0] << "y=" << N.coo[1] << " z=" << N.coo[2] << endl;

		malla->nor_tri[i] = N;
	}

}

void calculate_normales_ver(MallaTVT * malla)
{
	for(unsigned int i=0; i<malla->num_ver; i++)
	{
		Tupla3r N;
		vector<int> indices_tri;

		for(unsigned int j=0; j<malla->num_tri; j++)
		{
			if(malla->tri[j].ind[0] == i || malla->tri[j].ind[1] == i || malla->tri[j].ind[2] == i)
				indices_tri.push_back(j);
		}

		for(unsigned int k=0; k<indices_tri.size(); k++)
			N = sum_vector(N, malla->nor_tri[indices_tri[k]]);


		for(unsigned int j=0; j<3; j++)
			N.coo[j] = N.coo[j]/indices_tri.size();

		malla->nor_ver[i] = N;

		//cout << "N : x=" << N.coo[0] << "y=" << N.coo[1] << " z=" << N.coo[2] << endl;
	}
}


//***************************************************************************************
// Funcion para generar y almacenar los coord. de textura (malla generada por revolucion)
//***************************************************************************************

void calculate_coord_textura_revolucion(MallaTVT * malla, int N)
{
	int M = (malla->num_ver-2)/N;

	double d[M];	//vector de distancias
	d[0] = 0;
	for(unsigned int k=1; k<M; k++)
		d[k] = d[k-1] + distancia(malla->ver[k-1], malla->ver[k]);

	for(unsigned int i=0; i<N; i++)
	{
		for(unsigned int j=0; j<M; j++)
		{
			Tupla2r C;

			C.coo[0] = i/(N-1);

			C.coo[1] = d[j]/d[M-1];

			//cout << "malla->cte_ver[" << i << "x" << j << "] = " << C.coo[0] << " " << C.coo[1] << endl;

			malla->cte_ver[i*j] = C;
		}
	}
}



//********************************************************************
// Funciones para dibujar una malla (creacion y visualizacion de VBOs)
//********************************************************************

void draw_malla(MallaTVT* malla, int modo)
{
	if(modo==1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);//Puntos
	if(modo==2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Aristas
	if(modo==3)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Solido
	if(modo==4)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Ajedrez


	MTVT_Visualizar_VBOs_AV(malla);
}


void MTVT_Visualizar_VA(MallaTVT * pm)
{
	if(pm->nor_ver!=NULL)		//si hay normales de v. disponibles
	{
		glEnableClientState(GL_NORMAL_ARRAY) ;		//habilitar uso de array de normales
		glNormalPointer(GL_FLOAT, 0, pm->nor_ver) ;	//especifica puntero a normales
	}

	if(pm->col_ver!=NULL)		//si hay colores de v. disponibles
	{
		glEnableClientState(GL_COLOR_ARRAY) ;		//habilitar uso de array de col.
		glColorPointer(3, GL_FLOAT, 0, pm->col_ver) ;	//especifica puntero a colores
	}

	//habilitar 'vertex arrays'
	glEnableClientState(GL_VERTEX_ARRAY) ;
	//espicificar puntero a tabla de coords. de vertices
	glVertexPointer(3, GL_FLOAT, 0 , pm->ver);
	//dibujar usando vertices indexados
	glDrawElements(GL_TRIANGLES, 3*pm->num_tri, GL_UNSIGNED_INT, pm->tri);
}


GLuint VBO_Crear(GLuint tipo, GLuint tamanio, GLvoid * puntero)
{
	assert(tipo==GL_ARRAY_BUFFER || tipo==GL_ELEMENT_ARRAY_BUFFER) ;
	GLuint id_vbo ;		//resultado: identificador de VBO
	glGenBuffers(1, &id_vbo) ;	//crear nuevo VBO, obterner identificador
	glBindBuffer(tipo, id_vbo) ; 	//activar el VBO usando su identificador
	glBufferData(tipo, tamanio, puntero, GL_STATIC_DRAW) ;		//transferencia RAM->GPU
	glBindBuffer(tipo, 0);		//desactivacion del VBO (activar 0)
	return id_vbo ;		//devolver el identificador resultado
}


void MTVT_Crear_VBOs(MallaTVT * pm)
{
	//crear VBO conteniendo la tabla de vertices
	pm->id_vbo_ver = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_ver, pm->ver);

	//crear VBO con la tabla de triangulos (indices de vertices)
	pm->id_vbo_tri = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_tri, pm->tri);

	//crear VBO con los colores de los vertices
	if(pm->col_ver != NULL)
		pm->id_vbo_col_ver = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_ver, pm->col_ver);

	//crear VBO con las normales de los vertices
	if(pm->nor_ver != NULL)
		pm->id_vbo_nor_ver = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_ver, pm->nor_ver);

	//crear VBO con las normales de los triangulos
	if(pm->nor_tri != NULL)
		pm->id_vbo_nor_tri = VBO_Crear(GL_ARRAY_BUFFER, pm->tam_tri, pm->nor_tri);

	//crear VBO con la table de coord. de textura
	pm->id_vbo_cte_ver = VBO_Crear( GL_ARRAY_BUFFER, pm->tam_ctv, pm->cte_ver );
}

void MTVT_Visualizar_VBOs(MallaTVT *pm)
{
	//especificar formato de los vertices en su VBO (y offset)
	glBindBuffer(GL_ARRAY_BUFFER, pm->id_vbo_ver) ;		//act. VBO
	glVertexPointer(3, GL_FLOAT, 0, 0);		//formato y offset (0)
	glBindBuffer(GL_ARRAY_BUFFER, 0);		//desact VBO
	glEnableClientState(GL_VERTEX_ARRAY);		//act. uso VA

	//visualizar con glDrawElements (puntero a tabla == NULL)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pm->id_vbo_tri);
	glDrawElements(GL_TRIANGLES, 3L*pm->num_tri, GL_UNSIGNED_INT, NULL) ;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//desactivar uso de array de vertices
	glDisableClientState(GL_VERTEX_ARRAY);
}

void MTVT_Visualizar_VBOs_AV(MallaTVT *pm)
{
	if(pm->col_ver!=NULL)
	{
		glBindBuffer(GL_ARRAY_BUFFER, pm->id_vbo_col_ver);	//act. VBO col. v.
		glColorPointer(3, GL_FLOAT, 0 , 0);	//formato y offset de colores
		glEnableClientState(GL_COLOR_ARRAY);	//activa uso de colores de v.
	}
	if(pm->nor_ver!=NULL)
	{
		glBindBuffer(GL_ARRAY_BUFFER, pm->id_vbo_nor_ver);	//act. VBO nor. v.
		glNormalPointer(GL_FLOAT, 0 , 0);	//formato y offset de normales
		glEnableClientState(GL_NORMAL_ARRAY);	//activa uso de normales
	}

	MTVT_Visualizar_VBOs(pm);	//viualizacion con glDrawElements

	if(pm->col_ver!=NULL)
		glDisableClientState(GL_COLOR_ARRAY);	//desact. array de colores
	if(pm->nor_ver!=NULL)
		glDisableClientState(GL_NORMAL_ARRAY);	//desact. array de normales

}

//*****************************************************************************************
// Funciones para inicializar la entrada de una malla/una transformacion con sus atributos
//*****************************************************************************************

EntradaNGE malla(const char* nombre_fichero, bool revolucion = false)
{
	EntradaNGE objeto;
	objeto.tipo = '0';

	MallaTVT* malla = (MallaTVT*)malloc(sizeof(MallaTVT));
	generar_malla(malla, nombre_fichero, revolucion, 50);
	objeto.malla = malla;

	return objeto;
};

EntradaNGE transformacion(char tipo, Real x, Real y, Real z, Real angulo = 0)
{
	EntradaNGE transfEntrada;
	transfEntrada.tipo = '2';

	ParTransformacion* transf = (ParTransformacion*)malloc(sizeof(ParTransformacion));
	transf->tipo = tipo;
	transf->par[0] = x;
	transf->par[1] = y;
	transf->par[2] = z;
	transf->angulo = angulo;

	transfEntrada.transf = transf;

	return transfEntrada;
}

//**************************************************************************
// Funciones para visualizar un nodo de entradas (mallas y transformaciones)
//**************************************************************************

void NGE_Visualizar(NodoGE *nodo)
{
	glPushMatrix();
	for(unsigned int i=0; i<nodo->entrada.size(); i++)
	{
		switch(nodo->entrada[i].tipo)	//segun tipo:
		{
			case '0' : 	//malla
				MTVT_Visualizar_VBOs_AV(nodo->entrada[i].malla);
				break;
			case '1' :	//sub-escena
				NGE_Visualizar(nodo->entrada[i].subesc);
				break;
			case '2' :	//transformacion
				//glMultMatrixf(nodo->entrada[i].transf->coe);
				ComponerTrans(nodo->entrada[i].transf);
				break;
		}
	}
	glPopMatrix();
}


void ComponerTrans(ParTransformacion *pt)
{
	switch(pt->tipo)
	{
		case '0' : 	//rotacion
			glRotatef(pt->angulo, pt->par[0], pt->par[1], pt->par[2]);
			break;
		case '1' :	//escalado
			glScalef(pt->par[0], pt->par[1], pt->par[2]);
			break;
		case '2' :
			glTranslatef(pt->par[0], pt->par[1], pt->par[2]);
			break;
	}
};


//******************************************************
// Funciones para inicializar los objetos de la escena 3
//******************************************************

EntradaNGE pesa(Real alpha, Real d)
{
	EntradaNGE pesaEntrada;
	pesaEntrada.tipo = '1';

	NodoGE* pesa = new NodoGE;

	EntradaNGE hilo = malla("hilo.ply", true);
	pesa->entrada.push_back(hilo);

	EntradaNGE trans = transformacion('2', (Real)0.0, (Real)-1.0, (Real)0.0);
	pesa->entrada.push_back(trans);

	EntradaNGE rotY = transformacion('0', (Real)0.0, (Real)1.0, (Real)0.0, alpha);
	pesa->entrada.push_back(rotY);

	EntradaNGE rot = transformacion('0', (Real)0.0, (Real)0.0, (Real)1.0, (Real)30.0);
	pesa->entrada.push_back(rot);

	EntradaNGE hilo2 = malla("hilo2.ply", true);
	pesa->entrada.push_back(hilo2);

	EntradaNGE rot2 = transformacion('0', (Real)0.0, (Real)0.0, (Real)1.0, (Real)-60.0);
	pesa->entrada.push_back(rot2);

	EntradaNGE hilo3 = malla("hilo2.ply", true);
	pesa->entrada.push_back(hilo3);

	EntradaNGE rot3 = transformacion('0', (Real)0.0, (Real)0.0, (Real)1.0, (Real)30.0);
	pesa->entrada.push_back(rot3);

	EntradaNGE trans3 = transformacion('2', (Real)0.0, (Real)-2.66, (Real)0.0);
	pesa->entrada.push_back(trans3);

	EntradaNGE platillo = malla("platillo.ply");
	pesa->entrada.push_back(platillo);

	EntradaNGE trans4 = transformacion('2', d, (Real)0.1, (Real)0.0);
	pesa->entrada.push_back(trans4);

	EntradaNGE cubo = malla("cubo.ply");
	pesa->entrada.push_back(cubo);

	pesaEntrada.subesc = pesa;

	return pesaEntrada;
}

EntradaNGE brazo(Real alpha1, Real alpha2, Real d)
{
	EntradaNGE brazoEntrada;
	brazoEntrada.tipo = '1';

	NodoGE* brazo = new NodoGE;

	EntradaNGE rot = transformacion('0', (Real)0.0, (Real)0.0, (Real)1.0, alpha1);
	brazo->entrada.push_back(rot);

	EntradaNGE tallo = malla("tallo.ply");
	brazo->entrada.push_back(tallo);

	EntradaNGE trans2 = transformacion('2', (Real)0.0, (Real)3.0, (Real)0.0);
	brazo->entrada.push_back(trans2);

	EntradaNGE rot2 = transformacion('0', (Real)0.0, (Real)0.0, (Real)1.0, -alpha1);
	brazo->entrada.push_back(rot2);

	EntradaNGE trans3 = transformacion('2', (Real)0.0, (Real)-1.0, (Real)0.0);
	brazo->entrada.push_back(trans3);

	EntradaNGE pesa1 = pesa(alpha2, d);
	brazo->entrada.push_back(pesa1);

	EntradaNGE rot3 = transformacion('0', (Real)0.0, (Real)0.0, (Real)1.0, alpha1);
	brazo->entrada.push_back(rot3);

	EntradaNGE trans4 = transformacion('2', (Real)0.0, (Real)-6.0, (Real)0.0);
	brazo->entrada.push_back(trans4);

	EntradaNGE rot4 = transformacion('0', (Real)0.0, (Real)0.0, (Real)1.0, -alpha1);
	brazo->entrada.push_back(rot4);

	EntradaNGE pesa2 = pesa(alpha2, d);
	brazo->entrada.push_back(pesa2);

	brazoEntrada.subesc = brazo;

	return brazoEntrada;
}


NodoGE* escena3(Real alpha1, Real alpha2, Real d)
{
	NodoGE* grafoEscena = new NodoGE;

	EntradaNGE pie = malla("pie.ply");
	grafoEscena->entrada.push_back(pie);

	EntradaNGE trans = transformacion('2', (Real)0.0, (Real)4.3, (Real)0.0);
	grafoEscena->entrada.push_back(trans);

	EntradaNGE tallo = malla("tallo.ply");
	grafoEscena->entrada.push_back(tallo);

	EntradaNGE trans2 = transformacion('2', (Real)0.0, 3.2, (Real)0.0);
	grafoEscena->entrada.push_back(trans2);

	EntradaNGE brazo1 = brazo(alpha1, alpha2, d);
	grafoEscena->entrada.push_back(brazo1);

	return grafoEscena;
};


//******************************************************
// Funciones para inicializar los objetos de la escena 4
//******************************************************

EntradaNGE lata()
{
	EntradaNGE lataEntrada;
	lataEntrada.tipo = '1';

	NodoGE* lata = new NodoGE;

	EntradaNGE lata_pcue = malla("ply/lata-pcue.ply", true);

	lata->entrada.push_back(lata_pcue);

	EntradaNGE lata_psup = malla("ply/lata-psup.ply", true);
	lata->entrada.push_back(lata_psup);

	EntradaNGE lata_pinf = malla("ply/lata-pinf.ply", true);
	lata->entrada.push_back(lata_pinf);

	lataEntrada.subesc = lata;

	return lataEntrada;
}

NodoGE* escena4()
{
	NodoGE* grafoEscena = new NodoGE;

	EntradaNGE esc = transformacion('1', (Real)5.0, (Real)5.0, (Real)5.0);
	grafoEscena->entrada.push_back(esc);

	EntradaNGE lataEntrada = lata();
	grafoEscena->entrada.push_back(lataEntrada);

	EntradaNGE esc2 = transformacion('1', (Real)0.05, (Real)0.05, (Real)0.05);
	grafoEscena->entrada.push_back(esc2);

	EntradaNGE trans = transformacion('2', (Real)-15.0, (Real)0.0, (Real)0.0);
	grafoEscena->entrada.push_back(trans);

	EntradaNGE peon1 = malla("ply/peon.ply", true);
	grafoEscena->entrada.push_back(peon1);

	EntradaNGE trans2 = transformacion('2', (Real)0.0, (Real)0.0, (Real)10.0);
	grafoEscena->entrada.push_back(trans2);

	EntradaNGE peon2 = malla("ply/peon.ply", true);
	grafoEscena->entrada.push_back(peon2);

	EntradaNGE trans3 = transformacion('2', (Real)0.0, (Real)0.0, (Real)10.0);
	grafoEscena->entrada.push_back(trans3);

	EntradaNGE peon3 = malla("ply/peon.ply", true);
	grafoEscena->entrada.push_back(peon3);

	return grafoEscena;
}







