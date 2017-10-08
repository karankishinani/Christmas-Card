#include "\PFINAL\BIBLIO.C"
#include "\PFINAL\MOUSE.C"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.1416
#define GREEN 2
#define RED 4
#define LIGHTGRAY 7
#define WHITE 30
#define SNOW 15
#define TRUE 0
#define FALSE 1
#define C 262
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440
#define B 494
#define C8 523
#define D8 587

void estrella(int x, int y, int color, int size)
{
	int i,j,k;
	for (i=y-size;i<=y+size;i++)
		for(j=x-size;j<=x+size;j++)
		{
			if(i==y)
				pintaPixel(j, i, color);
			k=size;
			do{
				if ((i==y-k||i==y+k)&&(j==x||j==x-k||j==x+k))
					pintaPixel(j, i, color);
				k--;
			}while(k>=1);
		}
}

void estrella2(int x, int y, int color, int size)
{
	int i,j,k;
	for (i=y-size;i<=y+size;i++)
		for(j=x-size;j<=x+size;j++)
		{
			if(i==y&&!(j==x-1||j==x+1))
				pintaPixel(j, i, color);
			k=size;
			do{
				if(i!=y-1&&i!=y+1)
					if ((i==y-k||i==y+k)&&(j==x||j==x-k||j==x+k))
						pintaPixel(j, i, color);
				k--;
			}while(k>=1);
		}
} 

unsigned char leePixel(int x, int y)
{
	unsigned char color;
	_AH=0xd; /*Servicio Dh*/
	_CX=x; /*Posicion en x*/
	_DX=y; /*Posicion en y*/
	asm int 10h; /*Rutina de interrupcion en assembler*/
	color=_AL;
	return color;
}

void nieve(int x,int snowcolor)
{
	unsigned char color1, color2;
	int y=0;
	do
	{
		if(y>0)
		{
			delay(20);
			pintaPixel(x,y-1,color1);
		}
		color1=leePixel(x,y);
		color2=leePixel(x,y+1);
		if (color2==snowcolor)
		{
			pintaPixel(x,y,snowcolor);
			break;
		}
		else
			pintaPixel(x,y,snowcolor);
		y++;
	} while (y<=179);
}

void cuadrado(int x, int y, int color, int ancho, int largo)
{
	int i,j;
	for (i=y;i<=y+largo-1;i++)
		for (j=x;j<=x+ancho-1;j++)
			pintaPixel(j,i,color);
}

void linea_hor(int x, int y, int color, int longitud)
{
	int j;
	for (j=x;j<=x+longitud-1;j++)
		pintaPixel(j,y,color);
}

void lineav(int x, int y, int color, int longitud)
{ 
  int j;
  for(j=y; j<=y+longitud-1; j++)
    pintaPixel(x, j, color);
} /*fin de lineav*/

void dibujar_flecha(int x, int y, int color)
{
	int i,j,k;
	for (i=y;i<=y+8;i++)
		for(j=x;j<=x+8;j++)
		{

			if ((i==y||i==y+8)&&(j==x+4))
				pintaPixel(j, i, color);

			if ((i==y+1||i==y+7)&&(j==x+4||j==x+5))
				pintaPixel(j, i, color);

			if ((i==y+2||i==y+6)&&(j==x))
				for(k=x;k<=x+6;k++)
					pintaPixel(j+k-x, i, color);

			if ((i==y+3||i==y+5)&&(j==x))
				for(k=x;k<=x+7;k++)
					pintaPixel(j+k-x, i, color);

			if(i==y+4&&(j==x))
				for(k=x;k<=x+8;k++)
					pintaPixel(j+k-x, i, color);
		}
}

void tirar_nieve()
{
	nieve(rand()%320,SNOW);
}


int obtener_posicion(int *x, int *y)
{
	int boton;
	_AX=0x03;
	asm int 33h;
	*x = (int)_CX;
	*y = (int)_DX;
	boton=_BX&7;
	*x=*x/2;
	if(*x>=320-9) *x=320-9;
	return boton;
}

/*----------Codigo de la melodia----------*/
void espera(int ml)
{
	long pausa;
	clock_t ahora,antes;
	pausa=ml*(CLOCKS_PER_SEC/1000);
	ahora=antes=clock();
	while(ahora-antes<pausa)
		ahora=clock();
}

void sonido(unsigned frecuencia)
{
	unsigned char byt;
	outportb(0x43,0xb6);
	frecuencia=(unsigned)(1193180L/frecuencia);
	outportb(0x42,(char)frecuencia);
	outportb(0x42,(char)(frecuencia>>8));
	byt=inportb(0x61);
	byt|=3;
	outport(0x61,byt);
}

void nosonido(void)
{
	unsigned char byt;
	byt=inportb(0x61);
	byt &= 0xfc;
	outport(0x61,byt);
}

