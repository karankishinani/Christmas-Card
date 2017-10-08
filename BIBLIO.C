/*Archivo de Biblioteca de Funciones usando interrupciones de E/S y Ratón*/

/* Para evitar doble inclusion de codigo */
#ifndef _BIBLIOTECA121
#define _BIBLIOTECA121 1

/*Funciones de Entrada y Salida*/

/*-----------------------------------------------------------------------------*/
/*T1*/


void est_cursor(char x, char y){
 _AH=0x02; /*Funcion */
 _DH=y;
 _DL=x;
 _BH=0; /*Pagina*/
 asm int 10h;
}

/*Funcion para limpiar la pantalla*/

void limpiaP(){
 _AH=0x08;
 _BH=0;
 asm int 10h;
 _BH=_AH; /*Atributo*/
 _AH=0x06;
 _AL=0;  /*Pantalla Completa*/
 _CX=0;
 _DX=0x184F;
 asm int 10h;
 _AH=0x02; /*Establecer cursor en 0,0*/
 _DH=0;
 _DL=0;
 _BH=0;
 asm int 10h;
}

/*Funciones para leer caracteres con ECO utilizando las interrupciones del DOS Y BIOS*/

char leeChar() /*Con ECO usando BIOS*/
{
   _AH=0;
   asm int 16h;
   /*_AL ya contiene el caracter*/
   _AH=0x0E;
   _BH=0; /*Pagina*/
   asm int 10h;
   return _AL;
}

char leeC(){ /*Con ECO usando DOS*/
 _AH=0x01;
 asm int 21h;
 if(_AL==0) /*Tecla ASCII Extendido*/
  asm int 21h;
 return _AL; /*Caracter Leido*/
}

/*Funciones para leer caracteres sin ECO utilizando las interrupciones del DOS Y BIOS*/

char leerChar() /*Sin ECO usando BIOS*/
{
  _AH=0;
   asm int 16h;
   return _AL;
}

char leerC(){ /*Sin ECO usando DOS*/
 _AH=0x07;
 asm int 21h;
 if(_AL==0) /*Tecla ASCII Extendido*/
  asm int 21h;
 return _AL; /*Caracter Leido*/
}


/*-----------------------------------------------------------------------------*/
/*T2*/


//IMPRIME CADENA DE CARACTERES

void impcc(char* c)
{
	c[strlen(c)]='$';
	_AH=9;					
	_DX=c;
	asm int 21h;
}
  

//Función de entrada que reconoce la pulsación de cualquier tecla

int pulsat()
{
	_AH = 0x0B;		   
	asm int 21h;	

	return _AL;	//AL = 0 NO, AL = 255 SI
}


















/*-----------------------------------------------------------------------------*/
/*T3*/


/* Funcion que establece el modo video */
void modovideo(void)
{
_AH = 0x00;    			/* Activa el modo de video */
_AL = 0x13;  			    /* modo # 13h*/
asm int 10h;    		/* Rutina de interrupcion en assembler*/
}


/*-----------------------------------------------------------------------------*/
/*T4*/


/* colocar el color de fondo y plano.: interrupcion 10h de video */
/* Servicio 11*/ 

void fondo( int x)
{
_AH = 0xb;              /* Servicio 2 */		  			
_BH = 0;    /*numero de paleta*/
_BL = x;     			/*color*/ 			
asm int 10h;    		/* Rutina de interrupcion en assembler*/
}

/* 	Función que cambia la forma del cursor: interrupcion 10h de video */
/* Servicio 1*/
void cursor(int x )
{
_AH = 1;              /* Servicio 1 */		  			
_CH = 1;    /* comienzo de linea*/
_CL = x;     		/* final de linea*/		
asm int 10h;    		/* Rutina de interrupcion en assembler*/
}


/*-----------------------------------------------------------------------------*/
/*T5*/

void pintaPixel(int x, int y, unsigned char color){
	_AH=0xc;	/*Servicio 0c*/
	_AL=color;	/*color del pixel*/
	_BH=0;		/*Pagina donde estara el pixel*/
	_CX=x;		/*Posicion en x*/
	_DX=y;		/*Posicion en y*/
	asm int 10h;/*Rutina de interrupcion en assembler*/
}

char obtC(){
   _AH=0x0;		/*Servicio 0*/
   asm int 16h;	/*Rutina de interrupcion en assembler*/
   return _AL;	/*Retorno del caracter pulsado*/
}

/*-----------------------------------------------------------------------------*/
/*T6*/

char estadoimp(int puerto)//da el estado de la impresora
{
	_AH=0x02;
	_DX=puerto;/* numero del puerto (0=LPT1, 1=LPT2, 2=LPT3) */
	asm int 17h
	return _AH;
}

char inimp(int puerto)//inicializa la impresora
{
	_AH=0x01;
	_DX=puerto;/* numero del puerto (0=LPT1, 1=LPT2, 2=LPT3) */
	asm int 17h
	return _AH;
}

char impcar(char car,int puerto) //imprime un caracter
{
	_AH=0x00;
	_AL=car;
	_DX=puerto;/* numero del puerto (0=LPT1, 1=LPT2, 2=LPT3) */
	asm int 17h;
	return _AH;
}

/*-----------------------------------------------------------------------------*/
#endif
