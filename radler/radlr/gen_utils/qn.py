# This file is part of Radler.
#
# Radler is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Radler is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Radler.  If not, see <http://www.gnu.org/licenses/>.

'''
@license: GPLv3

Created on Dec, 2014

@author: Léonard Gérard leonard.gerard@sri.com

This file is used to track all the different namespaces used,
    to make sure that there is no possible collisions.

'''

from radler.astutils.names import QualifiedName
from radler.radlr import language
from radler.radlr.errors import internal_error


def qnify(f):
    """ Decorator used to permit to give either a qualname or something
    with a qualname stored in the '_qname' field, typically an ast node.
    """
    def l(qn, *args, **kargs):
        if not isinstance(qn, QualifiedName):
            try:
                qn = qn._qname
            except:
                internal_error("trying to get name of " + str(qn))
        return f(qn, *args, **kargs)
    return l


def mangle(qname, manglespace):
    return qname.mangle(language.forbidden_prefix, manglespace)

########
# Cmake target namespaces
########

@qnify
def cmake_ast(qn):
    """ Give the name of the target of the ast library of qn.
    qn is expected to be a module name.
    """
    return mangle(qn, 'ast')

@qnify
def cmake_user_src(qn):
    """ Give the name of the target of the user source code library of qn.
    qn is expected to be a module name.
    """
    return mangle(qn, 'usersrc')

@qnify
def cmake_initproc(qn):
    """ Give the name of the target of the init process of qn.
    qn is expected to be an operating system of some sort.
    """
    return mangle(qn, 'init')

@qnify
def cmake_main(qn):
    """ Give the name of the target of the main wrapper of node qn. """
    return mangle(qn, 'main')

@qnify
def cmake_userlib(qn):
    """ Give the name of the target of the library qn. """
    return mangle(qn, 'lib')

@qnify
def cmake_rosnode(qn):
    """ Give the name of the target of the ros node executable. """
    return mangle(qn, 'ros')


##############
# C Namespaces
##############

@qnify
def c_varname(qn):
    """ return the C variable name unique to this qn. """
    return mangle(qn, 'n')

@qnify
def c_typename(qn):
    """ return the C typename unique to qn. """
    return mangle(qn, 't')

@qnify
def c_main(qn):
    """ return the main function of the wrapper of the node qn. """
    return mangle(qn, 'main')

@qnify
def c_modinit(qn):
    """ return the module init function name of the module qn. """
    return mangle(qn, 'initmod')

@qnify
def c_astfun(qn):
    """ return the function name to used to access the ast of the module qn. """
    return 'radlast_' + qn.name()

@qnify
def c_ast_val(qn):
    """ return the "user way" of accessing an ast value from the C code.
    RMQ When used on topics for ex., it assumes that topics are not recursive,
    nor they can be inside a struct, since we consider all fields access
    to be indirections (shallow).
    """
    p = qn.pathwalk()
    r = "radlast_" + next(p) + "()->"
    fds = '->'.join(p)
    return r + fds

@qnify
def c_user_state(qn):
    """ return a user available unique name for a state type of node qn. """
    return mangle(qn, 'ustate')

@qnify
def c_user_step(qn):
    """ return a user available unique name for a step function of node qn. """
    return mangle(qn, 'ustep')

@qnify
def c_user_init(qn):
    """ return a user available unique name for a init function of node qn. """
    return mangle(qn, 'uinit')

@qnify
def c_user_finish(qn):
    """ return a user available unique name for a finish function of node qn. """
    return mangle(qn, 'ufinish')


@qnify
def c_kestrel_in_struct(qn):
    return mangle(qn, 'inst')
@qnify
def c_kestrel_out_struct(qn):
    return mangle(qn, 'outst')
@qnify
def c_kestrel_inflg_struct(qn):
    return mangle(qn, 'infst')
@qnify
def c_kestrel_outflg_struct(qn):
    return mangle(qn, 'outfst')




########
# Generated file namespaces
########

@qnify
def file_ast(qn, suffix='.h'):
    """ return the filename of the dumped ast of module qn. """
    return mangle(qn, 'ast') + suffix

########
# Catkin package namespaces
########

@qnify
def package_ast(qn):
    """ return the package name of the qn ast dump. """
    return mangle(qn, 'ast')


########
# ROS file namespaces
########

@qnify
def rosmsg(qn):
    """ return the ROS message filename used for topic qn. """
    return mangle(qn, 'rosmsg')
