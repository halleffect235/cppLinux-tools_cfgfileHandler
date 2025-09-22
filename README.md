<h1>cfgfileHandler.cpp</h1>
 
<div style="margin-left: 15px;"><h2><i>Class object which opens a config file, with multiple records, multiple data objects with mutiple parameters.</i><h2></div>

<div style="margin-left: 15px;">

       <h3> open a file and create a file structure</h3>
  
            <ul><li>int cfgfileOpen(char *fileName);</li></ul>

       <h3> return a pointer to a memory allocated file structure representing the configuration file</h3>
  
            ####          char** 	get_cfgfileStructure(void);

       <h3>  return a file structure back to free memory to prevent memory leaks</h3>
  
            ####          int 	free_cfgfileStructure(char ***, int);
  
       <h3>  Three data calls to retrive configuration parameters</h3>
  
            ####          getInt_cfgfileParaemter(char *paramterKey, int parameter number, int *intParam)
            ####          getFloat_cfgfileParaemter(char *paramterKey, int parameter number, float *floatParam)
            ####          getString_cfgfileParaemter(char *paramterKey, int parameter number, char **strParam)

  

</div>

