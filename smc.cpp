/**********************************************************\
|* Assignment 2: Sequence Machine Compiler / Interpreter. *|
|*                                                        *|
|* Written by Bryce Summers                               *|
|* Development started on 9.26.2020                       *|
|* Assignment released on 9.30.2020.                      *|
|* last modified on 11.4.2020. (version 1.1)              *|
|*                                                        *|
|* ITP - 132, Fall 2020                                   *|
\**********************************************************/

/**********************************************************\
|* Instructions:                                          *|
|*                                                        *|
|*  - Look at the box further down in the program that    *|
|*    states: "STUDENT CODE BEGINS HERE"                  *|
|*                                                        *|
|*     (search for checkSyntaxError1 function)            *|
|*                                                        *|
|*    Line #1935 As of 9:26 pm on November 4th, 2020      *|
|*                                                        *|
|*                                                        *|
|*  - Do NOT modify the code ABOVE that box.              *|
|*                                                        *|
|*  - You MAY modify the code BELOW that box.             *|
|*    Implement each error / warning function such that   *|
|*    if the text data coming in through an istream       *|
|*    contains the error, it logs the correct error       *|
|*    message to the outgoing string stream.              *|
|*                                                        *|
|*    The correct way to log an error should already be   *|
|*    mentioned in your starter code within a comment.    *|
|*                                                        *|
|*    Note: Some functions will receive 1 LINE of code    *|
|*          and others will receive a stream to the       *|
|*          entire program, which may have multiple       *|
|*          lines. (all CODE)                             *|
|*                                                        *|
|*    Note: To log line numbers                           *|
|*          stream the line number to the out stream      *|
|*          stream a new line character                   *|
|*          stream the error code.                        *|
|*    Example: In the checkWarning1 function, warning1    *|
|*             should be logged:                          *|
|*             out << line_number << '\n' << R1 << endl;  *|
|*                                                        *|
|*          See the runSequenceMachineProgram for an      *|
|*          example of how to calculate line numbers when *|
|*          working with an entire multiple line program. *|
|*                                                        *|
|*          For the single line functions, you don't      *|
|*          need to worry about this.                     *|
|*                                                        *|
\**********************************************************/

/**********************************************************\
|*                                                        *|
|* GRADING                                                *|
|*                                                        *|
|*  - When I eventually test and grade your code, I will  *|
|*    use your code below the box and will ignore your    *|
|*    code above the box, replacing it with either the    *|
|*    original code or modified code containing a         *|
|*    different set of tests. ('Secret tests')            *|
|*                                                        *|
|* Your work will be evaluated across 3 main areas.       *|
|*                                                        *|
|*  1 I will personally look at your code to see if how   *|
|*    it looks and that you have not 'gamed' the system.  *|
|*                                                        *|
|*    Does it look like you learned something?            *|
|*    Or, does it look like you've demonstrated your      *|
|*    knowledge?                                          *|
|*                                                        *|
|*  Assuming your work seems to be done in good faith...  *|
|*                                                        *|
|*  2 I will test your code against the unit tests I have *|
|*    given you. This is a test of how well you can       *|
|*    follow the empical / example specification.         *|
|*                                                        *|
|*  3 Your work will be tested against a set of 'secret'  *|
|*    tests that I will not share with you beforehand.    *|
|*                                                        *|
|*    This is a test of whether you are able to follow    *|
|*    the rational / formal description in the pdf.       *|
|*                                                        *|
|*    Does your code truly do what is expected or does    *|
|*    it overfit to the known tests?                      *|
|*                                                        *|
\**********************************************************/


/**********************************************************\
|*                                                        *|
|* Good Luck and please try your best!                    *|
|*                                                        *|
|* You don't need to implement everything to get a fine   *|
|* grade, focus on trying to practice various fundamental *|
|* structured programming skills like variables, if       *|
|* statements, while loops, booleans, int, and strings    *|
|*                                                        *|
\**********************************************************/





// Useful website that lists the standard capabilities
// of input file streams:
// http://www.cplusplus.com/reference/fstream/ifstream/
// Use C++ 11 when compiling.

// reading from a String.
#include <string>   // String variables and concatenation.
#include <sstream>  // std::stringstream

// reading a text file
#include <iostream> // Input / Output Streams
#include <fstream>  // File Streams.

#include <sys/stat.h> // Creating IO folder.

// ifstream: input from file.
// ofstream: output to file.
// fstream: input and output.



using namespace std; // Try removing this line and finding
                     // all of the datatypes that come
                     // from std, add std:: prefixes to
                     // each of them.

// Location of files.
const string INPUT_FILE_PATH   = "./io/input.txt";
const string INPUT_FILE_PATH2  = "./input.txt"; // back up.
const string OUTPUT_FILE_PATH  = "./io/output.txt";
const string OUTPUT_FILE_PATH2  = "./output.txt"; // back up.


// Sequence Machine Compiler Error message

// Syntax errors.
const string OK  = "";//Success\n"; // No error outputted for OK / good code.
const string S1  = "S1 : First letter of the line is not recognized.";
const string S2  = "S2 : Instruction not recognized. "
                        "(Capitalization is not the issue)\n     "
                        "Your instruction may be missing keywords "
                        "or be misspelled.";
const string S3  = "S3 : Comment needs 2 slashes, not 1.";
const string S4  = "S4 : Comment should use '/', rather than '\\'";
const string S5  = "S5 : Add another quote to the char literal.\n"
                   "     (Literal needs terminating ' character)";
const string S6  = "S6 : Backslash literal must be escaped. '\\'.";
const string S7  = "S7 : Character literal too large.\n"
                   "     Remove character from char literal.";
const string S8  = "S8 : A line must end with a semicolon ';'\n"
                   "     Multi-line statements are prohibited.";
const string S9  = "S9 : Don't capitalize syntax word(s)";
const string S10 = "S10: Add a right parens ')' character";
const string S11 = "S11: Add a left parens '(' character";

// Compiler errors.
const string C1  = "C1 : IO function variable misspelled,\n"
                   "     Try writing the variable name in lowercase.";
const string C2  = "C2 : read wants character data, not a "
                        "character stream, \n     try adding \"()\".";
const string C3  = "C3 : Variable name not found,\n     Try using "
                        "known variables like \"input\" or "
                        "\"output\"";

// Runtime Errors.
const string R1  = "R1 : Read at least once before writing,\n"
                   "     otherwise there is nothing to write!";
const string R2  = "R2 : Input Out of Bounds, don't read from the input\n"
                   "     when the input sequence is empty or exhausted\n"
                   "     Input line should begin: \"// IN: \" (Capital)\n";

// Style Errors.
const string L1  = "L1 : Do not indent Sequence Machine code.";
const string L2  = "L2 : Do not use extra spaces";
const string L3  = "L3 : Add one space before \"//\"";
const string L4  = "L4 : Add one space after \"//\"";
const string L5  = "L5 : Use space (' '), rather than tab ('\t') "
                        "characters.";
const string L6  = "L6 : Document your code with // comments!";
const string L7  = "L7 : Use less blank lines, did you copy your "
                        "code from a wysiwyg\n"
                   "     editor like Canvas or microsoft word into "
                        "a text editor?";

