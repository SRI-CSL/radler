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

Created on June, 2014

@author: Léonard Gérard leonard.gerard@sri.com

'''

from collections import Callable

from radler.astutils.location import Location
from radler.radlr import infos

#TODO: 7 colorize output https://pypi.python.org/pypi/colorama

warning_as_errors = False
continue_when_errors = False
verbosity_level = 0

def _logn(n):
    def __logn(message):
        if verbosity_level >= n:
            if isinstance(message, Callable):
                message = message()
            print(message)
    return __logn

log_err   = _logn(-1)
log_warn  = _logn(0)
log1  = _logn(1)
log2  = _logn(2)
log3  = _logn(3)
log4  = _logn(4)

def _txt_format(kind, message, location):
    return "{}: {}: {}\n{}".format(location.compact_desc(), kind, message,
                                   location.outline())

def warning(message, location):
    """ Output a user warning (verbosity level of 0),
    then exit(-1) if warning_as_errors is set.)
    """
    log_warn(_txt_format('warning', message, location))
    if warning_as_errors:
        exit(-1)

def error(message, location):
    """Output a user error (verbosity level of -1),
    then exit(-1) unless continue_when_errors is set.
    """
    log_err(_txt_format('error', message, location))
    if not continue_when_errors:
        exit(-1)

def noloc():
    return Location(str(infos.source_file))

def error_noloc(message):
    """Same as error but without any provided location."""
    location = noloc()
    error(message, location)

def internal_error(message, location=None):
    """ Error message for internal errors, ideally this should never happens.
    """
    if location is None:
        location = noloc()
    raise Exception(_txt_format('=!= internal error =!=', message, location))

def internal_assert(v, message):
    if not v: internal_error(message)
