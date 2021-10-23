#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

typedef struct Nave {
	int x;
	int y;
	int vida;
	int velocidad;
	int aux; //Tipo de enemigo (1,2,3) o cantidad de disparos realizados por el jugador
	Nave* siguiente;
}*PtrNave;

typedef struct Bala {
	int x;
	int y;
	int velocidad;
	bool direccion;
	bool activa;
	Bala* siguiente;
}*PtrBala;



//Globales
//**********************************************************

#define FPS 30.0


//Elementos de allegro que se utilizarán para el juego
//**********************************************************
ALLEGRO_DISPLAY* pantalla;

ALLEGRO_BITMAP* jugador;
ALLEGRO_BITMAP* jugadorIzq;
ALLEGRO_BITMAP* jugadorDer;
ALLEGRO_BITMAP* balaJugador;
ALLEGRO_BITMAP* enemigo1;
ALLEGRO_BITMAP* enemigo2;
ALLEGRO_BITMAP* enemigo3;
ALLEGRO_BITMAP* explosion0;
ALLEGRO_BITMAP* explosion1;
ALLEGRO_BITMAP* explosion2;
ALLEGRO_BITMAP* vida;
ALLEGRO_BITMAP* fondo;

//ALLEGRO_SAMPLE* musica;
//ALLEGRO_FONT* fuente;

//Funcion para pruebas
void PrintBalas(PtrBala& Lista) {
	PtrBala Aux = Lista;
	int cont = 0;
	while (Aux != NULL) {
		cont++;
		cout << endl << "Bala " << cont << " " << Aux->x << " " << Aux->y << endl;
		Aux = Aux->siguiente;
	}
}

PtrNave iniciarJugador(int RX, int RY) {
	PtrNave nave = new (Nave);
	nave->x = RX / 2;
	nave->y = (RY / 3) * 2;
	nave->aux = 0;
	nave->vida = 3;
	nave->velocidad = 10;
	nave->siguiente = NULL;
	return nave;
}

PtrNave crearEnemigo(int RX, int RY, int n) {
	PtrNave nave = new (Nave);
	nave->x = RX / 2;
	nave->y = 100;
	nave->aux = n;
	nave->vida = 1;
	nave->velocidad = 10;
	nave->siguiente = NULL;
	return nave;
}

PtrBala crearBala(int x, int y) {
	PtrBala bala = new (Bala);
	bala->x = x;
	bala->y = y;
	bala->velocidad = 20;
	bala->direccion = true;
	bala->activa = true;
	bala->siguiente = NULL;
	return bala;
}

void AgregarInicioBala(PtrBala& Lista, PtrBala& Nuevo) {
	Nuevo->siguiente = Lista;
	Lista = Nuevo;
}

void AgregarInicioEnemigo(PtrNave& Lista, PtrNave& Nuevo) {
	Nuevo->siguiente = Lista;
	Lista = Nuevo;
}

void EliminarBalasInactivas(PtrBala& Lista) {
	PtrBala Aux;	
	PtrBala temp;	
	Aux = Lista; 
	while (Aux != NULL) { 
		if (Aux->siguiente != NULL) {
			if (!Aux->siguiente->activa) {
				temp = Aux->siguiente;
				Aux->siguiente = temp->siguiente;
				delete(temp);
				temp = NULL;
			}
			else
				Aux = Aux->siguiente;
		}
		else
			Aux = Aux->siguiente;
	}
}

void EliminarEnemigosInactivos(PtrNave& Lista) {
	PtrNave Aux;
	PtrNave temp;
	Aux = Lista;
	while (Aux != NULL) {
		if (Aux->siguiente != NULL) {
			if (Aux->siguiente->vida<-24) {
				temp = Aux->siguiente;
				Aux->siguiente = temp->siguiente;
				delete(temp);
				temp = NULL;
			}
			else
				Aux = Aux->siguiente;
		}
		else
			Aux = Aux->siguiente;
	}
}

