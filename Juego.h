#pragma once
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
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
	int aux; //Tipo de enemigo (1,2,3) o Frames de invulnerabilidad del jugador (despues de recibir un hit)
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
ALLEGRO_BITMAP* jefe;
ALLEGRO_BITMAP* jefeInvisible;
ALLEGRO_BITMAP* explosion0;
ALLEGRO_BITMAP* explosion1;
ALLEGRO_BITMAP* explosion2;
ALLEGRO_BITMAP* explosionPequena;
ALLEGRO_BITMAP* vida;
ALLEGRO_BITMAP* fondo;

ALLEGRO_SAMPLE* backgroundMusic;
ALLEGRO_SAMPLE* disparoJugador;
ALLEGRO_SAMPLE* disparoEnemigo;
ALLEGRO_SAMPLE* hitJugador;
ALLEGRO_SAMPLE* hitEnemigo;
ALLEGRO_SAMPLE* jefeMusic;
ALLEGRO_SAMPLE* explosion;
ALLEGRO_SAMPLE* victory;
ALLEGRO_SAMPLE* lose;
ALLEGRO_SAMPLE* menuMusic;

ALLEGRO_FONT* fuente;

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

void DibujarHUD(int ptsvida, int puntuacion) {
	if (ptsvida == 3) {
		al_draw_bitmap(vida, 20, 50, NULL);
		al_draw_bitmap(vida, 60, 50, NULL);
		al_draw_bitmap(vida, 100, 50, NULL);
	}
	else if (ptsvida == 2) {
		al_draw_bitmap(vida, 60, 50, NULL);
		al_draw_bitmap(vida, 20, 50, NULL);
	}
	else if (ptsvida == 1)
		al_draw_bitmap(vida, 20, 50, NULL);

	string buf("Score: ");
	buf.append(to_string(puntuacion));
	const char* texto = buf.c_str();
	al_draw_text(fuente, al_map_rgb(250, 250, 250), 20, 20, ALLEGRO_ALIGN_LEFT, texto);
}


void dibujarExplosion(int x, int y, int vida) {
	if (vida < 1 && vida >= -8) {
		al_draw_bitmap(explosion0, x, y, NULL);
	}
	else if (vida < -8 && vida >= -16) {
		al_draw_bitmap(explosion1, x, y, NULL);
	}
	else if (vida < -16 && vida >= -24) {
		al_draw_bitmap(explosion2, x, y, NULL);
	}
}

