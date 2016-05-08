// shutdown
// memory speed
// register speed
// hlt and wake by timer


#include <system.h>

extern int timer_ticks;

char line[80];
char mnemonic[80];

char test(char x) {
    return x;
}

int kmain(void)
{
    print_int(sizeof (long long int));
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_video();
    security_init(); 
    timer_install();
    keyboard_install();
    
    __asm__ __volatile__ ("sti");

    //int a = 10;
    //int b = 0;
    //putch(a/b);

    settextcolor(10, 0);
    puts("Amuntu [Version 1.0.112]\n");
    settextcolor(10, 0);
    puts("(c) O.B. Corporation. All rights reserved.\n\n");
    settextcolor(8, 0);
    // Loop until any user logged in
    while(security_login() == 0);
    newline;

    infinite {
        settextcolor(14, 0);
        puts(users[curr_user].username);
        putch('@');
        puts("ProjectOS:~$ ");
        
        settextcolor(15, 0);
        get (mnemonic, 80);
        settextcolor(8, 0);

        if (strcmp(mnemonic, "adduser") == 0) {
            get(user, 16);
            get(pass, 16);
            security_add(user, pass);
        }
        else if (strcmp(mnemonic, "su") == 0) {
            security_login();
            newline;
        }
        else if (strcmp(mnemonic, "cls") == 0 || strcmp(mnemonic, "clear") == 0) {
            cls();
        }
        else if (strcmp(mnemonic, "echo") == 0) {
            getline(line, 80);
            puts(line);
            newline; newline;
        }
        else if (strcmp(mnemonic, "exit") == 0) {
            if (curr_user == 0) {
                break;
            } else {
                settextcolor(4, 0);
                puts("Permission denied.\n\n");
                settextcolor(8, 0);
            }

        }
        else if (strcmp(mnemonic, "cpuspeed") == 0) {
            puts("CPU Speed: ");
            timer_cpuspeed();
            newline;
        }
        else if (strcmp(mnemonic, "memspeed") == 0) {
            puts("Memory Speed: ");
            timer_memspeed();
            newline;
        }
        else if (strcmp(mnemonic, "hlt") == 0) {
            if (curr_user == 0) {
                __asm__ __volatile__ ("cli");
                __asm__ __volatile__ ("hlt");
            } else {
                settextcolor(4, 0);
                puts("Permission denied.\n\n");
                settextcolor(8, 0);    
            }
        }
        else if (strcmp(mnemonic, "shutdown") == 0) {
            if (curr_user == 0) {
                __asm__ __volatile__ ("cli");
                outportb(0x64, 0xFE);
                __asm__ __volatile__ (
                    "int $15"
                );
                //__asm__ __volatile__ ("int3");
            } else {
                settextcolor(4, 0);
                puts("Permission denied.\n\n");
                settextcolor(8, 0);
            }
        }
        else if (strcmp(mnemonic, "sleep") == 0) {
            get (mnemonic, 80);
            int num = mnemonic[0] - 48;
            int i;
            for(i = 1;i < strlen(mnemonic); i++){
                int t = mnemonic[i]-48;
                num = num*10 + t;
            }
            timer_wait(num);
        }
        else if (strcmp(mnemonic, "about") == 0) {
            settextcolor(6, 0); puts("\nOperating System Project\n\n");
            settextcolor(5, 0); puts("NAME: ");
            settextcolor(3, 0); puts("Amuntu v1.0.112\n\n");
            settextcolor(5, 0); puts("SUBMITTED TO:\n");
            settextcolor(3, 0); puts("Sir Amin\n\n");
            settextcolor(5, 0); puts("DEVELOPED BY:\n"); 
            settextcolor(3, 0); puts("Syed Owais Ali Chishti (p146011)\nBilal Zaib (p146099)\n\n"); 
            settextcolor(5, 0); puts("DATE:\n"); 
            settextcolor(3, 0); puts("7-May-2016\n\n");       
        }
        else if (strcmp(mnemonic, "help") == 0) {
            puts("adduser\nsu\necho\nsleep\ncpuspeed\nmemspeed\nabout\nhelp\nmath\ndate\ntime\ndatetime\nshutdown\nexit\n\n");       
        }
        else if (strcmp(mnemonic, "datetime") == 0) {
            print_datetime();
            newline; newline;
        }
        else if (strcmp(mnemonic, "date") == 0) {
            print_date();
            newline; newline;
        }
        else if (strcmp(mnemonic, "time") == 0) {
            print_time(); 
            newline; newline;
        }
        else if (strcmp(mnemonic, "math") == 0) {
            getline(line, 80);
            if (line[0] == 'h') {
                puts("+ -> a\n- -> s\n* -> t\n/ -> d\n^ -> r\n");
                puts("Example: 10 20 a 29 s 5 t");
            }
            else {
                float tmp = math_rpn(line);
                print_float(tmp);
            }
            newline; newline;
        }
        else {
            settextcolor(4, 0);
            puts(mnemonic);
            putch(':');
            puts(" Command not found. Try help\n\n");
            settextcolor(8, 0);
        }
    }
    puts("\n============= END OF PROJECT OS =============\n");
    getline(line, 80);
    outportb(0x64, 0xFE);
    for (;;);
    return 0;
}
