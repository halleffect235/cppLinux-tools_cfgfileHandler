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

 Revision History:
 
    2025-09-25 - jpl	Added code to eliminate blank lines and comment lines from data structure, modeule
    				cfgfileParse was modifies to check for beginning with #, or \n, if so file 
    				record is eliminated from data file structure and replication.
    
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

 Software Usage Limitations
 
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
				if(rSize > 1 && fC[cStart] != '#') {			// check for # and blank line eliminate from the structure
					// if(rSize <= 1) {rSize = 1;}			// not needed eliminated from code
					newPtr = (char *) malloc(rSize);

				
					if(newPtr == nullptr) {fStatus = -4;}
					strncpy(newPtr, &fC[cStart], rSize -1);	newPtr[rSize] = 0;
					cStart = i + 1;
					cCount = 0;				
					(cfgfileStruct)[cfgfileNoRcrds++] = (char *) newPtr;
					
				} else {				
					cStart = i + 1;
					cCount = 0;				
				}
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
	
	
int cfgfileHandler::getString_cfgfileParameter(char *key, int parmNo, char **retStr) {

	int i, j, k;
	int indx = 0;
	char *retPtr;
		
	if(cfgfileStructNotOpen) {return(-1);}
	if(parmNo > MAX_NO_PARMS_REC) {return(-2);}
	
	//
	// scan the file structure for a key parameter match, if found break 
	//   out and process the parameter
		for(i = 0; i < cfgfileNoRcrds; i++) {
			retPtr = strstr((cfgfileStruct)[i], key);
			if(retPtr != nullptr) {indx = i; k = 1; break;}			
		}
		
	//
	// test if indx still 0 if yes bail with nullptr
		if(!k) {return(-3);}
	
	//
	// parse file for our string, parameter			
	
		//printf("index, paramNo, %d, %d\n", indx, parmNo);
	
		i = cfgfileParseRecord(indx, parmNo, &retPtr);
		
	//
	// look at our return for errors and report
		if(i != 0) {*retStr == nullptr; return(i);}
		
		//printf("field string %s\n", retPtr);
	//
	// all good update our pointer to our field data string
	
		*retStr = retPtr;
	
		return(i);

}	


int cfgfileHandler::getInt_cfgfileParameter(char *key, int parmNo, int *retInt) {

	char *strPtr;
	int status;
	
	//
	// check the obvious no file open -2, illegal parameter number, exceeds allowed
		if(cfgfileStructNotOpen) {return(-1);}
		if(parmNo > MAX_NO_PARMS_REC) {return(-2);}
	
	//
	// get our configuration paremter string for our field
	
		status = getString_cfgfileParameter(key, parmNo, &strPtr);
	
	//
	// check for errors and bail if we have problems
	
		if(status) {
			(*retInt) = 0;
			return(status);
		}	
	
	//
	// no errors return a value, and free the pointer
		
		*retInt = atoi(strPtr);
		free(strPtr);	
		
		return(0);
	
}


int cfgfileHandler::getFloat_cfgfileParameter(char *key, int parmNo, float *retFloat) {

	char *strPtr;
	int status;
	
	//
	// check the obvious no file open -2, illegal parameter number, exceeds allowed
	
		if(cfgfileStructNotOpen) {return(-1);}
		if(parmNo > MAX_NO_PARMS_REC) {return(-2);}
	
	//
	// get our configuration paremter string for our field	
	
	status = getString_cfgfileParameter(key, parmNo, &strPtr);
	
	printf("error retuirn on float %d\n", status);
	
	//
	// check for errors and bail if we have problems	
	
		if(status) {
			(*retFloat) = 0;
			return(status);
		}
	//
	// no errors return a value, and free the pointer	
		printf("returned string for float: %s\n", strPtr);
		(*retFloat) = atof(strPtr);
		free(strPtr);
		
		return(0);
	
}


 int cfgfileHandler::cfgfileParseRecord(int indx, int parmNo, char **recPtr) {

	int i = 0, j = 0, k = 0;
	int sLength;
	int startPos, endPos, parmCnt = 0;;
	char field[80], byte;
	char *newPtr;
	char *tPtr;
	
	sLength = strlen((cfgfileStruct)[indx]);
	
	for(i = 0; i < sLength; i++) {
		byte = (cfgfileStruct)[indx][i];
		if( byte == ';' || byte == ',') { parmCnt++;}
		if(parmCnt == parmNo) {startPos = i + 1; break;}
	
	}

	if(startPos == 0) {return(-1);}

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
	
	tPtr = strstr(field, "\"");
	if(tPtr != nullptr) {
		packQuotedString(field);	
	} else {	
		rmvWhitespace(field);
	}
	//printf("field %s\n", field);
	sLength = strlen(field);
	newPtr = (char *) malloc(sLength + 1);
	if(newPtr == nullptr) {*recPtr = nullptr; return(-4);}	// memory allocation error
	strcpy(newPtr, field);	
	
	//printf("returned parameter |%s|\n", newPtr);
	
	*recPtr =  newPtr;
	
	return(0);

}

int cfgfileHandler::rmvWhitespace(char *inStr) {

	int strLen = strlen(inStr);
	
	if(strLen > 50) {return(-5);}		// inpot string exceeds maximum paraeter size in bytes
	
	int i, j = 0, k = 0;
	char tStr[50];
	
	 //printf("string length after white space removal %d, |%s|\n", strLen, inStr);
	 
	for(i = 0; i < strLen; i++) {if(! isspace(inStr[i])) {tStr[j++] = inStr[i];}}

	tStr[j] = 0;
	strLen = strlen(tStr); //printf("string length after white space removal %d, |%s|\n", strLen, tStr);
	strcpy(inStr, tStr);
	
	return(0);

}

int cfgfileHandler::packQuotedString(char *inStr) {

	int strLen = strlen(inStr);
	
	if(strLen > 50) {return(-5);}		// 50 characters is our string size limit
	
	int i = 0, j = 0, k = 0;

	char tStr[80];

	//
	// find first quote
	for(i = 0; i < strLen; i++) {	
		if(inStr[i] == '"' ) {break;}
	}


	//
	// copy until either quote of end of string if found
	
	for(j = i + 1; j < strLen; j++) {
	
		if(inStr[j] != '"' || inStr[i] == ';' || inStr[i] == ',' || inStr == 0) 
			{tStr[k++] = inStr[j];}
		else 
			{ tStr[k] = 0; break;}	
	}

	//
	// copy back our return string
	
	strcpy(inStr, tStr);
	
	return(0);

}


