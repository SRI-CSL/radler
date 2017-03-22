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

Created on May, 2014

@author: Léonard Gérard leonard.gerard@sri.com
'''
from collections import OrderedDict
from contextlib import contextmanager
from itertools import takewhile, chain, repeat
from pathlib import Path
import builtins
import collections
import curses


class id_generator:
    @classmethod
    def gen_id(cls):
        store = '__'+cls.__name__+'_id_counter'
        y = getattr(cls, store, 1)
        setattr(cls, store, y+1)
        return y

class Bunch(object):
    def __init__(self, **kw):
        self.__dict__.update(kw)

def sbl(tab, s1, s2):
    """ Smart Break Line, breaking line and indenting only if s1 not empty """
    if s1:
        return s1 + '\n' + (' '*tab) + s2
    else:
        return s2

def str(o):
    """ Fix PEP 3140 -- str(container) should call str(item), not repr(item)
    PS: tuples are not affected by this 'bug'.
    """
    if isinstance(o, dict):
        l = ["{k} : {v}".format(k=str(k), v=str(v)) for (k, v) in o.items()]
        s = "{{{el}}}".format(el=', '.join(l))
        return s
    if isinstance(o, list):
        l = ["{k}".format(k=str(k)) for k in o]
        s = "[{el}]".format(el=', '.join(l))
        return s
    else:
        return builtins.str(o)


def listjoin(separator, iterable, prefix='', suffix=''):
    l = separator.join(str(i) for i in iterable)
    return (prefix + l + suffix) if l else ''


def uniquelines(s):
    return '\n'.join(set(s.splitlines()))

class DefaultDict(dict):
    """ A DefaultDict returns a default value for missing keys.
    To simplify the interface, the constructor can only be used to set the
    default value. Any dictionary filling has to be done through the """
    def __init__(self, default_value):
        self.__default_value = default_value
    def __getitem__(self, key):
        try:
            return super().__getitem__(key)
        except KeyError:
            return self.__default_value


def DictfromField(field, base_dict_class=dict):
    class D(collections.abc.MutableMapping):
        def __init__(self):
            self.data = base_dict_class()
        def __getitem__(self, key):
            return self.data.__getitem__(getattr(key, field, key))
        def __setitem__(self, key, val):
            return self.data.__setitem__(getattr(key, field, key), val)
        def __delitem__(self, key):
            return self.data.__delitem__(getattr(key, field, key))
        def __iter__(self):
            return self.data.__iter__()
        def __len__(self):
            return self.data.__len__()
    return D


#TODO: 8 BucketDict allow (indices: [0], ...) access.
class BucketDict(OrderedDict):
    """ A bucket dictionary is an ordered dictionary allowing to add mappings
        by storing them in lists:
    d = BucketDict()
    d.add('a', 1)
    assert(d == {'a': 1})
    d.add('a', 2)
    assert(d == {'a': [1, 2]})
    # keywords are executed before the initialization list
    d = BucketDict([('a', 1), ('b', 1)], a = 2)
    assert(d == {'a': [2, 1], 'b': 1})
    """
    def __init__(self, *args, **kargs):
        """ Keyword arguments will be added first """
        OrderedDict.__init__(self)
        self.append(*args, **kargs)

    def add(self, key, value):
        """ value may be a list of new mappings or simply a value."""
        try:
            v = self[key]
        except KeyError: #new mapping
            self[key] = list(value) if isinstance(value, list) else value
            return
        if isinstance(v, list):
            v.extend(value if isinstance(value, list) else [value])
        else:
            self[key] = [v] + value if isinstance(value, list) else [v, value]

    def append(self, *args, **kargs):
        if len(args) > 1:
            raise TypeError('expected at most 1 arguments, got %d' % len(args))
        for k, v in kargs.items():
            self.add(k, v)
        if args:
            if isinstance(args, dict):
                for (k, v) in args.values():
                    self.add(k, v)
            else: #waiting for (key, val) tuples
                for p in args[0]:
                    if len(p) != 2:
                        raise TypeError("expected (key, value) tuples,"
                                        "got %s" % str(p))
                    self.add(*p)
        return self


def common_path(*ps):
    """ Compute the common root of the paths *p. """
    def cmp(t):
        return all(t[i]==t[i+1] for i in range(len(ps)-1))
    try:
        return Path(*(p[0] for p in takewhile(cmp, zip(*(p.parts for p in ps)))))
    except TypeError:
        raise Exception("No common root for paths"
                        "(giving absolute paths would solve this issue).")

def relative_path(path, anchor):
    path = path.resolve().parts
    anchor = anchor.resolve().parts
    lp = len(path)
    la = len(anchor)
    m = min(lp, la)
    for i in range(m):
        if path[i] != anchor[i]:
            break
    else:
        i+=1
    return Path(*(chain(repeat('..', la-i), path[i:])))


def link_path(path, dest, is_directory=True, relative=False):
    """ Create a symlink to dest at path, unless dir is a valid file.
    If the destination is a directory, is_directory should be True.
    path is expected to be a pathlib Path object.
    """
    if not path.exists():
        if path.is_symlink():
            path.unlink() # path is a broken symlink
        if relative:
            dest = relative_path(dest, path.parent)
        path.symlink_to(dest, is_directory)

def ensure_dir(path):
    """{path} is expected to be a libpath.Path object"""
    if path.exists():
        if not path.is_dir():
            raise Exception("{} should be a directory".format(dir))
    else:
        ensure_dir(path.parent)
        path.mkdir()


def write_file(filepath, filecontent):
    d = filepath.parent
    ensure_dir(d)
    with filepath.open('w', encoding='UTF-8') as f:
        f.write(filecontent)


@contextmanager
def ncurse_stdscr():
    stdscr = curses.initscr()
    curses.noecho()
    curses.cbreak()
    stdscr.keypad(1)
    try:  # Try to use colors
        curses.start_color()
    except:
        pass
    try:
        yield stdscr
    finally:  # Clean up
        stdscr.keypad(0)
        curses.echo()
        curses.nocbreak()
        curses.endwin()

