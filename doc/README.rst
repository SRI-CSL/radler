Compiling radler document
=========================

Install Sphinx from 
http://www.sphinx-doc.org

In case of mac, use port to install instead of pip.  

::

    sudo port install py39-sphinx
    sudo port select --set python python39
    sudo port select --set sphinx py39-sphinx

Generate target files using Sphinx. 

:: 

    make html
    make latexpdf 

You will find your html/latex under _build directory. 
