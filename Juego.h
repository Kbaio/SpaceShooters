#pragma once
#include <stdio.h>
#include <iostream>
//#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <chrono>

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
	int aux; //Tipo de enemigo (1,2,3)
	int balas; //balas disparadas
	enum Direccion direccion;
	chrono::steady_clock::time_point cooldown; 
	Nave* siguiente;
}*PtrNave;

typedef struct Bala {
	int x;
	int y;
	bool activa;
	Bala* siguiente;
}*PtrBala;



//Globales
//**********************************************************

#define FPS 30.0
enum Direccion { UP, DOWN, RIGHT, LEFT, NINGUNA };

//Elementos de allegro que se utilizarán para el juego
//**********************************************************
ALLEGRO_DISPLAY* pantalla;

ALLEGRO_BITMAP* jugador;
ALLEGRO_BITMAP* jugadorIzq;
ALLEGRO_BITMAP* jugadorDer;
ALLEGRO_BITMAP* jugadorHit;
ALLEGRO_BITMAP* jugadorIzqHit;
ALLEGRO_BITMAP* jugadorDerHit;
ALLEGRO_BITMAP* balaJugador;
ALLEGRO_BITMAP* balaEnemigo;
ALLEGRO_BITMAP* enemigo1;
ALLEGRO_BITMAP* enemigo2;
ALLEGRO_BITMAP* enemigo3;
ALLEGRO_BITMAP* explosion0;
ALLEGRO_BITMAP* explosion1;
ALLEGRO_BITMAP* explosion2;
ALLEGRO_BITMAP* explosionPequena;
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

void DibujarHUD(int ptsvida) {
	if (ptsvida == 3) {
		al_draw_bitmap(vida, 20, 20, NULL);
		al_draw_bitmap(vida, 60, 20, NULL);
		al_draw_bitmap(vida, 100, 20, NULL);
	}
	else if (ptsvida == 2) {
		al_draw_bitmap(vida, 60, 20, NULL);
		al_draw_bitmap(vida, 20, 20, NULL);
	}
	else if (ptsvida == 1)
		al_draw_bitmap(vida, 20, 20, NULL);

	//Imprimir Puntuacion
}

