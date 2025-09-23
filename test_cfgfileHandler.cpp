





#include "cfgfileHandler.h"

 
int main(void) {

	int i, nRecs;
	char **fStruct;

	cfgfileHandler cfgFile;
	
	cfgFile.cfgfileOpen((char *) "cfgFlexRadio.cfg");
	
	nRecs = cfgFile.get_cfgfileNoRecs();
	
	fStruct = cfgFile.get_cfgfileStructure();
	
	if(fStruct == nullptr) {printf("null ptr returned\n");}
	
	for( i = 0; i < nRecs; i++) {printf("%s\n", (fStruct)[i]);}	
	
	cfgFile.free_cfgfileStructure(&fStruct, nRecs);
	
	char *myPtr = cfgFile.getString_cfgfileParameter((char *) "band-4", 1) ;
	printf("Band-4 paraemter 1, |%s|\n", myPtr);
	
	int myInt = cfgFile.getInt_cfgfileParameter((char *) "band-1", 1) ;
	printf("Band-1 paraemter 1, |%d|\n", myInt);
	
	float myFloat = cfgFile.getFloat_cfgfileParameter((char *) "band-2", 1) ;
	printf("Band-2 paraemter 1, |%f|\n", myFloat);
	
	cfgFile.reset_cfgfileHandlerClass();
	
}
