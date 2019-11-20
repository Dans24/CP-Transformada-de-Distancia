#include <stdio.h>
#include <stdlib.h>

int main() {
	char command[100], img1[100], /*img2[100],*/ img3[100], img4[100];
	for(int i = 2 ; i <= 40 ; i++) {
		sprintf(command,"export OMP_NUM_THREADS=%d",i);
		system(command);
		sprintf(img1,"./exec imgTeste/gun.pbm imgResult/gun%d.pbm times/timegun2.txt",i);
		system(img1);
		printf("Gun number %d finished\n",i);
		//sprintf(img2,"./exec imgTeste/flowers.pbm imgResult/flowers%d.pbm times/timeflowers2.txt",i);
		//system(img2);
		sprintf(img3,"./exec imgTeste/digital.pbm imgResult/digital%d.pbm times/timedigital2.txt",i);
		system(img3);
		printf("Digital number %d finished\n",i);
		sprintf(img4,"./exec imgTeste/exemplo.pbm imgResult/exemplo%d.pbm times/timeexemplo2.txt",i);
		system(img4);
		printf("Exemplo number %d finished\n",i);
	}
	return 1;
}