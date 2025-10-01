# cfgfileHandler.cpp

## *Class object which opens a config file, with multiple records, multiple data objects with mutiple parameters.*

### open a file and create a file structure
- `int cfgfileOpen(char *fileName);`

### return a pointer to a memory allocated file structure representing the configuration file 
- `char** get_cfgfileStructure(void);`

### return a file structure back to free memory to prevent memory leaks
- `int free_cfgfileStructure(char ***, int);`

### Three data calls to retrieve configuration parameters
- `int getInt_cfgfileParaemter(char *paramterKey, int parameter number, int *intParam)` \
      `return converted int from parameter field`
- `int getDouble_cfgfileParaemter(char *paramterKey, int parameter number, double *doublParam)` \
     `return converted double from parameter field`
- `int getString_cfgfileParaemter(char *paramterKey, int parameter number, char **strParam)' \
     `return entire quoted string as an allocated pointer from parameter field or without quotes a compressed string free of whitespace` 

- `   return sring, if string is quoted, string is returned verbatum with all whitespace,  `
- `      if string is not quoted, string is returned packed with all whitespace removed`

- `   The following errors apply to all three of these routines`
- `      Error return -1 - no structure open`
- `                   -2 - parameter requested exceeds max allowed 15`
- `                   -3 - parameter key string not found`
- `                   -4 - general fault`
- `                   -5 - parameter string exceeds 50 characters`
 
### Sample Records from a typical configFile.cfg
- `# this is a typical configuration file`
- `#    first item is the base apraemter name upto 50 characters`
- `#    comma or semicolon seperated fields of upto 50 characters`
- `#    records beginning with "#" are ignored as comments`
- `#    parameter names can start anywhere on record, parameters must follow the parameter name
- `#`
- `#    parameters may be either string(upto 50 chars), integer, or float'
- '#`
- `#    commented lines are ignored in the internal cfgfile structure to conserve memory`
- `# band-1  , 167`
- `#     example of double parameter`
- ` band-1 ; 160.50`
- `#     example of integer parameter`
- `band-2 ,   80`
- `band-3 ,   40`
- `      example of string parameter`
- `band-4 ,   "this is 20 meters 17mHz   "`

