 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>



#include "cfgfileHandler.h"

cfgfileHandler::cfgfileHandler(void){


}

cfgfileHandler::~cfgfileHandler(void) {

	//free_cfgfileStructure(&cfgfileStruct, cfgfileNoRcrds);
}


int cfgfileHandler::reset_cfgfileHandlerClass() {

	free_cfgfileStructure(&cfgfileStruct, cfgfileNoRcrds);

	cfgfileNoRcrds = 0;
	
	strcpy(cfgfileOpenFileName, "");

	return(0);

}



int cfgfileHandler::cfgfileOpen(char *fName) {

	int fSize = 0;
	int	i, j, k;
	char *fCnt;
	
	//
	// test incoming filename for size and store it
		if(strlen(fName) > 200) {return(-3);}
		strcpy(cfgfileOpenFileName, fName);	
		
	// open out file and check for validity

		FILE *fp = fopen(fName, "r");	
		if(fp == NULL) {return(-1);}
	
	//
	// get the file size and reset position to the beginning
		fseek(fp, 0, SEEK_END);	
		fSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
	
	//
	// allocae enough memory for our file, then read in file data
		fCnt = (char *) calloc(fSize + 10, sizeof(char));
		fread(fCnt, fSize, sizeof(char), fp);
		//printf("file dump\n%s\n", fCnt);
		
	//
	// parse file into records each properly allocated
		cfgfileParse(fCnt, fSize);
	
	//
	// relase or allocated tempoary work area filedata
		free(fCnt);
		
	return(0);
	
}

int cfgfileHandler::cfgfileParse(char *fC, int fSize) {

	int i, j, k;
	int recCount = 0;
	int cStart = 0;
	char *newPtr;
	int cCount = 0;
	int rSize;
	
	//
	// get our record count for raw recs in file
		for(i = 1; i < fSize; i++ ) {if(fC[i] == '\n') {recCount++;}}
 
		cfgfileStruct = (char **) calloc(recCount, sizeof(char *));
		cfgfileNoRcrds = 0;
	
	//
	// 
		cStart = 0;	
		
		for(i = 0; i < fSize; i++) {
			if(fC[i] != '\n' && i != (fSize -1 )) {
				cCount++;
			}
			
			else {
				rSize = cCount + 1;
				if(rSize <= 1) {rSize = 1;}
				newPtr = (char *) malloc(rSize);
				strncpy(newPtr, &fC[cStart], rSize -1);	newPtr[rSize] = 0;
				cStart = i + 1;
				cCount = 0;				
				(cfgfileStruct)[cfgfileNoRcrds++] = (char *) newPtr;
			}		
		}
		
	return(0);

}	
	
	
char** cfgfileHandler::get_cfgfileStructure(void) {

	int i, j, k;
	int rSize;	
	char *newPtr;	
	char **retPtr;
//printf("enter file clone\n");
	if(cfgfileStruct == NULL) {return(nullptr);}			// no structure to clone
	
	retPtr = (char **) malloc((cfgfileNoRcrds * sizeof(char *)) + 10);	
//printf("allocate main ret ptr\n");
	//
	// loop through existing structure and clone it, then return it
	
	for(i = 0; i < cfgfileNoRcrds; i++) {
	
		rSize = strlen((cfgfileStruct)[i]);
		//printf("  cfgFile record size : %d\n", rSize);
		newPtr = (char *) calloc(rSize + 1, sizeof(char));
		strcpy(newPtr, (cfgfileStruct)[i]); 
		retPtr[i] = newPtr;
	
	}
	
	return(retPtr);
}

	
int cfgfileHandler::get_cfgfileNoRecs() {

	return(cfgfileNoRcrds);

}
	
int cfgfileHandler::free_cfgfileStructure(char ***ptr, int noRecs) {

	int i;
	
	if(noRecs == 0) {return(-1);}
	
	printf("number of records to free is %d\n", noRecs);

	for(i = 0; i < noRecs; i++) {printf("rec #%d\n", i); free((*ptr)[i]);}
	
	free(*ptr);	
	*ptr = nullptr;
	
	return(0);

}	
	
	
	
	
	
	

