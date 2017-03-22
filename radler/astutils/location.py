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

class Location:
    """ A location is a segment in a file.
    """
    def __init__(self, filename='', filetext='', start=0, end=0):
        self.filename = filename
        self.filetext = filetext
        self.start = start
        self.end = end

    def _populate(self):
        """ Compute user readable properties.
            This is only needed when the location has to be output.
        """
        if not hasattr(self, 'multiline'):
            start = self.start
            end = self.end
            txt = self.filetext
            self.start_line = txt.count('\n', 0, start) + 1
            self.start_column = start - txt.rfind('\n', 0, start) - 1
            self.end_line = txt.count('\n', start, end) + self.start_line
            self.end_column = end - txt.rfind('\n', 0, end) - 1
            self.multiline = self.start_line != self.end_line

    def compact_desc(self):
        self._populate()
        r = '{}:{}:{}'.format(self.filename, self.start_line, self.start_column)
        return r

    def outline(self, margin='  '):
        t = self.filetext
        if not t:
            return ''
        (bl, bc) = (self.start_line, self.start_column)
        (el, ec) = (self.end_line, self.end_column)
        bbc = t.rfind('\n', 0, self.start) + 1
        eec = t.find('\n', self.end)
        if self.multiline: # Two+ liner
            bec = t.rfind('\n', 0, self.end) + 1
            ebc = t.find('\n', self.start)
            pref_bline = str(bl) + ':'
            bline = pref_bline + t[bbc : ebc]
            pref_eline = str(el) + ':'
            eline = pref_eline + t[bec : eec]
            buline = ' ' * (bc + len(pref_bline)) + '^' * (ebc - bbc - bc)
            euline = ' ' * (len(pref_bline)) + '^' * (ec)
            inter = '[...]\n' if (el - bl) > 2 else ''
            s = ("{margin}{bline}\n"
                 "{margin}{buline}\n"
                 "{margin}{inter}{eline}\n"
                 "{margin}{euline}\n"
                 "".format(**locals()))
        else: # One liner
            line = t[bbc : eec]
            uline = ' ' * (bc) + '^' * (ec - bc)
            s = "{margin}{line}\n{margin}{uline}\n".format(**locals())
        return s


    def __str__(self):
        """ Standard printing of location, especially used for error reporting
        It ends with a new line.
        """
        o = self.outline()
        (bl, bc) = (self.start_line, self.start_column)
        (el, ec) = (self.end_line, self.end_column)
        if self.multiline:
            h = "from line {bl} column {bc} to line {el} column {ec}:\n"
        else:
            h = "at line {bl}, column {bc}-{ec}:\n"
        return h.format(**locals()) + o
