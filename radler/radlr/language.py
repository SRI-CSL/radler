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

import decimal

from radler.astutils.tools import DefaultDict
from radler.radlr.errors import internal_error, error


version = 'RADL 0.989'

extra_keywords = {
#C++ keywords
'alignas', 'alignof', 'and', 'and_eq', 'asm', 'auto', 'bitand', 'bitor',
'bool', 'break', 'case', 'catch', 'char', 'char16_t', 'char32_t', 'class',
'compl', 'const', 'constexpr', 'const_cast', 'continue', 'decltype', 'default',
'delete', 'do', 'double', 'dynamic_cast', 'else', 'enum', 'explicit', 'export',
'extern', 'false', 'float', 'for', 'friend', 'goto', 'if', 'inline', 'int',
'long', 'mutable', 'namespace', 'new', 'noexcept', 'not', 'not_eq', 'nullptr',
'operator', 'or', 'or_eq', 'private', 'protected', 'public', 'register',
'reinterpret_cast', 'return', 'short', 'signed', 'sizeof', 'static',
'static_assert', 'static_cast', 'struct', 'switch', 'template', 'this',
'thread_local', 'throw', 'true', 'try', 'typedef', 'typeid', 'typename',
'union', 'unsigned', 'using', 'virtual', 'void', 'volatile', 'wchar_t',
'while', 'xor', 'xor_eq',
#Usual macro definitions non commencing with __
'linux', 'unix'
}

forbidden_prefix = "radl"

defs = r"""
type int8
    REGEX ~r"(?P<value>(\b|[+-])\d+)\b(?!\.)"

type uint8
    REGEX ~r"\b(?P<value>\d+)\b(?!\.)"

type int16
    REGEX ~r"(?P<value>(\b|[+-])\d+)\b(?!\.)"

type uint16
    REGEX ~r"\b(?P<value>\d+)\b(?!\.)"

type int32
    REGEX ~r"(?P<value>(\b|[+-])\d+)\b(?!\.)"

type uint32
    REGEX ~r"\b(?P<value>\d+)\b(?!\.)"

type int64
    REGEX ~r"(?P<value>(\b|[+-])\d+)\b(?!\.)"

type uint64
    REGEX ~r"\b(?P<value>\d+)\b(?!\.)"

type float32
    REGEX ~r"(?P<value>(\b|[+-])(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?)\b(?!\.)"

type float64
    REGEX ~r"(?P<value>(\b|[+-])(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?)\b(?!\.)"

type bool
    REGEX ~r"\b(?P<value>true|false)"

type string
    REGEX ~r'"(?P<value>[^"]*)"'

type duration
    REGEX ~r"(?P<value>(\b|[+-])\d+)(?P<unit>sec|msec|usec|nsec)"

type time
    REGEX ~r"(?P<value>\b\d+)(?P<unit>sec|msec|usec|nsec)"

type ip
    REGEX ~r"\b(?P<value>\d\d?\d?\.\d\d?\d?\.\d\d?\d?\.\d\d?\d?)\b"


class module_settings
    MODULE_BASE_PATH string ?
    PATH string ?
    HEADER string ?
    FILENAME string *
    LIB cmake_library/static_library *
    POST_INIT_HOOK string ?

class cxx_class
    PATH string ?
    HEADER string
    FILENAME string *
    LIB cmake_library/static_library *
    CLASS string
    STEP_METHOD string ?

class cxx_file
    PATH string ?
    FILENAME string *
    LIB cmake_library/static_library *


class c_class
    PATH string ?
    HEADER string
    FILENAME string *
    LIB cmake_library/static_library *
    TYPENAME string ?        #defaults to the radl defined RADL_STATE macro
    INIT_FUNCTION string ?   #defaults to the radl defined RADL_INIT_FUN macro
    STEP_FUNCTION string ?   #defaults to the radl defined RADL_STEP_FUN macro
    FINISH_FUNCTION string ? #defaults to the radl defined RADL_FINISH_FUN macro

class cmake_library
    PATH string ?
    CMAKE_MODULE string
    CMAKE_COMPONENTS string *
    CMAKE_VAR_LIBRARIES string ?     #defaults to {CMAKE_MODULE}_LIBRARIES
    CMAKE_VAR_INCLUDE_DIRS string ?  #defaults to {CMAKE_MODULE}_INCLUDE_DIRS

class static_library
    PATH string ?
    HEADER_PATHS string *
    CXX cxx_file *

class external_rosdef
    PATH string ?
    FULLNAME string
    HEADER string ?

class struct
    FIELDS int8/uint8/int16/uint16/int32/uint32/int64/uint64/
           float32/float64/
           bool/struct/array/duration/time +
    EXTERNAL_ROS_DEF external_rosdef ?
    DEFS int8/uint8/int16/uint16/int32/uint32/int64/uint64/
           float32/float64/bool/struct/array/duration/time/string *

class array
    TYPE string ?
    SIZE uint64 ?
    VALUES int8/uint8/int16/uint16/int32/uint32/int64/uint64/
           float32/float64/
           bool/struct/array/duration/time*

class topic
    #Pay attention to the order of the types, parsing higher priority first
    FIELDS int8/uint8/int16/uint16/int32/uint32/int64/uint64/
           float32/float64/
           bool/struct/array/duration/time +
    EXTERNAL_ROS_DEF external_rosdef ?
    DEFS int8/uint8/int16/uint16/int32/uint32/int64/uint64/
           float32/float64/bool/struct/array/duration/time/string *

class publication
    TOPIC topic
    EACH uint32 ?

class subscription
    TOPIC topic
    MAXLATENCY duration

class node
    PATH string ?
    PUBLISHES publication *
    SUBSCRIBES subscription *
    CXX cxx_class ?
    C c_class ?
    PERIOD duration
    WCET duration ?
    DEVICES device_interface *
    DEFS int8/uint8/int16/uint16/int32/uint32/int64/uint64/
           float32/float64/bool/struct/array/duration/time/string *


class device_interface
    HEADER string ?
    CXX cxx_file *
    DEFS int8/uint8/int16/uint16/int32/uint32/int64/uint64/
           float32/float64/bool/struct/array/duration/time/string *

################
# Physical description
################

class processor
    TYPE string
    BITS int8
    ENDIANESS string

class device
    IMPLEMENTS device_interface
    REQUIRES_LINUX bool
    CXX cxx_file *

class bus
    ENDPOINTS processor/device *


class disk_image
    IMG string


################
# Mapping
################

class plant
    MACHINES machine *

##
# Machine level

class machine
    OS linux/lynxsecure/certikos

##
# Hypervisor level

class lynxsecure
    VMS lynxsecure_vm *

class certikos
    VMS certikos_vm *


##
# Virtual machine level

class lynxsecure_vm
    OS linux

class certikos_vm
    OS linux

##
# System level

class linux
    NODES_UID uint16
    IP ip ?
    IMG string ?
    NODES node *

"""


