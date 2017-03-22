#!/usr/bin/env python3.4
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

Created on Aug, 2014

@author: Léonard Gérard leonard.gerard@sri.com

This script tries to test as much as possible the examples.

As a bare minimum, it tries to compile the examples.

All tests need to be documented in the tests section below.
'''



from collections import OrderedDict
from pathlib import Path
from random import randint
import os
import shutil
import subprocess
import sys

from tarjan import tarjan


def call(*args, **kargs):
    """Call a subprocess with subprocess.call but setup the pwd env var first.
    """
    os.putenv('PWD', os.getcwd())
    return subprocess.call(*args, **kargs)


class Atest:
    """ Class used to describe a test with its file, folder, dependencies, etc.
    """
    def __init__(self, file, failing, folder='.', deps=None, plant=None):
        if file[0:1].isnumeric():
            print("ERROR, tests can't begin with a num (for mangling)")
            exit(-1)
        self.file = file
        self.failing = failing
        self.folder = Path(folder)
        self.deps = deps if deps != None else []
        self.plant = plant
    @property
    def filepath(self):
        return self.folder / self.file
    @property
    def objfile(self):
        p = '_'.join(self.folder.parts)
        # Mangling is correct because names don't begin with numbers.
        return str(len(p)) + p + str(len(self.file)) + self.file + 'o'

class Good(Atest):
    """ Atest with failing set to False,
    file computed from name with radl extension
    folder appended with 'good/'
    """
    def __init__(self, name, folder='', **kw):
        Atest.__init__(self, name+'.radl', False, 'good/'+folder, **kw)

class GoodAlone(Good):
    """ Good test in its own folder with the same name. """
    def __init__(self, name, **kw):
        Good.__init__(self, name, name, **kw)

class Bad(Atest):
    """ Atest with failing set to True """
    def __init__(self, name, folder='', **kw):
        Atest.__init__(self, name+'.radl', True, 'bad/'+folder, **kw)



#-------------------------
# Declare tests here
#-------------------------


eddy_ip = Good('eddy_ip', plant='plant')
flags1 = Good('flags1', plant='plant')
ip = Good('ip', plant='plant')
ipc = Good('ipc', plant='plant')
ivc_certikos = Good('ivc_certikos', plant='plant')
ivc_lynxsecure = Good('ivc_lynxsecure', plant='plant')
test_alias = Good('test_alias')
test_alias2 = Good('test_alias2')
test_auth = Good('test_auth', plant='plant')
test_c1 = Good('test_c1', plant='plant')
test1 = Good('test1')
test2 = Good('test2', plant='plant')
test22 = Good('test22', plant='plant')
test3 = Good('test3', deps=[test_alias], plant='plant')
topic_dec = Good('topic_dec')
topic_struct = Good('topic_struct')
topic_struct1 = Good('topic_struct1')
type_sizes = Good('type_sizes')
type_sizes2 = Good('type_sizes2')
static_libraries = Good('static_libraries')

house_thermo = GoodAlone('house_thermo', plant='plant')
thermostat = GoodAlone('thermostat')



b_int8 = Bad('int8')
b_int8__129 = Bad('int8_-129')
b_int8_128 = Bad('int8_128')
b_uint8__1 = Bad('uint8_-1')
b_uint8_257 = Bad('uint8_256')
b_ident_type1 = Bad('ident_type')
b_ident_type2 = Bad('ident_type2')
b_ident_type3 = Bad('ident_type3')
b_ident_type_alias = Bad('ident_type_alias')


#-------------------------
# End of test declarations
#-------------------------



# Tarjan the tests, the result is an ordering of the cliques.

tests = dict((t, t.deps) for t in locals().values() if isinstance(t, Atest))
tj_tests = tarjan(tests)

# Flatten and error when circular dep of tests (a clique of more than one elt).

tests = []
for i in range(len(tj_tests)):
    if len(tj_tests[i]) != 1:
        print("ERROR, the tests {} have a circular dependency."
              "".format(str(tj_tests[i])))
        exit(-1)
    else:
        tests.append(tj_tests[i][0])

# Now tests is correctly sorted and ready to be used.

nb_tests = len(tests)
nd = len(str(nb_tests))

def clean_mkdir(path):
    if Path(path).exists(): shutil.rmtree(path)
    os.mkdir(path)

# Create and cd to a temporary directory
destination = base_dest = 'tmp'
while Path(destination).exists():
    destination = base_dest + str(randint(0, 99999999))
clean_mkdir(destination)
old_dir = os.getcwd()
os.chdir(destination)

# Make a catkin/src dir for catkin_make
clean_mkdir('catkin')
os.mkdir('catkin/src')


#####
# Compile the tests with radler.sh script

radler_errors = []
radler_skipped = []
radler_compiled = []

class Toskip(Exception): pass

log_file = Path()
i = 0
while log_file.exists():
    log_file = Path('../test' + str(i) + '.log')
    i += 1

log_file_d = log_file.open('w')
def log(msg):
    print("\n@@@@\n@@@@ "+msg+"\n@@@@", file=log_file_d, flush=True)

cpt = 0
report = ""
for t in tests:
    try:
        #Do not try to compile if some deps aren't met
        for d in t.deps:
            if not d in radler_compiled:
                raise Toskip
        #Deps are met
        cmd = ["../../radler.sh","--ws_dir", "catkin/src", "compile", "--ROS",
               "-o", t.objfile]
        for d in t.deps:
            cmd.extend(['-O', d.objfile])
        if getattr(t, 'plant', None):
            cmd.extend(['--plant', t.plant])
        cmd.append('../' + str(t.filepath))
        #Run it
        log("Test {} ({})".format(t.filepath, ' '.join(cmd)))
        r = call(cmd, stdout=log_file_d)
        if r and not t.failing: #We have an error
            radler_errors.append(t)
            msg = "\nFailed to compile {}".format(t.filepath)
            report += msg
            log(msg)
        elif not r and t.failing: #We should have failed
            radler_errors.append(t)
            msg = "\n{} Should have failed to compile".format(t.filepath)
            report += msg
            log(msg)
        else:
            if t.failing:
                log("Success (expected failure).")
            else:
                log("Success (correct compilation).")
            radler_compiled.append(t)
    except Toskip:
        radler_skipped.append(t)
        report += "\nSkipped {} because of {}".format(t.filepath, d.filepath)
    #Sum up to the user
    cpt +=1
    e = len(radler_errors)
    s = len(radler_skipped)
    c = len(radler_compiled)
    sys.stdout.write('\r{{:>{nd}}}/{{}} compiled with {{:>{nd}}} errors and ({{:>{nd}}} skipped)'.format(nd=nd).format(
                    cpt, nb_tests, e, s))
print()
if report:
    print("Report (see {} for full log):".format(log_file.name)+report)



#####
# Try to catkin make all the ROS package at once
clean = True
os.chdir('catkin')
try:
    r = call(['catkin_make'])
    cat_st = 'failed' if r else 'succeeded'
    print("Catkin {} to compile the {} generated ROS module.".format(
            cat_st, len(radler_compiled)))
    clean = input("\n\nDo you want to clean the temporary folder '" +
                  str(destination) + "' ? [Y/n]")
    if clean == 'n' or clean == 'N':
        clean = False
except FileNotFoundError:
    print("Could not find and run catkin_make.")


# Get out of the temporary directory and delete it
os.chdir(old_dir)
if clean: shutil.rmtree(destination)






