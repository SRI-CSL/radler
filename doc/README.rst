Compiling radler document
=========================

Install Sphinx from 
http://www.sphinx-doc.org/en/1.4.8/index.html

In case of mac, use port to install instead of pip.  

::

    sudo port install py27-sphinx
    sudo port select --set python python27
    sudo port select --set sphinx py27-sphinx

Generate target files using Sphinx. 

:: 

    make html
    make latexpdf 

You will find your html/latex under _build directory. 
