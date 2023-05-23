#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>
#include"shared.h"

typedef enum{
	MENSAJE,
	INSTRUCCIONES_CONSOLA,
	PAQUETE,
	CONTEXTO_EJECUCION,
	CAMBIAR_ESTADO,
	MANEJAR_IO,
	MANEJAR_WAIT,
	MANEJAR_SIGNAL,
	MANEJAR_F_OPEN,
	MANEJAR_F_CLOSE,
	MANEJAR_F_SEEK,
	MANEJAR_F_READ,
	MANEJAR_F_WRITE,
	MANEJAR_F_TRUNCATE,
	MANEJAR_CREATE_SEGMENT,
	MANEJAR_DELETE_SEGMENT,
	MANEJAR_MOV_IN,
}op_code;

typedef struct{
	int size;
	void* stream;
} t_buffer;

typedef struct{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

//Mensajes
void enviar_mensaje(char* mensaje, int socket_cliente);
int recibir_operacion(int socket_cliente);
void* recibir_buffer(int* size, int socket_cliente);
void recibir_mensaje(t_log* logger, int socket_cliente);
void crear_buffer(t_paquete* paquete);

//Paquetes
t_list* recibir_paquete(int);
t_paquete* crear_paquete(op_code);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void agregar_a_paquete_con_header(t_paquete *paquete, void *valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket_cliente);
void eliminar_paquete(t_paquete* paquete);
void* serializar_paquete(t_paquete* paquete, int bytes);

// LA EMPAQUETASION O.o
void empaquetar_instrucciones(t_paquete* instrucciones_a_mandar, t_list* lista_de_instrucciones);
t_list* desempaquetar_instrucciones(t_list* paquete, int comienzo);
void empaquetar_tabla_segmentos(t_paquete* paquete, t_list* tabla_segmentos);
t_list* desempaquetar_tabla_segmentos(t_list* paquete, int comienzo);
void empaquetar_contexto_ejecucion(t_paquete* paquete, t_contexto_ejecucion* contexto);
t_contexto_ejecucion* desempaquetar_contexto_ejecucion(t_list* paquete);

//Sends
void send_instrucciones(int fd_modulo, t_list* lista_de_instrucciones);
void send_contexto_ejecucion(t_contexto_ejecucion* contexto, int fd_modulo);
void send_cambiar_estado(t_contexto_ejecucion* contexto, int fd_modulo);
void send_tiempo_io(int tiempo_io, int fd_modulo);
void send_recurso_wait(char* recurso, int fd_modulo);
void send_recurso_signal(char* recurso, int fd_modulo);
void send_nombre_f_open(char* nombre_archivo, int fd_modulo);
void send_nombre_f_close(char* nombre_archivo, int fd_modulo);
void send_nombre_f_seek(char* nombre_archivo, int fd_modulo);
void send_nombre_f_read(char* nombre_archivo, int dir_logica, int cantidad_bytes, int fd_modulo);
void send_nombre_f_write(char* nombre_archivo, int dir_logica, int cantidad_bytes, int fd_modulo);
void send_nombre_f_wait(char* nombre_archivo, int fd_modulo);
void send_nombre_f_truncate(char* nombre_archivo, int tamanio, int fd_modulo);
void send_create_segment(int id_segmento, int tamanio, int fd_modulo);
void send_delete_segment(int id_segmento, int fd_modulo);
void send_leer_valor(int dir_fisica, int fd_modulo);

//Recvs
t_list* recv_instrucciones(t_log* logger, int fd_modulo);
t_contexto_ejecucion* recv_contexto_ejecucion(int fd_modulo);
t_contexto_ejecucion* recv_cambiar_estado(int fd_modulo);
int recv_tiempo_io(int fd_modulo);
char* recv_recurso(int fd_modulo);
char* recv_valor(int fd_modulo);

//Traducción
int traducir_direccion(int dir_logica);

#endif /* PROTOCOLO_H_ */

