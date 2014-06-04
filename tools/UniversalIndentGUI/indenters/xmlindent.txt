WHAT IS IT?

  XML Indent is a XML stream reformatter written in ANSI C.  You can
  find the latest version here:

    - http://www.cs.helsinki.fi/u/penberg/xmlindent/

VERSION
  0.2.17

PLATFORMS

  Compiles and runs on most POSIX compatible systems.

MAINTAINER

  Pekka Enberg <penberg at iki dot fi>

CONTRIBUTORS

  Graham Barr, Peter Bray, Alexander Dupuy, Thomas Fischer, Markus
  Hjort, Aubin Paul, Brett Pemberton, Basile Starynkevitch, and Nicola
  S. Vitale.

LICENSE

  XML Indent is Free Software released under the GNU General Public
  License (GPL).  See the file LICENSE for details.

USAGE

  xmlindent [options] [filename] ...
  Options:
        -o <output>     Output file
        -i <indent>     Indent level
        -t              Use tabs instead of spaces for indent
        -l <max-cols>   Maximum columns for line wrapping
        -n <pos>        Suppress newline at position
        -f              Force newline on elements without children
        -h              Help
        -v              Version information
        -w              Overwrite original file
