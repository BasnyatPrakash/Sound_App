#include <stdio.h>
#include <math.h>
#include <curl/curl.h>
#include <string.h>

#include "sound.h"
#include "screen.h"

#define PI 3.14159

#ifdef COMM

void send_dBs(double *dbs){
	CURL *curl;
	CURLcode res;
	char postdata[200];
	int i;
	char temp[100];

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if(curl){
		sprintf(postdata, "%s", "dBs=");

		for(i = 0;i < 8;i++){
			sprintf(temp,"{\"d\": \"%.2f\"}, ", dbs[i]);
			strcat(postdata, temp);
		} //for loop prepare the post data

		curl_easy_setopt(curl, CURLOPT_URL, "http://cc-puv.fi/~e1500942/php/testCurl.php");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
		res = curl_easy_perform(curl);

		if(res != CURLE_OK){
			printf("Cannot send\n");
		}

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
#endif

void displayWAVdata(short int *s){
	int i, j, k; //loop control variables
	double sum, rms, sum_short;
	double Leq_short[8];

	k = 0; //index counter for Leq_short
	sum_short = 0; //sum of sample for 1/8 sec

	for(i = 0;i < 80;i++){ //outer 80 times
		for(j=0, sum=0.0;j<FS/80;j++){ //inner 200 times, total 16000 times
			sum+= (int)(*s)*(*s);//calculate the square of sample
			s++;
		}
		rms = sqrt(sum/(FS/80)); //calculate RMS value for 200 samples
		sum_short += sum; //for 2000 samples sum

		if(i%10 == 9){  //10 cycles of i
			Leq_short[k] = 20*log10(sqrt(sum_short/(FS/8)));
			k++;
			sum_short = 0;
		}

#ifdef DEBUG
		printf("rms(dB) %d = %.3f\n", i, 20*log10(rms)); //result in dB
#else
		displayBar(i+1,(int)(20*log10(rms)));
		//make a vertical bar
#endif
	}
#ifdef COMM //if COMM is defined, send short Leq to server
			//an HTTP POST string is generated, contains short Leq
			//curl() function required
#endif
}


void printID(char id[]){
	int i;

	for(i = 0;i < 4;i++){
		printf("%c", id[i]);
	}
	puts(" ");
}

void displayWAVHeader(WAVEHEADER h){
	double duration;
	int i;
	char str[25]; //temporal string to display header info
	duration = (double)h.SubChunk2Size/(h.BitPerSample/8)/h.NumberOfChannel/h.SampleRate;

#ifdef DEBUG
	printf("Duration: %.2f seconds\n",duration);
	printf("1. Chunk ID: %d\n");
	for(i = 0;i < 4; i++) printf("%c", h.ChunkID[i]);

	printf("2. Chunk Size: %d\n", h.ChunkSize);
	printf("3. Format: "); printID(h.Format);
	for(i = 0;i < 4; i++) printf("%c", h.Format[i]);

	printf("4. Subchunk1 ID: %d\n"); printID(h.SubChunk1ID);
	printf("5. Subchunk1 size: %d\n",h.SubChunk1Size);
	printf("6. Audio format: %d\n", h.AudioFormat);
	printf("7. Number of channel: %d\n", h.NumberOfChannel);
	printf("8. Samle rate: %d\n", h.SampleRate);
	printf("9. Byte rate: %d\n", h.ByteRate);
	printf("10. Block align: %d\n", h.BlockAlign);
	printf("11. Bits per sample: %d\n", h.BitPerSample);
	printf("12. Subchunk2 ID: %d\n"); printID(h.SubChunk2ID);
	for(i = 0;i < 4; i++) printf("%c", h.SubChunk2ID[i]);

	printf("13. Subchunk2 size: %d\n", h.SubChunk2Size);

#else //follow code is final of project
	//display only No.Ch, Samplerate, BisperSpl, Duration
	//at the top of the screen

	sprintf(str, "No.of Channel: %d", h.NumberOfChannel);
	displayXY(str, RED, bg(BLUE), 1, 1);
	sprintf(str, "Sample Rate: %5d", h.SampleRate);
	displayXY(str, GREEN, bg(WHITE), 1, 21);
	sprintf(str, "Bits per sample: %d", h.BitPerSample);
	displayXY(str, YELLOW, bg(CYAN), 1, 41);
	sprintf(str, "Duration: %d", duration);
	displayXY(str, MAGENTA, bg(YELLOW), 1, 61);
#endif

}

void createTestTone(int freq, int duration){
	FILE *fp; //file handler

	short int sample; // for each sample is 16 signed int
	int i; //loop counter
	WAVEHEADER h;

	fp = fopen("TestTone.wav","wb"); //create file
	if(fp != NULL){
		fillID(h.ChunkID, "RIFF");
		fillID(h.Format, "WAVE");
		fillID(h.SubChunk1ID, "fmt");
		fillID(h.SubChunk2ID, "data");

		h.SubChunk1Size = 16; h.AudioFormat = 1; //PCM encoding
		h.NumberOfChannel = 1; h.SampleRate = 16000; //mono, 16000 Fs
		h.BitPerSample = 16; h.SubChunk2Size  = h.SampleRate*duration*2*(h.NumberOfChannel);
		h,ByteRate = (h.SampleRate)*(h.NumberOfChannel)*(h.BitPerSample)/8;
		h.BlockAlign = (h.NumberOfChannel)*(h.BitPerSample)/8;
		h.ChunkSize = h.SubChunk2Size + 36;

		fwrite(&h, sizeof(h), 1, fp); //write header to a wave file

		for(i = 0;i < 5*16000;i++){
			sample = sin(2*PI*freq*i/16000)*32768;

			fwrite(&sample, sizeof(sample), 1, fp);
		}
		fclose(fp);
		printf("Test a tone created\n");
	}
}

void fillID(char *id, char *s){
	int i;

	for(i=0;i<4;i++){
		*id++ = *s++;
	}
}