void dibujarEnemigo(int x, int y, int n, int& vida) {
	if (vida > 0) {
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
		}
		else if (vida < -8 && vida >= -16) {
			al_draw_bitmap(explosion1, x, y, NULL);
		}
		else if (vida < -16 && vida >= -24) {
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

void dibujarJugadorHit(int x, int y) {
	al_draw_bitmap(jugadorHit, x, y, NULL);
}

void dibujarJugadorIzqHit(int x, int y) {
	al_draw_bitmap(jugadorIzqHit, x, y, NULL);
}

void dibujarJugadorDerHit(int x, int y) {
	al_draw_bitmap(jugadorDerHit, x, y, NULL);
}

enum Direccion DireccionAleatoria( ) {
	switch (rand() % 4) {
	case 0:
		return RIGHT;
		break;
	case 1:
		return LEFT;
		break;
	case 2:
		return UP;
		break;
	case 3:
		return DOWN;
		break;
	}
}

PtrNave iniciarJugador(int RX, int RY) {
	PtrNave nave = new (Nave);
	nave->x = RX / 2;
	nave->y = (RY / 3) * 2;
	nave->aux = NULL;
	nave->vida = 3;
	nave->velocidad = 10;
	nave->siguiente = NULL;
	nave->balas = 0;
	nave->direccion = NINGUNA;
	nave->cooldown = chrono::steady_clock::now();
	return nave;
}

//PtrNave crearEnemigoN(int RX, int n) {
//	PtrNave nave = new (Nave);
//	nave->cooldown = chrono::steady_clock::now();
//
//	nave->x = RX / 2;
//	nave->y = 100;
//	nave->aux = n;
//	nave->vida = 1;
//	nave->velocidad = 10;
//	nave->siguiente = NULL;
//	nave->balas = 0;
//	return nave;
//}

PtrNave crearEnemigo(int RX) {
	PtrNave nave = new (Nave);
	nave->cooldown = chrono::steady_clock::now();
	nave->y = 0;
	nave->siguiente = NULL;
	nave->x = rand() % (RX - 200);
	nave->balas = 0;
	//cout << nave->x << endl;

	switch (rand() % 3 + 1) {
		case 1:
			nave->aux = 1;
			nave->vida = 3;
			nave->velocidad = 3;
			nave->direccion = NINGUNA;
			break;
		case 2:
			nave->aux = 2;
			nave->vida = 1;
			nave->velocidad = 5;
			nave->direccion = DireccionAleatoria();
			break;
		case 3:
			nave->aux = 3;
			nave->vida = 1;
			nave->velocidad = 10;
			switch (rand() % 2){
			case 0:
				nave->direccion = RIGHT;
				break;
			case 1:
				nave->direccion = LEFT;
				break;
			}
			break;
	}
	return nave;
}

PtrBala crearBala(int x, int y) {
	PtrBala bala = new (Bala);
	bala->x = x;
	bala->y = y;
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
	//Dibujar Hitboxs Naves
	//al_draw_rectangle(xNave, yNave, xNave + ancho, yNave + alto, al_map_rgb(255, 255, 255), 3); 
	if (xBala + 12 > xNave && xBala + 12 < xNave + ancho && yBala < yNave + alto && yBala > yNave){
		return true;
	}
	return false;
}


void ActualizarBalasJugador(PtrBala& Lista, PtrNave& ListaEnemigos) {
	PtrBala Aux = Lista;
	PtrNave AuxEnemigos;
	while (Aux != NULL) {
		if (Aux->activa) {
			Aux->y = Aux->y - 15;
			if (Aux->y < 0) 
				Aux->activa = false;
			else {
				AuxEnemigos = ListaEnemigos;
				while (AuxEnemigos != NULL) {
					if (AuxEnemigos->vida > 0) {
						switch (AuxEnemigos->aux) {
						case 1:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 10, AuxEnemigos->y + 20, 110, 53)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								Aux->activa = false;
								al_draw_bitmap(explosionPequena, Aux->x, Aux->y, NULL);
							}
							break;
						case 2:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 10, AuxEnemigos->y + 20, 108, 47)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								Aux->activa = false;
								al_draw_bitmap(explosionPequena, Aux->x, Aux->y, NULL);
							}
							break;
						case 3:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 8, AuxEnemigos->y + 10, 117, 37)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								Aux->activa = false;
								al_draw_bitmap(explosionPequena, Aux->x, Aux->y, NULL);
							}
							break;
						}
					}
					AuxEnemigos = AuxEnemigos->siguiente;
				}
				if (Aux->activa)
					al_draw_bitmap(balaJugador, Aux->x, Aux->y, NULL);
			}
		}
		Aux = Aux->siguiente;
	}
}

void ActualizarBalasEnemigos(PtrBala& Lista, PtrNave& Jugador, int RY) {
	PtrBala Aux = Lista;
	while (Aux != NULL) {
		if (Aux->activa) {
			Aux->y = Aux->y + 15;
			if (Aux->y > RY)
				Aux->activa = false;
			else {
				al_draw_bitmap(balaEnemigo, Aux->x, Aux->y, NULL);
				if (Colision(Aux->x, Aux->y, Jugador->x, Jugador->y + 20, 110, 50)) {
					Jugador->vida = Jugador->vida - 1;
					Aux->activa = false;
					switch (Jugador->direccion) {
					case NINGUNA:
						dibujarJugadorHit(Jugador->x, Jugador->y);
						break;
					case RIGHT:
						dibujarJugadorDerHit(Jugador->x, Jugador->y);
						break;
					case LEFT:
						dibujarJugadorIzqHit(Jugador->x, Jugador->y);
						break;
					}
					al_draw_bitmap(explosionPequena, Aux->x, Aux->y, NULL);
				}
			}			
		}
		Aux = Aux->siguiente;
	}	
}


