#include "Python.h"
#include "eHealth.h"
int fact(int n)
{
   if(n<=1)
      return 1;
   else
      return n*fact(n-1);
}

/*
float getTemperature()
{
    return (float)eHealth.getTemperature();
}
*/

PyObject* wrap_fact(PyObject* self, PyObject* args)
{
   int n,result;
   if(!PyArg_ParseTuple(args,"i:fact", &n))
      return NULL;
   result = fact(n);
   return Py_BuildValue("i",result);
}

PyObject* wrap_getTemperature(PyObject* self, PyObject* args)
{
    double result = (double)eHealth.getTemperature();
    return Py_BuildValue("d",result);
}
static PyMethodDef iHealthMethods[]=
{
   {"fact",wrap_fact,METH_VARARGS, "Calculte N!"},
   {"getTemperature",wrap_getTemperature,METH_VARARGS},
   {NULL, NULL}

};

extern "C"
void initiHealth()
{
   PyObject* m;
   m=Py_InitModule("iHealth", iHealthMethods);
}

