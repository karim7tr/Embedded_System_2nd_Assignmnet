
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef BUFFER_H
#define	BUFFER_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define BUFFER_SIZE 128

typedef struct {
    char data[BUFFER_SIZE];
    int head; // Written index (data to write)
    int tail; // Reading index (data to read)
    int count; // Nombre d'octets dans le tampon
} CircularBuffer;

CircularBuffer uartBuffer;

void add_to_buffer(unsigned char value);
int read_from_buffer(CircularBuffer uartBuffer);

#endif	/* BUFFER_H */

