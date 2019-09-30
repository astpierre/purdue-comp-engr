import os
import sys
import re
from pprint import pprint as pp

'''
  ----------------
  REFERENCE NOTES:
  ----------------
    abc...      letters
    123...      digits
    \d          any digit                       -> [0-9]
    \D          any NON-digit                   -> [^0-9]
    .           any character
    \.          period
    [ab-d]      one of 'a', 'b', 'c', or 'd'
    [^ab-d]     not 'a', 'b', 'c', nor 'd'
    \w          any alphanumeric character      -> [a-zA-Z0-9_]
    \W          any NON-alphanumeric character  -> [^a-zA-Z0-9_]
    {m}         m repetitions
    {m,n}       m to n (range) repetitions
    *           zero or more repetitions
    +           one or more repetitions
    ?           zero or one repetition (optional)
    \s          any whitespace                  -> [ \t\n\r\f\v]
    \S          any NON-whitespace character    -> [^ \t\n\r\f\v]
    ^...        start of string
    ...$        end of string
    (...)       capture group
    (a(bc))     capture sub-group
    (.*)        capture all
    (abc|def)   matches 'abc' or 'def'
    \b          word boundary
    re.match()      Determine if the RE matches at the beginning of the str
    re.search()     Scan thru str, looking for any location where RE matches
    re.findall()    Find all substrs where RE matches, return as list
'''

def extractArguments(commandline):
    pattern = r"[+\\]([a-z])\s([\w/]+)\b"
    match = re.findall(pattern, commandline)
    argValList = [m for m in match]
    return sorted(argValList)

def extractNumerics(sentence):
    pattern = r"([+-]?\d+[.]?\d{0,}[eE]?[+-]?\d{0,})\b"
    matches = re.findall(pattern, sentence)
    return matches


if __name__ == "__main__":
    # Tests for Q1
    command = "myScript.bash +v \i 2 +p /local/bin/somefolder +v \i 2 +p /local/bin/somefolder"
    pp(extractArguments(command))

    # Tests for Q2
    sentence = "abkaf 2.12 24 asdg4 asdg52.9 +2.1 +-0.0"
    pp(extractNumerics(sentence))
    sentence = "With the electron's charge being =-1.6022e-19, some choices you have are -110, -32.0 and +55. Assume that pi equals 3.1415, 'e' equals 2.7 and Na is +6.0221E+023."
    pp(extractNumerics(sentence))

