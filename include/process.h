// process.h
#ifndef PROCESS_H
#define PROCESS_H

// Estados posibles del proceso
typedef enum {
    READY,     // Listo para ejecutarse
    RUNNING,   // En ejecución
    BLOCKED,   // Esperando un evento
    FINISHED   // Finalizado
} ProcessState;

// Estructura de un proceso
typedef struct {
    int pid;                // Identificador único
    int burst_time;         // Tiempo total de ejecución
    int remaining_time;     // Tiempo restante para terminar
    int priority;           // Nivel de prioridad
    int memory_required;    // Memoria que necesita
    ProcessState state;     // Estado actual
} Process;

#endif
