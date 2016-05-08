#include <system.h>

int user_count = 0;
extern char user[16];
extern char pass[16];
extern int curr_user;

void security_init() {
	strcpy(users[0].username, "root\0");
	strcpy(users[0].password, "root\0");
	user_count++;
}

void security_add(char* s1, char* s2) {
	strcpy(users[user_count].username, s1);
	strcpy(users[user_count].password, s2);	
	user_count++;
	puts("User added.\n\n");
}

int security_login() {
	puts("User: ");
	getline(user, 16);
	puts("Pass: ");
	getpass(pass, 16);
	int i;
	for (i = 0; i < 16; i++) {
		if (strcmp(users[i].username, user) == 0 && strcmp(users[i].password, pass) == 0) {
			curr_user = i;
			return 1;
		}
	}
	puts("Authentication failed.\n\n");
	return 0;
}