void melodia()
{
    int x1, y1;
    short seccion=0;
    int boton;
    switch(seccion)
    {
        case 0:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(C8);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(C8);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(C8);
            	espera(500);
            	sonido(B);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(B);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(B);
            	espera(500);/**/
            	seccion++;
            }
            
    	case 1:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(250);
            	sonido(A);
            	espera(250);
            	sonido(E);
            	espera(750);
            	nosonido();
            	espera(500);/**/
            	seccion++;
            }
            
    	case 2:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(250);
            	sonido(A);
            	espera(500);
            	sonido(E);
            	espera(500);
            	sonido(G);
            	espera(500);/**/
            	seccion++;
            }
            
    	case 3:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(250);
            	sonido(A);
            	espera(250);
            	sonido(E);
            	espera(750);
            	nosonido();
            	espera(500);/**/
            	seccion++;
            }
            
    	case 4:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(D);
            	espera(250);
            	sonido(E);
            	espera(500);
            	sonido(F);
            	espera(250);
            	sonido(G);
            	espera(250);
            	sonido(A);
            	espera(500);
            	sonido(G);
            	espera(250);/**/
            	seccion++;
            }
            
    	case 5:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(250);
            	sonido(A);
            	espera(250);
            	sonido(E);
            	espera(750);
            	nosonido();
            	espera(750);/* */
            	seccion++;
            }
            
    	case 6:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(A);
            	espera(500);
            	sonido(G);
            	espera(250);
            	sonido(A);
            	espera(250);
            	sonido(G);
            	espera(250);
            	sonido(A);
            	espera(500);/**/
            	seccion++;
             }
             
    	case 7:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(A);
            	espera(500);
            	sonido(D);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(D);
            	espera(750);
            	nosonido();
            	espera(500);/* */
            	seccion++;
             }
             
    	case 8:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                break;
            }
            else
            {
            	sonido(C8);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(C8);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(C8);
            	espera(500);
            	sonido(B);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(B);
            	espera(175);
            	nosonido();
            	espera(75);
            	sonido(B);
            	espera(500);/**/
            	seccion++;
             }
             
    	case 9:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                break;
            }
            else
            {
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(250);
            	sonido(A);
            	espera(250);
            	sonido(E);
            	espera(750);
            	nosonido();
            	espera(500);/**/
            	seccion++;
             }
             
    	case 10:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                break;
            }
            else
            {
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(250);
            	sonido(A);
            	espera(250);
            	sonido(E);
            	espera(750);/**/
            	seccion++;
             }
             
    	case 11:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                break;
            }
            else
            {
            	sonido(G);
            	espera(500);
            	sonido(A);
            	espera(1500);/**/
            	seccion++;
             }
             
    	case 12:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	nosonido();
            	espera(500);
            	sonido(C8);
            	espera(500);
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(250);
            	sonido(A);
            	espera(250);
            	sonido(G);
            	espera(500);/**/
            	seccion++;
             }
             
    	case 13:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	nosonido();
            	espera(250);
            	sonido(C8);
            	espera(500);
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(250);
            	sonido(A);
            	espera(250);
            	sonido(G);
            	espera(500);/**/
            	seccion++;
             }
             
    	case 14:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	nosonido();
            	espera(250);
            	sonido(C8);
            	espera(500);
            	sonido(A);
            	espera(250);
            	sonido(B);
            	espera(1000);/**/
            	seccion++;
             }
             
    	case 15:
    		boton=obtener_posicion(&x1,&y1);
    		if(y1>=0&&y1<=179&&boton==1)
    		{
                seccion=16;
                break;
            }
            else
            {
            	sonido(C8);
            	espera(500);
            	sonido(D8);
            	espera(500);
            	sonido(C8);
            	espera(1000);
            }
    }
    nosonido();
}
/*----------Fin de melodia----------*/

void snowbox()
{
	int i;
	linea_hor(0,180,RED,320);
	for(i=1;i<=9;i++)
		linea_hor(0,180+i,65+i-1,320);
	linea_hor(0,190,RED,320);
	/*Imprimimos el mensaje de pulsar una tecla*/
	est_cursor(1,24);
	impcc("Pulsar cualquier tecla para continuar.");
	
}

void circulo(int cx,int cy,int radio,char color){
  int i,j;
  int x,y;
  for(i=0; i<=360; i++)
    for(j=radio; j>=0; j--){
      x=cx+j*cos(i*PI/180);
      y=cy-j*sin(i*PI/180);
      pintaPixel(x,y,color);
    }
}
void triangulo(int x1,int y1,int x2,int y2,char color){
 int i,j;
 int h;
 float xm,w;
 float p;
 int h1;
 float w1;
 float j1,j2;
 h=y2-y1;
 xm=(x1+x2)/2;
 w=xm-x1;
 p=w/h;
 for(i=y2; i>=y1; i--){
  h1=i-y1;
  w1=p*h1;
  j1=x1+w-w1;
  j2=x1+w+w1;
  for(j=(int)j1; j<=(int)j2; j++)
    pintaPixel(j,i,color);
 }
}
void arco(int cx, int cy, int radio, int grosor, int ang1, int ang2,char color){
 int i,j;
 int x,y;
 for(i=ang1; i<=ang2; i++)
   for(j=radio; j>=(radio-grosor); j--){
      x=cx+j*cos(i*PI/180);
      y=cy-j*sin(i*PI/180);
      pintaPixel(x,y,color);
   }
}

void modoTexto(){
 _AH=0x00;
 _AL=0x02;
 asm int 10h;
}

void esconder_raton()
{
	_AX=2;
	asm int 33h;
}


