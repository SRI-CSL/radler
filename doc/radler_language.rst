File constraints
================

A radl description file is a text file, preferably encoded in utf8, with
extension ".radl". Such a file is called in short a radl file.

Meta syntax rules
=================

A radl file define a module whose name is the file name. A module is a
set of value declarations. A declaration may be an alias, used to
declare a value equal to another one but with a new name. The name of a
value may be omitted, note that it'll prevent the user to reference this
value. The type of a value may also be omitted, note that if the type is
ambiguous, the inference will choose one. When defining a class field,
one may declare a new value or refer to another value by its
identifier.

Grammar
-------

:: 

    module := decl*
    decl := alias | NAME? (':' TYPE)? TYPEVALUE | NAME? (':' CLASS)? class_value
    alias := NAME = identifier
    class_value := '{' field * '}'
    field := FIELDNAME value + 
    value := identifier | decl
    identifier := root_name | identifier '.' NAME
    root_name := NAME

Grammar terminals
-----------------

The ``NAME`` terminal is a spaceless word beginning with a letter which
may contain numbers and underscore (the regex
``[a-zA-Z][a-zA-Z0-9_]*``). ``NAME`` is also restricted not to be a
keyword, or begin with 'radl'. The other terminals are defined by the
language.py_ file, with
declarations of the form

.. _language.py: https://github.com/SRI-CSL/radler/blob/master/radler/radlr/language.py

:: 

    'type' TYPE 'REGEX' TYPEVALUE

and

:: 

    'class' CLASS (FIELDNAME (TYPE|CLASS) ('*'|'+'|'?')?)*

Keywords
--------

Keywords are all ``TYPE``, ``CLASS`` and ``FIELDNAME`` plus the
``extra_keywords`` entry of
language.py_.

White spaces
------------

The syntax requires all terminals to be whitespace separated. A whitespace is any number greater than 1 of space, tabulation and end of line.

Comments
--------

After ``#``, any character is discarded up to the end of line.

Identifier scoping rules
========================

Scoping regions
---------------

A file ``MODULE``.radl defines an implicit scoping region for its
content whose name is ``MODULE``. Sub-regions are defined by class
values. A class value declaration defines one and only one nested
scoping region, syntactically delimited by matching braces, whose name
is the declaration ``NAME``.

Local unicity of names
----------------------

Inside each region (not comprising its sub-regions), ``NAME`` of each
declarations are unique. Moreover, each module name ``MODULE`` is
ensured to be unique.

Global unicity of qualified names
---------------------------------

A qualified name (qname) is an identifier whose ``root_name`` is a
module name. By unicity of module names and declaration names, a qname
defines a value uniquely.

Resolution of identifiers to qualified names
--------------------------------------------

When resolving an identifier, the first step is the resolution of its
``root_name``, which is matched with the closest enclosing scoping region
or in the last resort to another module name. At that point, the
``root_name`` is replaced by the qualified name of its matching region
and the identifier becomes a qualified name.

Example
~~~~~~~

:: 

    ---- file: module1.radl ----
    x : int32 0
    s : struct { FIELDS x : int32 42 }
    ----------------------------

This file declares three values whose qnames are ``module1.x``,
``module1.s`` and ``module1.s.x``.

:: 

    ---- file: module2.radl ----
    x : int32 0
    s : struct { FIELDS
        x : int32 0
        s2 : struct { FIELDS
            y = x
            y2 = s.x
            y3 = module2.s.x
            z = module2.x
            a = module1.s.x
        }
    }
    ----------------------------

