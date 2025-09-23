# cfgfileHandler.cpp

## *Class object which opens a config file, with multiple records, multiple data objects with mutiple parameters.*

### open a file and create a file structure
- `int cfgfileOpen(char *fileName);`

### return a pointer to a memory allocated file structure representing the configuration file 
- `char** get_cfgfileStructure(void);`

### return a file structure back to free memory to prevent memory leaks
- `int free_cfgfileStructure(char ***, int);`

### Three data calls to retrieve configuration parameters
- `int getInt_cfgfileParaemter(char *paramterKey, int parameter number, int *intParam)`
- `int getFloat_cfgfileParaemter(char *paramterKey, int parameter number, float *floatParam)`
- `int getString_cfgfileParaemter(char *paramterKey, int parameter number, char **strParam)`
 
### Sample Records from a typical configFile.cfg
- `#this is a typical configuration file`
- `# first item is the base apraemter name upto 50 cvharacters`
- `#    comma or semicolon seperated fields of upto 50 characters`
- `#    records beginning with "#" are ifgnored as comments`
- `#    parameter names can start anywhere on record, parameters must follow the parameter name
- `#`
- `#    parameters may be either string(upto 50 chars), integer, or float'
- '#`
- `#    commented lines are ignored in the internal cfgfile structure to conserve memory`
- `# band-1  , 167`
- ` band-1 ; 160`
- `band-2 ,   80`
- `band-3 ,   40`
- `band-4 ,   20`
