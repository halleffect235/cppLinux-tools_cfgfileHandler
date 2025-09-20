/*
-------------------------------------------------------------------------------------------------------------------------------

 Class cfgfileHandler

    This software was developed and is maitained by :

        J.P. Langan
        13186 15th Street South
        Afton, MN 55001

        Support inquiries to softw-dev@dyn-eng.com

 Copyright September 10, 2025 - jpl

-------------------------------------------------------------------------------------------------------------------------------

 Operating Systems Supported:

    POP-OS                      tested
    Oracle versions 3 - 9.5     tested
    Debian                      believed to work but not tested
    Ubuntu                      beleived to work but not tested    
    
-------------------------------------------------------------------------------------------------------------------------------

 Public: Program modules
 
 	cfgfileHandler()				Constructor
 	~cfgfileHandler()				Destructor
 	
 	int cfgfileOpen(char *)				Open file and create working file data srtucture
	char** 	get_cfgfileStructure(void)		Create a clone of the internal file data structure 
							  and return a pointer to a working copy
	int get_cfgfileNoRecs(void)			Return the number of records in the file data structure
	int free_cfgfileStructure(char ***, int)	Free the local working copy of the file data structure
							  memory allocations, root ptr becomes nullptr
	int reset_cfgfileHandlerClass(void)		Free internal data structure and reset all parameters, 
							  so a new "cfgfileOpen" will be ready for new file.					  
	char* getString_cfgfileParameter(char *, int)	Return a pointer to record parameter string
	int getInt_cfgfileParameter(char *, int)	Return a record parameter as an integer value
	float getFloat_cfgfileParameter(char *, int)	Return a record parameter as a float value

-------------------------------------------------------------------------------------------------------------------------------

 Softwaer Usage Limitations
 
 	cfgfileOpen...					file path limited to 511 bytes
 	
 	cfgfileStruct...				file size limited to 511 records
 							Paraeter field limited to 49 characters
 							Record is limited to 15 parameters
 							file record length limited to 511 characters
 							
 	getFloat..., getString..., getInt...		Paramter count limited to 15 paraemters
 	
------------------------------------------------------------------------------------------------------------------------------- 	

 Software Return Errors
 
 	cfgfileOpen...					-1 file path too long
 							-2 file can not be opened
 							-3 file contains too many records
 							-4 file structure can't be created (usually memory allocation failure)

-------------------------------------------------------------------------------------------------------------------------------
*/


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

	int	fSize = 0;
	int	i, j, k;
	char	*fCnt;
	int 	fStatus;
	
	//
	// test incoming filename for size and store it
		if(strlen(fName) > MAX_FILE_PATH_LENGTH) {return(-1);}
		strcpy(cfgfileOpenFileName, fName);	
		
	// open out file and check for validity

		FILE *fp = fopen(fName, "r");	
		if(fp == NULL) {return(-2);}
	
	//
	// get the file size and reset position to the beginning
		fseek(fp, 0, SEEK_END);	
		fSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
	
	//
	// allocate enough memory for our file, then read in file data
		fCnt = (char *) calloc(fSize + 10, sizeof(char));
		if(fCnt == nullptr) {return(-4);}
		fread(fCnt, fSize, sizeof(char), fp);
		//printf("file dump\n%s\n", fCnt);
		
	//
	// parse file into records each properly allocated
		fStatus = cfgfileParse(fCnt, fSize);
		if(fStatus) {return(fStatus);}
	
	//
	// relase or allocated tempoary work area filedata
		free(fCnt);
		
	return(0);
	
}