void DestruirBalas(PtrBala& Lista) {
	PtrBala Aux = Lista;
	while (Aux != NULL) {
		Lista = Lista->siguiente; 
		delete(Aux); 
		Aux = Lista;
	}
}

void DestruirEnemigos(PtrNave& Lista) {
	PtrNave Aux = Lista;
	while (Aux != NULL) {
		Lista = Lista->siguiente;
		delete(Aux);
		Aux = Lista;
	}
}


bool Colision(int xBala, int yBala, int xNave, int yNave, int ancho, int alto) {
	//al_draw_rectangle(xNave, yNave, xNave + ancho, yNave + alto, al_map_rgb(255, 255, 255), 3); //Dibujar Hitbox Nave
	if (xBala + 12 > xNave && xBala + 12 < xNave + ancho && yBala < yNave + alto && yBala > yNave){
		return true;
	}
	return false;
}


void MoverBalas(PtrBala& Lista, PtrNave& ListaEnemigos) {
	PtrBala Aux = Lista;
	PtrNave AuxEnemigos;
	bool colision = false;
	while (Aux != NULL) {
		if (Aux->activa) {
			Aux->y = Aux->y - 15;
			if (Aux->y < 0) 
				Aux->activa = false;
			else {
				AuxEnemigos = ListaEnemigos;
				while (AuxEnemigos != NULL) {
					if (AuxEnemigos->vida == 1) {
						switch (AuxEnemigos->aux) {
						case 1:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 10, AuxEnemigos->y + 20, 110, 53)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								Aux->activa = false;
							}
							break;
						case 2:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 10, AuxEnemigos->y + 20, 108, 47)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								Aux->activa = false;
							}
							break;
						case 3:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 8, AuxEnemigos->y + 10, 117, 37)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								Aux->activa = false;
							}
							break;
						}
					}
					AuxEnemigos = AuxEnemigos->siguiente;
				}

				al_draw_bitmap(balaJugador, Aux->x, Aux->y, NULL);
				//al_draw_rectangle(Aux->x, Aux->y, Aux->x + 23, Aux->y + 23, al_map_rgb(255, 255, 255), 3);
			}
		}
		Aux = Aux->siguiente;
	}
}

void DibujarHUD(int ptsvida) {
	if (ptsvida = 3) {
		al_draw_bitmap(vida, 60, 20, NULL);
		al_draw_bitmap(vida, 100, 20, NULL);
	}
	else if (ptsvida = 2)
		al_draw_bitmap(vida, 60, 20, NULL);
	al_draw_bitmap(vida, 20, 20, NULL);

	//Imprimir Puntuacion
}

void dibujarEnemigo(int x, int y, int n, int& vida) {
	if (vida == 1) {
		switch (n) {
		case 1:
			al_draw_bitmap(enemigo1, x, y, NULL);
			break;
		case 2:
			al_draw_bitmap(enemigo2, x, y, NULL);
			break;
		case 3:
			al_draw_bitmap(enemigo3, x, y, NULL);
			break;
		}
	}	
	else { //Dibujar Explosion
		if (vida < 1 && vida >= -8) {
			al_draw_bitmap(explosion0, x, y, NULL);
		}else if (vida < -8 && vida >= -16) {
			al_draw_bitmap(explosion1, x, y, NULL);
		}else if (vida < -16 && vida >= -24) {
			al_draw_bitmap(explosion2, x, y, NULL);
		}
		vida--;
	}
}

void DibujarEnemigos(PtrNave Lista) {
	PtrNave Aux = Lista;
	while (Aux != NULL) {
		dibujarEnemigo(Aux->x, Aux->y, Aux->aux, Aux->vida);
		Aux = Aux->siguiente;
	}
}

//DIBUJAR EL PERSONAJE EN EL DISPLAY
void dibujarJugador(int x, int y) {
	al_draw_bitmap(jugador, x, y, NULL);
}

void dibujarJugadorIzq(int x, int y) {
	al_draw_bitmap(jugadorIzq, x, y, NULL);
}

void dibujarJugadorDer(int x, int y) {
	al_draw_bitmap(jugadorDer, x, y, NULL);
}


