#include "../include/consola.h"


t_list* leer_instrucciones(char* path, t_log* logger){
	t_list* lista_de_instrucciones = list_create();
	FILE *pseudocodigo;
	char buffer[MAX_LINE_LENGTH];
	char *instruccion_token;
	char *parametro1;
	char *parametro2;
	char *parametro3;
	t_instruccion instruccion;

	pseudocodigo = fopen(path, "r");

	if (pseudocodigo == NULL) {
		log_error(logger, "No se pudo abrir el archivo.\n");
		exit(1);
	}

	while (fgets(buffer, MAX_LINE_LENGTH, pseudocodigo) != NULL) {
	        // Eliminar el carácter de salto de línea del final de la línea
	        buffer[strcspn(buffer, "\n")] = '\0';

	        // Obtener la instrucción y los parámetros de la línea
	        instruccion_token = strtok(buffer, " ");
	        parametro1 = strtok(NULL, " ");
	        parametro2 = strtok(NULL, " ");
	        parametro3 = strtok(NULL, " ");

	        instruccion.instruccion = instruccion_token;
	        instruccion.parametro1 = parametro1;
	        instruccion.parametro2 = parametro2;
	        instruccion.parametro3 = parametro3;

	        // SOLO PARA CHEQUEAR
	        log_info(logger, "Instruccion: %s ", instruccion_token);

	        if(parametro1 != NULL){
	        	log_info(logger, "Parametro 1: %s ", parametro1);
	        }

	        if(parametro2 != NULL){
	        	log_info(logger, "Parametro 2: %s ", parametro2);
	        }

	        if(parametro3 != NULL){
	        	log_info(logger, "Parametro 3: %s ", parametro3);
	        }

	        log_info(logger, "\n");

	        list_add(lista_de_instrucciones, &instruccion);
	    }

	    // Cerrar el archivo
	    fclose(pseudocodigo);

	return lista_de_instrucciones;
}


int main(int argc, char** argv) {

	t_log* logger = log_create("consola.log", "consola_main", true, LOG_LEVEL_INFO);
	t_config* config = config_create("consola.config"); //VER SI ESTE CONFIG TIENE QUE SEGUIR ESTANDO XQ CREO QUE ESTARIA HARCODEADO

	if(argc > 3){
		return EXIT_FAILURE;
	}

	t_config* path_config = config_create(argv[1]); //Tira warning aca xq no lo usamos nunca

	//FILE* pseudo_code = fopen(argv[2], "r");

	t_list* lista_de_insturcciones_pseudocodigo = leer_instrucciones(argv[2], logger);

	if(config == NULL){
		log_error(logger, "No se encontró el archivo :(");
		exit(1);
	}

	char* IP_KERNEL = config_get_string_value(config, "IP_KERNEL");
	// El enunciado dice q el puerto es numerico, pero la funcion getaddrinfo recibe char* y no puedo castear de int a char* :(
	char* PUERTO_KERNEL = config_get_string_value(config, "PUERTO_KERNEL");

	// Conexion Kernel
	int fd_kernel = crear_conexion(IP_KERNEL, PUERTO_KERNEL);
	enviar_mensaje("Hola, soy consola.", fd_kernel);

	terminar_programa(logger, config);
	liberar_conexion(fd_kernel);

	return 0;
}