sized_types = {
    # sizes are expected to be increasing.
    'int'  : [8, 16, 32, 64],
    'uint' : [8, 16, 32, 64],
    'float': [32, 64],
}

def int_fits(value, size):
    #Python ints are arbitrary precision, so we can simply do this.
    return -2**(size-1) <= int(value) < 2**(size-1)

def uint_fits(value, size):
    #Python ints are arbitrary precision, so we can simply do this.
    return 0 <= int(value) < 2**size

# The decimal module doesn't seem to conform exactly to IEEE 754, but anyway,
# the conversion from a string isn't well specified in IEEE 754.
context_IEEE_754_float32 = decimal.Context(
    prec=24,
    rounding=decimal.ROUND_HALF_EVEN,
    Emin=-126,
    Emax=127,
    capitals=1, clamp=0, flags=[], traps=[]
)
context_IEEE_754_float64 = decimal.Context(
    prec=53,
    rounding=decimal.ROUND_HALF_EVEN,
    Emin=-1022,
    Emax=1023,
    capitals=1, clamp=0, flags=[], traps=[]
)

context_IEEE_754_float128 = decimal.Context(
    prec=113,
    rounding=decimal.ROUND_HALF_EVEN,
    Emin=-16382,
    Emax=16383,
    capitals=1, clamp=0, flags=[], traps=[]
)

def float_fits(value, size):
    d = decimal.Decimal(value)
    if size == 32:
        return d.normalize() == d.normalize(context=context_IEEE_754_float32)
    if size == 64:
        return d.normalize() == d.normalize(context=context_IEEE_754_float64)
    if size == 128:
        return d.normalize() == d.normalize(context=context_IEEE_754_float128)
    raise internal_error("Trying to fit a float of size {}".format(size))

check_type_size = {
    'int'   : int_fits,
    'uint'  : uint_fits,
    'float' : float_fits,
}

def wrap_fit_to_check(fun, t, size):
    def f(value, loc):
        try:
            if not fun(value, size):
                error("The value {} doesn't fit in the {}bits of {}."
                      "".format(str(value), size, t), loc)
        except ValueError:
            error("A value of type {} is expected."
                  "".format(t), loc)
    return f

check_type = {
    'int8'    : wrap_fit_to_check(int_fits, 'int8', 8),
    'int16'   : wrap_fit_to_check(int_fits, 'int16', 16),
    'int32'   : wrap_fit_to_check(int_fits, 'int32', 32),
    'int64'   : wrap_fit_to_check(int_fits, 'int64', 64),
    'uint8'   : wrap_fit_to_check(uint_fits, 'uint8', 8),
    'uint16'  : wrap_fit_to_check(uint_fits, 'uint16', 16),
    'uint32'  : wrap_fit_to_check(uint_fits, 'uint32', 32),
    'uint64'  : wrap_fit_to_check(uint_fits, 'uint64', 64),
    'float32' : wrap_fit_to_check(float_fits, 'float32', 32),
    'float64' : wrap_fit_to_check(float_fits, 'float64', 64),
}


