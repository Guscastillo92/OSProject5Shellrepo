// Gustavo Castillo
// My implementation of a basic shell


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isCommandExit(char* command);
bool isCommandType(char* command);
bool isCommandCopy(char* command);
bool isCommandExecutable(char* command);
bool isCommandDelete(char* command);
int type(char* file1);
int copy(char* file1, char* file2);
int execute(char* file);
void delete(char * file);

																														

int main(int argc, char **argv) {
	// TODO
        printf("Gus: Welcome to the Gus Shell 0_0 \n");
	char command[100] = {0};
	while(true){
		printf(">");
		scanf("%s", command);
		
		if ( isCommandExit(command)){ //exits the loop
			break;
		}
		else if(isCommandType(command)){ //calls the function to prin to screen
			char filename[100] = {0};
			scanf("%s", filename);
			type(filename);
		}
		else if(isCommandCopy(command)){ //copies file to a new or existing file
			char filename[100] = {0};
			char filename2[100]= {0};
			scanf("%s", filename);
			scanf("%s", filename2);
			copy(filename, filename2);
		}
		else if(isCommandDelete(command)){//deletes an existing file
			char filename[100] = {0};
			scanf("%s", filename);
			delete(filename);
		}
		else{
			if(execute(command) == 0){//tries to execute command
				printf("Gus: Error, either you gave fat fingers or are trying to do something that isnt allowed, Try Again \n");
			}	
		}


        }
	return 0;
}

bool isCommandExit(char* command){//theses are just compares to identify command

	return !strcmp(command, "exit");

}

bool isCommandType(char* command){

	return !strcmp(command, "type");

}
bool isCommandCopy(char* command){
	return !strcmp(command, "copy");
}

bool isCommandExecutable(char* command){//ended up not using this
	return true;
}
bool isCommandDelete(char* command){
	return !strcmp(command, "delete");
}
int type(char* file1){
	//I got most of this code for file IO in C from cs.bu.edu
	FILE *printFile;

	printFile = fopen(file1, "r"); 

	char Line[255];
	
	if(printFile == NULL){ //makes sure the file is valid
		fprintf(stderr, "Gus: Cant open the file entered %s\n", file1 );
		return 0;
	}

	while(fgets( Line, 255, printFile) !=  NULL){ //prints contents to the screen
		printf("%s", Line);
	}
	fclose(printFile);
	return 0;

}
int copy(char* file1, char* file2){
	//I got most of this code for file IO in C from cs.bu.edu
	FILE *printFile, *copyToFile;

	printFile = fopen(file1, "r");
	copyToFile = fopen(file2, "w");

	char Line[255];
//Opens up the files and gets ready to copy
	
	if(printFile == NULL){
		fprintf(stderr, "Gus: Cant open the file entered %s\n", file1 );
		return 0;
	}

	if(copyToFile == NULL){
		fprintf(stderr, "Gus: Cant open the file entered %s\n", file2);
		return 0;
	}

	while(fgets( Line, 255, printFile) !=  NULL){ //copies to the file
		fprintf(copyToFile, "%s", Line);
	}

	fclose(printFile);
	fclose(copyToFile);
	return 0;

}

int execute(char * file){
	if(system(file) == -1){//executes the program
		return 0;
	}
	else{
		return 1;
	}
}
void delete(char * file){
	if( remove(file) != 0){ //deletes a file and checks if it exists
		perror("Gus: the file could not be deleted n00b  ");
	}
	else{
		puts( "Gus: Congratz you did something right, file deleted");
	}
}
