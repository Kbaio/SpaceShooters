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

//OBJETO PERSONAJE
struct Personaje {
	int x;
	int y;
	Personaje() {

	}
	Personaje(int _x, int _y) {
		x = _x;
		y = _y;

	}
};

//Globales
//**********************************************************
enum Direccion { UP, DOWN, RIGHT, LEFT };

bool teclasDireccion[4] = { false, false, false, false }; //!
Personaje* personajeP;
Personaje* enemigoP;
bool sentido = 0;
#define FPS 60.0


//Elementos de allegro que se utilizarán para el juego
//**********************************************************
ALLEGRO_DISPLAY* pantalla;
ALLEGRO_COLOR transparente;

ALLEGRO_BITMAP* personaje; //CONTIENE LAS IMAGENES
ALLEGRO_BITMAP* enemigo;
ALLEGRO_BITMAP* fondo;

ALLEGRO_SAMPLE* musica;
ALLEGRO_FONT* fuente;

//FUNCIONES MOVIMIENTO

void moverPersonaje(int movimiento) {
	if (teclasDireccion[DOWN]) {
		if (personajeP->y < (900 - 30)) personajeP->y += movimiento;
	}
	if (teclasDireccion[UP]) {
		if (personajeP->y > 60 + 10) personajeP->y -= movimiento;
	}
	if (teclasDireccion[RIGHT]) {
		if (personajeP->x < (1500 - 30)) personajeP->x += movimiento;
		sentido = true;
	}
	if (teclasDireccion[LEFT]) {
		if (personajeP->x > 500) personajeP->x -= movimiento;
		sentido = false;
	}

}


void iniciarPersonaje(int x, int y) {
	personajeP = new Personaje(x, y);
}

//iniciarPersonaje: CREA LAS VARIABLES ANONIMAS DEL PERSONAJE Y EL ENEMIGO


//DIBUJAR EL PERSONAJE EN EL DISPLAY
void dibujarPrincipal(int x, int y) {
	al_draw_bitmap(personaje, x, y, NULL);
	al_flip_display();
}


int juego() {
	if (!al_init()) {
		fprintf(stderr, "No se puede iniciar allegro!\n");
		return -1;
	}
	int movimiento = 5;


	//---------------------------------------
	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	const int RX = monitor.x2 - monitor.x1;
	const int RY = monitor.y2 - monitor.y1;

	int movF = 0;
	//---------------------------------------

	//Esta línea de código permite que la ventana tenga la capacidad de cambiar de tamaño
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE | ALLEGRO_FULLSCREEN);

	pantalla = al_create_display(RX, RY);
	//al_set_window_position(pantalla, 200, 200);
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
	personaje = al_load_bitmap("Imagenes/NaveAliada.png");
	enemigo = al_load_bitmap("Imagenes/enemigo.png");
	fondo = al_load_bitmap("Imagenes/Fondo.png");
	//*******************

	//Líneas para obtener las funcionalidades de los audios
	//*******************
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1000);
	//*******************

	//Se cargan los audios que se van a utilizar en el juego
	//*******************
	musica = al_load_sample("Musica/Musica.ogg");

	//*******************

	//Líneas para obtener las funcionalidades del teclado
	//*******************
	al_init_primitives_addon();
	al_install_keyboard();
	//*******************


	//Timers que se necesitarán para el juego
	//**********************************************************
	ALLEGRO_TIMER* primerTimer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER* segundoTimer = al_create_timer(1 / FPS);
	ALLEGRO_TIMER* tercerTimer = al_create_timer(1.0 / FPS);
	//**********************************************************

	//Se crea una cola de eventos
	ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();

	//Registro de los eventos
	//**********************************************************
	al_register_event_source(colaEventos, al_get_timer_event_source(primerTimer));
	al_register_event_source(colaEventos, al_get_timer_event_source(segundoTimer));
	al_register_event_source(colaEventos, al_get_timer_event_source(tercerTimer));
	al_register_event_source(colaEventos, al_get_keyboard_event_source());
	//**********************************************************

	//Inicialización de los timer
	//**********************************************************
	al_start_timer(primerTimer);
	al_start_timer(segundoTimer);
	al_start_timer(tercerTimer);
	//**********************************************************
	bool hecho = true;
	iniciarPersonaje(RX / 2, RY / 2);

	ALLEGRO_KEYBOARD_STATE estadoTeclado;

	al_get_keyboard_state(&estadoTeclado);

	while (hecho) {

		ALLEGRO_EVENT eventos;

		al_wait_for_event(colaEventos, &eventos);


		/*Evento que toma en cuenta la tecla más actual presionada, se van activando en un array que representa cada movimiento
		Observación: Si se presiona una segunda tecla, al mismo tiempo que se está presionando la primera, este evento será capaz de detectar las dos teclas
		y representarlas en el array de activación (teclas)
		*/
		if (eventos.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (eventos.keyboard.keycode) {

			case ALLEGRO_KEY_DOWN:
				teclasDireccion[DOWN] = true;
				break;

			case ALLEGRO_KEY_UP:
				teclasDireccion[UP] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				teclasDireccion[RIGHT] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				teclasDireccion[LEFT] = true;
				break;


			}

		}
		/*Evento que toma en cuenta cuando se deja de presionar alguna tecla, funciona de la misma forma que el evento anterior, cuando se deja de presionar una
		tecla, se desactiva del array de activación (teclas)
		*/
		if (eventos.type == ALLEGRO_EVENT_KEY_UP) {
			switch (eventos.keyboard.keycode) {

			case ALLEGRO_KEY_DOWN:
				teclasDireccion[DOWN] = false;
				break;

			case ALLEGRO_KEY_UP:
				teclasDireccion[UP] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				teclasDireccion[RIGHT] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				teclasDireccion[LEFT] = false;
				break;


			case ALLEGRO_KEY_ESCAPE:
				hecho = true;
				break;
			}

		}
		if (eventos.type == ALLEGRO_EVENT_TIMER) {
			if (eventos.timer.source == primerTimer) {
				moverPersonaje(movimiento);

				al_draw_scaled_bitmap(fondo, 0, movF, 1920, 1080, 0, 0, RX, RY, NULL);
				if (movF == 0) {
					movF = 1080;
				}
				movF--;
			}

			/*else if (eventos.timer.source == segundoTimer) {
				moverEnemigo(movimiento);

			}*/
			else if (eventos.timer.source == tercerTimer) {
				dibujarPrincipal(personajeP->x, personajeP->y);
				//dibujarEnemigo(enemigoP->x, enemigoP->y);
			}

		}
		if (eventos.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ALLEGRO_KEY_ESCAPE) {
				hecho = false;
			}
		}

	}



}