int juego() {
	if (!al_init()) {
		fprintf(stderr, "No se puede iniciar allegro!\n");
		return -1;
	}


	//---------------------------------------
	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	const int RX = monitor.x2 - monitor.x1;
	const int RY = monitor.y2 - monitor.y1;
	int movF = 0;
	//---------------------------------------

	//Esta línea de código permite que la ventana tenga la capacidad de cambiar de tamaño
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE | ALLEGRO_FULLSCREEN);
	//al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	pantalla = al_create_display(RX, RY);
	al_set_window_title(pantalla, "Space Shooters");
	if (!pantalla) {
		fprintf(stderr, "No se puede crear la pantalla!\n");
		return -1;
	}
	//Líneas para obtener las funcionalidades del uso de las fuentes
	//*******************
	al_init_font_addon();
	al_init_ttf_addon();
	//*******************
	//Línea para obtener las funcionalidades de las imágenes
	//*******************
	al_init_image_addon();
	//*******************


	//Se crean los contenedores de las imágenes que se utilizarán en el juego
	//*******************
	jugador = al_load_bitmap("Imagenes/Nave/nave.png");
	jugadorIzq = al_load_bitmap("Imagenes/Nave/naveIzquierda.png");
	jugadorDer = al_load_bitmap("Imagenes/Nave/naveDerecha.png");
	balaJugador = al_load_bitmap("Imagenes/Bala/balaJugador.png");
	enemigo1 = al_load_bitmap("Imagenes/Enemigos/enemigo1.png");
	enemigo2 = al_load_bitmap("Imagenes/Enemigos/enemigo2.png");
	enemigo3 = al_load_bitmap("Imagenes/Enemigos/enemigo3.png");
	explosion0 = al_load_bitmap("Imagenes/Explosion/explosion0.png");
	explosion1 = al_load_bitmap("Imagenes/Explosion/explosion1.png");
	explosion2 = al_load_bitmap("Imagenes/Explosion/explosion2.png");
	vida = al_load_bitmap("Imagenes/HUD/corazon.png");
	fondo = al_load_bitmap("Imagenes/HUD/Fondo.png");
	//*******************

	//Líneas para obtener las funcionalidades de los audios
	//*******************
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);
	//*******************

	//Se cargan los audios que se van a utilizar en el juego
	//*******************
	//musica = al_load_sample("Musica/Musica.ogg");

	//*******************

	//Líneas para obtener las funcionalidades del teclado
	//*******************
	al_init_primitives_addon();
	al_install_keyboard();
	//*******************


	//Timers que se necesitarán para el juego
	//**********************************************************
	ALLEGRO_TIMER* TimerFrames = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER* TimerBalasInactivas = al_create_timer(10);	//Timer que indica cuando eliminar de la lista las balas inactivas
	ALLEGRO_TIMER* TimerEnemigosInactivos = al_create_timer(20); //Timer que indica cuando eliminar de la lista los enemigos eliminados
	//**********************************************************

	//Se crea una cola de eventos
	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();

	//Registro de los eventos
	//**********************************************************
	al_register_event_source(colaEventos, al_get_timer_event_source(TimerFrames));
	al_register_event_source(colaEventos, al_get_timer_event_source(TimerBalasInactivas));
	al_register_event_source(colaEventos, al_get_timer_event_source(TimerEnemigosInactivos));
	al_register_event_source(colaEventos, al_get_keyboard_event_source());
	//**********************************************************

	//**********************************************************
	bool hecho = true;
	int velocidad = 10;
	PtrNave Jugador = iniciarJugador(RX, RY);
	PtrNave Enemigos = NULL;
	PtrBala Balas = NULL;
	PtrBala bala =	NULL;

	PtrNave enemigo = crearEnemigo(300, 100, 1);
	AgregarInicioEnemigo(Enemigos, enemigo);
	enemigo = crearEnemigo(600, 100, 2);
	AgregarInicioEnemigo(Enemigos, enemigo);
	enemigo = crearEnemigo(900, 100, 3);
	AgregarInicioEnemigo(Enemigos, enemigo);

	ALLEGRO_KEYBOARD_STATE estadoTeclado;
	ALLEGRO_EVENT eventos;


	//Inicialización de los timer
	//**********************************************************
	al_start_timer(TimerBalasInactivas);
	al_start_timer(TimerFrames);
	al_start_timer(TimerEnemigosInactivos);

	while (hecho) {

		al_wait_for_event(colaEventos, &eventos);

		if (eventos.type == ALLEGRO_EVENT_TIMER) {

			if (eventos.timer.source == TimerFrames) {

				al_draw_scaled_bitmap(fondo, 0, movF, 1920, 1080, 0, 0, RX, RY, NULL);
				if (movF == 0) {
					movF = 1080;
				}
				movF--;
				MoverBalas(Balas, Enemigos);
				

				al_get_keyboard_state(&estadoTeclado);	//Revisa el estado del teclado y mueve al personaje
				dibujarJugador(Jugador->x, Jugador->y);
				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_DOWN)) {
					if (Jugador->y < (RY - 80)) Jugador->y += velocidad;
				}
				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_UP)) {
					if (Jugador->y > RY / 2) Jugador->y -= velocidad;
				}
				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_RIGHT)) {
					if (Jugador->x < (RX - 120)) Jugador->x += velocidad;
					dibujarJugadorDer(Jugador->x, Jugador->y);
				}
				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_LEFT)) {
					if (Jugador->x > 9) Jugador->x -= velocidad;
					dibujarJugadorIzq(Jugador->x, Jugador->y);
				}

				DibujarEnemigos(Enemigos);
				DibujarHUD(Jugador->vida);
				al_flip_display();

			}
			else if (eventos.timer.source == TimerBalasInactivas) {
				//cout << "inicio balas: ";
				//PrintBalas(Balas);
				EliminarBalasInactivas(Balas);
				//cout << "final balas: ";
				//PrintBalas(Balas);
			}else if (eventos.timer.source == TimerEnemigosInactivos) {
				EliminarEnemigosInactivos(Enemigos);
			}
			/*
			else if (eventos.timer.source == timerEnemigo) {
				direccionEnemigo[direccion] = false;
				switch (rand() % 4) {			//Cambia de direcion al enemigo
				case UP:
					direccionEnemigo[UP] = true;
					direccion = UP;
					break;

				case DOWN:
					direccionEnemigo[DOWN] = true;
					direccion = DOWN;
					break;

				case RIGHT:
					direccionEnemigo[RIGHT] = true;
					direccion = RIGHT;
					break;

				case LEFT:
					direccionEnemigo[LEFT] = true;
					direccion = LEFT;
					break;
				}
			}
			*/
		}

		else if (eventos.type == ALLEGRO_EVENT_KEY_UP) {		//ESCAPE para cerrar el programa
			switch (eventos.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				bala = crearBala(Jugador->x + 44, Jugador->y - 20);
				AgregarInicioBala(Balas, bala);
				Jugador->aux++;	//Estadistica
				break;
			case ALLEGRO_KEY_ESCAPE:
				hecho = false;
				break;
			}
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));		//Limpia el display
		

	}
	al_destroy_timer(TimerFrames);
	al_destroy_timer(TimerBalasInactivas);
	al_destroy_timer(TimerEnemigosInactivos);
	al_destroy_event_queue(colaEventos);
	al_destroy_display(pantalla);
	al_destroy_bitmap(jugador);
	al_destroy_bitmap(jugadorIzq);
	al_destroy_bitmap(jugadorDer);
	al_destroy_bitmap(enemigo1);
	al_destroy_bitmap(enemigo2);
	al_destroy_bitmap(enemigo3);
	al_destroy_bitmap(explosion0);
	al_destroy_bitmap(explosion1);
	al_destroy_bitmap(explosion2);
	al_destroy_bitmap(balaJugador);
	al_destroy_bitmap(vida);
	al_destroy_bitmap(fondo);
	DestruirBalas(Balas);
	DestruirEnemigos(Enemigos);


}
