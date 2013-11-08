#include "Python.h"
#include "eHealth.h"

extern SerialPi Serial;

int cont = 0;

int fact(int n)
{
   if(n<=1)
      return 1;
   else
      return n*fact(n-1);
}

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

//airflow.breathing
PyObject* wrap_getAirFlow(PyObject* self, PyObject* args)
{
    int result =eHealth.getAirFlow();
    return Py_BuildValue("i",result);
}

//ecg
PyObject* wrap_getECG(PyObject* self, PyObject* args)
{
    double result = (double)eHealth.getECG();
    return Py_BuildValue("d",result);
}

//--galvanic
//----------skin conductance
PyObject* wrap_getSkinConductance(PyObject* self, PyObject* args)
{
    double result = (double)eHealth.getSkinConductance();
    return Py_BuildValue("d",result);
}

//----------skin resistance
PyObject* wrap_getSkinResistance(PyObject* self, PyObject* args)
{
    double result = (double)eHealth.getSkinResistance();
    return Py_BuildValue("d",result);
}

//----------skin conductance voltage
PyObject* wrap_getSkinConductanceVoltage(PyObject* self, PyObject* args)
{
    double result = (double)eHealth.getSkinConductanceVoltage();
    return Py_BuildValue("d",result);
}

//positionometer
//-------init position sensor
PyObject* wrap_initPositionSensor(PyObject* self, PyObject* args)
{
    eHealth.initPositionSensor();
    return Py_BuildValue("i",0);
}

//-------get body position
PyObject* wrap_getBodyPosition(PyObject* self, PyObject* args)
{
    int result = (int)eHealth.getBodyPosition();
    return Py_BuildValue("i",result);
}

//pulsioximeter

void raadPulsioximeter()
{
    cont++;
    if(cont == 500)
    {
	eHealth.readPulsioximeter();
	cont = 0;
    }
}

//--------setup pulsioximeter
PyObject* wrap_setupPulsioximeter(PyObject* self, PyObject* args)
{
    eHealth.initPulsioximeter();
    attachInterrupt(6,raadPulsioximeter,RISING);

    return Py_BuildValue("i",0);
}

//---------getBPM
PyObject* wrap_getBPM(PyObject* self, PyObject* args)
{
    int result = eHealth.getBPM();
    return Py_BuildValue("i",result);
}

//---------getOxygenSatureation
PyObject* wrap_getOxygenSaturation(PyObject* self, PyObject* args)
{
    int result = eHealth.getOxygenSaturation();
    return Py_BuildValue("i",result);
}

//----------digital write 
PyObject* wrap_digitalWrite(PyObject* self, PyObject* args)
{
    digitalWrite(2,HIGH);
    return Py_BuildValue("i",0);
}

//glucometer
//-----setup glucometer
PyObject* wrap_setupGlucometer(PyObject* self, PyObject* args)
{
    eHealth.readGlucometer();
    delay(100);
    return Py_BuildValue("i",0);
}

//-----get glucometer length
PyObject* wrap_getGlucometerLength(PyObject* self, PyObject* args)
{
    int result = (int)eHealth.getGlucometerLength();
    delay(100);
    return Py_BuildValue("i",result);
}

//-----get glucose mg/dl
PyObject* wrap_getGlucose(PyObject* self, PyObject* args)
{
   int n,result;
   if(!PyArg_ParseTuple(args,"i:fact", &n))
      return NULL;
   result = eHealth.glucoseDataVector[n].glucose;
   return Py_BuildValue("i",result);
}


//methods
static PyMethodDef iHealthMethods[]=
{
   {"fact",wrap_fact,METH_VARARGS, "Calculte N!"},
   {"getTemperature",wrap_getTemperature,METH_VARARGS},
   {"getAirFlow",wrap_getAirFlow,METH_VARARGS},
   {"getECG",wrap_getECG,METH_VARARGS},
   {"getSkinConductance",wrap_getSkinConductance,METH_VARARGS},
   {"getSkinResistance",wrap_getSkinResistance,METH_VARARGS},
   {"getSkinConductanceVoltage",wrap_getSkinConductanceVoltage,METH_VARARGS},  
   {"initPositionSensor",wrap_initPositionSensor,METH_VARARGS}, 
   {"getBodyPosition",wrap_getBodyPosition,METH_VARARGS},   
   {"setupPulsioximeter",wrap_setupPulsioximeter,METH_VARARGS},  
   {"getBPM",wrap_getBPM,METH_VARARGS}, 
   {"getOxygenSaturation",wrap_getOxygenSaturation,METH_VARARGS}, 
   {"digitalWrite",wrap_digitalWrite,METH_VARARGS},
   {"setupGlucometer",wrap_setupGlucometer,METH_VARARGS}, 
   {"getGlucometerLength",wrap_getGlucometerLength,METH_VARARGS}, 
   {"getGlucose",wrap_getGlucose,METH_VARARGS}, 
   {NULL, NULL}
};

extern "C"
void initiHealth()
{
   PyObject* m;
   m=Py_InitModule("iHealth", iHealthMethods);
}

