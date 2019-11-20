#include <stdio.h>
#include <stdlib.h>

int main() {
	system("./exec imgTeste/gun.pbm imgResult/gun.pbm times/timegun.txt");
	system("./exec imgTeste/digital.pbm imgResult/digital.pbm times/timedigital.txt");
	system("./exec imgTeste/exemplo.pbm imgResult/exemplo.pbm times/timeexemplo.txt");
	printf("Terminado\n");
	return 0;
}