// Warnings.
const string W1  = "WARNING 1 : Useless Sequence Machine Instruction,\n"
                   "            you can delete this line.";
const string W2  = "WARNING 2 : In many languages, the \\ character "
                               "means this line \n"
                   "            will continue onto the next line. "
                               "Please remove it.";

const string W3  = "WARNING 3 : Use Single Quotes '\\'' "
                               "for char literals.";

// -- Library Function Declarations. ---------------------------

// -- Examples broken up into functions.
void testInputFunctions();
void testInput_AND_OutputFunctions();

// -- Input.
bool openFile(ifstream & input_file, string filepath);
void readByWord(ifstream & input_file);
void readByLine(ifstream & input_file);
// Delimit input by letter n and line breaks.
void readByletterN(ifstream & input_file);
void readByChar(ifstream & input_file);
void closeFile(ifstream & input_file);

// -- Output.
bool openFile(ofstream & output_file, string filepath);
void writeToFile(ofstream & output_file, string data);
void redirectCoutToFile(ofstream & output_file);
void redirectCoutToStringStream(stringstream & stringStream);
void resetSTDOutput();
void closeFile(ofstream & output_file);



void rewindStream(istream & code);
void printAllFullErrorMessages();
string id(const string error_message);

// Error Bitset bits. Used to specify which checks to perform.
const int SYNTAX   = 1 << 0;
const int COMPILE  = 1 << 1;
const int RUN      = 1 << 2;
const int WARNINGS = 1 << 3;
const int STYLE    = 1 << 4;
const int ALL = SYNTAX | COMPILE | RUN | WARNINGS | STYLE;
const int NONE = 0;

// Level bits.
const int LVL1     = 1 << 5;
const int LVL2     = 1 << 6;
const int LVL3     = 1 << 7;
const int LVL4     = 1 << 8;

const int ALL_LVLS = LVL1 | LVL2 | LVL3 | LVL4;

// -- Sequence Machine Compiler Functions
void compileSequenceMachineProgram(istream &code, stringstream & out, bool verbose = true, int whichChecks = ALL);

// -- Sub Functions.
void checkForSyntaxErrors (istream & code, stringstream & out);
void checkForcompileErrors(istream & code, stringstream & out);
void checkForWarnings     (istream & code, stringstream & out);

// If no Syntax or compile errors are found.
// Runs the code, outputs either a runtime error or the
// correct output string computed from the input string.
void runSequenceMachineProgram(istream & code, stringstream & out);
void checkForStyleErrors(istream & code, stringstream & out);


// individual Syntax Error checks.
void checkSyntaxError1  (istream & line, stringstream & out);
void checkSyntaxError2  (istream & line, stringstream & out);
void checkSyntaxError3  (istream & line, stringstream & out);
void checkSyntaxError4  (istream & line, stringstream & out);
void checkSyntaxError5  (istream & line, stringstream & out);
void checkSyntaxError6  (istream & line, stringstream & out);
void checkSyntaxError7  (istream & line, stringstream & out);
void checkSyntaxError8  (istream & line, stringstream & out);
void checkSyntaxError9  (istream & line, stringstream & out);
void checkSyntaxError10 (istream & line, stringstream & out);
void checkSyntaxError11 (istream & line, stringstream & out);

// individual compiler error checks.
void checkCompileError1 (istream & line, stringstream & out);
void checkCompileError2 (istream & line, stringstream & out);
void checkCompileError3 (istream & line, stringstream & out);

// Individual style (L) error checks for a single line.
void checkStyleError1   (istream & line, stringstream & out);
void checkStyleError2   (istream & line, stringstream & out);
void checkStyleError3   (istream & line, stringstream & out);
void checkStyleError4   (istream & line, stringstream & out);
void checkStyleError5   (istream & line, stringstream & out);

// A stream to the all of the code in the entire file is given.
void checkStyleError6   (istream & code, stringstream & out);
void checkStyleError7   (istream & code, stringstream & out);

// Warnings
void checkWarning1      (istream & code, stringstream & out);
void checkWarning2      (istream & line, stringstream & out);
void checkWarning3      (istream & line, stringstream & out);


// Auto - Tester using Unit tests.
// Positive: Checks errors of every type whose bit is set.
//           Checks test whose level bit is set.
void executeUnitTests(int whichTests);
void test(string        input,          // IN
          string        expectedOutput, // IN
          stringstream &log,            // OUT (<<)
          int & fail_count,             // OUT (increments)
          int & test_id,                // IN / OUT (increments)
          int whichChecks);             // IN
void logToOutputFile(stringstream & log);

// Sanitizes a string by removing spaces, tabs, line breaks,
// unifying case, etc.
// Used compare strings that humans would think are equal.
string clean(string str);

// Replaces '\t' with "[\\t]",
//          ' '  with '_',
//     and  '\n' with "[\\n]"
// Makes the invisible characters more visible.
string visible(string str);

// Convert all letter in the input string to lowercase letters.
// Useful if you want to search for words without caring about
// capitalization.
string toLowerCase(string str);

// Helper functions for determining a line' instruction type.
// WARNING: Only guaranteed to work if the line has
//          no Syntax or Compile errors.
enum Op{NO_OP, READ_IN, READ_LITERAL, WRITE_OUT};
Op getInstructionType(string line);

// returns the value indicated by the char literal in this line.
// WARNING: works iff getInstructionType(line) returns READ_LITERAL.
char parseLiteral(string line);

string removeComment(string str);
string removeSpaces(string str);

// used for aligning string output data.
const int   ONE_DIGIT   = 1;
const int   TWO_DIGITS  = 10;
const int THREE_DIGITS  = 100;
const int   FOUR_DIGITS = 1000;

// Streams a formatted line number to the given out stream.
void streamLineNumberPrefix(stringstream & out, int line_number);


void DEBUG(string str)
{
    cout << "Debug:|" << str << "|" << endl;
}

// returns true if the user is not Done.
bool userSession(int session);

// -- Implementation ----------------------------------

int main () {

    mkdir("./io"); // Delete this line if working with online gdb.
                   // or if it is causing problems.

    int count = 0;
    while(userSession(++count));

    return 0;
}

