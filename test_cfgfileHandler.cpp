





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
	
	cfgFile.reset_cfgfileHandlerClass();
	
}
