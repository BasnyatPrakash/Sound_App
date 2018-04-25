//#define DEBUG //for conditional compiling
#define FS 16000
#define COMM

typedef struct{
	char ChunkID[4]; //chunk ID; text
	int ChunkSize; //chunk size, 4 bytes
	char Format[4]; //"WAVE"
	char SubChunk1ID[4]; //"fmt "
	int SubChunk1Size; //4 bytes
	short int AudioFormat; //2 bytes
	short int NumberOfChannel; // 2 bytes
	int SampleRate; //4 bytes
	int ByteRate; //4 bytes
	short int BlockAlign; //2 bytes
	short int BitPerSample;// 2 bytes
	char SubChunk2ID[4]; //"data"
	int SubChunk2Size; //4 bytes
}WAVEHEADER;

void send_dBs(double []);
void fillID(char *id, char *s);
void displayWAVHeader(WAVEHEADER h);