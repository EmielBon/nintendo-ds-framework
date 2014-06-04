/*****************************************************************************
 * The contents of this file are subject to the RECIPROCAL PUBLIC LICENSE
 * Version 1.1 ("License"); You may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/rpl.php. Software distributed under the
 * License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND,
 * either express or implied.
 *
 * @product: phpStylist
 * @author:  Mr. Milk (aka Marcelo Leite)
 * @email:   mrmilk@anysoft.com.br
 * @version: 1.0
 * @date:    2007-11-22
 *
 *****************************************************************************/

CONTENTS
--------
Below you will find instructions on how to use phpStylist:

- Web Server Usage
- Command Line Mode
- PSPad Integration
- Command Line Options

==============================================================================

WEB SERVER USAGE
----------------

phpStylist runs as a single file on you web server. You don't need any special
module or library. It has been tested with php from 4.4.2 to 5.2.2.

Save phpStylist.php to your web server folder and start it from the browser.
For example, http://localhost/phpStylist.php.

On the left menu, you will see more than 30 options that you can use to adjust
the application to your coding style. All options are sticky based on cookies.
Select one of your files or click on the button "Use Sample" and try each
option to see what it is all about.

If you want to type in or paste code directly into the app, first click on the
option "SHOW EDITABLE TEXT BOX". The right panel will then become editable.

COMMAND LINE MODE
-----------------

You can also use phpStylist through the command line to automatically format
local files. You will still need php installed.

First, find the exact location of you php.exe and the exact location where you
placed phpStylist. Let's say they are in
"C:\Program Files\PHP\php.exe" and "C:\Program Files\Apache\htdocs\phpStylist.php"

You then must run php passing phpStylist.php along with the -f argument. At
this point the command line would be like this:
"C:\Program Files\PHP\php.exe" -f "C:\Program Files\Apache\htdocs\phpStylist.php"

But that's not all. You also need to add the full path of the source file you
want to format and the options you want to be used. For each of those 34 options
you see on the web server usage, there will be an option on the command line.
You can use the "--help" option to see a list of options.

Use the --help switch to see all options (full list at the end of this file):
"C:\Program Files\PHP\php.exe" -f "C:\Program Files\Apache\htdocs\phpStylist.php" --help

The first phpStylist paramenter MUST be the source file name you want to
format. After the file name, you can add as many options as you want, in any
order. It can get pretty big, but it works. Another example:
"C:\Program Files\PHP\php.exe" -f "C:\Program Files\Apache\htdocs\phpStylist.php"
"C:\Program Files\Apache\htdocs\source_file_to_format.php" --space_after_if
--indent_case --indent_size 4 --space_after_comma --line_before_function

Output will be to STDOUT, so if you want to send it to a file, append "> filename"
at the end of the command line. In our above example:
"C:\Program Files\PHP\php.exe" -f "C:\Program Files\Apache\htdocs\phpStylist.php"
"C:\Program Files\Apache\htdocs\source_file_to_format.php" --space_after_if
--indent_case --indent_size 4 --line_before_comment_multi --vertical_array
--line_before_function > "C:\Code Library\Formatted Code\destination_file.php"

Don't forget the quotes around long file names.

PSPAD INTEGRATION
-----------------
PSPad is a popular, powerful and free code editor. It can be extended through
scripting. I have also created a script that will automatically format php code
from inside the editor. In fact, the script runs phpStylist in command line
mode, sending the current editor file name. It then get the results and replace
the code in the editor.

Save the file phpStylist.js to your PSPad javascript folder, usually
C:\Program Files\PSPad\Script\JScript.

Open the phpStylist.js file and edit the first two variables:
	php_path     = "C:\\Program Files\\xampp\\php\\php.exe";
	stylist_path = "C:\\Program Files\\xampp\\htdocs\\phpStylist.php";
	
Replace the paths with the appropriate for your system. Don't forget to double
backslashes.

You will also see all the options, some are commented out, some are active (the
current setup is the one I use). Simply comment out or uncomment the options
you want to use and save the file. Restart PSPad or use the the option Scripts,
Recompile Scripts.

Now, just open a php file on the editor and select phpStylist from the menu.
That's all. You can also select some block of code before using the option so
you can reformat only that portion. Of course, try to select a full block such
as a function.

If you don't use PSPad or don't want the integration you don't need the file
phpStylist.js.

FULL LIST OF OPTIONS
--------------------

Indentation and General Formatting:
--indent_size n                    n characters per indentation level
--indent_with_tabs                 Indent with tabs instead of spaces
--keep_redundant_lines             Keep redundant lines
--space_inside_parentheses         Space inside parentheses
--space_outside_parentheses        Space outside parentheses
--space_after_comma                Space after comma

Operators:
--space_around_assignment          Space around = .= += -= *= /= <<<
--align_var_assignment             Align block +3 assigned variables
--space_around_comparison          Space around == === != !== > >= < <=
--space_around_arithmetic          Space around - + * / %
--space_around_logical             Space around && || AND OR XOR << >>
--space_around_colon_question      Space around ? :

Functions, Classes and Objects:
--line_before_function             Blank line before keyword
--line_before_curly_function       Opening bracket on next line
--line_after_curly_function        Blank line below opening bracket
--space_around_obj_operator        Space around ->
--space_around_double_colon        Space around ::

Control Structures:
--space_after_if                   Space between keyword and opening parentheses
--else_along_curly                 Keep else/elseif along with bracket
--line_before_curly                Opening bracket on next line
--add_missing_braces               Add missing brackets to single line structs
--line_after_break                 Blank line after case "break"
--space_inside_for                 Space between "for" elements
--indent_case                      Extra indent for "Case" and "Default"

Arrays and Concatenation:
--line_before_array                Opening array parentheses on next line
--vertical_array                   Non-empty arrays as vertical block
--align_array_assignment           Align block +3 assigned array elements
--space_around_double_arrow        Space around double arrow
--vertical_concat                  Concatenation as vertical block
--space_around_concat              Space around concat elements

Comments:
--line_before_comment_multi        Blank line before multi-line comment (/*)
--line_after_comment_multi         Blank line after multi-line comment (/*)
--line_before_comment              Blank line before single line comments (//)
--line_after_comment               Blank line after single line comments (//)
