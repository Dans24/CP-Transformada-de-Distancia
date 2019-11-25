#include <stdio.h>
#include <stdlib.h>

int main() {
	char command[100];
	int i = 2;
	for( ; i < 40 ; i*=2) {
		sprintf(command,"export OMP_NUM_THREADS=%d",i);
		system(command);
		system("./exec ../imgTeste/gun.pbm ../imgResult/gun2.pbm ../times/timegun2.txt");
		system("./exec ../imgTeste/digital.pbm ../imgResult/digital2.pbm ../times/timedigital2.txt");
		system("./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo2.pbm ../times/timeexemplo2.txt");
		printf("Iteração %d\n",i);
	}
	//20 threads
	i=20;
	sprintf(command,"export OMP_NUM_THREADS=%d",i);
	system(command);
	ssystem("./exec ../imgTeste/gun.pbm ../imgResult/gun2.pbm ../times/timegun2.txt");
	system("./exec ../imgTeste/digital.pbm ../imgResult/digital2.pbm ../times/timedigital2.txt");
	system("./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo2.pbm ../times/timeexemplo2.txt");
	printf("Iteração %d\n",i);
	//40 threads
	i=40;
	sprintf(command,"export OMP_NUM_THREADS=%d",i);
	system(command);
	ssystem("./exec ../imgTeste/gun.pbm ../imgResult/gun2.pbm ../times/timegun2.txt");
	system("./exec ../imgTeste/digital.pbm ../imgResult/digital2.pbm ../times/timedigital2.txt");
	system("./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo2.pbm ../times/timeexemplo2.txt");
	printf("Iteração %d\n",i);
	return 0;
}