#include <stdio.h>
#include <stdlib.h>

int main() {
	char img[150];
	int i = 2;
	for( ; i < 40 ; i*=2) {
		sprintf(img,"./exec ../imgTeste/gun.pbm ../imgResult/gun%do.pbm ../times/timegun%do.txt %d",i,i,i);
		system(img);
		sprintf(img,"./exec ../imgTeste/digital.pbm ../imgResult/digital%do.pbm ../times/timedigital%do.txt %d",i,i,i);
		system(img);
		sprintf(img,"./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo%do.pbm ../times/timeexemplo%do.txt %d",i,i,i);
		system(img);
		printf("Iteração %d\n",i);
	}
	//20 threads
	i=20;
	sprintf(img,"./exec ../imgTeste/gun.pbm ../imgResult/gun%do.pbm ../times/timegun%do.txt %d",i,i,i);
	system(img);
	sprintf(img,"./exec ../imgTeste/digital.pbm ../imgResult/digital%do.pbm ../times/timedigital%do.txt %d",i,i,i);
	system(img);
	sprintf(img,"./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo%do.pbm ../times/timeexemplo%do.txt %d",i,i,i);
	system(img);
	printf("Iteração %d\n",i);
	//40 threads
	i=40;
	sprintf(img,"./exec ../imgTeste/gun.pbm ../imgResult/gun%do.pbm ../times/timegun%do.txt %d",i,i,i);
	system(img);
	sprintf(img,"./exec ../imgTeste/digital.pbm ../imgResult/digital%do.pbm ../times/timedigital%do.txt %d",i,i,i);
	system(img);
	sprintf(img,"./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo%do.pbm ../times/timeexemplo%do.txt %d",i,i,i);
	system(img);
	printf("Iteração %d\n",i);
	return 0;
}
