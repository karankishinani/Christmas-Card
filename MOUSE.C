/* Para Evitar Que se Incluyan Varias Veces el mismo archivo */
#ifndef _BIBLIOTECA_RATON_121
#define _BIBLIOTECA_RATON_121

/*Archivo de Biblioteca de Funciones usando interrupciones del Ratón*/

/*Funciones de Manejo del Raton*/


/*---------------------------------------------------------------------------------------------*/
/*T1*/
/*Funcion reset del raton */

void reset_raton()
{ 
	_AX=0;
	asm int 33h;
	if (_AX==0)
		return 0; /*no esta instalado*/
	else 
		return 1; /*si esta instalado*/
}

/*---------------------------------------------------------------------------------------------*/
/*T2*/






/*---------------------------------------------------------------------------------------------*/
/*T3*/






/*---------------------------------------------------------------------------------------------*/
/*T4*/
/* 7.	Función de botón presionado.: interrupcion 33h de mouse */
/* Servicio 0Ch */
   
   int PulsadoBoton()
    {
	int bot;
 	 	asm{
                 mov ax,3  /* Servicio 0Ch */
                 int 0x33  	/* Rutina de interrupcion en assembler*/
                 mov bot,bx  /*Eventos que deben provocar la llamada del controlador*/
             }
      return bot;
    }

/* Función de soltar botón.: interrupcion 33h de mouse 
 Servicio 0Ch */

void EsperarSoltadoBoton()
{  
	int bot;
	do{
		do{
			bot=PulsadoBoton();
			printf(" %i",bot);
			/* 0 se mueve el raton 
			1 boton izquierdo
			2 boton derecho */
			delay(500);
		}while(bot!=2);
		PulsadoBoton();
	}while(bot!=0);
      printf(" \n boton suelto %i",bot);
	  getch();
}


/*   Función que cambia el  tamaño del cursor*/
void tamcursor(int x )
{
_AH = 1;              /* Servicio 1 */		  			
_CH = 1;    /* comienzo de linea*/
_CL = x;     		/* final de linea*/		
asm int 10h;    		/* Rutina de interrupcion en assembler*/
}

/*---------------------------------------------------------------------------------------------*/
/*T5*/
void showMouse(void) 
{ 
    _AX=0x1;		/*Servicio 1*/
	asm int 33h;	/*Rutina de interrupcion assembler*/
}
void limMouseH(int x, int x2){
	_AX=0x7;		/*Servicio 7*/
	_CX=x;			/*Limite izquierdo*/
	_DX=x2;			/*Limite derecho*/
	asm int 33h;	/*Rutina de interrupcion assembler*/
}
void limMouseV(int y, int y2){
	_AX=0x8;		/*Servicio 7*/
	_CX=y;			/*Limite superior*/
	_DX=y2;			/*Limite inferior*/
	asm int 33h;	/*Rutina de interrupcion assembler*/
}

#endif