####
# Value and type mapping
#
# Here we define how radl types and values are mapped to different backends.
# The default behavior is to not do anything and output the value as a string.
####

_default_typemap = {'C': 'char*', 'ROS': 'string'}

type_mapping = DefaultDict(_default_typemap)
type_mapping.update((
    ('int8'    , {'C': 'int8_t'         , 'ROS': 'int8'   }),
    ('int16'   , {'C': 'int16_t'        , 'ROS': 'int16'  }),
    ('int32'   , {'C': 'int32_t'        , 'ROS': 'int32'  }),
    ('int64'   , {'C': 'int64_t'        , 'ROS': 'int64'  }),
    ('uint8'   , {'C': 'uint8_t'        , 'ROS': 'uint8'  }),
    ('uint16'  , {'C': 'uint16_t'       , 'ROS': 'uint16' }),
    ('uint32'  , {'C': 'uint32_t'       , 'ROS': 'uint32' }),
    ('uint64'  , {'C': 'uint64_t'       , 'ROS': 'uint64' }),
    ('float32' , {'C': 'float'          , 'ROS': 'float32'}),
    ('float64' , {'C': 'double'         , 'ROS': 'float64'}),
    ('bool'    , {'C': 'uint8_t'        , 'ROS': 'bool'   }),
    ('duration', {'C': 'radl_duration_t', 'ROS': 'int64'  }),
    ('time'    , {'C': 'radl_duration_t', 'ROS': 'int64'  }),
))


#When outputting a value as a string (the default) we need to quote it.
def _quote_value(value): return '"'+value+'"'
_default_quote = {'C': _quote_value, 'ROS': _quote_value}

#Most of the times the radl syntax is the same as the backends one.
def _inline_value(value): return value
_default_inline = {'C': _inline_value, 'ROS': _inline_value}

def _bool_convert_C(value):
    if value == 'false':
        return '0'
    elif value == 'true':
        return '1'
    else:
        internal_error("incorrect boolean value")
_bool_mapping = {'C': _bool_convert_C, 'ROS': _inline_value}

value_mapping = DefaultDict(_default_quote)
value_mapping.update((
    ('int8'    , _default_inline),
    ('int16'   , _default_inline),
    ('int32'   , _default_inline),
    ('int64'   , _default_inline),
    ('uint8'   , _default_inline),
    ('uint16'  , _default_inline),
    ('uint32'  , _default_inline),
    ('uint64'  , _default_inline),
    ('float32' , _default_inline),
    ('float64' , _default_inline),
    ('bool'    , _bool_mapping),
    ('duration', _default_inline),
    ('time'    , _default_inline),
))

_interpret_value_map = DefaultDict(lambda x:x)
_interpret_value_map.update((
    ('int8'    , int),
    ('int16'   , int),
    ('int32'   , int),
    ('int64'   , int),
    ('uint8'   , int),
    ('uint16'  , int),
    ('uint32'  , int),
    ('uint64'  , int),
    ('float32' , float),
    ('float64' , float),
    ('bool'    , lambda x: False if x == 'false' else True),
    ('duration', int),
    ('time'    , int),
))

def interpret_value(t, value):
    return _interpret_value_map[t](value)


def main_unit(v): return v
def sec2nsec(sec):   return str(int(sec) *1000000000)
def msec2nsec(msec): return str(int(msec)*1000000)
def usec2nsec(usec): return str(int(usec)*1000)

unit_normalize = {
    'duration': {'nsec': main_unit, 'sec' : sec2nsec,
                 'msec': msec2nsec, 'usec': usec2nsec},
    'time'    : {'nsec': main_unit, 'sec' : sec2nsec,
                 'msec': msec2nsec, 'usec': usec2nsec},
    }


#TODO: 2 test common flag handling
#TODO: 2 write a example to stress certikos (one with usb NIC and one with joystick).

#TODO: 3 Seperate compilation of each system.
#TODO: 3 Fix the getdate+Certikos to ensure time sync within a boundary.

#TODO: 5 Scheduling should take WCET into account
#TODO: 4 integrate the monitoring branch

#TODO: 6 generate firewall rules
#TODO: 6 check connectivity and maxlatencies (includes WCET and scheduling so that the computation is simply T + maxlatency what ever is the scheduling)
#TODO: 7 min and max period
#TODO: 8 what is needed to decide if marshalling is necessary? see processor
#TODO: 8 how to handle gracefully the float/double size issue? see radl_lib
#TODO: 8 allow subtyping with alias x : int8 0  y : int16 = x
