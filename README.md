# cfgfileHandler.cpp
 
<div style="margin-left: 15px;"><h2><i>Class object which opens a config file, with multiple records, multiple data objects with mutiple parameters.</i><h2></div>



       ###  open a file and create a file structure
  
            ####          int cfgfileOpen(char *fileName);

       ###  return a pointer to a memory allocated file structure representing the configuration file
  
            ####          char** 	get_cfgfileStructure(void);

       ###  return a file structure back to free memory to prevent memory leaks
  
            ####          int 	free_cfgfileStructure(char ***, int);
  
       ###  Three data calls to retrive configuration parameters
  
            ####          getInt_cfgfileParaemter(char *paramterKey, int parameter number, int *intParam)
            ####          getFloat_cfgfileParaemter(char *paramterKey, int parameter number, float *floatParam)
            ####          getString_cfgfileParaemter(char *paramterKey, int parameter number, char **strParam)

  



