<h1>cfgfileHandler.cpp</h1>
 
<div style="margin-left: 15px;"><h2><i>
 Class object which opens a config file, with multiple records, multiple data objects with mutiple parameters.
</i><h2>
</div>

<div style="margin-left: 15px;">

<h3> 
       
open a file and create a file structure
       
</h3><ul><li>
            
                       int cfgfileOpen(char *fileName);
            
</li></ul><h3> 
 
return a pointer to a memory allocated file structure representing the configuration file 
 
       
</h3><ul><li> 
  
                      char** 	get_cfgfileStructure(void);
</li></ul>
<h3>  
 return a file structure back to free memory to prevent memory leaks
</h3><ul><li>
  
                      int 	free_cfgfileStructure(char ***, int);
  
</li></ul><h3>  
 Three data calls to retrive configuration parameters
</h3><ul><li>
  
                      getInt_cfgfileParaemter(char *paramterKey, int parameter number, int *intParam)
</li><li>
                      getFloat_cfgfileParaemter(char *paramterKey, int parameter number, float *floatParam)
</li><li>
                      getString_cfgfileParaemter(char *paramterKey, int parameter number, char **strParam)
</li></ul>  

</div>

