#ifndef KERNEL_H_
#define KERNEL_H_

#include <protocolo.h>
#include <sockets.h>
#include <shared.h>
#include <commons/log.h>
#include <commons/config.h>
#include <pthread.h>
#include <semaphore.h>

#endif /* KERNEL_H_ */

//sss
typedef enum
{
	FIFO,
	HRRN,
} t_algoritmo;
//Memoria Robado tp Nahu
typedef struct
{
	int indice_tabla_de_pagina;
	int numero_pagina;
} t_pagina;

typedef struct
{
	t_list *instrucciones;
	//t_list *segmentos;
} t_proceso;


// INSTRUCCIONES QUE TIENEN DOS PARAMETROS
typedef struct
{
	op_code operacion;		//ANTES ERA DE TIPO cod_instruccion
	char *parametro1;
	char *parametro2;
} instruccion;


typedef struct
{
	int id;
	int direccion_fisica;
	int tamanio_segmentos;

}t_segmento;


typedef struct
{
	//int pid;
	//int program_counter;
	//estado_proceso estado;
	//int socket_consola;
	bool interrupcion;
	//t_list *instrucciones;
	// punteros de las listas en dudaa
	//t_list *tabla_de_segmentos;
	t_registros registros;
	t_contexto_ejecucion contexto_de_ejecucion;
	t_segmento seg_fault;						//Agregado para la MMU, probablemente vaya en el contexto
	//bool con_desalojo;

} t_pcb;

t_log* logger;
t_log* logger_obligatorio;
t_config* config;
int server_socket;
int fd_cpu;
int fd_memoria;
int fd_filesystem;
char* server_name;

// Variables del config (Las pongo aca asi no estamos revoleando el cfg para todos lados)
char* IP;
char* PUERTO;
char* IP_FILESYSTEM;
char* PUERTO_FILESYSTEM;
char* IP_CPU;
char* PUERTO_CPU;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
t_algoritmo ALGORITMO_PLANIFICACION;
int ESTIMACION_INICIAL;
float HRRN_ALFA;
int GRADO_MAX_MULTIPROGRAMACION;
char** RECURSOS;
int* INSTANCIAS_RECURSOS;

// Variables PCBs
t_list* lista_pcbs;
int generador_pid;
t_queue* cola_ready;
t_queue* cola_exit;
t_queue* cola_listos_para_ready;
t_queue* cola_exec;


// Semaforos y pthread
pthread_mutex_t mutex_generador_pid;
pthread_mutex_t mutex_cola_ready;
pthread_mutex_t mutex_cola_listos_para_ready;
pthread_mutex_t mutex_cola_exit;
pthread_mutex_t mutex_cola_exec;
sem_t sem_multiprog;
sem_t sem_listos_ready;
sem_t sem_ready;
sem_t sem_exec;
sem_t sem_exit;

// INIT
void leer_config();
void asignar_algoritmo(char* algoritmo);
bool generar_conexiones();
int inicializar_servidor();
void inicializar_variables();

// COMUNICACION
static void procesar_conexion(void *void_args);
void iterator(char* value);
int server_escuchar(int server_socket);

// PCBS
t_pcb *pcb_create(t_proceso *proceso, int pid);
void cambiar_estado(t_pcb *pcb, estado_proceso nuevo_estado);
void armar_pcb(t_list *instrucciones);

// PLANIFICACION
void planificar();
void planificar_largo_plazo();
void exit_pcb();
void ready_pcb();
t_pcb *safe_pcb_pop(t_queue *queue, pthread_mutex_t *mutex);
void setear_pcb_ready(t_pcb* pcb);
void log_cola_ready();
t_list *pcb_queue_to_pid_list(t_queue *queue);
char* algoritmo_to_string(t_algoritmo algoritmo);
void planificar_corto_plazo();
void planificar_FIFO();
void run_pcb(t_pcb* pcb);
void planificar_HRRN();

//instruccion     *obtener_ultima_instruccion(t_pcb *pcb)
//{
//	int ultima_instruccion_idx = pcb->program_counter - 1;
//	instruccion *ultima_instruccion = list_get(pcb->instrucciones, ultima_instruccion_idx);
//return ultima_instruccion;
//}

