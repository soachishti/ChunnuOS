#ifndef __SYSTEM_H
#define __SYSTEM_H

#define __NOINLINE  __attribute__((noinline))
#define __REGPARM   __attribute__ ((regparm(3)))
#define __NORETURN  __attribute__((noreturn))
#define true  0
#define false 1
#define newline putch('\n')
#define infinite while(1)

typedef unsigned long long uint64_t;
typedef int size_t;

typedef signed char 			int8_t;
typedef unsigned char 			uint8_t;
typedef signed int 				int16_t;
typedef unsigned int 			uint16_t;
typedef signed long int 		int32_t;
typedef unsigned long int 		uint32_t;
typedef signed long long int 	int64_t;
typedef unsigned long long int 	uint64_t;

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

struct User {
    char username[16];
    char password[16];
};

struct User users[16];

int curr_user;
char user[16];
char pass[16];

/* MAIN.C */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern int strcmp(char*, char*);
extern char* strcpy(char *s1, const char *s2);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* CONSOLE.C */
extern void init_video(void);
extern void puts(char *text);
extern void putch(char c);
extern void print_int(int num);
extern void print_float(float num);
extern void cls();
extern void gotoxy(int, int);
extern char getch();
extern void get(char*, int);
extern void getline(char *, int);
extern void getpass(char *, int);
void settextcolor(unsigned char forecolor, unsigned char backcolor);

/* GDT.C */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void timer_wait(int ticks);
extern void timer_install();
extern void timer_cpuspeed();
extern void timer_memspeed();

/* KEYBOARD.C */
extern void keyboard_install();
extern char keyboard_read();

/* BUFFER (GENERAL.C) */
extern void add_to_buffer(char value, char buffer[], int *write, int *read, int size);
extern char get_from_buffer(char buffer[], int *write, int *read, int size);
extern void enable_int();
extern void disable_int();

extern void security_init();
extern void security_add(char* s1, char* s2);
extern int security_login();

extern void print_time();
extern void print_date();
extern void print_datetime();

extern float math_rpn();

static inline uint64_t rdtsc()
{
    uint64_t ret;
    asm volatile ( "rdtsc" : "=A"(ret) );
    return ret;
}

#endif