void presentacion(){

	    cuadrado(0,0,3,320,200);
			cuadrado(8,8,77,304,184);
			cuadrado(16,16,0,288,168);
			est_cursor(4,3);
			impcc("UNIVERSIDAD TECNOLOGICA DE PANAMA");
			est_cursor(5,4);
			impcc("  FACULTAD DE ING. DE SISTEMAS");
			est_cursor(10,5);
			impcc("  COMPUTACIONALES");
			est_cursor(6,8);
			impcc("   PROGRAMACION APLICADA 2");
			est_cursor(7,9);
			impcc("      PROYECTO FINAL");
			est_cursor(7,10);
			impcc("     TARJETA NAVIDENA");
			est_cursor(5,12);
			impcc("          INTEGRANTES");
			est_cursor(7,13);
			impcc("AXEL ALEMAN        8-878-1461");
			est_cursor(7,14);
			impcc("COLLAZOS CRISTIAN  8-889-0816");
			est_cursor(7,15);
			impcc("FENG EIMY          3-733-1709");
			est_cursor(7,16);
			impcc("GOOD LUIS          8-869-2090");
			est_cursor(7,17);
			impcc("GRACIA JOSE        8-893-1290");
			est_cursor(7,18);
			impcc("KISHINANI KARAN    3-735-1345");
			est_cursor(5,20);
			impcc("         GRUPO: 1IL121");
			est_cursor(9,21);
			impcc("   VIERNES 5 DIC 2014");
			est_cursor(9,22);
			impcc("    II SEMESTRE 2014");
			leerChar();
}


void dibujo()
{
		/*------------------------------------------------------------*/
	
	  /*FONDO DEL PINO CON ESTRELLITAS*/
	  cuadrado(0,0,3,320,68);
	  cuadrado(0,68,78,320,55);  /*77,53,76*/
	  cuadrado(0,123,77,320,57);
	  
	  estrella(30, 70, WHITE, 5);
	  estrella(14, 20, WHITE, 7);
	  estrella(50, 44, WHITE, 5);
	  estrella(90, 21, WHITE, 3);
	  
	  
      /*DIBUJO DEL PINO*/
      triangulo(208,20,237,46,SNOW);   /*triangulo 1 blanco - 234*/
	  triangulo(210,20,235,46,2);   /*triangulo 1 */
	  triangulo(185,46,260,76,SNOW);  /*triangulo 2 - blanco */
	  triangulo(190,46,255,76,2);  /*triangulo 2*/
	  triangulo(170,76,275,110,SNOW); /*triangulo 3 - blanco*/
	  triangulo(175,76,270,110,2); /*triangulo 3 */
	  triangulo(151,100,295,150,SNOW); /*triangulo 4 - blanco*/
	  triangulo(156,100,290,150,2); /*triangulo 4 - 198*/
	  
	  cuadrado(200, 100, 2, 45, 40); /*Cuadro 2*/
	  cuadrado(215, 46, 2, 14, 132);  /*Cuadro 1*/
	  cuadrado(215, 151, 6, 14, 27);  /*Tronco */
	  estrella(222, 20, 14, 10); 
	  
	  /*DIBUJO DE LOS REGALOS Y CON SUS LAZOS*/
	  cuadrado(172,160, 54, 20, 18+2); /*Gift 1 -190*/
	  linea_hor(172,  168, 14, 20); lineav(182, 160, 14, 18+2);
	  cuadrado(190, 156, 5, 21, 22+2); /*Gift 2 - 210*/
	  linea_hor(190,  161, 14, 21); lineav(202, 156, 14, 22+2);
	  cuadrado(209, 166, 42, 26, 12+2); /*Gift 3 - 229*/
	  linea_hor(209,  173, 14, 26); lineav(224, 166, 14, 12+2);
	  cuadrado(250, 154, 39, 29, 24+2); /*Gift 4 - 274*/
	  linea_hor(250,  161, 14, 29); lineav(263, 154, 14, 24+2);
	  cuadrado(280, 158, 8, 12, 20+2);  /*Gift 5 - 299*/
	  linea_hor(280,  164, 14, 12); lineav(288, 158, 14, 20+2);
	  
	  /*DIBUJO DE LAS BOLAS DEL PINO*/
	  circulo(208,48,4,12);   /*Bola 1*/
	  circulo(225,40,4,43);   /*Bola 3*/
	  circulo(237,48,4,35);   /*Bola 2*/
	  circulo(260,78,4,45);   /*Bola 4*/
	  circulo(190,78,4,44);   /*Bola 5*/
	  circulo(215,70,4,37);	  /*Bola 6 rosado*/
	  circulo(230,93,4,69);	  /*Bola 7*/
	  circulo(270,112,4,39);  /*Bola 8*/
	  circulo(175,112,4,32);  /*Bola 9*/
	  circulo(220,108,4,56);  /*Bola 10*/
	  circulo(156,150,4,63);	/*Bola 11*/
	  circulo(290,150,4,43);	/*Bola 12*/
	  circulo(250,130,4,76);	/*Bola 13*/
	  circulo(200,129,4,37);   /*Bola 14*/
	  circulo(230,140,4,92);
	  circulo(190,150,4,45);
	  circulo(265,150,4,58);

		/*Galleta de Gengibre*/
		circulo(50,140,30,0x06);/*Galleta*/
		circulo(40,128,5,WHITE); /*Ojo Izquierdo*/
		circulo(65,128,5,WHITE); /*Ojo Derecho*/
		/*Sombrero*/
		cuadrado(25,110,WHITE,50,5);
		triangulo(25,60,75,110,0x28);
		circulo(50,60,5,0x02);
		/*Boca*/
		arco(50,130,30,6,225,315,0x28);
		/*Nariz*/
		triangulo(45,135,52,142,0x02);
		delay(1000);
		/*------------------------------------------------------------*/
}


