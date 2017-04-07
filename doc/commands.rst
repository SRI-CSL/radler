Commands
========

radler.sh
---------

radler.sh is a simple bash script used to run the actual python Radler
script radler/main.py

Radler script
-----------------

The script may be used to  handle object files with the subcommands
``obj_version`` and ``obj_compatible`` or to compile .radl description
with the ``compile`` subcommand. The script has two levels of arguments.
The arguments before the subcommand and the one after, specific to the
subcommand.

Generic arguments
~~~~~~~~~~~~~~~~~

The full list of arguments is provided by the ``--help`` argument.

``--ws_dir`` 

This is used to specify where is the workspace directory. The
workspace directory is where the files are generated. This is by
default equal to ``src``.

Compile subcommand
~~~~~~~~~~~~~~~~~~

The full list of arguments for the ``compile`` subcommand is available
as the ``--help`` argument to the subcommand
(``radler.sh compile --help``).

The radl description file is a positional compulsory argument. It has
to be a file with the '.radl' extension.

``--object_files``

To compile .radl description which depends on other modules, one has
to give the object files of those modules with this argument.

``--object_dest``

By default, the generated object file has the same name as its
module, with the '.radlo' extension. Moreover it is by default
written at the root of the workspace directory. This command can be used  
to change the name and directory of the generated object file.