bool userSession(int session)
{
    cout << "*********************************************************";
    cout << endl << endl << endl;
    cout << "---------------------------------------------------------";
    cout << endl;
    cout << "Enter any/all of the following options, then press enter." << endl;
    cout << endl;

    //cout << "Only what is specified will be used." << endl;
    //cout << endl;
    //cout << "U: Run every unit test available." << endl;
    /*
    cout << "A: Run ALL Categories of tests." << endl;
    cout << "0: Run Tests of ALL levels" << endl;
    cout << endl;
    cout << "S: Check Syntax Errors." << endl;
    cout << "C: Check Compile Time Errors." << endl;
    cout << "R: Run the Code if no syntax or compile errors are found.\n"
            "   Produces either a Runtime Error or an output sequence." << endl;
    cout << "W: Check Warnings." << endl;
    cout << "L: Check Style Errors. Maybe L stands for Linter." << endl;
    cout << endl;
    */
    cout << "1: Run tests up to level 1." << endl;
    cout << "2: Run tests up to level 2." << endl;
    cout << "3: Run tests up to level 3." << endl;
    //cout << "4: Run tests up to level 4." << endl;
    //cout << endl;
    cout << "X: Execute compiler on file: " << INPUT_FILE_PATH << endl;
    cout << "D: Done, EXIT this program." << endl;

    bool valid_command = true;
    bool compile_input_file = false;
    int enabled = NONE;
    bool exit_program = false;

    do
    {
        exit_program = false;
        valid_command = true; // innocent until proven guilty.

        cout << "---------------(Scroll UP to see past output!)-----------" << endl;
        cout << "<User Input #" << session << ">: ";

        string input;
        cin >> input >> std::skipws;

        cout << "---------------------------------------------------------" << endl;

        stringstream options(input);

        while(options.eof() == false)
        {
            char c = options.get();

            switch(c)
            {
                default:

                    if(options.eof() == false)
                    {
                        cout << " - option '" << c << "' unknown." << endl;
                        valid_command = false;
                    }
                    continue;
                case 'd':
                case 'D': exit_program = true; break;
                          // Done, NOT notDone.
                case 'u':
                case 'U': enabled |= ALL;
                          enabled |= ALL_LVLS; break;
                case 'a':
                case 'A': enabled |= ALL;      break;
                case 's':
                case 'S': enabled |= SYNTAX;   break;
                case 'c':
                case 'C': enabled |= COMPILE;  break;
                case 'r':
                case 'R': enabled |= RUN;      break;
                case 'w':
                case 'W': enabled |= WARNINGS; break;
                case 'l':
                case 'L': enabled |= STYLE;    break;

                case '0': enabled |= ALL_LVLS; break;

                case '4': enabled |= LVL4;
                case '3': enabled |= LVL3;
                case '2': enabled |= LVL2;
                case '1': enabled |= LVL1;     break;

                case 'x': // x stands for execute.
                case 'X': compile_input_file = true; break;
            }
        }
    }while(false == valid_command);

    if(exit_program)
    {
        return false; // Don't go again.
    }

    if(enabled == NONE && compile_input_file == false)
    {
        enabled = ALL | ALL_LVLS;
    }

    cout << "\n\n" << endl;


    //printAllFullErrorMessages();

    ifstream code;

    if(enabled != NONE)
    {
        executeUnitTests(enabled);
    }

    // Try to open the code for a normal compile.
    else if(!openFile(code, INPUT_FILE_PATH) &&
            !openFile(code, INPUT_FILE_PATH2))
    {
        // Input file not found. Prompt student to create it!
        cout << "\n";
        cout << "If you want to test your own code, put it in\n"
                "a text file at one of those path locations." << endl;
        cout << "\n\n\n";
    }
    else
    {
        // Normal Compile.
        stringstream log;
        compileSequenceMachineProgram(code, log);

        stringstream source_code_raw;
        rewindStream(code);
        while(code.eof() == false)
        {
            source_code_raw << (char)code.get();
        }
        code.close();

        cout << "Source Code (" << INPUT_FILE_PATH << ")" << endl;
        cout << "------+-----------------"
                "---------------------------------";
        stringstream src(visible(source_code_raw.str()));
        int line_number = 0;
        while(!src.eof())
        {
            string line;
            getline(src, line);
            line_number++;
            cout << "\n";
            if(line_number <  FOUR_DIGITS){cout << " ";}
            if(line_number < THREE_DIGITS){cout << " ";}
            if(line_number <   TWO_DIGITS){cout << " ";}

            cout << line_number << ". |" << line;
        }
        cout << "[EOF]" << endl;
        cout << "------+-----------------"
               "---------------------------------" << endl;
        cout << endl << endl;


        cout << "Compilation Log" << endl;
        cout << "============================================" << endl << endl;

        // NOTE: There must be output.
        cout << log.str() << endl;
        cout << "--------------------------------------------" << endl;

        // Output logging communication to user.
        logToOutputFile(log);

        cout << endl;
    }

    return true; // notDone.
}