void fuego_artificial(){
 int x,y;
 int largo,color,mask;
 y=170;
 x=rand()%40+105;
 color=rand()%46+32;
 mask=77;
 largo=5;
 do{
  /*Animacion del cohete subiendo*/
  cuadrado(x,y,(char)color,5,largo);
  delay(25);
  cuadrado(x,y,(char)mask,5,largo);
  if(y==120){
    cuadrado(x,y,78,5,3);
    cuadrado(x,y+3,77,5,6);
    mask=78;
  }
  if(y==60){
   cuadrado(x,y,3,5,8);
   cuadrado(x,y+8,78,5,3);
   mask=3;
  }
  y-=10;
  if(y%40==0)
    largo+=2;
  /*if(y<=120 && y>60)
    mask=77;
  else if(y<=60)
    mask=3;*/
  
 }while(y>=20);
 /*Emulacion de la explosion*/
 estrella2(x,y,(char)color,10);
 delay(100);
 estrella2(x,y,(char)mask,10);
 estrella2(x,y,(char)color,12);
 delay(120);
 estrella2(x,y,(char)mask,12);
 estrella2(x,y,(char)color,14);
 delay(140);
 estrella2(x,y,(char)mask,14);
}
void animacion(){
       int i;
       /*Estrella que parpadean*/
       for(i=0; i<3; i++){
		estrella(30, 70, 80, 5);
		delay(200);
		estrella(30, 70, WHITE, 5);
		estrella(14, 20, 79, 7);
		delay(200);
		estrella(14, 20, WHITE, 7);
		estrella(50, 44, 79, 5);
		delay(200);
		estrella(50, 44, WHITE, 5);
		estrella(90, 21, 79, 3);
		delay(200);
		estrella(90, 21, WHITE, 3);
       }
       /*Bolas que cambian de color*/
       for(i=0; i<2; i++){
	  /*Imagen 1*/
	  circulo(208,48,4,45);
	  circulo(225,40,4,44);
	  circulo(237,48,4,37);
	  circulo(260,78,4,69);
	  circulo(190,78,4,39);
	  circulo(215,70,4,32);
	  circulo(230,93,4,56);
	  circulo(270,112,4,63);
	  circulo(175,112,4,43);
	  circulo(220,108,4,76);
	  circulo(156,150,4,37);
	  circulo(290,150,4,92);
	  circulo(250,130,4,45);
	  circulo(200,129,4,58);
	  circulo(230,140,4,12);
	  circulo(190,150,4,43);
	  circulo(265,150,4,35);
	  delay(200);
	  /*Imagen 2*/
	  circulo(208,48,4,35);
	  circulo(225,40,4,45);
	  circulo(237,48,4,44);
	  circulo(260,78,4,37);
	  circulo(190,78,4,69);
	  circulo(215,70,4,39);
	  circulo(230,93,4,32);
	  circulo(270,112,4,56);
	  circulo(175,112,4,63);
	  circulo(220,108,4,43);
	  circulo(156,150,4,76);
	  circulo(290,150,4,37);
	  circulo(250,130,4,92);
	  circulo(200,129,4,45);
	  circulo(230,140,4,58);
	  circulo(190,150,4,12);
	  circulo(265,150,4,43);
	  delay(200);
	  /*Imagen 3*/
	  circulo(208,48,4,43);
	  circulo(225,40,4,35);
	  circulo(237,48,4,45);
	  circulo(260,78,4,44);
	  circulo(190,78,4,37);
	  circulo(215,70,4,69);
	  circulo(230,93,4,39);
	  circulo(270,112,4,32);
	  circulo(175,112,4,56);
	  circulo(220,108,4,63);
	  circulo(156,150,4,43);
	  circulo(290,150,4,76);
	  circulo(250,130,4,37);
	  circulo(200,129,4,92);
	  circulo(230,140,4,45);
	  circulo(190,150,4,58);
	  circulo(265,150,4,12);
	  delay(200);
	  /*Imagen 4*/
	  circulo(208,48,4,12);
	  circulo(225,40,4,43);
	  circulo(237,48,4,35);
	  circulo(260,78,4,45);
	  circulo(190,78,4,44);
	  circulo(215,70,4,37);
	  circulo(230,93,4,69);
	  circulo(270,112,4,39);
	  circulo(175,112,4,32);
	  circulo(220,108,4,56);
	  circulo(156,150,4,63);
	  circulo(290,150,4,43);
	  circulo(250,130,4,76);
	  circulo(200,129,4,37);
	  circulo(230,140,4,92);
	  circulo(190,150,4,45);
	  circulo(265,150,4,58);
       }
       /*Unos cuantos fuegos artificiales*/
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       fuego_artificial();
       
}

