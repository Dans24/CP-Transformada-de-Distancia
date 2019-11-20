#include <stdio.h>
#include <stdlib.h>

int main() {
	const char clean[30], command[100], img1[100], img2[100], img3[100], img4[100];
	sprintf(clean,"rm -f exec");
	system(clean);
	for(int i = 1 ; i <= 40 ; i++) {
		sprintf(command,"export OMP_NUM_THREADS=%d",i);
		system(command);
		sprintf(img1,"./exec imgTeste/gun.pbm imgResult/gun%d.pbm times/timegun.txt",i);
		system(img1);
		sprintf(img2,"./exec imgTeste/flowers.pbm imgResult/flowers%d.pbm times/timeflowers.txt",i);
		system(img2);
		sprintf(img3,"./exec imgTeste/digital.pbm imgResult/digital%d.pbm times/timedigital.txt",i);
		system(img3);
		sprintf(img4,"./exec imgTeste/exemplo.pbm imgResult/exemplo%d.pbm times/timeexemplo.txt",i);
		system(img4);
	}
	free(clean);
	free(command);
	free(img1);
	free(img2);
	free(img3);
	free(img4);
	return 1;
}