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

We define the language used to describe an RADL grammar.
Any element not defined is taken from the rule_syntax of parsimonious,
that is 'regex', '_' (to denote meaning less elements and comments,
                      placed on the right of any leaf)

    RMQ the language doesn't support recursive definitions
'''

from parsimonious import Grammar
from parsimonious.grammar import rule_syntax
from radler.astutils.nodeutils import clean_node


meta_keywords = "class|type"

meta_rules = (rule_syntax +
    r"""
    meta = _ (clas / typ)* end

    clas = 'class' _ defKind field*
    field = symbol some_kind ('*' / '+' / '?' )? _
    typ = 'type' _ defKind 'REGEX' _ regex _

    ### Utils

    end = ~r"$"
    quoted = ('"' ~r'[^"]*' '"') / ("'" ~r"[^']*" "'")
    some_kind = kind ('/' _ kind)*
    kind = _basic_word _     # will be checked to be defined
    defKind = _basic_word _  # define a new kind
    symbol = _basic_word _   # is lower priority over kind
    """ +
    # basic_word begins with a letter and may contain numbers and '_'
    # but they should not be a meta_keyword
    r"""
    _basic_word = ~r"(?!({keywords})\b)[a-zA-Z][a-zA-Z0-9_]*"
    """.format(keywords=meta_keywords))
#    meta = _ (class / type / enum / struct)*
#    enum = 'enum' _ defKind '{' _ symbol* '}' _
#    struct = 'struct' _ defKind '{' _ (symbol ':' _ symbol)* '}' _


class MetaParser:
    def __init__(self, meta_rules=meta_rules):
        #TODO: 99 automatically insert the _ and end rules, or have literals..
        self.meta_grammar = Grammar(meta_rules, 'meta')
    def __call__(self, text):
        """ Parse a text following the meta grammar.
        @return: a cleaned tree without '_' and 'end' rules.
        """
        return clean_node(self.meta_grammar.parse(text),
                          to_prune=['_','end'],
                          txt_leaf=['_basic_word', 'regex'])

meta_parser = MetaParser()