void regalos(int x, int y, int color, int color2)
{
	int i;

	/*listones*/

	/*1*/

	linea_hor(x+2,y+6,color2,3);
	linea_hor(x+9,y+6,color2,3);
	

       pintaPixel(x+1,y+7,color2);
       pintaPixel(x+1,y+8,color2);
       pintaPixel(x+12,y+7,color2);
       pintaPixel(x+12,y+8,color2);

       pintaPixel(x+5,y+7,color2);
       pintaPixel(x+6,y+8,color2);
       pintaPixel(x+7,y+8,color2);
       pintaPixel(x+8,y+7,color2);

	linea_hor(x+2,y+9,color2,10);


	/*2*/

	linea_hor(x+13,y-1,color2,3);
	linea_hor(x+20,y-1,color2,3);


       pintaPixel(x+12,y,color2);
       pintaPixel(x+12,y+1,color2);
       pintaPixel(x+23,y,color2);
       pintaPixel(x+23,y+1,color2);

       pintaPixel(x+16,y,color2);
       pintaPixel(x+17,y+1,color2);
       pintaPixel(x+18,y+1,color2);
       pintaPixel(x+19,y,color2);

	linea_hor(x+13,y+2,color2,10);


	/*3*/

       pintaPixel(x+9, y+15,color2);
       pintaPixel(x+10,y+15,color2);
       pintaPixel(x+13,y+15,color2);
       pintaPixel(x+14,y+15,color2);

       pintaPixel(x+8,y+16,color2);
       pintaPixel(x+15,y+16,color2);

       pintaPixel(x+11,y+16,color2);
       pintaPixel(x+12,y+16,color2);

	linea_hor(x+9,y+17,color2,6);



	/*lazos*/

	
	pintaPixel(x+10, y+19, color2);
	pintaPixel(x+11, y+19, color2);
	pintaPixel(x+12, y+19, color2);
	pintaPixel(x+13, y+19, color2);

        for(i = (y+11); i < (y+18); i++)
	{
 	pintaPixel(x+6, i, color2);
	pintaPixel(x+7, i, color2);
	}

        for(i = (y+20); i < (y+27); i++)
	{
 	pintaPixel(x+11, i, color2);
 	pintaPixel(x+12, i, color2);
	}

        for(i = (y+4); i < (y+19); i++)
	{
 	pintaPixel(x+17, i, color2);
 	pintaPixel(x+18, i, color2);
	}


         
	/*cajas*/
        /*lineas horizontales*/

        for(i = (x+13); i<(x+23);i++)
        pintaPixel(i, y+3, color);

        for(i = (x); i<(x+13);i++)
        pintaPixel(i, y+10, color);

        for(i = (x+4); i<(x+20);i++)
	{
        pintaPixel(i, y+18, color);
	pintaPixel(i, y+20, color);
	}

        for(i = (x); i<(x+23);i++)
	pintaPixel(i, y+27, color);
	
	/*lineas verticales*/
        for(i = (y+10); i < (y+28); i++)
 	pintaPixel(x, i, color);

        for(i = (y+4); i < (y+15); i++)
 	pintaPixel(x+13, i, color);

        for(i = (y+4); i < (y+28); i++)
 	pintaPixel(x+22, i, color);

        for(i = (y+18); i < (y+20); i++)
 	pintaPixel(x+4, i, color);

        for(i = (y+20); i < (y+28); i++)
 	pintaPixel(x+5, i, color);

        for(i = (y+20); i < (y+28); i++)
 	pintaPixel(x+18, i, color);

        for(i = (y+18); i < (y+20); i++)
 	pintaPixel(x+19, i, color);


}

void caja(int x, int y, int color)
{
  	  linea_hor(x,y,color,18);
	  lineav(x,y,color,14);
	  linea_hor(x,y+13,color,18);
	  lineav(x+17,y,color,14);
	  
	  linea_hor(x+2,y+2,color,14);
	  lineav(x+2,y+2,color,9);
	  linea_hor(x+2,y+11,color,14);
	  lineav(x+15,y+2,color,9);

	
	  linea_hor(x+5,y+6,color,8);
	  linea_hor(x+5,y+7,color,8);
} /*fin cuadrado1814*/

void bombon(int x, int y, int color)
{

       
	lineav(x+0,y+2,color,2);
	lineav(x+1,y+2,color,2);
	
	linea_hor(x+2,y+4,color,2);
	linea_hor(x+5,y+4,color,6);
	linea_hor(x+11,y+5,color,2);
	linea_hor(x+5,y+13,color,5);
	linea_hor(x+9,y,color,2);
	linea_hor(x+6,y+5,color,3);

	lineav(x+3,y+8,color,4);

	lineav(x+4,y+1,color,3);

	lineav(x+6,y+9,color,2);

	lineav(x+7,y+2,color,6);

	lineav(x+8,y+9,color,2);

	lineav(x+11,y+1,color,3);

	lineav(x+11,y+8,color,4);

	lineav(x+13,y+3,color,2);
	lineav(x+14,y+3,color,2);

	pintaPixel(x+5,y,color);
	pintaPixel(x+6,y+1,color);
	pintaPixel(x+8,y+1,color);

	pintaPixel(x+4,y+7,color);
	pintaPixel(x+5,y+6,color);

	pintaPixel(x+4,y+9,color);
	pintaPixel(x+5,y+8,color);

	pintaPixel(x+4,y+12,color);
	pintaPixel(x+5,y+11,color);

	pintaPixel(x+7,y+12,color);

	pintaPixel(x+9,y+6,color);
	pintaPixel(x+10,y+7,color);

	pintaPixel(x+9,y+8,color);
	pintaPixel(x+10,y+9,color);

	pintaPixel(x+9,y+11,color);
	pintaPixel(x+10,y+12,color);


}

