#include <system.h>

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;
char memtest[4096];
int cpu_ghz = 0;
uint64_t cpu_start = 0;
uint64_t cpu_end = 0;

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;
    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 18 == 0)
    {
        //puts("One second has passed\n");
    }
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int seconds)
{
    unsigned long eticks;
    eticks = timer_ticks + (seconds*18);
    while(timer_ticks < eticks) {
        putch(0);
    }
}

void timer_memspeed()
{
    unsigned long eticks;
    eticks = timer_ticks + 18;
    int bytes = 0;
    while(timer_ticks < eticks) {
        putch(0);
        memset(memtest, 255, 4096);
        bytes++;
    }
    bytes = bytes*4096;
    print_int(bytes);
    puts(" Bytes/s\n");
}


void timer_cpuspeed()
{
    unsigned long eticks;
    eticks = timer_ticks + 18;
    register unsigned int iter = 0;
    while(timer_ticks < eticks) {
        putch(0);
        iter++;
    }
    float resGHz = (iter*3.0) / 1000000.0;
    print_float(resGHz);
    puts(" GHz\n");
}


/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
