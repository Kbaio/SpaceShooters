//Esta funcion se utiliza para verificar la poscicion del mouse
bool mouse_Range(int X, int Y, int varX, float varY1, float varY2, int mousex, int mousey) {
	if ((mousex >= X / 2 - varX && mousex <= X / 2 + varX) && (mousey >= (Y * (varY1 / 768.0)) && mousey <= (Y * (varY2 / 768.0)))) {
		return true;
	}
	return false;
}

void get_Mouse(ALLEGRO_EVENT& eventos, int& mousex, int& mousey) {
	mousex = eventos.mouse.x;
	mousey = eventos.mouse.y;
}

void mostrarInstrucciones(ALLEGRO_TIMER* timer1, ALLEGRO_EVENT_QUEUE* cola_eventos, ALLEGRO_BITMAP* fondo, ALLEGRO_FONT* titulo, ALLEGRO_FONT* fuente, int X, int Y, ALLEGRO_SAMPLE* seleccion) {
	ALLEGRO_EVENT eventos;
	ALLEGRO_BITMAP* instrucciones = al_load_bitmap("Imagenes/Instrucciones.png");
	int movF = 0;
	int mousex = 0;
	int mousey = 0;
	bool estado = true;
	while (estado) {
		al_wait_for_event(cola_eventos, &eventos);
		if (eventos.type == ALLEGRO_EVENT_TIMER) {
			if (eventos.timer.source == timer1) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_scaled_bitmap(fondo, 0, movF, X, Y, 0, 0, X, Y, NULL);
				if (movF == 0) {
					movF = 1080;
				}
				movF--;
				al_draw_text(titulo, al_map_rgb(250, 250, 15), X / 2, (Y * (150.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SPACE SHOOTERS");
				al_draw_text(fuente, al_map_rgb(250, 15, 250), X / 2, (Y * (250.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "INSTRUCCIONES");
				al_draw_bitmap(instrucciones, X / 2 - 200, (Y * (350 / 768.0)), NULL);
				al_draw_text(fuente, al_map_rgb(250, 250, 250), X / 2, (Y * (550.0 / 768.8)), ALLEGRO_ALIGN_CENTER, "ATRAS");
			}
		}
		if (eventos.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			get_Mouse(eventos, mousex, mousey);
		}
		if (mouse_Range(X, Y, 100, 540.0, 580.0, mousex, mousey)) {
			al_draw_text(fuente, al_map_rgb(250, 250, 15), X / 2, (Y * (550.0 / 768.8)), ALLEGRO_ALIGN_CENTER, "ATRAS");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				al_play_sample(seleccion, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				estado = false;
			}
		}
		al_flip_display();
	}
}

void CargarArchivo(int x, int y, ALLEGRO_FONT* fuente, int inicio)//Se carga el archivo en memoria secundaria a pantalla con el puntaje y nombre escritos en el display
{
	char nombre[40];
	char puntaje[10];
	int i = 0;
	int e = 0;
	FILE* archivo;
	archivo = fopen("puntuacion.txt", "r");
	if (archivo != NULL) {
		while (!feof(archivo)) {
			fscanf(archivo, "Nombre:%s\n", nombre);
			fscanf(archivo, "Puntaje: %s\n", puntaje);
			if (inicio <= i && i < inicio + 5) {

				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (300.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_RIGHT, "Nombre: ");
				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (300.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_LEFT, nombre);
				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (320.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_RIGHT, "Puntaje: ");
				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (320.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_LEFT, puntaje);
				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (340.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_LEFT, " ");
				e++;
			}
			i++;
		}
		fclose(archivo);
	}
}

void mostrarEstadisticas(ALLEGRO_EVENT_QUEUE* cola_eventos, ALLEGRO_FONT* titulo, ALLEGRO_FONT* fuente, ALLEGRO_FONT* fuente2, ALLEGRO_BITMAP* fondo,ALLEGRO_TIMER* timer, int X, int Y) {
	bool repetir = true;
	int inicio = 0;
	int movF = 0;
	while (repetir) {
		ALLEGRO_EVENT eventos;
		al_wait_for_event(cola_eventos, &eventos);
		if (eventos.type == ALLEGRO_EVENT_TIMER) {
			if (eventos.timer.source == timer) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_scaled_bitmap(fondo, 0, movF, X, Y, 0, 0, X, Y, NULL);
				if (movF == 0) {
					movF = 1080;
				}
				movF--;
				al_draw_text(titulo, al_map_rgb(0, 250, 15), X / 2, (Y * (150.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SPACE INVADERS");
				al_draw_text(fuente, al_map_rgb(250, 127, 0), X / 2, (Y * (250.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "RESULTADOS");
				CargarArchivo(X, Y, fuente2, inicio);
				al_draw_text(fuente, al_map_rgb(250, 250, 250), X / 2, (Y * (650.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "Presiona escape para salir");
			}
		}
		if (eventos.keyboard.keycode == ALLEGRO_KEY_UP) {
			if (inicio >= 1) {
				inicio = inicio - 1;
			}
		}
		else if (eventos.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			inicio = inicio + 1;
		}
		else if (eventos.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			repetir = false;
		}
		al_flip_display();
	}

}