// Auto - Tester using Unit tests.
// Positive: Checks errors of every type whose bit is set.
//           Checks test whose level bit is set.
void executeUnitTests(int ENABLED)
{

    stringstream failure_log;
    stringstream & fl = failure_log; // fl means failure_log;

    int fc = 0; // fail count.
    int id = 1; // test id.


    // Check only for syntax and compilation problems.
    const int SC = SYNTAX | COMPILE;

    test("",                        OK, fl, fc, id, SC);
    test("// comment",              OK, fl, fc, id, SC);
    test("// Another message",      OK, fl, fc, id, SC);
    test("read from input();",      OK, fl, fc, id, SC);
    test("read from ' ' literal;",  OK, fl, fc, id, SC);
    test("write to output;",        OK, fl, fc, id, SC);


    test("read from input(); // Hamburger.",
                                    OK, fl, fc, id, SC);
    test("read from input(); // \\/.,!)#+$_%#(&^$)(*\t \t bad.",
                                    OK, fl, fc, id, SC);
    test("read from ' ' literal; // Hotdog.",
                                    OK, fl, fc, id, SC);
    test("write to output; // read from '%' literal.",
                                    OK, fl, fc, id, SC);


    if(LVL1 & ENABLED)
    {
        // Testing Error S1.
        test("dead from input();",      S1, fl, fc, id, SC);
        test(";// comment",             S1, fl, fc, id, SC);
        test(",      output << 'X';",   S1, fl, fc, id, SC);
        test("a;",                      S1, fl, fc, id, SC);
        test("@;",                      S1, fl, fc, id, SC);
    }


    if(LVL3 & ENABLED)
    {
        test("R;\n"
             "r;\n"
             "W;\n"
             "w;\n"
             "\n"
             " \n"
             "\t"
                 ,              "1\n" + S2 +
                              "\n2\n" + S2 +
                              "\n3\n" + S2 +
                              "\n4\n" + S2, fl, fc, id, SC);

        // Testing Error S2 (S2 is hard)
        test("retrieve the input();",   S2, fl, fc, id, SC);
        test("read from 'X';",          S2, fl, fc, id, SC);
        test("write data to output;",   S2, fl, fc, id, SC);
        test("read 'X' literal;",       S2, fl, fc, id, SC);

        test("read from 'X'literal;",   S2, fl, fc, id, SC);
        test("read from'X' literal;",   S2, fl, fc, id, SC);
        test("read frominput();",       S2, fl, fc, id, SC);
        test("readfrom input();",       S2, fl, fc, id, SC);
        test("writetooutput;",          S2, fl, fc, id, SC);
        test("writeto output;",         S2, fl, fc, id, SC);
        test("write tooutput;",         S2, fl, fc, id, SC);
        //test("read from 'X'; literal;", S2, fl, fc, id, SC);
        test("read from 'X';// literal;",
                                        S2, fl, fc, id, SC);
        //test("read from output();",   S2, fl, fc, id, SC);
    }

    if(LVL1 & ENABLED)
    {
        // Testing Error S3
        test("/",                        S3, fl, fc, id, SC);
    }

    if(LVL3 & ENABLED)
    {
        test("/ This is a comment",      S2 + '\n'
                                       + S3, fl, fc, id, SC);
    }

    if(LVL1 & ENABLED)
    {
        test("write to output; / comment"
             ,                           S3, fl, fc, id, SC);
    }


    if(LVL2 & ENABLED)
    {
        // Testing Error S4
        test("\\/ comment",              S2 + '\n' +
                                         S4, fl, fc, id, SC);
        test("/\\ comment",              S2 + '\n' +
                                         S4, fl, fc, id, SC);
        test("\\\\ comment",             S2 + '\n' +
                                         S4, fl, fc, id, SC);
        test("write to output; \\\\ comment",
                                         S4, fl, fc, id, SC);

    }

    if(LVL3 & ENABLED)
    {
        test("// cOewhi\\!@#$%^&*()",    OK, fl, fc, id, SC);
    }


    if(LVL1 & ENABLED)
    {
        // Testing Error S5
        test("read from 'a literal;",    S5, fl, fc, id, SC);
        test("read from a' literal;",    S5, fl, fc, id, SC);
    }

    if(LVL2 & ENABLED)
    {
        // Testing Error S6
        test("read from '\\' literal;",  S6, fl, fc, id, SC);
        test("// '\\' literal;",         OK, fl, fc, id, SC);
    }

    if(LVL3 & ENABLED)
    {
        // Testing Error S7
        test("read from 'a\\' literal;", S7, fl, fc, id, SC);
        test("read from 'ab' literal;",  S7, fl, fc, id, SC);
        test("read from '_a_' literal;", S7, fl, fc, id, SC);
        test("read from '\\n' literal;", OK, fl, fc, id, SC);
    }

    if(LVL1 & ENABLED)
    {
        // Testing Error S8
        test("read from input()",        S8, fl, fc, id, SC);
        test("write to output",          S8, fl, fc, id, SC);
        test("read from 'a' literal // ;",
                                         S8, fl, fc, id, SC);
    }

    if(LVL3 & ENABLED)
    {
        // Testing Error S9
        test("Read from input();",       S9, fl, fc, id, SC);
        test("read FROM input();",       S9, fl, fc, id, SC);
        test("read from 'x' literaL;",   S9, fl, fc, id, SC);
        test("wriTe to output;",         S9, fl, fc, id, SC);
        test("write tO output;",         S9, fl, fc, id, SC);

        test("// write tO output;",      OK, fl, fc, id, SC);
        test("// rEAD from input();",    OK, fl, fc, id, SC);
        test("//   From",                OK, fl, fc, id, SC);
        test("// wRiTE to output;",      OK, fl, fc, id, SC);
        test("// LItERAL",               OK, fl, fc, id, SC);
    }

    if(LVL2 & ENABLED)
    {
        // Testing Error S10 ( and S11 )
        test("read from input(;",        S10, fl, fc, id, SC);
        test("read from input);",        S11, fl, fc, id, SC);
        test("read from input(a);",      S10 + '\n'
                                       + S11, fl, fc, id, SC);
    }

    if(LVL3 & ENABLED)
    {
        // Testing Error C1
        test("read from Input();",       C1, fl, fc, id, SC);
        test("read from iNPUT();",       C1, fl, fc, id, SC);
        test("write to OUTPUT();",       C1, fl, fc, id, SC);
        test("write to outpuT();",       C1, fl, fc, id, SC);
        test("WriTe to OutPut;",         S9 + '\n'
                                       + C1, fl, fc, id, SC);
    }

    if(LVL3 & ENABLED)
    {
        // Testing Error C2
        test("read from input;",         C2, fl, fc, id, SC);
    }

    if(LVL2 & ENABLED)
    {
        // Testing Error C3
        test("read from coolVariable;",  C3, fl, fc, id, SC);
        test("write to cout;",           C3, fl, fc, id, SC);
    }


    // Edge Cases.
    //test("\\",                     S3 + '\n'
      //                           + S4, fl, fc, id, SC);

    //-------------------------------------------------
    // Test Warnings. (code: W)
    //-------------------------------------------------

    const int SCW  = SYNTAX | COMPILE | WARNINGS;
    const int NR   = ALL ^ RUN; // Don't run the code.
    const int W    = WARNINGS;

    if(LVL3 & ENABLED)
    {
        test("read from ' ' literal;\n"
             "read from input(); // Overwrite.\n"
             "write to output;"
             ,                           "1\n" +
                                         W1, fl, fc, id, NR);

        test("read from input();\n"
             "write to output;\n"
             "read from input();"
             ,                           "3\n" +
                                         W1, fl, fc, id, SCW);

        test("read from input(); // Skip first\n"
             "read from input(); // input.\n"
             "write to output;"
             ,                           "1\n" +
                                         OK, fl, fc, id, NR);


        test("read from input(); // Hello\\\n"
             ,                           "1\n" +
                                         W1 + '\n'
                                       + "1\n" +
                                         W2, fl, fc, id, NR);

        test("write to output; // World\\"
             ,                           W2, fl, fc, id, NR);

        test("read from \"x\" literal;", W1 + '\n'
                                       + W3, fl, fc, id, W);
        test("read from '\"' literal;\n"
             "write to output; // ;)" ,  OK, fl, fc, id, W);
    }

    //----------------------------------
    // RUNTIME ERRORS / OUTPUT (code: R)
    //----------------------------------

    const int SCR = SYNTAX | COMPILE | RUN;

    // Level 1 if I give them most of the runtime code...
    if(LVL1 & ENABLED)
    {
        // -- Test R1, You must read before writing.
        test("write to output;",         R1, fl, fc, id, SCR);

        test("// read from input();\n"
             "write to output;\n"
             "read from input();",       "2\n" +
                                         R1, fl, fc, id, SCR);

        // -- Test R2
        // Uses default 0 length input. Read is out of bounds.
        test("read from input();",       R2, fl, fc, id, SCR);

        // Non-default input sequence specified with IN comment.
        test("// IN: a b\n"
             "read from input();\n"
             "write to output();\n"
             "read from input();\n"
             "write to output();\n"
             "read from input();"
             "write to output();",       "5\n" +
                                         R2, fl, fc, id, SCR);


        // Test Duplication program.
        // Does it produce the correct output?
        test("// IN: Hello\n"
             "read from input();\n"
             "write to output();\n"
             "write to output();",
             "OUT: HelloHello\n",           fl, fc, id, SCR);

        test("// IN: / ;\n"
             "read from input();\n"
             "write to output();\n"
             "write to output();",
             "OUT: //\n",                   fl, fc, id, SCR);

        test("// IN: print input()\n"
             "read from input();\n"
             "write to output();\n"
             "write to output();",
             "OUT: printprint\n",           fl, fc, id, SCR);


        // Test Split and Combine Program.
        // Does it produce the correct output?
        test("// IN: I a m\n"
             "// Split and Combine.\n"
             "read from input();\n"
             "write to output();\n"
             "\n"
             "read from ' ' literal;\n"
             "write to output();\n"
             "\n"
             "read from input();\n"
             "write to output();\n"
             "\n"
             "read from input();\n"
             "write to output(); // happy",
             "OUT: I am",                   fl, fc, id, ALL);
    }

    if(LVL3 % ENABLED)
    {
        // Test Finding different errors on different lines.
        // Does it produce the correct output?
        test("// IN: I a m\n"
             "// Split and Combine.\n"
             "read from input();\n"
             "write to output();\n"
             "read fr0m ' ' literal;\n"
             "\n\n\n\n\n\n\n"
             "write to output();\n"
             "read from input();\n"
             "write to outut();\n"
             "read from input();\n"
             "write to output();//happy",
                                         "5\n" +
                                         S2 + '\n'
                                       + "15\n" +
                                         C3 + '\n'
                                       + "17\n" +
                                         L3 + '\n'
                                       + L4 + '\n'
                                       + L7 + '\n'
                                        ,fl, fc, id, ALL);
    }


    //-----------------------
    // STYLE ERRORS (code: L)
    //-----------------------

    int SCL = SYNTAX | COMPILE | STYLE; // No Warnings, no Run.

    // Note: NR (All NOT RUN) is stronger as it can generate
    //                        false positive warning messages,
    //                        when none should be produced.

    if(LVL1 & ENABLED)
    {
        // Line level style tests.
        test(" read from input(); //",          L1, fl, fc, id, SCL);
        test(" // Comment.",                    L1, fl, fc, id, NR);
    }

    if(LVL2 & ENABLED)
    {
        test("    ",                            L2, fl, fc, id, NR);
        test("read  from input(); // ",         L2, fl, fc, id, SCL);
        test("//  This is my comment.",         L2, fl, fc, id, NR);

        test("write to output;// Hi",           L3, fl, fc, id, NR);
        test("read from 'x' literal;// 3",      L3, fl, fc, id, SCL);

        test("//Comment",                       L4, fl, fc, id, NR);
        test("write to output; //Comment",      L4, fl, fc, id, NR);
    }

    if(LVL1 & ENABLED)
    {
        test("// Hello\tWorld",                 L5, fl, fc, id, NR);
        test("\t",                              L5, fl, fc, id, NR);
        test("\t// Comment.",                   L1 + '\n'
                                              + L5, fl, fc, id, NR);
    }

    if(LVL2 & ENABLED)
    {
        // Full code level style tests.
        test("read from input();\n"
             "write to output();"
             ,                                  L6, fl, fc, id, NR);

        test(" read from input();",             L1 + '\n'
                                              + L6, fl, fc, id, SCL);

        test("read from input(); //\n"
             "\n"
             "\n"
             "\n"
             "write to output(); //"
             ,                                  L7, fl, fc, id, NR);

        test("read from input(); //\n"
             "\n"
             "\n"
             "write to output(); //"
             ,                                  L7, fl, fc, id, NR);
    }



    if(failure_log.str() != "")
    {
        failure_log << "\n=====END OF LOG=======\n";
    }
    else
    {
        failure_log << "[SUCCESS, NO FAILURES]";
    }

    // Display results on the console.
    cout << failure_log.str() << endl;

    cout << endl;
    cout << "Done Unit Testing. ";// << endl << endl;

    int nTests = id - 1;
    int nFail  = fc; // fail count;
    int nPass  = nTests - nFail;

    int perPassed = nPass*100000 / nTests; //accurate to hundreths.
    int pTenth = perPassed % 1000 / 10;
    int pWhole = perPassed / 1000;

    // Round to nearest tenth
    pTenth = (pTenth + 5) / 10;

    // point used for formatting fractional part with 0's.
    string point = ".";
    //if(pTenth < TWO_DIGITS){point +=  '0';}
    // .00 = "." + '0' + 0

    cout << "Passed " << nPass << " of " << nTests << " tests. (";
    cout << pWhole << point << pTenth << "%)\n\n";



    int perFailed = nFail*100000 / nTests; //accurate to hundredths place.
    int fTenth = perFailed % 1000 / 10;
    int fWhole = perFailed / 1000;

    fTenth = ((fTenth + 5) / 10);

    point = ".";
    //if(fTenth < TWO_DIGITS){point += '0';}


    cout << nFail << " tests failed. (";
    cout << fWhole << point << fTenth << "%) \n";

    logToOutputFile(failure_log);

    cout << endl;
}