void ActualizarEnemigos(PtrNave& Lista, PtrBala& Balas, int RX, int RY, PtrNave Jugador) {
	PtrBala bala;
	PtrNave Aux = Lista;
	chrono::steady_clock::time_point cooldownAux;
	chrono::duration<double> time_span;
	while (Aux != NULL) {
		if (Aux->vida > 0) {
			cooldownAux = chrono::steady_clock::now();
			time_span = chrono::duration_cast<chrono::duration<double>>(cooldownAux - Aux->cooldown);

			switch (Aux->aux) {
			case 1: //Enemigo #1
				if (Aux->y < (RY / 2) - 77)
					Aux->y = Aux->y + 1;
				if (Jugador->x > Aux->x)	//Se mueve en direccion del jugador
					Aux->x = Aux->x + Aux->velocidad;
				else
					Aux->x = Aux->x - Aux->velocidad;
				if (time_span.count() >= 1) {	//Cooldown de 1 segundo
					Aux->cooldown = cooldownAux;
					bala = crearBala(Aux->x + 34, Aux->y + 73);
					AgregarInicioBala(Balas, bala);
					Aux->balas++;	//Estadistica
				}
				break;
			case 2: //Enemigo #2		Se mueve de forma aleatoria
				if (Aux->direccion == DOWN) {
					if (Aux->y < (RY / 2) - 90)
						Aux->y = Aux->y + Aux->velocidad;
					else
						Aux->direccion = DireccionAleatoria();
				}
				else if (Aux->direccion == RIGHT) {
					if (Aux->x < RX- 100) 
						Aux->x = Aux->x + Aux->velocidad;
					else
						Aux->direccion = DireccionAleatoria();
				}
				else if (Aux->direccion == LEFT) {
					if (Aux->x > 15) 
						Aux->x = Aux->x - Aux->velocidad;
					else
						Aux->direccion = DireccionAleatoria();
				}
				else if (Aux->direccion == UP) {
					if (Aux->y > 15) 
						Aux->y = Aux->y - Aux->velocidad;
					else
						Aux->direccion = DireccionAleatoria();
				}
				if (time_span.count() >= 0.3) {	//Cooldown de 0.3 segundo
					Aux->cooldown = cooldownAux;
					bala = crearBala(Aux->x + 34, Aux->y + 77);
					AgregarInicioBala(Balas, bala);
					Aux->balas++;	//Estadistica
				}
				break;
			case 3:	//Enemigo #3
				if (Aux->y < (RY / 2) - 77)
					Aux->y = Aux->y + 1;

				if (Aux->x > RX - 100)	//Cambia de direccion si llega al limite
					Aux->direccion = LEFT;
				else if (Aux->x < 0)
					Aux->direccion = RIGHT;

				if (Aux->direccion == LEFT)	//Se mueve hacia la izquierda o derecha
					Aux->x = Aux->x - Aux->velocidad;
				else if (Aux->direccion == RIGHT)
					Aux->x = Aux->x + Aux->velocidad;

				if (time_span.count() >= 0.5) {	//Cooldown de 0.5 segundo
					Aux->cooldown = cooldownAux;
					bala = crearBala(Aux->x + 73, Aux->y + 53);
					AgregarInicioBala(Balas, bala);
					bala = crearBala(Aux->x + 7, Aux->y + 53);
					AgregarInicioBala(Balas, bala);
					Aux->balas = Aux->balas + 2;	//Estadistica
				}
				break;
			}
		}
		Aux = Aux->siguiente;
	}
}

void MoverJugador (PtrNave& Jugador, ALLEGRO_KEYBOARD_STATE& estadoTeclado, int RX, int RY) {
	Jugador->direccion = NINGUNA;
	if (al_key_down(&estadoTeclado, ALLEGRO_KEY_DOWN)) {
		if (Jugador->y < (RY - 80)) Jugador->y += Jugador->velocidad;
	}
	if (al_key_down(&estadoTeclado, ALLEGRO_KEY_UP)) {
		if (Jugador->y > RY / 2) Jugador->y -= Jugador->velocidad;
	}
	if (al_key_down(&estadoTeclado, ALLEGRO_KEY_RIGHT)) {
		if (Jugador->x < (RX - 120)) Jugador->x += Jugador->velocidad;
		Jugador->direccion = RIGHT;
	}
	if (al_key_down(&estadoTeclado, ALLEGRO_KEY_LEFT)) {
		if (Jugador->x > 9) Jugador->x -= Jugador->velocidad;
		Jugador->direccion = LEFT;
	}

	switch (Jugador->direccion) {
	case NINGUNA:
		dibujarJugador(Jugador->x, Jugador->y);
		break;
	case RIGHT:
		dibujarJugadorDer(Jugador->x, Jugador->y);
		break;
	case LEFT:
		dibujarJugadorIzq(Jugador->x, Jugador->y);
		break;
	}
}

