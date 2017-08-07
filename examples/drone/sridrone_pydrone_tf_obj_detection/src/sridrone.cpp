#include "ros/ros.h"
#include "sridrone.h"
#include <iostream>

#include <Python.h>

using namespace std;

SRIDrone::SRIDrone()
{
    Py_Initialize();

    char **argv;
    PySys_SetArgv(0, argv);

    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyString_FromString("./"));

    PyRun_SimpleString("import sys\nprint sys.path\nprint\n");

    PyObject *pName = PyString_FromString("mydrone");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL)
    {
        PyObject *pDroneInit = PyObject_GetAttrString(pModule, "mydrone_init");

        if ( !(pDroneInit && PyCallable_Check(pDroneInit)) )
        {
            if (PyErr_Occurred()) PyErr_Print();
            cout << "Cannot find function 'mydrone_init'" << endl;
        }
		else 
		{
        	PyObject_CallObject(pDroneInit, NULL);
			Py_DECREF(pDroneInit);
		}

		Py_DECREF(pModule);
    }
    else
    {
        PyErr_Print();
        cout << "Failed to load 'mydrone'" << endl;
    }
}

void SRIDrone::step(const radl_in_t * in, const radl_in_flags_t* iflags,
                    radl_out_t * out, radl_out_flags_t * oflags) 
{
	if ( *RADL_THIS->print_data ) {
		cout << "-----------------------------------" << endl;
	}

    radl_turn_off( radl_TIMEOUT, &oflags->object_detection );
    radl_turn_off( radl_STALE, &oflags->object_detection );

	if ( *RADL_THIS->check_iflags && *RADL_THIS->print_data ) {
		if ( radl_is_stale(iflags->led_anim) ) 
			cout << "led_anim is stale" << endl;
		if ( radl_is_timeout(iflags->led_anim) ) 
			cout << "led_anim is timeout" << endl;
	}

    PyObject *pName = PyString_FromString("mydrone");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL)
    {
        PyObject *pDroneMain = PyObject_GetAttrString(pModule, "mydrone_mainloop");

        if ( !(pDroneMain && PyCallable_Check(pDroneMain)) )
        {
            if (PyErr_Occurred()) PyErr_Print();
            cout << "Cannot find function 'mydrone_mainloop'" << endl;
            return;
        }
		else 
		{
    		PyObject *pValue;
        	pValue = PyObject_CallObject(pDroneMain, NULL);

        	if (pValue != NULL)
        	{
            	int id = PyInt_AsLong(pValue);
            	cout << "id " << id << endl;
				out->object_detection->id = id; 
            	Py_DECREF(pValue);
        	}
        	else
        	{
            	PyErr_Print();
            	std::cout << "Call failed" << std::endl;
        	}

			Py_DECREF(pDroneMain);
		}

        PyObject *pDroneLED = PyObject_GetAttrString(pModule, "mydrone_led");

        if ( !(pDroneLED && PyCallable_Check(pDroneLED)) )
        {
            if (PyErr_Occurred()) PyErr_Print();
            cout << "Cannot find function 'mydrone_led'" << endl;
            return;
        }
		else 
		{
			// set led animation 
			if ( !radl_is_stale(iflags->led_anim) && !radl_is_timeout(iflags->led_anim) )    
			{
				PyObject *pArgs = PyTuple_New(1);	
				PyObject *pValue = PyInt_FromLong(in->led_anim->id);	

				PyTuple_SetItem(pArgs, 0, pValue);	
            	Py_DECREF(pValue);

				PyObject_CallObject(pDroneLED, pArgs); 
            	Py_DECREF(pArgs);

				Py_DECREF(pDroneLED);

				if ( *RADL_THIS->print_data ) {
					cout << "ardrone.setAnimation = " << in->led_anim->id << endl;
				}
			}

			Py_DECREF(pModule);
		}
    }
    else
    {
        PyErr_Print();
        std::cout << "Failed to load 'mydrone'" << std::endl;
        return;
    }
}