void logToOutputFile(stringstream & log)
{
    ofstream log_file;
    string path;
    if(openFile(log_file, OUTPUT_FILE_PATH))
    {
        log_file << log.str();
        path = OUTPUT_FILE_PATH;
    }
    else if (openFile(log_file, OUTPUT_FILE_PATH2))
    {
        log_file << log.str();
        path = OUTPUT_FILE_PATH2;
    }

    if(log_file.is_open())
    {
        cout << "Log was written to this file: ";
        cout << path << endl;
        log_file.close();
    }
}



// Note: RAW Actual output filled during compilation process.
void test(string        input,          // IN
          string        expectedOutput, // IN
          stringstream &log,            // OUT (<<)
          int & fail_count,             // OUT (increments)
          int & test_id,                // IN / OUT (increments)
          int whichChecks)              // IN
{
    stringstream code(input);
    stringstream actualOutput;

    // Execute the compilation process.
    compileSequenceMachineProgram
    (
        code,
        actualOutput,
        false,
        whichChecks
    );
    rewindStream(code);


    if(clean(expectedOutput) != clean(actualOutput.str()))
    {
        fail_count++;
        int id = test_id;

        // Add line breaks between fail logs.
        if(fail_count >= 2){log << endl << endl;}

        log << "log #" << fail_count << ": "
            << "Test " << id << " Failed." << endl;
        log << "======================";

        if(id >= TWO_DIGITS)  {log << "=";}
        if(id >= THREE_DIGITS){log << "=";}
        if(id >= FOUR_DIGITS) {log << "=";}

        if(fail_count >= TWO_DIGITS)  {log << "=";}
        if(fail_count >= THREE_DIGITS){log << "=";}
        if(fail_count >= FOUR_DIGITS) {log << "=";}

        log << endl << endl;

        log << "  Source Code" << endl;
        log << "  ------+-----------------"
               "--------------------------";
        stringstream src(visible(input));
        int line_number = 0;
        while(!src.eof())
        {
            string line;
            getline(src, line);
            line_number++;
            log << "\n  ";
            if(line_number <  FOUR_DIGITS){log << " ";}
            if(line_number < THREE_DIGITS){log << " ";}
            if(line_number <   TWO_DIGITS){log << " ";}

            log << line_number << ". |" << line;
        }
        log << "[EOF]" << endl;
        log << "  ------+-----------------"
               "--------------------------" << endl;
        log << endl << endl;

        log << "  Your Compiler's Output" << endl;
        log << "  ----------------------" << endl;
        rewindStream(actualOutput);
        while(!actualOutput.eof())
        {
            string line;
            getline(actualOutput, line);

            // If first character is number, it contains
            // line number info.
            if(line.length() >= 1 &&
               '0' <= line[0] && line[0] <= '9')
            {
                int line_number;
                stringstream(line) >> line_number;
                log << "  ";
                streamLineNumberPrefix(log, line_number);
                log << "." << endl;
            }
            else if(line.length() > 0)
            {
                log << "       " << line << endl;
            }
        }
        if(actualOutput.str() == "")
        {
            log << "  [NO OUTPUT]" << endl;
        }
        log << "  ----------------------" << endl << endl << endl;


        log << "  The Correct Output Expected" << endl;
        log << "  ---------------------------" << endl;



        stringstream correct(expectedOutput);
        while(!correct.eof())
        {
            string line;
            getline(correct, line);

            if(line.length() > 0)
            {
                log << "    " << line << endl;
            }
        }

        if(expectedOutput == "")
        {
            log << "    [NO OUTPUT]" << endl;
        }


        log << "  ---------------------------" << endl;
    }
    else
    {
        log << OK;
    }

    // Empty the output buffer used for tests.
    actualOutput.str("");
    test_id++;
}