void borde()
{

        linea_hor(0,0,11,106);
	linea_hor(0,1,11,106);
	linea_hor(0,2,11,106);	

        linea_hor(106,0,56,108);
	linea_hor(106,1,56,108);
	linea_hor(106,2,56,108);

        linea_hor(214,0,12,106);
	linea_hor(214,1,12,106);
	linea_hor(214,2,12,106);

        linea_hor(0,197,11,106);
	linea_hor(0,198,11,106);
	linea_hor(0,199,11,106);	

        linea_hor(106,197,56,108);
	linea_hor(106,198,56,108);
	linea_hor(106,199,56,108);

        linea_hor(214,197,12,106);
	linea_hor(214,198,12,106);
	linea_hor(214,199,12,106);

	lineav(0,2,11,197);
	lineav(1,2,11,197);
	lineav(2,2,11,197);

	lineav(317,2,12,198);
	lineav(318,2,12,198);
	lineav(319,2,12,198);



}

void rayas()
{

	linea_hor(52,13,11,75);
	linea_hor(52,14,11,75);
	linea_hor(52,15,11,75);
	linea_hor(52,16,11,75);
	linea_hor(52,17,11,75);

	linea_hor(52,182,11,75);
	linea_hor(52,183,11,75);
	linea_hor(52,184,11,75);
	linea_hor(52,185,11,75);
	linea_hor(52,186,11,75);

	linea_hor(194,13,12,75);
	linea_hor(194,14,12,75);
	linea_hor(194,15,12,75);
	linea_hor(194,16,12,75);
	linea_hor(194,17,12,75);

	linea_hor(194,182,12,75);
	linea_hor(194,183,12,75);
	linea_hor(194,184,12,75);
	linea_hor(194,185,12,75);
	linea_hor(194,186,12,75);

	lineav(8,22,11,36);
	lineav(12,22,11,87);
	lineav(16,22,11,60);
	lineav(20,22,11,111);
	lineav(24,22,11,27);

	lineav(62,17,11,18);
	lineav(70,17,11,43);
	lineav(78,17,11,12);

	lineav(103,17,11,18);
	lineav(111,17,11,43);
	lineav(119,17,11,12);

	lineav(151,22,56,20);
	lineav(159,22,56,43);
	lineav(167,22,56,9);


	lineav(295,22,12,36);
	lineav(299,22,12,87);
	lineav(303,22,12,60);
	lineav(307,22,12,111);
	lineav(311,22,12,27);

	lineav(204,17,12,18);
	lineav(212,17,12,43);
	lineav(220,17,12,12);

	lineav(245,17,12,18);
	lineav(253,17,12,43);
	lineav(261,17,12,12);




}

void fondo_blanco()
{       int i;
        for(i = 0 ; i< 320; i++)
	lineav(i,0,SNOW,200);


}


void tarjeta()
{

/*	fondo_blanco(); */
        borde();
	rayas();

	regalos(5,150,11,12);
	regalos(148,150,56,56);
	regalos(291,150,12,11);

	bombon(1,53,11);
	bombon(9,78,11);
	bombon(17,46,11);

	bombon(55,30,11);
	bombon(63,55,11);
	bombon(71,23,11);

	bombon(96,30,11);
	bombon(104,55,11);
	bombon(112,28,11);

	bombon(5,105,11);
	bombon(13,128,11);


	bombon(144,35,56);
	bombon(152,60,56);
	bombon(160,28,56);

	bombon(197,30,12);
	bombon(205,55,12);
	bombon(213,23,12);

	bombon(238,30,12);
	bombon(246,55,12);
	bombon(254,23,12);

	bombon(288,53,12);
	bombon(296,78,12);
	bombon(304,46,12);

	bombon(292,105,12);
	bombon(300,128,12);

caja(8,8,11);
caja(151,8,56);
caja(294,8,12);

caja(8,178,11);
caja(151,178,56);
caja(294,178,12);


}