void DireccionEnemigo2(PtrNave& Lista) {
	PtrNave Aux = Lista;
	while (Aux != NULL) {
		if (Aux->aux == 2)
			Aux->direccion = DireccionAleatoria();
		Aux = Aux->siguiente;
	}
}


int juego() {
	if (!al_init()) {
		fprintf(stderr, "No se puede iniciar allegro!\n");
		return -1;
	}
	srand(time(0));

	//---------------------------------------
	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	const int RX = monitor.x2 - monitor.x1;
	const int RY = monitor.y2 - monitor.y1;
	int movF = 0;
	//---------------------------------------

	//Esta línea de código permite que la ventana tenga la capacidad de cambiar de tamaño
	//al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE | ALLEGRO_FULLSCREEN);
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
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
	jugadorHit = al_load_bitmap("Imagenes/Nave/naveHit.png");
	jugadorIzqHit = al_load_bitmap("Imagenes/Nave/naveIzquierdaHit.png");
	jugadorDerHit = al_load_bitmap("Imagenes/Nave/naveDerechaHit.png");
	balaJugador = al_load_bitmap("Imagenes/Bala/balaJugador.png");
	balaEnemigo = al_load_bitmap("Imagenes/Bala/balaEnemigo.png");
	enemigo1 = al_load_bitmap("Imagenes/Enemigos/enemigo1.png");
	enemigo2 = al_load_bitmap("Imagenes/Enemigos/enemigo2.png");
	enemigo3 = al_load_bitmap("Imagenes/Enemigos/enemigo3.png");
	explosion0 = al_load_bitmap("Imagenes/Explosion/explosion0.png");
	explosion1 = al_load_bitmap("Imagenes/Explosion/explosion1.png");
	explosion2 = al_load_bitmap("Imagenes/Explosion/explosion2.png");
	explosionPequena = al_load_bitmap("Imagenes/Explosion/explosionPequena.png");
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
	ALLEGRO_TIMER* TimerLiberarMemoria = al_create_timer(10);	//Timer que indica cuando liberar la memoria de los enemigos y las balas inactivas
	ALLEGRO_TIMER* TimerEnemigo = al_create_timer(3);			//Timer que indica cuando cambiar de direccion al enemigo que se mueve aleatoriamente
	ALLEGRO_TIMER* TimerCrearEnemigo = al_create_timer(3);			//Timer que indica cuando generar un nuevo enemigo
	//**********************************************************

	//Se crea una cola de eventos
	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();

	//Registro de los eventos
	//**********************************************************
	al_register_event_source(colaEventos, al_get_timer_event_source(TimerFrames));
	al_register_event_source(colaEventos, al_get_timer_event_source(TimerLiberarMemoria));
	al_register_event_source(colaEventos, al_get_timer_event_source(TimerEnemigo));
	al_register_event_source(colaEventos, al_get_timer_event_source(TimerCrearEnemigo));
	al_register_event_source(colaEventos, al_get_keyboard_event_source());
	//**********************************************************

	//**********************************************************
	bool loop = true;
	PtrNave Jugador = iniciarJugador(RX, RY);
	PtrNave Enemigos = NULL;
	PtrBala BalasJugador = NULL;
	PtrBala BalasEnemigos = NULL;
	PtrBala bala =	NULL;
	chrono::steady_clock::time_point cooldownAux;
	chrono::duration<double> time_span;

	PtrNave enemigo = crearEnemigo(RX);
	//AgregarInicioEnemigo(Enemigos, enemigo);
	//enemigo = crearEnemigo(RX);
	//AgregarInicioEnemigo(Enemigos, enemigo);
	//enemigo = crearEnemigo(RX);
	//AgregarInicioEnemigo(Enemigos, enemigo);

	ALLEGRO_KEYBOARD_STATE estadoTeclado;
	ALLEGRO_EVENT eventos;


	//Inicialización de los timer
	//**********************************************************
	al_start_timer(TimerLiberarMemoria);
	al_start_timer(TimerEnemigo);
	al_start_timer(TimerCrearEnemigo);
	al_start_timer(TimerFrames);

	while (loop) {

		al_wait_for_event(colaEventos, &eventos);

		if (eventos.type == ALLEGRO_EVENT_TIMER) {

			if (eventos.timer.source == TimerFrames) {

				al_draw_scaled_bitmap(fondo, 0, movF, 1920, 1080, 0, 0, RX, RY, NULL);
				if (movF == 0) {
					movF = 1080;
				}
				movF--;

				al_get_keyboard_state(&estadoTeclado);	//Revisa el estado del teclado
				MoverJugador(Jugador, estadoTeclado, RX, RY);

				ActualizarEnemigos(Enemigos, BalasEnemigos, RX, RY, Jugador);
				ActualizarBalasJugador(BalasJugador, Enemigos);
				ActualizarBalasEnemigos(BalasEnemigos, Jugador, RY);
				

				DibujarEnemigos(Enemigos);
				DibujarHUD(Jugador->vida);
				al_flip_display();

			}
			else if (eventos.timer.source == TimerLiberarMemoria) {
				//cout << "inicio balas: ";//PrintBalas(Balas);
				EliminarBalasInactivas(BalasJugador);
				EliminarBalasInactivas(BalasEnemigos);
				EliminarEnemigosInactivos(Enemigos);
				//cout << "final balas: ";//PrintBalas(Balas);
			}
			else if (eventos.timer.source == TimerEnemigo) {
				DireccionEnemigo2(Enemigos);
			}
			else if (eventos.timer.source == TimerCrearEnemigo) {
				enemigo = crearEnemigo(RX);
				AgregarInicioEnemigo(Enemigos, enemigo);
			}
			
		}

		else if (eventos.type == ALLEGRO_EVENT_KEY_UP) {		//ESCAPE para cerrar el programa
			switch (eventos.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				cooldownAux = chrono::steady_clock::now();
				time_span = chrono::duration_cast<chrono::duration<double>>(cooldownAux - Jugador->cooldown);
				//cout <<time_span.count()  << endl; 
				if (time_span.count() >= 0.5) {	//Cooldown de 0.5 segundos
					Jugador->cooldown = cooldownAux;
					bala = crearBala(Jugador->x + 44, Jugador->y - 20);
					AgregarInicioBala(BalasJugador, bala);
					Jugador->balas++;	//Estadistica
				}
				break;
			case ALLEGRO_KEY_ESCAPE:
				loop = false;
				break;
			}
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));		//Limpia el display
	}
	al_destroy_timer(TimerFrames);
	al_destroy_timer(TimerLiberarMemoria);
	al_destroy_timer(TimerEnemigo);
	al_destroy_timer(TimerCrearEnemigo);
	al_destroy_event_queue(colaEventos);
	al_destroy_display(pantalla);
	al_destroy_bitmap(jugador);
	al_destroy_bitmap(jugadorIzq);
	al_destroy_bitmap(jugadorDer);
	al_destroy_bitmap(jugadorHit);
	al_destroy_bitmap(jugadorIzqHit);
	al_destroy_bitmap(jugadorDerHit);
	al_destroy_bitmap(enemigo1);
	al_destroy_bitmap(enemigo2);
	al_destroy_bitmap(enemigo3);
	al_destroy_bitmap(explosion0);
	al_destroy_bitmap(explosion1);
	al_destroy_bitmap(explosion2);
	al_destroy_bitmap(explosionPequena);
	al_destroy_bitmap(balaJugador);
	al_destroy_bitmap(balaEnemigo);
	al_destroy_bitmap(vida);
	al_destroy_bitmap(fondo);
	DestruirBalas(BalasJugador);
	DestruirBalas(BalasEnemigos);
	DestruirEnemigos(Enemigos);


}