void compileSequenceMachineProgram
    (istream & code,
     stringstream & out,
     bool verbose,
     int shouldCheck)
{

    bool errors_found = false;

    stringstream err;

    if(shouldCheck & SYNTAX)
    {
        if(verbose)
        {
            out << "Checking for Syntax Errors..." << endl;
            out << "-----------------------------" << endl;
        }

        checkForSyntaxErrors (code, err);
        rewindStream(code);

        out << err.str();
        if(err.str() != "")
        {
            errors_found = true;
            err.str(""); // Clear.
        }
    }

    if(shouldCheck & COMPILE)
    {
        if(verbose)
        {
            out << "\n\nChecking for Compile Errors..." << endl;
            out <<     "------------------------------" << endl;
        }
        checkForcompileErrors(code, err);
        rewindStream(code);

        out << err.str();
        if(err.str() != "")
        {
            errors_found = true;
            err.str(""); // Clear.
        }
    }




    if(shouldCheck & WARNINGS)
    {
        if(verbose)
        {
            out << "\n\nChecking for Warnings..." << endl;
            out <<     "------------------------" << endl;
        }

        checkForWarnings(code, out);
        rewindStream(code);
    }


    if(verbose && (shouldCheck & (SYNTAX | COMPILE | WARNINGS)))
    {
        out << "\n\nDone Compiling." << endl;
    }

    if(shouldCheck & STYLE)
    {
        if(verbose)
        {
            out << "\n\nChecking for Style Errors..." << endl;
            out <<     "----------------------------" << endl;
        }

        checkForStyleErrors(code, out);
        rewindStream(code);

        if(verbose)
        {
            out << "\n\nDone Style Checking." << endl;
        }
    }

    if(errors_found)
    {
        if(verbose)
        {
            out << "Errors Found, Code was not run." << endl;
        }
    }

    if(!errors_found && (shouldCheck & RUN))
    {
        if(verbose)
        {
            out << "\n\nRunning code..." << endl;
            out <<     "---------------" << endl;
        }

        runSequenceMachineProgram(code, out);
        rewindStream(code);
    }
}

void printAllFullErrorMessages()
{
    cout << "Syntax errors" << endl;
    cout << "-------------" << endl;
    cout << S1  << endl;
    cout << S2  << endl;
    cout << S3  << endl;
    cout << S4  << endl;
    cout << S5  << endl;
    cout << S6  << endl;
    cout << S7  << endl;
    cout << S8  << endl;
    cout << S9  << endl;
    cout << S10 << endl;
    cout << S11 << endl;
    cout << endl;

    cout << "Compile errors" << endl;
    cout << "--------------" << endl;
    cout << C1  << endl;
    cout << C2 << endl;
    cout << C3 << endl;
    cout << endl;

    cout << "Warnings" << endl;
    cout << "--------" << endl;
    cout << W1 << endl;
    cout << W2 << endl;
    cout << W3 << endl;
    cout << endl;

    cout << "Runtime errors" << endl;
    cout << "--------------" << endl;
    cout << R1  << endl;
    cout << R2 << endl;
    cout << endl;

    cout << "Style errors" << endl;
    cout << "------------" << endl;
    cout << L1  << endl;
    cout << L2 << endl;
    cout << L3 << endl;
    cout << L4 << endl;
    cout << L5 << endl;
    cout << L6 << endl;
    cout << L7 << endl;
    cout << endl;
}

string id(const string error_message)
{
    char first, second, third;
    first  = error_message[0];
    second = error_message[1];
    third  = error_message[2];

    string output;
    output = output + first;
    output = output + second;

    if(error_message[2] != ' ')
    {
        output = output + third;
    }

    return output;
}



// -- Sequence Machine Compiler Functions
void checkForSyntaxErrors (istream & code, stringstream & out)
{
    stringstream line_error_stream;
    stringstream temp_error_stream;

    int line_number = 0;
    bool err = false;
    while(code.eof() == false)
    {
        string line_data;
        getline(code, line_data);
        line_number++;

        stringstream line(line_data);

        checkSyntaxError1  (line, temp_error_stream);
        rewindStream(line);

        if(temp_error_stream.str() == "")
        {
            checkSyntaxError2  (line, temp_error_stream);
            rewindStream(line);
        }

        line_error_stream << temp_error_stream.str();
        temp_error_stream.str("");

        checkSyntaxError4  (line, temp_error_stream);
        rewindStream(line);

        // Don't ever print both S3 and S4.
        if(temp_error_stream.str() == "")
        {
            checkSyntaxError3  (line, temp_error_stream);
            rewindStream(line);
        }


        checkSyntaxError5  (line, temp_error_stream);
        rewindStream(line);

        checkSyntaxError6  (line, temp_error_stream);
        rewindStream(line);

        checkSyntaxError7  (line, temp_error_stream);
        rewindStream(line);

        // Only mention the semi-colon if nothing more
        // important is found wrong.
        if(temp_error_stream.str() == "")
        {
            checkSyntaxError8  (line, temp_error_stream);
            rewindStream(line);
        }


        checkSyntaxError9  (line, temp_error_stream);
        rewindStream(line);

        checkSyntaxError10 (line, temp_error_stream);
        rewindStream(line);

        checkSyntaxError11 (line, temp_error_stream);
        rewindStream(line);

        line_error_stream << temp_error_stream.str();
        temp_error_stream.str("");

        if(line_error_stream.str() != "")
        {
            out << line_number << endl;
            out << line_error_stream.str();
            line_error_stream.str("");
            err = true;
        }
    }

    if(err)
    {
        out << endl;
    }
}

void checkForcompileErrors(istream & code, stringstream & out)
{
    stringstream line_error_stream;

    bool err = false;
    int line_number = 0;
    while(code.eof() == false)
    {
        string line_data;
        getline(code, line_data);
        line_number++;

        stringstream line(line_data);

        checkCompileError1(line, line_error_stream);
        rewindStream(line);

        checkCompileError2(line, line_error_stream);
        rewindStream(line);

        // Only print this error is C1 and C2 were not printed.
        if(line_error_stream.str() == "")
        {
            checkCompileError3(line, line_error_stream);
            rewindStream(line);
        }

        if(line_error_stream.str() != "")
        {
            err = true;

            out << line_number << endl;
            out << line_error_stream.str() << endl;
            line_error_stream.str("");
        }
    }

    if(err)
    {
        out << endl;
    }
}