void dibujarExplosionJefe(int x, int y, int vida) {
	if (vida < 1 && vida >= -8) {
		al_draw_bitmap(explosion0, x, y, NULL);
	}
	else if (vida < -8 && vida >= -16) {
		al_draw_bitmap(explosion1, x, y, NULL);
	}
	else if (vida < -16 && vida >= -24) {
		al_draw_bitmap(explosion2, x, y, NULL);
	}
	if (vida < 1 && vida >= -8) {
		al_draw_bitmap(explosion0, x + 300, y + 80, NULL);
	}
	else if (vida < -8 && vida >= -16) {
		al_draw_bitmap(explosion1, x + 300, y + 80, NULL);
	}
	else if (vida < -16 && vida >= -24) {
		al_draw_bitmap(explosion2, x + 300, y + 80, NULL);
	}
	if (vida < 1 && vida >= -8) {
		al_draw_bitmap(explosion0, x + 200, y + 50, NULL);
	}
	else if (vida < -8 && vida >= -16) {
		al_draw_bitmap(explosion1, x + 200, y + 50, NULL);
	}
	else if (vida < -16 && vida >= -24) {
		al_draw_bitmap(explosion2, x + 200, y + 50, NULL);
	}
	if (vida < 1 && vida >= -8) {
		al_draw_bitmap(explosion0, x + 150, y + 20, NULL);
	}
	else if (vida < -8 && vida >= -16) {
		al_draw_bitmap(explosion1, x + 150, y + 20, NULL);
	}
	else if (vida < -16 && vida >= -24) {
		al_draw_bitmap(explosion2, x + 150, y + 20, NULL);
	}
	if (vida < 10 && vida >= -18) {
		al_draw_bitmap(explosion0, x + 330, y + 5, NULL);
	}
	else if (vida < -18 && vida >= -26) {
		al_draw_bitmap(explosion1, x + 330, y + 5, NULL);
	}
	else if (vida < -26 && vida >= -34) {
		al_draw_bitmap(explosion2, x + 330, y + 5, NULL);
	}
	if (vida < 10 && vida >= -18) {
		al_draw_bitmap(explosion0, x, y + 100, NULL);
	}
	else if (vida < -18 && vida >= -26) {
		al_draw_bitmap(explosion1, x, y + 100, NULL);
	}
	else if (vida < -26 && vida >= -34) {
		al_draw_bitmap(explosion2, x, y + 100, NULL);
	}
	if (vida < 30 && vida >= -38) {
		al_draw_bitmap(explosion0, x + 50, y + 50, NULL);
	}
	else if (vida < -38 && vida >= -46) {
		al_draw_bitmap(explosion1, x + 50, y + 50, NULL);
	}
	else if (vida < -46 && vida >= -54) {
		al_draw_bitmap(explosion2, x + 50, y + 50, NULL);
	}
	if (vida < 30 && vida >= -38) {
		al_draw_bitmap(explosion0, x + 220, y + 10, NULL);
	}
	else if (vida < -38 && vida >= -46) {
		al_draw_bitmap(explosion1, x + 220, y + 10, NULL);
	}
	else if (vida < -46 && vida >= -54) {
		al_draw_bitmap(explosion2, x + 220, y + 10, NULL);
	}
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
		case 4:
			al_draw_bitmap(jefe, x, y, NULL);
			break;
		}
	}
	else { //Dibujar Explosion
		if (n == 4) {
			dibujarExplosionJefe(x, y, vida);
		}
		else {
			dibujarExplosion(x, y, vida);
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
	nave->aux = 0;
	nave->vida = 3;
	nave->velocidad = 10;
	nave->siguiente = NULL;
	nave->direccion = NINGUNA;
	nave->cooldown = chrono::steady_clock::now();
	return nave;
}

PtrNave iniciarJefe(int RX, int RY) {
	PtrNave nave = new (Nave);
	nave->x = rand() % (RX - 200);
	nave->y = -124;
	nave->aux = 4;
	nave->vida = 35;
	nave->velocidad = 5;
	nave->siguiente = NULL;
	nave->direccion = DireccionAleatoria();
	nave->cooldown = chrono::steady_clock::now();
	return nave;
}


PtrNave crearEnemigo(int RX) {
	PtrNave nave = new (Nave);
	nave->cooldown = chrono::steady_clock::now();
	nave->siguiente = NULL;
	nave->x = rand() % (RX - 200);

	switch (rand() % 3 + 1) {
		case 1:
			nave->aux = 1;
			nave->y = -73;
			nave->vida = 3;
			nave->velocidad = 3;
			nave->direccion = NINGUNA;
			break;
		case 2:
			nave->aux = 2;
			nave->y = -77;
			nave->vida = 1;
			nave->velocidad = 5;
			nave->direccion = DireccionAleatoria();
			break;
		case 3:
			nave->aux = 3;
			nave->y = -53;
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


void ActualizarBalasJugador(PtrBala& Lista, PtrNave& ListaEnemigos, int& puntuacion, int& enemigosEliminados) {
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
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 10, AuxEnemigos->y + 20, 110, 45)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								if (AuxEnemigos->vida == 0) {
									puntuacion = puntuacion + 50;
									enemigosEliminados++;
									al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
								}
								Aux->activa = false;
								al_draw_bitmap(explosionPequena, Aux->x - 15, Aux->y, NULL);
								al_play_sample(hitEnemigo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							}
							break;
						case 2:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 10, AuxEnemigos->y + 20, 108, 47)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								if (AuxEnemigos->vida == 0) {
									puntuacion = puntuacion + 50;
									enemigosEliminados++;
									al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
								}
								Aux->activa = false;
								al_draw_bitmap(explosionPequena, Aux->x - 15, Aux->y, NULL);
								al_play_sample(hitEnemigo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							}
							break;
						case 3:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 8, AuxEnemigos->y + 10, 117, 37)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								if (AuxEnemigos->vida == 0) {
									puntuacion = puntuacion + 50;
									enemigosEliminados++;
									al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
								}
								Aux->activa = false;
								al_draw_bitmap(explosionPequena, Aux->x - 15, Aux->y, NULL);
								al_play_sample(hitEnemigo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							}
							break;
						case 4:
							if (Colision(Aux->x, Aux->y, AuxEnemigos->x - 5, AuxEnemigos->y + 50, 390, 60)) {
								AuxEnemigos->vida = AuxEnemigos->vida - 1;
								if (AuxEnemigos->vida == 0) {
									puntuacion = puntuacion + 500; //+500 por ser el jefe
									enemigosEliminados++;
									al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
								}
								Aux->activa = false;
								al_draw_bitmap(explosionPequena, Aux->x - 15, Aux->y, NULL);
								al_play_sample(hitEnemigo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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
			Aux->y = Aux->y + 10;
			if (Aux->y > RY)
				Aux->activa = false;
			else {
				al_draw_bitmap(balaEnemigo, Aux->x, Aux->y, NULL);
				if (Jugador->aux == 0) {
					if (Colision(Aux->x, Aux->y, Jugador->x, Jugador->y + 20, 110, 50)) {
						Jugador->vida = Jugador->vida - 1;
						Aux->activa = false;
						Jugador->aux = 45;
						al_draw_bitmap(explosionPequena, Aux->x - 15, Aux->y, NULL);
						al_play_sample(hitJugador, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						if (Jugador->vida == 0) {
							al_play_sample(explosion, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						}
					}
				}
			}			
		}
		Aux = Aux->siguiente;
	}	
}


void ActualizarEnemigos(PtrNave& Lista, PtrBala& Balas, int RX, int RY, PtrNave Jugador, int& balas) {
	PtrBala bala;
	PtrNave Aux = Lista;
	chrono::steady_clock::time_point cooldownAux;
	chrono::duration<double> time_span;
	while (Aux != NULL) {
		if (Aux->vida > 0) {
			cooldownAux = chrono::steady_clock::now();
			time_span = chrono::duration_cast<chrono::duration<double>>(cooldownAux - Aux->cooldown);

			if (Aux->y < 0)
				Aux->y = Aux->y + Aux->velocidad;

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
					balas++;	
					al_play_sample(disparoEnemigo, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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
				if (time_span.count() >= 0.5) {	//Cooldown de 0.5 segundo
					Aux->cooldown = cooldownAux;
					bala = crearBala(Aux->x + 34, Aux->y + 77);
					AgregarInicioBala(Balas, bala);
					balas++;	
					al_play_sample(disparoEnemigo, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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
					balas = balas + 2;	
					al_play_sample(disparoEnemigo, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				break;
			case 4: //Enemigo #4		Jefe
				if (Aux->direccion == RIGHT || Aux->direccion == LEFT) {
					if (Jugador->x + 55 > Aux->x + 190)	//Se mueve en direccion del jugador
						Aux->x = Aux->x + Aux->velocidad;
					else
						Aux->x = Aux->x - Aux->velocidad;
				}
				else if (Aux->direccion == DOWN) {
					if (Aux->y < (RY / 2) - 130)
						Aux->y = Aux->y + Aux->velocidad;
					else
						Aux->direccion = DireccionAleatoria();
				}
				else if (Aux->direccion == UP) {
					if (Aux->y > 15)
						Aux->y = Aux->y - Aux->velocidad;
					else
						Aux->direccion = DireccionAleatoria();
				}
				if (time_span.count() >= 0.2) {	//Cooldown de 0.2 segundo
					Aux->cooldown = cooldownAux;
					bala = crearBala(rand() % 380 + Aux->x, Aux->y + 120);
					AgregarInicioBala(Balas, bala);
					//bala = crearBala(rand() % 380 + Aux->x, Aux->y + 120);
					//AgregarInicioBala(Balas, bala);
					balas = balas + 1;
					al_play_sample(disparoEnemigo, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				break;
			}
		}
		Aux = Aux->siguiente;
	}
}

void MoverJugador(PtrNave& Jugador, ALLEGRO_KEYBOARD_STATE& estadoTeclado, int RX, int RY) {
	if (Jugador->vida > 0) {
		Jugador->direccion = NINGUNA;
		if (Jugador->aux > 0)
			Jugador->aux--;
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

		if (Jugador->aux == 0) {	//Dibujar jugador
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
		else {					//Dibujar jugador herido/frames de invulnerabilidad
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
		}
	}
	else {
		dibujarExplosion(Jugador->x, Jugador->y, Jugador->vida);
		Jugador->vida = Jugador->vida - 1;
	}

	
	
}

void DireccionEnemigo2(PtrNave& Lista) {
	PtrNave Aux = Lista;
	while (Aux != NULL) {
		if (Aux->aux == 2 || Aux->aux == 4)
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
	fuente = al_load_font("Fuente/ARCADE_N.ttf", 20, NULL);
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
	jefe = al_load_bitmap("Imagenes/Enemigos/jefe.png");
	jefeInvisible = al_load_bitmap("Imagenes/Enemigos/jefeInvisible.png");
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
	al_reserve_samples(1000);
	//*******************

	//Se cargan los audios que se van a utilizar en el juego
	//*******************
	backgroundMusic = al_load_sample("Sonidos/backgroundMusic.wav");
	disparoJugador = al_load_sample("Sonidos/disparoJugador.wav");
	disparoEnemigo = al_load_sample("Sonidos/disparoEnemigo.wav");
	hitJugador = al_load_sample("Sonidos/hitJugador.wav");
	hitEnemigo = al_load_sample("Sonidos/hitEnemigo.wav");
	jefeMusic = al_load_sample("Sonidos/jefeMusic.ogg");
	explosion = al_load_sample("Sonidos/explosion.wav");
	victory = al_load_sample("Sonidos/victory.wav");
	lose = al_load_sample("Sonidos/lose.wav");
	menuMusic = al_load_sample("Sonidos/MENUFONDO.wav");

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
	ALLEGRO_TIMER* TimerEnemigo = al_create_timer(2);			//Timer que indica cuando cambiar de direccion al enemigo que se mueve aleatoriamente
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
	PtrNave enemigo = NULL;
	PtrBala BalasJugador = NULL;
	PtrBala BalasEnemigos = NULL;
	PtrBala bala =	NULL;
	time_t inicio, fin;
	int enemigosCreados = 0;
	int enemigosEliminados = 0;
	int balasEnemigas = 0;
	int balasJugador = 0;
	int puntuacion = 0;
	chrono::steady_clock::time_point cooldownAux;
	chrono::duration<double> time_span;

	//enemigo = iniciarJefe(RX, RY);
	//AgregarInicioEnemigo(Enemigos, enemigo);
	//enemigo = crearEnemigo(RX);
	//AgregarInicioEnemigo(Enemigos, enemigo);
	//enemigo = crearEnemigo(RX);
	//AgregarInicioEnemigo(Enemigos, enemigo);

	ALLEGRO_KEYBOARD_STATE estadoTeclado;
	ALLEGRO_EVENT eventos;

	ALLEGRO_SAMPLE_ID backgroundMusicID;
	al_play_sample(backgroundMusic, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundMusicID);

	//Inicialización de los timer
	//**********************************************************
	al_start_timer(TimerLiberarMemoria);
	al_start_timer(TimerEnemigo);
	al_start_timer(TimerCrearEnemigo);
	al_start_timer(TimerFrames);

	inicio = time(NULL);

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

				ActualizarEnemigos(Enemigos, BalasEnemigos, RX, RY, Jugador, balasEnemigas);
				DibujarEnemigos(Enemigos);
				ActualizarBalasJugador(BalasJugador, Enemigos, puntuacion, enemigosEliminados);
				ActualizarBalasEnemigos(BalasEnemigos, Jugador, RY);
				

				fin = time(NULL);
				DibujarHUD(Jugador->vida, puntuacion + difftime(fin, inicio));
				al_flip_display();

				if (Enemigos != NULL) {
					if ((Jugador->vida < -24) || ((Enemigos->aux == 4) && (Enemigos->vida <= -54))) {
						if (Jugador->vida < -24)
							al_play_sample(lose, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						else
							al_play_sample(victory, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

						al_stop_sample(&backgroundMusicID);
						loop = false;
					}
				}
				

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
				if (enemigosCreados < 20) {
					enemigo = crearEnemigo(RX);
					AgregarInicioEnemigo(Enemigos, enemigo);
					enemigosCreados++;
				}
				if (enemigosEliminados == 20) {
					al_stop_timer(TimerCrearEnemigo);
					enemigo = iniciarJefe(RX, RY);
					AgregarInicioEnemigo(Enemigos, enemigo);
					enemigosCreados++;
					al_stop_sample(&backgroundMusicID);
					al_play_sample(jefeMusic, 1.5, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundMusicID);
				}
			}
			
		}

		else if (eventos.type == ALLEGRO_EVENT_KEY_UP) {		
			switch (eventos.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:		//Disparar
				if (Jugador->vida > 0) {
					cooldownAux = chrono::steady_clock::now();
					time_span = chrono::duration_cast<chrono::duration<double>>(cooldownAux - Jugador->cooldown);
					//cout <<time_span.count()  << endl; 
					if (time_span.count() >= 0.3) {	//Cooldown de 0.3 segundos
						Jugador->cooldown = cooldownAux;
						bala = crearBala(Jugador->x + 44, Jugador->y - 20);
						AgregarInicioBala(BalasJugador, bala);
						balasJugador++;
						al_play_sample(disparoJugador, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}

				break;
			case ALLEGRO_KEY_ESCAPE:	//ESCAPE para cerrar el programa
				loop = false;
				break;
			}
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));		//Limpia el display
	}

	al_play_sample(menuMusic, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	loop = true;

	fin = time(NULL);

	puntuacion = puntuacion + difftime(fin, inicio);
	if (Enemigos != NULL) {
		if ((Enemigos->aux == 4) && (Enemigos->vida <= -54))
			puntuacion = puntuacion + 500;
	}
	if (Jugador->vida > 0)
		puntuacion = puntuacion + (Jugador->vida * 100);


	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, RY / 11, ALLEGRO_ALIGN_CENTER, "Game over");

	string buf("Puntuacion: ");
	buf.append(to_string(puntuacion));
	const char* texto = buf.c_str();
	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, (RY / 11) * 2, ALLEGRO_ALIGN_CENTER, texto);

	buf.assign("Vidas: ");
	if (Jugador->vida <= 0) {
		buf.append("0");
	}
	else
		buf.append(to_string(Jugador->vida));
	texto = buf.c_str();
	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, (RY / 11) * 3, ALLEGRO_ALIGN_CENTER, texto);

	buf.assign("Tiempo de ejecucion: ");
	buf.append(to_string((int)difftime(fin, inicio)));
	buf.append(" segundos");
	texto = buf.c_str();
	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, (RY / 11) * 4, ALLEGRO_ALIGN_CENTER, texto);

	buf.assign("Disparos realizados: ");
	buf.append(to_string(balasJugador));
	texto = buf.c_str();
	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, (RY / 11) * 5, ALLEGRO_ALIGN_CENTER, texto);

	buf.assign("Disparos enemigos: ");
	buf.append(to_string(balasEnemigas));
	texto = buf.c_str();
	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, (RY / 11) * 6, ALLEGRO_ALIGN_CENTER, texto);

	buf.assign("Enemigos generados: ");
	buf.append(to_string(enemigosCreados));
	texto = buf.c_str();
	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, (RY / 11) * 7, ALLEGRO_ALIGN_CENTER, texto);

	buf.assign("Enemigos eliminados: ");
	buf.append(to_string(enemigosEliminados));
	texto = buf.c_str();
	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, (RY / 11) * 8, ALLEGRO_ALIGN_CENTER, texto);

	al_draw_text(fuente, al_map_rgb(250, 250, 250), RX / 2, (RY / 11) * 10, ALLEGRO_ALIGN_CENTER, "Presione escape para continuar...");


	al_flip_display();

	while (loop) {
		al_wait_for_event(colaEventos, &eventos);

		if (eventos.type == ALLEGRO_EVENT_KEY_UP) {
		switch (eventos.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:	//ESCAPE para cerrar el programa
			loop = false;
			break;
		}
		}
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
	al_destroy_bitmap(jefe);
	al_destroy_bitmap(jefeInvisible);
	al_destroy_bitmap(explosion0);
	al_destroy_bitmap(explosion1);
	al_destroy_bitmap(explosion2);
	al_destroy_bitmap(explosionPequena);
	al_destroy_bitmap(balaJugador);
	al_destroy_bitmap(balaEnemigo);
	al_destroy_bitmap(vida);
	al_destroy_bitmap(fondo);
	al_destroy_font(fuente);
	al_destroy_sample(backgroundMusic);
	al_destroy_sample(disparoJugador);
	al_destroy_sample(disparoEnemigo);
	al_destroy_sample(hitJugador);
	al_destroy_sample(hitEnemigo);
	al_destroy_sample(jefeMusic);
	al_destroy_sample(explosion);
	al_destroy_sample(victory);
	al_destroy_sample(lose);
	al_destroy_sample(menuMusic);
	DestruirBalas(BalasJugador);
	DestruirBalas(BalasEnemigos);
	DestruirEnemigos(Enemigos);

	return puntuacion;
}
