#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "screen.h"
#include "sound.h"

int main(int argc, char *argv[]){
	WAVEHEADER myheader;
	FILE *fp; //file header

	short int samples[FS]; //1 sec of samples
	int ret;

	/*if(argc == 1){
		fp = fopen("groovy.wav","rb");
	}
	else if(argc == 2){
		fp = fopen("groovy.wav","rb");
	}
	else{
		printf("Useage: exampleApp [wavefile_name]\n");
	}*/

	for(;;){
		ret = system("arecord -q -r16000 -f S16_LE -c1 -d1 test.wav", NULL); //exe arecord command
		if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT || WTERMSIG(ret)==SIGQUIT)) break;

		fp=fopen("test.wav","rb");

		if(fp!=NULL){
			clearScreen(); //clears the screen
			fread(&myheader, sizeof(myheader), 1, fp);
			fread(&samples, sizeof(short int)*FS, 1, fp);
			displayWAVHeader(myheader);
			displayWAVdata(samples);
			fclose(fp);
		}
	}

#ifdef DEBUG //comditional compiling
	createTestTone(1000);
#endif

}