void checkForWarnings(istream & code, stringstream & out)
{
    bool err = false;
    stringstream code_error_stream;

    checkWarning1(code, code_error_stream);
    rewindStream(code);

    if(code_error_stream.str() != "")
    {
        out << code_error_stream.str();
        err = true;
    }

    stringstream line_error_stream;

    int line_number = 0;
    while(code.eof() == false)
    {
        string line_data;
        getline(code, line_data);
        line_number++;

        stringstream line(line_data);

        checkWarning2(line, line_error_stream);
        rewindStream(line);

        checkWarning3(line, line_error_stream);
        rewindStream(line);

        if(line_error_stream.str() != "")
        {
            err = true;

            out << line_number << endl;
            out << line_error_stream.str() << endl;
            line_error_stream.str("");
        }
    }

    // print with new line if warning(s) found.
    if(err)
    {
        out << endl;
    }
}

void checkForStyleErrors(istream & code, stringstream & out)
{
    stringstream line_error_stream;

    bool err = false;
    int line_number = 0;
    while(code.eof() == false)
    {
        string line_data;
        getline(code, line_data);
        line_number++;


        stringstream line(line_data);

        checkStyleError1(line, line_error_stream);
        rewindStream(line);

        checkStyleError2(line, line_error_stream);
        rewindStream(line);

        checkStyleError3(line, line_error_stream);
        rewindStream(line);

        checkStyleError4(line, line_error_stream);
        rewindStream(line);

        checkStyleError5(line, line_error_stream);
        rewindStream(line);

        if(line_error_stream.str() != "")
        {
            err = true;

            out << line_number << endl;
            out << line_error_stream.str() << endl;
            line_error_stream.str("");
        }
    }

    stringstream code_error_stream;

    // Now check for the full code level errors.
    rewindStream(code);

    checkStyleError6(code, code_error_stream);
    rewindStream(code);

    checkStyleError7(code, code_error_stream);
    rewindStream(code);

    // print with new line if style errors found.
    if(code_error_stream.str() != "")
    {
        out << "-----\n\n" << code_error_stream.str();
        err = true;
    }

    // print with new line if warning(s) found.
    if(err)
    {
        out << endl;
    }
}


//========================
// -- Useful File methods.
//========================

void rewindStream(istream & input_stream)
{
    // If this isn't done, it won't rewind.
    input_stream.clear(std::istream::goodbit);

    // Set input iterator to beginning of stream + 0 offset.
    input_stream.seekg (0, input_stream.beg);
}

bool openFile(ifstream & file, string filepath)
{
  file = ifstream(filepath);
  if (!file.is_open())
  {
    cerr << "Unable to Open: " << filepath << endl;
  }

  return file.is_open(); // Success.
}

void closeFile(ifstream & file)
{
    file.close();
}

// Output file.
bool openFile(ofstream & file, string filepath)
{
  file = ofstream(filepath);
  if (!file.is_open())
  {
    cerr << "Unable to Open: " << filepath << endl;
  }

  return file.is_open(); // Success.
}

void closeFile(ofstream & output_file)
{
    // Make sure all of the data
    // has been sent to the hardware file.
    output_file.flush();
    output_file.close();
}



//+==========================================+
//|-- Useful Text Processing Methods. -------|
//+------------------------------------------+
//|   You may wish to use them in your error |
//|   detection  implementations.            |
//+==========================================+

// Removes everything except for spaces and numbers.
string clean(string str)
{
    stringstream in(str);
    stringstream out;

    while(!in.eof())
    {
        char c = in.get();

        if(in.fail())
        {
            break;
        }

        if('A' <= c && c <= 'Z')
        {
            c = c + 'a' - 'A';
        }

        if('a' <= c && c <= 'z')
        {
            out << c;
        }

        // Numbers helps keep the line numbers honest.
        if('0' < c && c <= '9' && c != '1')
        {
            out << c;
        }

        // Keep some other special characters to check for more bugs.
        if(c == '\'' || c == '/' || c == '\\' || c == '"')
        {
            out << c;
        }
    }

    return out.str();
}

// https://theasciicode.com.ar/ascii-printable-characters/
// dot-full-stop-ascii-code-46.html
string visible(string str)
{
    stringstream in(str);
    stringstream out;

    while(!in.eof())
    {
        char c = in.get();

        if(in.fail() || in.eof()){break;}

        if(c == ' ')
        {
            out << ' ';

            // Uncomment any of these if you have
            // trouble seeing spaces...
            //out << '_';
            //out << '.';

            //out << (char)176; // tone.

            //out << (char)220; // top block
            //out << (char)219; // Middle block.
            //out << (char)223; // bottom block.

            //out << (char)254; // square.
        }
        else if (c == '\t')
        {
            out << "[\\t]";
        }
        else if (c == '\n')
        {
            out << "[\\n]" << endl;
        }
        else
        {
            out << c;
        }
    }

    return out.str();
}

string toLowerCase(string str)
{
    stringstream in(str);
    stringstream out;

    while(!in.eof())
    {
        char c = in.get();

        if('A' <= c && c <= 'Z')
        {
            c = c + 'a' - 'A';
        }

        out << c;
    }

    return out.str();
}

// NO_OP, READ_IN, READ_LITERAL, or WRITE_OUT
Op getInstructionType(string line)
{
    // Index where the comment starts.
    size_t comment = line.find("//");
    if(comment == string::npos)
    {
        comment = line.length();
    }

    size_t input   = line.find("input");
    if(input != string::npos && input < comment)
    {
        return READ_IN;
    }

    size_t literal = line.find("literal");
    if(literal != string::npos && literal < comment)
    {
        return READ_LITERAL;
    }

    size_t output  = line.find("output");
    if(output != string::npos && output < comment)
    {
        return WRITE_OUT;
    }

    // Blank lines and lines that only contain a comment.
    return NO_OP;
}

char parseLiteral(string line, stringstream & out)
{
    Op op_code = getInstructionType(line);

    // Error on the part of the compiler programmer,
    // not the user's program.
    if(op_code != READ_LITERAL)
    {
        cerr << "ERROR: parseLiteral only works for lines of type "
               "READ_LITERAL. call getInstruction(line) and check "
               "that it returns READ_LITERAL first before calling "
               "parseLiteral(line)." << endl;
        exit(0xBAD);
    }

    size_t left  = line.find("'");
    size_t right = line.find("'", left + 1);

    // Ideally, this function will never be called with lines
    // that include syntax errors, but just in case the syntax
    // errors are not yet caught...
    if(left == string::npos || right == string::npos)
    {
        out << "ERROR: parseLiteral did not find 2 single quotes, "
                "therefore there is no character literal in this "
                "line. Maybe there is an uncaught syntax error?";
        out << endl;
        //exit(0xBAD);
        return '?';
    }

    size_t len = line.length();
    if(left + 2 < len &&
       (line[left + 2] != '\'' || line[left + 1] == '\\') &&
       line[left + 1] != '\\' &&
       left + 3 < len &&
       line[left + 3] != '\'')
    {
        out << "ERROR: character literal malformed. 'x' or '\\x' "
               "are the appropriate forms, where x could be any "
               "character and \\ is the escape char. '\' is prohibited."
               "Maybe there is an uncaught syntax error?";
        out << endl;
        return '?';
    }

    char c1 = line[left + 1];
    char c2 = line[left + 2]; // Data char or closing quote (').
    if(c1 != '\\')
    {
        return c1;
    }
    else
    {
        switch(c2)
        {
            case 'n':  return '\n';
            case 't':  return '\t';
            case '\'': return '\'';
            case '\\': return '\\';
            default:
                out << "ERROR: unknown escape character." << endl;
                return '?';
        }
    };

    cout << "parseCharacter(), we should never reach this line." << endl;
    return '?';
}

