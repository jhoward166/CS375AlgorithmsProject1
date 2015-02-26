#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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
	bottomUp(string1, xCount, string2, yCount, argv[3]);
}

int bottomUp(char* stringX, int xLen, char* stringY, int yLen, char *outFile){
	int grid[xLen+1][yLen+1];
	int i;
	int j;
	int size;
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	for(i=0; i<=xLen; i++){
		for(j=0; j<=yLen; j++){
			grid[i][j] = 0;
		}
	}
	for(i=1; i<=xLen; i++){
		for(j=1; j<=yLen; j++){
			if(stringX[i-1]==stringY[j-1]){
				//printf("%d %d", grid[i][j], grid[i-1][j-1]);
				grid[i][j]=(grid[i-1][j-1])+1;
			}else{
				int higher;
				if(grid[i][j-1] > grid[i-1][j]){
					higher = grid[i][j-1];
				}else{
					higher = grid[i-1][j];
				}
				grid[i][j] = higher;
			}
		}
	}
	gettimeofday(&end, NULL);
	size = grid[xLen][yLen];
	FILE *output =  fopen(outFile, "w");
	if(!output){
		printf("%s could not be opened. Program terminated.\n", outFile);
		return -1;
	}
	if(xLen < 11 && yLen < 11){
		char letters[size]; 
		int val = -1;
		int hit = 0;
		int x = xLen;
		int y = yLen;
		int i;
		int j;
		for(j=0; j<yLen; j++){
			for(i=0; i< xLen; i++){
				fprintf(output,"%d ", grid[i][j]);
			}
			fprintf(output,"\n");
		}
		
		while(val != 0){
			if((grid[x][y] > grid[x-1][y]) && (grid[x][y] > grid[x][y-1])){
				hit++;
				letters[size-hit] = stringX[x-1];
				x=x-1;
				y=y-1;
				val = grid[x][y];
			}else if(grid[x][y] == grid[x][y-1]){
				y=y-1;
				val = grid[x][y];
			}else if(grid[x][y] == grid[x-1][y]){
				x=x-1;
				val = grid[x][y];
			}
		}
		fprintf(output,"Longest Common Subsequence: ");
		for(i =0; i<size; i++){
			fprintf(output,"%c ",letters[i]);
		}
		fprintf(output,"Bottom Up LCS Time: %ld milliseconds\n", (end.tv_sec* 1000000 +end.tv_usec)-(start.tv_sec* 1000000 +start.tv_usec));
	}else{
		fprintf(output,"Bottom Up LCS Size: %d\n", size);
		fprintf(output,"Bottom Up LCS Time: %ld milliseconds\n", (end.tv_sec* 1000000 +end.tv_usec)-(start.tv_sec* 1000000 +start.tv_usec));
	}
	close(output);
	return 0;
}