void mensaje_inicial(char *linea1, char *linea2, char *linea3)
{

*(linea1) = 'A';
*(linea1 + 1) = 'u';
*(linea1 + 2) = 'n';
*(linea1 + 3) = 'q';
*(linea1 + 4) = 'u';
*(linea1 + 5) = 'e';

*(linea1 + 6) = ' ';

*(linea1 + 7) = 'e';
*(linea1 + 8) = 'l';

*(linea1 + 9) = ' ';

*(linea1 + 10) = 't';
*(linea1 + 11) = 'i';
*(linea1 + 12) = 'e';
*(linea1 + 13) = 'm';
*(linea1 + 14) = 'p';
*(linea1 + 15) = 'o';

*(linea1 + 16) = ' ';
*(linea1 + 17) = ' ';
*(linea1 + 18) = ' ';
*(linea1 + 19) = ' ';
*(linea1 + 20) = ' ';
*(linea1 + 21) = ' ';
*(linea1 + 22) = ' ';
*(linea1 + 23) = ' ';
*(linea1 + 24) = ' ';
*(linea1 + 25) = ' ';
*(linea1 + 26) = ' ';
*(linea1 + 27) = ' ';
*(linea1 + 28) = ' ';
*(linea1 + 29) = ' ';
*(linea1 + 30) = ' ';
*(linea1 + 31) = '\0';


*(linea2 ) = 't';
*(linea2 + 1) = 'r';
*(linea2 + 2) = 'a';
*(linea2 + 3) = 'n';
*(linea2 + 4) = 's';
*(linea2 + 5) = 'c';
*(linea2 + 6) = 'u';
*(linea2 + 7) = 'r';
*(linea2 + 8) = 'r';
*(linea2 + 9) = 'a';

*(linea2 + 10) = ' ';

*(linea2 + 11) = 'd';
*(linea2 + 12) = 'e';

*(linea2 + 13) = ' ';

*(linea2 + 14) = 'p';
*(linea2 + 15) = 'r';
*(linea2 + 16) = 'i';
*(linea2 + 17) = 's';
*(linea2 + 18) = 'a';
*(linea2 + 19) = ',';

*(linea2 + 20) = ' ';

*(linea2 + 21) = 'l';
*(linea2 + 22) = 'a';

*(linea2 + 23) = ' ';

*(linea2 + 24) = 'N';
*(linea2 + 25) = 'a';
*(linea2 + 26) = 'v';
*(linea2 + 27) = 'i';
*(linea2 + 28) = 'd';
*(linea2 + 29) = 'a';
*(linea2 + 30) = 'd';
*(linea2 + 31) = '\0';

*(linea3) = 'n';
*(linea3 + 1) = 'o';
*(linea3 + 2) = 's';

*(linea3 + 3) = ' ';

*(linea3 + 4) = 'd';
*(linea3 + 5) = 'e';
*(linea3 + 6) = 'j';
*(linea3 + 7) = 'a';

*(linea3 + 8) = ' ';

*(linea3 + 9) = 'e';
*(linea3 + 10) = 't';
*(linea3 + 11) = 'e';
*(linea3 + 12) = 'r';
*(linea3 + 13) = 'n';
*(linea3 + 14) = 'o';
*(linea3 + 15) = 's';

*(linea3 + 16) = ' ';

*(linea3 + 17) = 'i';
*(linea3 + 18) = 'n';
*(linea3 + 19) = 's';
*(linea3 + 20) = 't';
*(linea3 + 21) = 'a';
*(linea3 + 22) = 'n';
*(linea3 + 23) = 't';
*(linea3 + 24) = 'e';
*(linea3 + 25) = 's';
*(linea3 + 26) = '.';

*(linea3 + 27) = ' ';
*(linea3 + 28) = ' ';
*(linea3 + 29) = ' ';
*(linea3 + 30) = ' ';
*(linea3 + 31) = '\0';


}

void limpiamensaje(char *linea1, char *linea2, char *linea3)
{

int i;

for(i = 0; i < 31; i++)
*(linea1 + i) = ' ';

*(linea1 + 31) = '\0';


for(i = 0; i < 31; i++)
*(linea2 + i) = ' ';
*(linea2 + 31) = '\0';

for(i = 0; i < 31; i++)
*(linea3 + i) = ' ';
*(linea3 + 31) = '\0';

}

void despedida()
{  int i;
 
   circulo(10,20,4,39); /*rojo*/
   circulo(70,30,4,45);  /*verde*/
   circulo(50,80,4,44);  /*amarillo*/
   circulo(250,10,4,95);   /*blanquito*/   
   circulo(278,140,4,54);   /*azul*/ 
   
   circulo(240,130,4,39);
   circulo(80,138,4,45);
   circulo(140,160,4,44);
   circulo(300,115,4,95);
   circulo(100,60,4,54);  
   circulo(240, 170,4,43);
   circulo(120,45,4, 67);
 
   
   estrella(300, 18, 80, 5);
   estrella(46, 130,15, 7);
   estrella(220, 175, 15, 6);
   estrella(50, 160, 15, 5);
   
   regalos(5,170,11,12);
   regalos(148,170,56,56);
   regalos(291,170,12,11);
  
   est_cursor(6,10);
   impcc("FELIZ NAVIDAD");
   est_cursor(16,12);
   impcc("Y HASTA LUEGO! :)");
   //leerChar();

   /*Estrella que parpadean*/
  do{  
  for(i=0; i<3; i++)
   {
		estrella(210, 45, 80, 5);
		delay(200);
		estrella(210, 45, 15, 5);
		estrella(250, 80, 78, 7);
		delay(200);
		estrella(250, 80, 15, 7);
		estrella(170, 70, 45, 5);
		delay(200);
		estrella(170, 120,15, 5);
		estrella(170,120,79,5);
		delay(200);
		estrella(90, 150, 79, 3);
		estrella(90, 150,15, 3);
		delay(200);
		estrella(15, 30, 15, 3);
		estrella(15, 30,46, 3);
		delay(200);
    }   
}while(!pulsat());
   
} /*fin de despedida*/

void mensaje(char *linea1, char *linea2, char *linea3)
{
   
    fflush();
        est_cursor(4,11);
	impcc(linea1);

	est_cursor(4,13);
	impcc(linea2);

	est_cursor(6,15);
	impcc(linea3);

	est_cursor(7,21);
	impcc("Editar: E");

	est_cursor(24,21);
	impcc("Salir: Otro");




}


