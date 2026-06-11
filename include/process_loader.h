// process_loader.h
#ifndef PROCESS_LOADER_H
#define PROCESS_LOADER_H

#include "process.h"

// Carga procesos desde un archivo y devuelve el arreglo; count recibe la cantidad
Process* load_processes(const char* filename, int* count);

#endif
