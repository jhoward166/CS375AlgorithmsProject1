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
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	ans = recursive(string1,string2);
	gettimeofday(&end, NULL);
	FILE *output = fopen(argv[3], "w");
	if(!output){
		printf("%s could not be opened. Program terminated.\n", argv[3]);
		return -1;
	}
	fprintf(output, "Recursive LCS size: %d\n",ans);
	fprintf(output, "Recursive LCS time: %ld milliseconds", (end.tv_sec* 1000000 +end.tv_usec)-(start.tv_sec* 1000000 +start.tv_usec));
	close(output);
}

int recursive(char* stringX, char* stringY){
	if(*stringX == '\0' || *stringY == '\0'){
		//terminating string will count as a hit so return -1 to set initial count to zero when it begins checking actual characters
		return -1;
	}else if(*stringX == *stringY){
		return 1+recursive(stringX+1, stringY+1);
	}else{
		int comp1;
		int comp2;
		comp1 = recursive(stringX+1, stringY);
		comp2 = recursive(stringX, stringY+1);
		if(comp1 > comp2){
			return comp1;
		}else{
			return comp2;
		}
	}
}
