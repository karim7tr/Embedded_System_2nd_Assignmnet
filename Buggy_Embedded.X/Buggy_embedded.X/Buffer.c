#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Buffer.h"


void add_to_buffer(unsigned char value) {
    uartBuffer.data[uartBuffer.head] = value;
    uartBuffer.head++;
    if (uartBuffer.head >= BUFFER_SIZE)
        uartBuffer.head = 0;
}

int read_from_buffer(CircularBuffer uartBuffer) {
    int value;
    value = uartBuffer.data[uartBuffer.tail];
    uartBuffer.tail++;
    if (uartBuffer.tail >= BUFFER_SIZE)
        uartBuffer.tail = 0;
    return value;
}