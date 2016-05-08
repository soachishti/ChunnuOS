#include <system.h>

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

int strcmp(char *s1, char* s2) {
    for (; *s1 == *s2; s1++, s2++) {
        if (*s1 == '\0')
            return 0;
    }
    return (*s1 < *s2) ? -1 : 1;
}

char* strcpy (char* s1, const char* s2) {
    char *s = s1;
    while((*s++ = *s2++) != 0);
    return s1;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}


void add_to_buffer(char value, char buffer[], int *write, int *read, int size) {
    if (*read == (*write + 1) % size) {
        return; // Buffer full
    }
    buffer[*write] = value;
    *write = (*write + 1) % size;
}

char get_from_buffer(char buffer[], int *write, int *read, int size) {
    char ch;
    if (*read == *write) {
        return -1;
    }
    ch = buffer[*read];
    *read = (*read + 1) % size;
    return ch;
}

void enable_int() {
    __asm__ __volatile__ ("sti");
}

void disable_int() {
    __asm__ __volatile__ ("cli");
}