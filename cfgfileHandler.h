
# 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#
#define  MAXNO_cfgfile_RECS 500
#
#




class cfgfileHandler {


	public:	cfgfileHandler(void);
		~cfgfileHandler(void);	
	
		int cfgfileOpen(char *);
		char** get_cfgfileStructure(void);
		int get_cfgfileNoRecs(void);
		int free_cfgfileStructure(char ***, int);
		int reset_cfgfileHandlerClass(void);
		

	private:
	
		int cfgfileParse(char*, int);		
		char **cfgfileStruct = nullptr;
		char cfgfileOpenFileName[200];
		int cfgfileNoRcrds = 0;

} ;
 

