





#include "cfgfileHandler.h"

 
int main(void) {

    int i, nRecs, myInt, retStat;
	char **fStruct;
	char *myPtr;
	float myFloat;

	cfgfileHandler cfgFile;
	
    retStat = cfgFile.cfgfileOpen((char *) "cfgFlexRadio.cfg");
    if(retStat) {printf("File not found\n"); exit(99);}
	
	nRecs = cfgFile.get_cfgfileNoRecs();
	
	fStruct = cfgFile.get_cfgfileStructure();
	
    if(fStruct == nullptr) {printf("null ptr returned\n"); exit(99);}
	
    for( i = 0; i < nRecs; i++) {printf("%s\n", (fStruct)[i]);}
	
	cfgFile.free_cfgfileStructure(&fStruct, nRecs);
	
    retStat += cfgFile.getString_cfgfileParameter((char *) "band-4", 1, &myPtr) ;
	printf("Band-4 paraemter 1 as string, |%s|\n", myPtr);
	
    retStat += cfgFile.getInt_cfgfileParameter((char *) "band-2", 1, &myInt) ;
	printf("Band-2 paraemter 1, as INT, |%d|\n", myInt);
	
    retStat += cfgFile.getFloat_cfgfileParameter((char *) "band-1", 1, &myFloat) ;
	printf("Band-1 paraemter 1 as float, |%f|\n", myFloat);

    if(retStat) {printf("Errors returned: %d\n", retStat);}
	
	cfgFile.reset_cfgfileHandlerClass();
	
}