void editar_mensaje( char *linea1, char *linea2, char *linea3)
{
        char aux = ' ';
	int nleido;

	limpiamensaje(linea1,linea2,linea3);
	nleido = 0;


        
	while(aux != '*')
	{
	limpiaP();
	impcc("Introduzca su nueva frase \n(30 caracteres por linea)\n(* para terminar la linea)");
	impcc("\n\nL1: ");
	impcc(linea1);	

	if(nleido == 30)
	impcc("\n\nLimite de Caracteres.");
	
	aux = leerChar();

	if(aux != '*' && aux != 8 && nleido < 30 && aux != 13)
	*(linea1+nleido) = aux;

	if(aux == 8 && nleido > 0)
	{
	
	nleido--;
	*(linea1+nleido) = ' ';

	} else{

	if(nleido < 30)
	nleido++;
	      }

	

	}

	aux = ' ';
	nleido = 0;
	while(aux != '*')
	{
	limpiaP();
	impcc("Introduzca su nueva frase \n(30 caracteres por linea)\n(* para terminar la linea)");
	impcc("\n\nL2: ");
	impcc(linea2);	

	if(nleido == 30)
	impcc("\n\nLimite de Caracteres.");
	
	aux = leerChar();

	if(aux != '*' && aux != 8 && nleido < 30 && aux != 13)
	*(linea2+nleido) = aux;

	if(aux == 8 && nleido > 0)
	{
	
	nleido--;
	*(linea2+nleido) = ' ';

	} else{

	if(nleido < 30)
	nleido++;
	      }

	

	}

	aux = ' ';
	nleido = 0;

	while(aux != '*')
	{
	limpiaP();
	impcc("Introduzca su nueva frase \n(30 caracteres por linea)\n(* para terminar la linea)");
	impcc("\n\nL3: ");
	impcc(linea3);	

	if(nleido == 30)
	impcc("\n\nLimite de Caracteres.");
	
	aux = leerChar();

	if(aux != '*' && aux != 8 && nleido < 30 && aux != 13)
	*(linea3+nleido) = aux;

	if(aux == 8 && nleido > 0)
	{
	
	nleido--;
	*(linea3+nleido) = ' ';

	} else{

	if(nleido < 30)
	nleido++;
	      }

	

	}


}

int botonsuelto_T1(int boton)
{
  _AX=6;
  _BX=boton;
  asm int 33h;
  return _BX;
}

void main()
{
	int i=1, clicks;
	int x1=0, y1, flechax=0, boton, nevar=FALSE;

	char *linea1;
	char *linea2;
	char *linea3;
	char opc = 'e';
	

	linea1=(char*)malloc(32*sizeof(char));
	linea2=(char*)malloc(32*sizeof(char));
	linea3=(char*)malloc(32*sizeof(char));

	mensaje_inicial(linea1,linea2,linea3);




	/*Establecemos modo de video 13h*/
	modovideo();
        /*Muestro la hoja de presentacion*/
        presentacion();
        cuadrado(0,0,0x00,320,200);
	
	/*El Dibujo*/
	dibujo();
	
	/*Mostramos el cursor del raton*/
	showMouse();
	
	do
	{
		/*Dibujamos el cuadro de la flechita de nieve y pulsar tecla*/
		snowbox();
		/*Dibujamos la flecha*/
		dibujar_flecha(flechax,181,RED);
		delay(100);

		/*Animacion*/
		delay(500);
clicks=(int)botonsuelto_T1(0); /*0 IZQ, 1 DER, 2 CENTRO*/
if(clicks==2){
		      delay(100);
		      switch(leePixel(x1,y1)){
			 case 0x02:
			 case 0x28:
			 case 0x0E:
			 case 0x06:
			 case 54:
			 case 5:
			 case 42:
			 case 39:
			 case 8:
			 case 12:
			 case 43:
			 case 45:
			 case 35:
			 case 44:
			 case 37:
			 case 69:
			 case 32:
			 case 56:
			 case 63:
			 case 76:
			 case 92:
			 case 58:
			 case 0x0F: /*Animacion*/
			      animacion();
			      break;
			  }
                    }
		
		/*Activar melodia*/
		boton=obtener_posicion(&x1,&y1);
		if(y1>=0&&y1<=179&&boton==2)
		{
            		melodia();
        	}
		
		/*Tirar Nieve*/
		if (nevar==TRUE)
			tirar_nieve();
		boton=obtener_posicion(&x1,&y1);
		while(y1>=181&&y1<=189&&boton==1)
		{
			snowbox();
			dibujar_flecha(x1,181,RED);
			delay(100);
			flechax=x1;
			boton=obtener_posicion(&x1,&y1);	
		}
		if(flechax==0&&nevar==TRUE)
		{
			cuadrado(0,0,0x00,320,180);
			dibujo();
			nevar=FALSE;
		}
		else if(flechax==320-9)
			nevar=TRUE;

	}while(!pulsat());

	leerChar();

    while(opc == 'e' || opc == 'E')
{	
	
	esconder_raton();
	limpiaP();
	tarjeta();
        mensaje(linea1,linea2,linea3);

	opc = leerChar();
	
	switch(opc)
	{
	case 'e':
	case 'E': editar_mensaje(linea1,linea2,linea3);
		  break;

	}

}
    limpiaP();
	despedida();

free(linea1);
free(linea2);
free(linea3);

}