string removeComment(string line)
{
    string comment = "//";
    size_t index = line.find(comment);

    // the word input() was not found.
    if(index == string::npos)
    {
        return line;
    }

    return line.substr(0, index);
};

string removeSpaces(string line)
{
    stringstream in(line);
    stringstream out;

    while(in.eof() == false)
    {
        char c = in.get();

        if(c != ' ' && c != '\t')
        {
            out << c;
        }
    }

    return out.str();
};


void streamLineNumberPrefix(stringstream & out, int line_number)
{

    //out << "Line: ";
    if(line_number < FOUR_DIGITS)
    {
        out << " ";
    }

    if(line_number < THREE_DIGITS)
    {
        out << " ";
    }

    if(line_number < TWO_DIGITS)
    {
        out << " ";
    }

    out << line_number;
}


/**************************************************************\.
|*                                                            *|
|* STUDENT CODE BEGINS HERE                                   *|
|*                                                            *|
|* DO NOT MODIFY ANY CODE ABOVE THIS MESSAGE                  *|
|*                                                            *|
|* WHEN YOUR WORK IS EVALUATED, YOUR CODE BELOW MAY BE TESTED *|
|* WITH A 'SECRET' / MODIFED VERSION OF THE CODE ABOVE.       *|
|*                                                            *|
|* TO ENSURE THAT YOUR CODE RUNS, MAKE SURE THAT YOUR CODE    *|
|* BELOW COMPILES AND RUNS WITH AN UNALTERED VERSION OF       *|
|* THE ABOVE.                                                 *|
|*                                                            *|
|* GOOD LUCK                                                  *|
\**************************************************************/


// individual Syntax Error checks.
void checkSyntaxError1  (istream & line, stringstream & out)
{

    // FIXME: Almost correct...

    // out << S1 << endl;

    char c = line.get(); // firstCharacter.

    if(!line.fail() && // Handle blank lines.
       c != '/'  &&
       c != '\\' &&
       c != 'r'  &&
       c != 'w'  &&
       c != 'W'  &&
       c != '\n'
      )
    {
        out << S1 << endl;
    }
}

// Hard.
// http://www.cplusplus.com/reference/string/string/find/
void checkSyntaxError2  (istream & line, stringstream & out)
{
    // out << S2 << endl;
};


void checkSyntaxError3  (istream & line, stringstream & out)
{
    // out << S3 << endl;
};


void checkSyntaxError4  (istream & line, stringstream & out)
{
    // out << S4 << endl;
};


void checkSyntaxError5  (istream & line, stringstream & out)
{
    // out << S5 << endl;
};


// Tricky.
// Note: Single Quote character: '\''
//          Backslash Character: '\\'
void checkSyntaxError6  (istream & line, stringstream & out)
{
    // out << S6 << endl;
};


void checkSyntaxError7  (istream & line, stringstream & out)
{
    // out << S7 << endl;
};

// Medium.
void checkSyntaxError8  (istream & line, stringstream & out)
{
    // out << S8 << endl;
};


// HARD.
void checkSyntaxError9  (istream & line_stream, stringstream & out)
{
    // out << S9 << endl;
};

void checkSyntaxError10 (istream & line, stringstream & out)
{
    // out << S10 << endl;
};


void checkSyntaxError11 (istream & line, stringstream & out)
{
    // out << S11 << endl;
};

// Similar to Syntax Error 9 (S9)
void checkCompileError1 (istream & line_stream, stringstream & out)
{
    // out << C1 << endl;
};

// Medium - Hard
void checkCompileError2 (istream & line_stream, stringstream & out)
{
    // out << C2 << endl;
};

void checkCompileError3 (istream & line_stream, stringstream & out)
{
    // out << C3 << endl;
};


// EASY
void checkStyleError1   (istream & line, stringstream & out)
{
    // out << L1 << endl;
};


void checkStyleError2   (istream & line, stringstream & out)
{
    // out << L2 << endl;
};


void checkStyleError3   (istream & line, stringstream & out)
{
    // out << L3 << endl;
};


void checkStyleError4   (istream & line, stringstream & out)
{
    // out << L4 << endl;
};

// EASY
void checkStyleError5   (istream & line, stringstream & out)
{
    // out << L5 << endl;
};


void checkStyleError6   (istream & code, stringstream & out)
{
    // out << L6 << endl;
};


void checkStyleError7   (istream & code, stringstream & out)
{
    // out << L7 << endl;
};

// Use getInstructionType function defined earlier.
void checkWarning1      (istream & code, stringstream & out)
{
    // out << W1 << endl;
}


void checkWarning2      (istream & line, stringstream & out)
{
    // out << W2 << endl;
}

void checkWarning3      (istream & line, stringstream & out)
{
    // out << W3 << endl;
}



// Run the progam, raise runtime errors when found.
void runSequenceMachineProgram(istream & code, stringstream & out)
{
    // -- Try to parse the input sequence.
    //    It should be in the first line of code prefixed by
    //    "// IN: "
    string line;
    getline(code, line);

    // // IN: firstString.
    stringstream inputSequence;
    if(line.find("// IN: ") == 0)
    {
        inputSequence = stringstream(line);

        // Skip the "//" and the "IN:" tokens.
        string token; // A place to dump the tokens to.
        inputSequence >> token;
        inputSequence >> token;
    }
    else // Go over that first line again if not the input.
    {
        rewindStream(code);
    }



    // -- Simulate a sequence machine by executing in order
    //    every instruction written in the program.
    // STUDENT: Modify the below code to throw Runtime Errors when appropriate.
    //
    // out << line_number << '\n' << R1 << endl; // Runtime Error 1
    // out << line_number << '\n' << R1 << endl; // Runtime Error 2

    // The processor's one string variable.
    string processor_register = "";
    int line_number = 0;

    stringstream outputSequence;
    outputSequence << "OUT: ";

    // go through every line and execute it.
    while(code.eof() == false)
    {
        getline(code, line);
        line_number++;

        Op op_code = getInstructionType(line);

        if(op_code == NO_OP)
        {
            continue;
        }

        if(op_code == WRITE_OUT)
        {
            outputSequence << processor_register;
        }
        else if(op_code == READ_IN)
        {
            inputSequence >> processor_register;
        }
        else if(op_code == READ_LITERAL)
        {
            char c = parseLiteral(line, out);
            processor_register = string("") + c;
        }
    }

    // Convert string stream to string.
    out << outputSequence.str() << endl;
}
