#include "Juego.h"
#include "Funciones.h";
using namespace std;
#define FPS 60.0

//Programa Principal
int main() {
	//Verifica si hubo algun error iniciando allegro
	if (!al_init()) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede inicializar Allegro", NULL, NULL);
		return -1;
	}
	//Elementos de allegro que se utilizaran 
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(7);
	al_install_mouse();

	//Se obtienen las medidas del monitor
	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	const int EX = monitor.x2 - monitor.x1;
	const int EY = monitor.y2 - monitor.y1;

	//Se define que el programa este en pantalla completa
	al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	ALLEGRO_DISPLAY* pantalla = al_create_display(EX, EY);
	al_set_window_title(pantalla, "Space Shooters");

	//Se verifica que la pantalla se pueda abrir bien
	if (!pantalla)
	{
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede crear la pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}

	//Timers y Punteros de allegro
	ALLEGRO_TIMER* primerTimer = al_create_timer(1.0 / FPS);
	
	//Cola
	ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();
	
	//Fuentes
	ALLEGRO_FONT* titulo = al_load_font("Fuente/ARCADE_I.ttf",80,NULL);
	ALLEGRO_FONT* fuente = al_load_font("Fuente/ARCADE_N.ttf", 40, NULL);
	ALLEGRO_FONT* fuente2 = al_load_font("Fuente/ARCADE_N.ttf", 20, NULL);

	//Bitmaps
	ALLEGRO_BITMAP* fondo = al_load_bitmap("Imagenes/HUD/Fondo.png");

	//Sonidos
	ALLEGRO_SAMPLE* SeleccionEffecto = al_load_sample("Sonidos/MENUMOVE.wav");
	ALLEGRO_SAMPLE* musicaFondo = al_load_sample("Sonidos/MENUFONDO.wav");

	//Se registran los eventos en la cola de eventos
	al_register_event_source(cola_eventos, al_get_timer_event_source(primerTimer));
	al_register_event_source(cola_eventos, al_get_display_event_source(pantalla));
	al_register_event_source(cola_eventos, al_get_keyboard_event_source());
	al_register_event_source(cola_eventos, al_get_mouse_event_source());

	//Variables a utilizar
	bool estado = true;
	int mousex = 0;
	int mousey = 0;
	int movF = 0;
	int X = al_get_display_width(pantalla);
	int Y = al_get_display_height(pantalla);
	int puntuacion = 0;

	//Se inician los timers
	al_start_timer(primerTimer);
	al_play_sample(musicaFondo,0.05,0,1,ALLEGRO_PLAYMODE_LOOP,NULL);
	al_reserve_samples(2);

	while (estado) {
		ALLEGRO_EVENT eventos;
		al_wait_for_event(cola_eventos, &eventos);
		if (eventos.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			get_Mouse(eventos, mousex, mousey);
		}
		if (eventos.type == ALLEGRO_EVENT_TIMER)
		{
			if (eventos.timer.source == primerTimer) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_scaled_bitmap(fondo, 0, movF, X, Y, 0, 0, X, Y, NULL);
				if (movF == 0) {
					movF = 1080;
				}
				movF--;
				al_draw_text(titulo, al_map_rgb(250, 15, 15), X / 2, (Y * (150.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SPACE SHOOTERS");
				al_draw_text(fuente, al_map_rgb(250, 250, 250), X / 2, (Y * (250.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "JUGAR");
				al_draw_text(fuente, al_map_rgb(250, 250, 250), X / 2, (Y * (350.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "RESULTADOS"); //410
				al_draw_text(fuente, al_map_rgb(250, 250, 250), X / 2, (Y * (450.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "INSTRUCCIONES"); //480
				al_draw_text(fuente, al_map_rgb(250, 250, 250), X / 2, (Y * (550.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SALIR"); //550
			}
		}

		//Si se presiona Jugar
		if(mouse_Range(X,Y,100,240.0,280.0,mousex,mousey)) {
			al_draw_text(fuente, al_map_rgb(250, 250, 20), X / 2, (Y * (250.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "JUGAR");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				al_play_sample(SeleccionEffecto, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				if (eventos.mouse.button & 1) {
					al_destroy_sample(musicaFondo);
					al_destroy_display(pantalla);
					juego(titulo);
					main();
					
				}
			}
		}

		//Si se presiona Resultados
		if (mouse_Range(X, Y, 200, 340.0, 380.0, mousex, mousey)){
			al_draw_text(fuente, al_map_rgb(250, 250, 20), X / 2, (Y * (350.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "RESULTADOS");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				al_play_sample(SeleccionEffecto, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				if (eventos.mouse.button & 1) {
					mostrarEstadisticas(cola_eventos, titulo, fuente, fuente2,fondo, primerTimer, X, Y);
				}
			}
		}

		//Si se presiona Instrucciones
		if (mouse_Range(X, Y, 250, 440.0, 480.0, mousex, mousey)){
			al_draw_text(fuente, al_map_rgb(250, 250, 20), X / 2, (Y * (450.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "INSTRUCCIONES");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				al_play_sample(SeleccionEffecto, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				if (eventos.mouse.button & 1) {
					mostrarInstrucciones(primerTimer,cola_eventos, fondo,titulo,fuente,X,Y,SeleccionEffecto);
				}
			}
		}

		//Si se presiona Salir
		if (mouse_Range(X, Y, 100, 540.0, 580.0, mousex, mousey)){
			al_draw_text(fuente, al_map_rgb(250, 250, 20), X / 2, (Y * (550.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SALIR");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				al_play_sample(SeleccionEffecto, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				if (eventos.mouse.button & 1) {
					estado = false;
				}
			}
		}

		//Si se presiona la tecla escape se sale del juego
		if (eventos.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (eventos.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				estado = false;
			}
		}
		al_flip_display();
	}
	al_destroy_timer(primerTimer);
	al_destroy_display(pantalla);
	al_destroy_bitmap(fondo);
	al_destroy_font(titulo);
	al_destroy_event_queue(cola_eventos);
	al_destroy_font(fuente);
	al_destroy_sample(SeleccionEffecto);
	al_destroy_sample(musicaFondo);
}