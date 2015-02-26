#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
int xLen;
int yLen;
int main(int argc, char** argv){
	if(argc != 4){
		printf("Incorrect number of arguments. Program terminated.\n");
		return -1;
	}
	FILE *inFile1 = fopen(argv[1], "r");
	if(!inFile1){
		printf("%s could not be opened. Program terminated.\n", argv[1]);
		return -1;
	}
	FILE *inFile2 = fopen(argv[2], "r");
	if(!inFile2){
		printf("%s could not be opened. Program terminated.\n", argv[2]);
		return -1;
	}
	int ans;
	char* string1;
	char* string2;
	int size1 = 128;
	int size2 = 128;
	string1 = malloc(size1);
	string2 = malloc(size2);
	int storeSize = 10;
	int xCount = 0;
	int yCount = 0;
	char c;
	while((c=fgetc(inFile1))!=EOF){
		xCount++;
		if(xCount > size1){
			size1 = size1*2;
			if(realloc(string1, size1)==NULL){
				printf("Realloc failed. Terminating program.\n");
				return -1;
			}
		}
		string1[xCount-1] = c;
	}
	while((c=fgetc(inFile2))!=EOF){
		yCount++;
		if(yCount > size2){
			size2 = size2*2;
			if(realloc(string2, size2)==NULL){
				printf("Realloc failed. Terminating program.\n");
				return -1;			
			}
		}
		string2[yCount-1] = c;
	}
	close(inFile1);
	close(inFile2);
	xLen = xCount;
	yLen = yCount;	
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	ans = topDown(string1, xCount,string2, yCount);
	gettimeofday(&end, NULL);
	FILE *output = fopen(argv[3], "w");
	if(!output){
		printf("%s could not be opened. Program terminated.\n", argv[3]);
		return -1;
	}
	fprintf(output, "Memoization LCS size: %d\n", ans);
	fprintf(output, "Memoization LCS time: %ld milliseconds", (end.tv_sec* 1000000 +end.tv_usec)-(start.tv_sec* 1000000 +start.tv_usec));
	close(output);
}

int topDown(char* stringX, int xlen, char* stringY, int ylen){
	int storage[xLen+1][yLen+1];
	int i;
	int j;
	for(i=0; i<=xLen; i++){
		for(j=0; j<=yLen; j++){
			storage[i][j] = -2;
		}
	}
	return solve(stringX, stringY, 0,0, storage);
}

int solve(char* stringX, char* stringY, int i, int j, int storage[xLen][yLen]){
	if(storage[i][j] < -1){	
		if(*(stringX+i) == '\0' || *(stringY+j) == '\0' || i>xLen || j>yLen){
			storage[i][j] = -1;
		}else if(*(stringX+i) == *(stringY+j)){
			storage[i][j] = 1+solve(stringX, stringY, i+1, j+1, storage);
		}else{
			int comp1;
			int comp2;
			comp1 = solve(stringX, stringY, i+1, j, storage);
			comp2 = solve(stringX, stringY, i, j+1, storage);
			if(comp1 > comp2){
				storage[i][j] = comp1;
			}else{
				storage[i][j] = comp2;
			}
		}
	}
	return storage[i][j];
}
