/*
 Class cfgfileHandler

    This software was developed and is maitained by :

        J.P. Langan
        13186 15th Street South
        Afton, MN 55001

        Support inquiries to softw-dev@dyn-eng.com

 Copyright September 10, 2025 - jpl

-------------------------------------------------------------------------------------------------------------------------------

 Updates/changes
 
 	2025-09-19 - jpl - Added following three public routines
 
 		int 	getString_cfgfileParameter(char *, int, char **);
		int 	getInt_cfgfileParameter(char *, int, int *);
		int	getFloat_cfgfileParameter(char *, int, float *);
		
		These routines are designed to scan the file structure for a parmater name match and return the parameter as
			requested.  Error are returned in the call as an integer...
			
		Error codes: 
			-1 no file is open for scanning 
			-2 paramter requested exceeds max allowable 
			-3 paraemter name not found in structure 
			-4 memory allocation error

-------------------------------------------------------------------------------------------------------------------------------

Operating Systems Supported:

    POP-OS                      tested
    Oracle versions 3 - 9.5     tested
    Debian                      believed to work but not tested
    Ubuntu                      beleived to work but not tested

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <ctype.h>



#ifndef CFGFILEHANDLER_H
#define CFGFILEHANDLER_H
 
//
// A few limitations
#define  MAX_NUM_CFGFILE_RECS	511
#define  MAX_PARAM_CHARS	 49
#define  MAX_REC_LENGTH		511
#define  MAX_NO_PARMS_REC	 15
#define  MAX_FILE_PATH_LENGTH	511





class cfgfileHandler {

	public:	cfgfileHandler(void);
		~cfgfileHandler(void);	
	
		int 	cfgfileOpen(char *);
		char** 	get_cfgfileStructure(void);
		int 	get_cfgfileNoRecs(void);
		int 	free_cfgfileStructure(char ***, int);
		int 	reset_cfgfileHandlerClass(void);
		int 	getString_cfgfileParameter(char *, int, char **);
		int 	getInt_cfgfileParameter(char *, int, int *);
		int	getFloat_cfgfileParameter(char *, int, float *);
		

	private:
	
		int	cfgfileParse(char*, int);	
		int	cfgfileParseRecord(int, int, char **);
		int	rmvWhitespace(char *);
		int	packQuotedString(char *);
		
		char	**cfgfileStruct = nullptr;
		char	cfgfileOpenFileName[200];
		int	cfgfileNoRcrds = 0;
		int	cfgfileStructNotOpen = 255;

};
 
#endif  // CFGFILEHANDLER_H  end of block
