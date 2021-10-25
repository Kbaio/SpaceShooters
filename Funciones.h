
//Esta funcion se utiliza para verificar la poscicion del mouse
bool mouse_Range(int X, int Y, int varX, float varY1, float varY2, int mousex, int mousey) {
	if ((mousex >= X / 2 - varX && mousex <= X / 2 + varX) && (mousey >= (Y * (varY1 / 768.0)) && mousey <= (Y * (varY2 / 768.0)))) {
		return true;
	}
	return false;
}

void get_Mouse(ALLEGRO_EVENT &eventos,int &mousex,int &mousey) {
	mousex = eventos.mouse.x;
	mousey = eventos.mouse.y;
}

void guardarArchivo(char* puntaje, char* nombre)
{
	FILE* archivo;
	archivo = fopen("puntuacion.txt", "a");

	if (NULL == archivo) {
		fprintf(stderr, "No se pudo crear archivo %s.\n", "resultados.txt");
		exit(-1);
	}
	else {
		fprintf(archivo, "Nombre:%s\n", nombre);
		fprintf(archivo, "Puntaje: %s\n", puntaje);
		fprintf(archivo, "\n\n");
	}
	fclose(archivo);
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
			if (inicio <= i && i < inicio + 4) {
				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (300.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_RIGHT, "Nombre: ");
				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (300.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_LEFT, nombre);
				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (330.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_RIGHT, "Puntaje: ");
				al_draw_text(fuente, al_map_rgb(250, 250, 250), x / 2, (y * (330.0 / 768.0)) + 75 * e, ALLEGRO_ALIGN_LEFT, puntaje);
				e++;
			}
			i++;
		}
		fclose(archivo);
	}
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


void definirTeclas(ALLEGRO_EVENT_QUEUE* cola_eventos, ALLEGRO_EVENT &eventos, bool &repetir, char nombre[30],int &pos_Caracter ) {
	bool test = false;
	if (eventos.keyboard.keycode == ALLEGRO_KEY_LEFT || eventos.keyboard.keycode == ALLEGRO_KEY_RIGHT 
		|| eventos.keyboard.keycode == ALLEGRO_KEY_DOWN || eventos.keyboard.keycode == ALLEGRO_KEY_UP
		|| eventos.keyboard.keycode == ALLEGRO_KEY_DELETE || eventos.keyboard.keycode == ALLEGRO_KEY_HOME
		||eventos.keyboard.keycode == ALLEGRO_KEY_TAB || eventos.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
	}
	else if (eventos.keyboard.keycode == ALLEGRO_KEY_ENTER) {
		repetir = false;
	}
	else if (eventos.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
		if (pos_Caracter != 0) {
			nombre[pos_Caracter] = NULL;
			pos_Caracter--;
		}
	}
	else if (pos_Caracter != 28) {
		if (eventos.keyboard.keycode == ALLEGRO_KEY_SPACE) {
			nombre[pos_Caracter] = char(95);
			pos_Caracter++;
		}
		else {
			if (eventos.keyboard.unichar != ALLEGRO_KEY_BACKSPACE) {
				nombre[pos_Caracter] = eventos.keyboard.unichar;
				pos_Caracter++;
			}
		}
	}
}

void gameOver(ALLEGRO_EVENT_QUEUE* cola_eventos, ALLEGRO_FONT* titulo, ALLEGRO_FONT* fuente, int X, int Y) {
	//char buffer[20];
	char puntos[40] = "Puntuacion: ";
	//strcat_s(puntos, 20, buffer);
	char nombre[30];
	nombre[0] = char(95);
	char letra;
	int pos_Caracter = 0;
	int contador = 0;
	int contador2 = 0;
	bool repetir = true;
	while (repetir) {
		ALLEGRO_EVENT eventos;
		al_wait_for_event(cola_eventos, &eventos);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		if (eventos.type == ALLEGRO_EVENT_KEY_CHAR) {
			definirTeclas(cola_eventos, eventos, repetir, nombre, pos_Caracter);
		}
		nombre[pos_Caracter] = '<';
		nombre[pos_Caracter + 1] = NULL;
		al_draw_text(titulo, al_map_rgb(255, 0, 0), X / 2, Y / 2 - 300, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
		al_draw_text(fuente, al_map_rgb(255, 255, 20), X / 2, Y / 2 - 150, ALLEGRO_ALIGN_CENTRE, puntos);
		al_draw_text(fuente, al_map_rgb(255, 255, 255), X / 2, Y / 2, ALLEGRO_ALIGN_CENTRE, nombre);
		al_draw_text(fuente, al_map_rgb(255, 255, 255), X / 2, Y / 2 + 200, ALLEGRO_ALIGN_CENTRE, "Presione Enter para finalizar");
		al_draw_text(fuente, al_map_rgb(124, 255, 0), X / 2, Y / 2 - 50, ALLEGRO_ALIGN_CENTRE, "Ingrese su nombre");
		al_flip_display();
	}
	//Se el nombre no es vacio se borra lo que no haya escrito el usuario (como el caracter para ubicar)
	if (pos_Caracter != 0) {
		nombre[pos_Caracter] = NULL;
	}
	else {//Si el usuario no escribe el nombre so coloca un signo de interrogacion
		nombre[0] = 'B';
		nombre[1] = 'O';
		nombre[2] = 'T';
	}
	//guardarArchivo(puntos, nombre);
}