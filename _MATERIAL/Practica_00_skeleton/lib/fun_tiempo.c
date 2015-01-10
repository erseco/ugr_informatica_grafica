

// funciones auxiliares de interfaz con las funciones en <time.h>
// Carlos Ureña, Septiembre de 2013.
// compatibilidad con MACOSX por Ernesto Serrano, Octubre de 2014

#include <math.h>
#include <stdlib.h> 
#include <assert.h>
#include <pthread.h>
#include "fun_tiempo.h"
#ifdef __MACH__ // Incluimos las librerías necesarias para que funcione en OSX
#include <mach/clock.h>
#include <mach/mach.h>
#endif


//----------------------------------------------------------------------

const long 
   nnss = (long)1000000000L ;   // numero de nanosegundos en un segundo 
                              // (mil millones)
#ifdef __MACH__
  const clock_id_t id_reloj = (clock_id_t)-1; // En MACOSX no tenemos identificador de reloj
#else
  const clockid_t id_reloj = CLOCK_REALTIME ; // identificador del reloj en uso 
                               // (se usa reloj de tiempo real).
#endif
//----------------------------------------------------------------------
// escribe en "transcurrido" el intervalo de tiempo entre "inicio" y "fin"
// ("inicio" debe ser anterior o igual a "fin")

void tiempo_transcurrido( struct timespec       * transcurrido, 
                          const struct timespec * inicio, 
                          const struct timespec * fin
                        ) 
{  
   assert( transcurrido != NULL && inicio != NULL && fin != NULL );
   assert( inicio->tv_sec <= fin->tv_sec ) ;
   
   transcurrido->tv_sec = fin->tv_sec - inicio->tv_sec ;
   if ( inicio->tv_nsec <= fin->tv_nsec )
      transcurrido->tv_nsec = fin->tv_nsec - inicio->tv_nsec  ;
   else
   {  transcurrido->tv_nsec = nnss - ( inicio->tv_nsec - fin->tv_nsec );
      assert( transcurrido->tv_sec > 0 ) ;
      transcurrido->tv_sec -- ;
   }
}

//----------------------------------------------------------------------
// devuelve el número de nanosegundos en una estructura de tiempo

long tiempo_nanosegundos( const struct timespec * tiempo )
{
   return  nnss*tiempo->tv_sec + tiempo->tv_nsec  ;
}

//**********************************************************************
//
// funciones "publicas"

//----------------------------------------------------------------------
// devuelve el instante de tiempo de la llamada
struct timespec ahora() 
{
  struct timespec t;
#ifdef __MACH__ // OS X no tiene clock_gettime, usamos clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  t.tv_sec = mts.tv_sec;
  t.tv_nsec = mts.tv_nsec;
#else
  clock_gettime(id_reloj, &t);
#endif

  return t;
}


//----------------------------------------------------------------------
// devuelve la duración en segundos del intervalo de tiempo transcurrido 
// entre 'inicio' y 'fin'

double duracion( const struct timespec * inicio, const struct timespec * fin ) 
{
   struct timespec duracion ;
   long nanosegundos ;
   
   assert( inicio != NULL );
   assert( fin != NULL );

   tiempo_transcurrido( &duracion, inicio, fin ) ;
   nanosegundos = tiempo_nanosegundos( &duracion ); 
   
   return (double)nanosegundos/(double)nnss;
}




   