int cfgfileHandler::cfgfileParse(char *fC, int fSize) {

	int cCount = 0, fStatus = 0, rSize = 0;	
	int i = 0, j = 0, k = 0;
	int recCount = 0, cStart = 0;
	
	char *newPtr;
	
	//
	// get our record count for raw recs in file
		for(i = 1; i < fSize; i++ ) {if(fC[i] == '\n') {recCount++;}}
		
		if(recCount > MAX_NUM_CFGFILE_RECS) {return(-3);}		// too many records in file for structure
 
		cfgfileStruct = (char **) calloc(recCount, sizeof(char *));
		
		if(cfgfileStruct == nullptr) {return(-4);}			// return error structure couldn't be allocated
		
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
				if(newPtr == nullptr) {fStatus = -4;}
				strncpy(newPtr, &fC[cStart], rSize -1);	newPtr[rSize] = 0;
				cStart = i + 1;
				cCount = 0;				
				(cfgfileStruct)[cfgfileNoRcrds++] = (char *) newPtr;
			}		
		}
		
		
	if(fStatus == -4) {
	
		// release memory that has been allocated here
		
		return(fStatus);	
	}
	
	cfgfileStructNotOpen = 0;	// clear not open flag
		
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
	
	//printf("number of records to free is %d\n", noRecs);

	for(i = 0; i < noRecs; i++) {if((*ptr)[i] != nullptr) {free((*ptr)[i]);}}
	
	if((*ptr) != nullptr) {free(*ptr);}	
	*ptr = nullptr;
	
	return(0);

}	
	
	
char *cfgfileHandler::getString_cfgfileParameter(char *key, int parmNo) {

	int i, j, k;
	int indx = 0;
	char *retPtr;
		
	if(cfgfileStructNotOpen) {return(nullptr);}
	if(parmNo > MAX_NO_PARMS_REC) {return(nullptr);}
	
	//
	// scan the file structure for a key parameter match, if found break 
	//   out and process the parameter
		for(i = 0; i < cfgfileNoRcrds; i++) {
			retPtr = strstr((cfgfileStruct)[i], key);
			if(retPtr != nullptr && (cfgfileStruct)[i][0] != '#') {indx = i; break;}			
		}
		
	//
	// test if indx still 0 if yes bail with nullptr
		if(indx == 0) {return(nullptr);}
	
	//
	// parse file for our string, parameter	
		return(cfgfileParseRecord(indx, parmNo));

}	


int cfgfileHandler::getInt_cfgfileParameter(char *key, int parmNo) {

	char *strPtr;
	int retInt;
	
	if(cfgfileStructNotOpen) {return(-1);}
	if(parmNo > MAX_NO_PARMS_REC) {return(-2);}
	
	strPtr = getString_cfgfileParameter(key, parmNo);	
	retInt = atoi(strPtr);
	free(strPtr);	
	return(retInt);
	
}


float cfgfileHandler::getFloat_cfgfileParameter(char *key, int parmNo) {

	char *strPtr;
	float myFloat;
	
	if(cfgfileStructNotOpen) {return(-1);}
	if(parmNo > MAX_NO_PARMS_REC) {return(-2);}
	
	
	strPtr = getString_cfgfileParameter(key, parmNo);
	myFloat = atof(strPtr);
	free(strPtr);
	return(myFloat);
	
}


char *cfgfileHandler::cfgfileParseRecord(int indx, int parmNo) {

	int i = 0, j = 0, k = 0;
	int sLength;
	int startPos, endPos, parmCnt = 0;;
	char field[50], byte;
	char *recPtr;
	
	sLength = strlen((cfgfileStruct)[indx]);
	
	for(i = 0; i < sLength; i++) {
		byte = (cfgfileStruct)[indx][i];
		if( byte == ';' || byte == ',') { parmCnt++;}
		if(parmCnt == parmNo) {startPos = i + 1; break;}
	
	}

	if(startPos == 0) {return(nullptr);}

	for(i = startPos; i < sLength; i++) {
		byte = (cfgfileStruct)[indx][i]; //printf("byte in xfer to field %d, length %d\n", (int) byte, sLength);
		//printf("byte read in string after pareter match %d\n", (int) byte);
		if(byte != ',' && byte != ';' && byte != '\0' && byte != '\n') {
			field[j++] = byte;
		}
		else {
			
			break;		
		}
	}
	
	field[j] = 0;
	
	rmvWhitespace(field);
	
	sLength = strlen(field);
	recPtr = (char *) malloc(sLength + 1);
	strcpy(recPtr, field);	
	
	//printf("returned parameter |%s|\n", recPtr);
	
	return(recPtr);

}

int cfgfileHandler::rmvWhitespace(char *inStr) {

	int strLen = strlen(inStr);
	int i, j = 0, k = 0;
	char tStr[50];
	
	 //printf("string length after white space removal %d, |%s|\n", strLen, inStr);
	 
	for(i = 0; i < strLen; i++) {if(! isspace(inStr[i])) {tStr[j++] = inStr[i];}}

	tStr[j] = 0;
	strLen = strlen(tStr); //printf("string length after white space removal %d, |%s|\n", strLen, tStr);
	strcpy(inStr, tStr);
	
	return(0);

}






