This file declares nine values whose qnames are ``module2.x``,
``module2.s``, ``module2.s.x``, ``midule2.s.s2``, ``module2.s.s2.y``,
``module2.s.s2.y2``, ``module2.s.s2.y3``, ``module2.s.s2.z``, and
``module2.s.s2.a``. When defining the alias ``y = x``, the identifier
``x`` is resolved by looking for a name ``x`` defined in ``s2`` (which
doesn't exist) then in the enclosing region ``s`` where it is found,
thus resolving to ``module2.s.x``. ``s.x`` in the declaration of ``y2``
is resolved to the same qname by first resolving ``s`` to ``module2.s``
and replacing it to get ``module2.s.x``. When resolving the identifiers
``module2.s.x``, ``module2.x``, and ``module1.s.x``, the ``root_name`` is
found to be a module name meaning that these identifiers are already
qualified names.

Shadowing
---------

While using qualified names for identifiers permit to overcome most
possible shadowings, a region will shadow any module with identical
name.

Example
~~~~~~~

:: 

    --- file: module3.radl ---

    module1 : struct { FIELDS
        y = module1.x
    }
    --------------------------

In this file, the resolution of ``module1.x`` will result in
``module3.module1.x`` since the closest enclosing region named
``module1`` is the one defined in ``module3``. Thus the definition of
the struct named ``module1`` shadows the actual module ``module1``.
Note that in this example, since ``module3.module1.x`` isn't
declared, the compiler will complain that it is missing.

Radler language
===================

Logical level
-------------

The two main classes used to describe the logical level are node and
topic. Their full definitions may be found in
language.py_. The most
important elements are:

:: 

    class node
        PUBLISHES publication *
        SUBSCRIBES subscription *
        CXX cxx_class
        PERIOD duration
        WCET duration
    class topic
        FIELDS int8/uint8/int16/uint16/int32/uint32/int64/uint64/
               float32/float64/
               bool/struct/array/duration/time +

Nodes
~~~~~

When creating a node, Radler will construct one instance of the
provided C++ class (the ``CXX`` field). The step method of this
instance will be called at a fixed frequency defined by the node's
period (the ``PERIOD`` field). This step function needs to be proven
to have a worst case execution time no greater than the one described
here in the ``WCET`` field. At each call, the step function is
provided with the messages received from its subscriptions and is
required to write the messages it has to publish.

Topics
~~~~~~

A topic (defined uniquely by its name) is a purely logical way to
define point-to-point communications between one producer and
multiple consumers. There can be exactly one node
publishing to a topic while  many  nodes can subscribe to
it.

External files and ``PATH``
---------------------------

File reference
~~~~~~~~~~~~~~

An external file is described by a string representing its path. This
path may be absolute (for example "/etc/example.cfg") or relative
("src/defs.h"). Relative paths are resolved relatively to the working
directory of the scoping region. Absolute path files are not
recommended, but may be useful in very specific cases.

Working directory of a region, ``PATH`` and ``MODULE_BASE_PATH``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If a ``PATH`` field exists in a region, it is used to set the working
directory of this region relatively to the parent region's working
directory. The module working directory is the directory of the
module file except when it is redefined by the ``MODULE_BASE_PATH``
of the ``module_settings`` value.

Example
~~~~~~~

:: 

   ---- file: path1.radl ----
   n: node {
       PATH "nodes/example"
       CXX { PATH "src" FILENAME "n.cpp" }
   }
   --------------------------

Considering that path1.radl is in "/tmp/pathexample", the working
directory inside the region ``n`` is "/tmp/pathexample/nodes/example"
and the file referred by "n.cpp" is
"/tmp/pathexample/nodes/example/src/n.cpp"

:: 

   ---- file: path2.radl ----
   n: node {
       PATH "nodes/example"
       CXX { PATH "src" FILENAME "n.cpp" }
   }
   settings : module_settings {
       MODULE_BASE_PATH "/usr/pathexample"
   }
   --------------------------

By adding this ``module_settings`` value, "n.cpp" refers to
"/usr/pathexample/nodes/example/src/n.cpp".

Libraries
---------

Any user code needing libraries has to be declared as using a library
with the ``LIB`` field. This field allows two forms of libraries,
``cmake_library`` and ``static_library``.

Static library
~~~~~~~~~~~~~~

Static libraries are of the simplest form, gathering a set of source
files in their ``CXX`` field while the library header files are found
in the ``HEADER_PATHS`` paths.

Cmake library
~~~~~~~~~~~~~

The cmake library enables the use of arbitrarily complex libraries
since it is a user defined cmake script. The ``CMAKE_MODULE`` field
provide the cmake module name used to find it in the working
directory. ``COMPONENTS`` are the required components from this
module, used when calling the cmake ``find_module`` command. By
default, it is expected that the module defines two variables named
``${CMAKE_MODULE}_LIBRARIES`` and ``${CMAKE_MODULE}_INCLUDE_DIRS``
defining respectively the libraries to be linked against and the
include directories. Both variable names can be specified if their
naming doesn't follow this convention, respectively with the fields
``CMAKE_VAR_LIBRARIES`` and ``CMAKE_VAR_INCLUDE_DIRS``.

Typing
------

Inference
~~~~~~~~~

When a value is type annotated, it is checked to be of this type. If no
type annotation is provided, the kind of the value is extracted from 
the ones possible in the value declaration context. If there is an
ambiguity, it chooses the first relevant one in the order of declaration
in language.py_.

Checking
~~~~~~~~

User values are checked to be correct with their type with the
function ``check_type`` found in
language.py_.

Subtyping
~~~~~~~~~

Subtyping allows for example to use a 16bits integer (``int16``)
where a 32bits integer is required (``int32``). For now, subtyping is
only done on ``sized_types`` by allowing a type to be used in a
bigger version. ``sized_types`` and possible sizes are explicit in
language.py_. User values
are checked to fit the type's size with the function
``check_type_size``.

User code
=========

Compilation
-----------

Include directories
~~~~~~~~~~~~~~~~~~~

The generated code is setup so that user code is compiled with the
necessary include folders, i.e., the specified library header folders
and the working directory of the file references.

Compiler definitions
~~~~~~~~~~~~~~~~~~~~

The user code is compiled with the following definitions:

-  ``IN_RADL_GENERATED_CONTEXT`` : The basic definition to detect if the code is compiled within Radler compilation chain.
-  ``RADL_NODE_NAME`` : The name of the current radl node.
-  ``RADL_NODE_QNAME`` : Which is set to the node qname (with dot separators, for example "``modulename.nodename``").
-  ``RADL_MODULE_NAME`` : The name of the current radl module.
-  ``RADL_MODULE`` : A pointer to the current module ast root. 
-  ``RADL_HEADER`` : The radl generated header to be included by the user code (defining input and output data types).
-  ``RADL_STATE`` : The radl default name to be used for the C state type (if not specified in the radl file).
-  ``RADL_STEP_FUN`` : The default name to be used for the C step function (if not specified in the radl file).
-  ``RADL_INIT_FUN`` : The default name to be used for the C init function (if not specified in the radl file).
-  ``RADL_FINISH_FUN`` : The default name to be used for the C finish function (if not specified in the radl file).

C++ node definition
-------------------

Each node is a Mealy machine. The user provide a class which will be
instantiated with the default constructor to generate an instance
representing the state of the machine. Then, the ``step`` method of this
instance will be called to execute one step of the machine. The
signature of the ``step`` method is required to be:

:: 

    void step(const radl_in_t*, const radl_inflags_t*, radl_out_t*, radl_outflags_t*)

The four argument types are structures defined in the generated header
file.

The input structure ``radl_in_t``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This structure has one field per subscription of the node. The field
name is the radl name of the subscription. Each field is in turn a
structure reflecting the topic of the subscription, whose fields are
the name of the radl topic ``FIELDS``.

The output structure ``radl_out_t``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is similar to the input structure except that is is used by the
step function to publish its publications. To this effect, the step
function has to fill the output structure.

The flag structures ``radl_in_flags_t``, ``radl_out_flags_t``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Similarly to the input and output structures, these have a field for
each subscription (resp. publication). The type of each field is a
``radl_flags_t`` as described in
`radl\_flags.h`_.

.. _radl\_flags.h: https://github.com/SRI-CSL/radler/blob/master/radl_lib/include/radl_flags.h

C node definition
-----------------

This is the same as the C++ case, except that instead of a class, the user needs to
provide 4 things. To describe them, we use the default names provided by
radl, but those may be decided in the radl file.

-  A state type, that we call ``RADL_STATE`` here
-  An init function of signature : ``void RADL_INIT_FUN(RADL_STATE *)``
-  A step function of signature :
   ``void RADL_STEP_FUN(RADL_STATE *, const radl_in_t*, const radl_inflags_t*, radl_out_t*, radl_outflags_t*)``
-  A finish function of signature :
   ``void RADL_FINISH_FUN(RADL_STATE *)``

The flags
---------

Computation of the output flags
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The main idea of flags is to have some Boolean metadata attached to
messages, which by default propagate through nodes. To this effect,
the default value of the output flags of each publication of a node
are set to the logical OR of all the flags of its subscriptions,
equivalent to the following pseudocode:

:: 

   v = 0;
   for each s in subscriptions:
       v = v OR in_flags->s
   for each p in publications:
       out_flags->p = v

Then, the input flags are given to the step function as read-only
while the preset output flags are provided to the step function to
give it a chance to turn on or off the desired flags. So, if the step
function doesn't change the output flags, they will propagate the
input flags.

Computation of the input flag ``radl_STALE``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The so-called stale flag has the broad meaning that its associated
value isn't "fresh". More precisely, it either means that the
publisher of the value flagged it as stale (by automatic propagation
or by choice) or that no new message arrived since the last call to
the step function. In the latter case, the step function gets the
same input value (the mailbox hasn't changed) but it is flagged as
stale. To check if a subscription ``s`` is stale, one simply calls
``radl_is_stale(in_flags->s)`` which returns a Boolean.

Computation of the input flag ``radl_TIMEOUT``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The so-called timeout flag has the broad meaning that its associated
value has violated the timing constraints. More precisely, it either
means that the publisher of the value flagged it as timeout (by
automatic propagation or by choice) or that we haven't received a
message since period of the publisher plus the maxlatency. In the
latter case, timing constraints are exceeded and something unexpected
is happening. To check if a subscription ``s`` is timeout, one simply
calls ``radl_is_timeout(in_flags->s)`` which returns a Boolean.

Turning off/on output flags
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The function ``radl_turn_on`` is used to turn on a flag. For example
to turn on the stale flag of the publication ``p``, we would do:

:: 

   radl_turn_on(rald_STALE, &out_flags->p);

To turn off flags, the similar function ``rald_turn_off`` should be
used.

Introspection
-------------

To allow more robust and generic user code, it is possible to access
values defined in the radl description.

Modules root entries
~~~~~~~~~~~~~~~~~~~~

The generic way of doing so is to use the generated module root ast
access functions. For example if we want to read the radl value of
qname ``module1.x``, one will first call the ``radlast_module1``
function to get to the module root entry.

Shortcuts
~~~~~~~~~

Instead of needing to know the current module name and call the
corresponding root ast access function, one can use the provided
macro ``RADL_MODULE``. When writing a step function, one can directly
access the node it is used in by using the ``RADL_THIS`` macro.

Field access
~~~~~~~~~~~~

The generic rule is that fields of values are the names of the
declared value inside this value. This name is in turn

-  a pointer to the value (the generic case)
-  the value itself (for a ``topic``, a ``struct`` or inside them).

The ``DEFS`` field
~~~~~~~~~~~~~~~~~~

To allow the user to define values which are not radl relevant, but
that should be statically defined and shared, we added the ``DEFS``
field in the ``node`` and ``topic`` classes.

Example
~~~~~~~

Consider the following radl description: 

:: 

   ---- file: introspec.radl ----
   x : int32 1
   t : topic { FIELDS
       a : int32 2
   }
   n : node {
       DEFS
           y : int32 3
           s : struct { FIELDS
               z : int32 4
           }
       PATH working_dir "nodes/example"
       CXX { PATH "src" FILENAME "n.cpp" }
   }
   ----------------------------

In the user code, if one wants to get the value of ``x`` (1):

:: 

   *(radlast_introspec()->x)

or

:: 

   *(RADL_MODULE->x)

Note the indirection, since we are in the generic case, the field
``x`` is a pointer to its value. To access ``a``, since it is inside
a ``topic``, we don't need the indirection:

:: 

   RADL_MODULE->t.a

Note that ``t`` is a topic so it is not a pointer, its field are
accessed directly. This also applies to  any other value, for example
to read "nodes/example", one will do:

:: 

   *(RADL_MODULE->n->working_dir)

or, when writing the step function for ``n``:

:: 

   *(RADL_THIS->working_dir)

Note that in order to access this value, we gave it a name in the
radl description. Finally, to sum it up, to access ``z`` when
writing the step function of ``n``:

:: 

   RADL_THIS->s.z
