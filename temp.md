# cfgfileHandler.cpp

## *Class object which opens a config file, with multiple records, multiple data objects with mutiple parameters.*

### open a file and create a file structure
- `int cfgfileOpen(char *fileName);`

### return a pointer to a memory allocated file structure representing the configuration file 
- `char** get_cfgfileStructure(void);`

### return a file structure back to free memory to prevent memory leaks
- `int free_cfgfileStructure(char ***, int);`

### Three data calls to retrieve configuration parameters
- `getInt_cfgfileParaemter(char *paramterKey, int parameter number, int *intParam)`
- `getFloat_cfgfileParaemter(char *paramterKey, int parameter number, float *floatParam)`
- `getString_cfgfileParaemter(char *paramterKey, int parameter number, char **strParam)`
 
### Sample Records from a typical configFile.cfg
-`#this is a typical configuration file`
-`# first item is the base apraemter name `
-`#    comma of seperated fields of upto 50 characters`
-`#    records beginning with "#" are ifgnored as comments`
-`#`
-`# band-1  , 167`
-` band-1 ; 160`
-`band-2 ,   80`
-`band-3 ,   40`
-`band-4 ,   20`
