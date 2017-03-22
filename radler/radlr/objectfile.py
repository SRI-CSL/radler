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

Created on Jul, 2014

@author: Léonard Gérard leonard.gerard@sri.com
'''
import pickle

from radler.astutils.names import NonExistingIdent
from radler.radlr import infos, language
from radler.radlr.errors import warning, log_err, error_noloc
from radler.radlr.sanitize import update_idents


version = "0.6"

class Objectfile:
    def __init__(self, root_node):
        self.root_node = root_node
        self.ros_type_of_struct = infos.ros_type_of_struct
        self.c_typedecl = infos.c_typedecl
        self.lang_version = language.version
        self.obj_version = version
        self.radler_version = infos.radler_version
        self.publishers = infos.publishers
    def check_compat(self, filepath=None):
        #For now, compatibility requires exact version matching.
        filepath = ' ' + str(filepath) if filepath else ''
        try:
            if self.obj_version != version:
                log_err("Object file{} is version {} (current version is {})."
                    "".format(str(filepath), self.obj_version, version))
                return False
        except AttributeError:
            #We had an issue trying to read self.obj_version
            log_err("Object file{} is of unknown version."
                    "".format(str(filepath), self.obj_version, version))
            return False
        if self.lang_version != language.version:
                log_err("Object file{} has been created with language version {}"
                        " (current version is {})."
                        "".format(str(filepath), self.lang_version, language.version))
                return False
        if self.radler_version != infos.radler_version:
            log_err("Object file{} has been created with radler version {}"
                    " (current version is {})."
                    "".format(str(filepath), self.radler_version, infos.radler_version))
            return False
        return True
    def load_in_namespace(self, namespace, filepath):
        if not self.check_compat(filepath):
            error_noloc("Failed to load the object {}.".format(filepath))
        n = self.root_node
        # reroot node
        n._namespace.father = namespace
        # add node to the root namespace
        try: #verify we are adding a new name
            namespace.lookup_node(n._qname)
            warning("Loading {} is shadowing a previous definition of {}"
                    "".format(str(filepath), str(n._qname)))
        except: pass #everything is ok
        namespace.associate(n._qname, n)
        try:
            update_idents(self.root_node, namespace)
        except NonExistingIdent as e:
            error_noloc("Could not resolve the identifier {}.\n"
                        "Check that you loaded its module first."
                        "".format(e.ident))
    def module_name(self):
        return self.root_node._name
    def module_qname(self):
        return self.root_node._qname


def save(node, filepath):
    """Save a node in a file (Path object)
    """
    o = Objectfile(node)
    with filepath.open('wb') as f:
        pickle.dump(o, f)

def obj_open(filepath):
    """ Return the object from the object file.
    """
    with filepath.open('rb') as f:
        o = pickle.load(f)
    return o

def load(filepath):
    """Load a file (Path object) in the global namespace infos.root_namespace.
    """
    o = obj_open(filepath)
    o.load_in_namespace(infos.root_namespace, filepath)
    infos.ros_type_of_struct.update(o.ros_type_of_struct)
    infos.c_typedecl.update(o.c_typedecl)
    infos.loaded_modules.append(o.module_qname())
    infos.publishers.update(o.publishers)
