
#include <bits/stdc++.h>
using namespace std;

/*+++++++++++++++ variables and methods of MethodLevelLoc.h ++++++++++++++++++*/
extern int total_method;
extern void clearLOC();
extern void methodSeparator(string &temp);

/*+++++++++++++++ variables and methods of ComplexityAnalyzer.h ++++++++++++++++++*/
extern int total_constructor_number;

/************************* Variables to be used *************************/
int blank_line;
int physical_line;
int logical_statements;
int only_comment_line;
int only_statement_line;
int comment_and_statement_line;

// Temporary variables
bool multiple_line_comment_flag;
int temp_statement_counter_per_line; // for counting total logical statements in a line

/************************* Methods to be used *************************/
int CalcLOC(string file_name);
int onlyStatementCounter(string &temp, int start_index, int final_index);
int findTheIndexAfterComment(string &temp, int start_index, int len);
void initializeAllVariable();
void javaAnalyzer(string file_name);
void LOCResultPrinter();
void singleLineAnalyzer(string &temp, int start_index, int final_index);
void assignLineType(bool &flag_statement_line, bool &flag_comment_line);
bool onlyCommentLineFinder(string &temp, int start_index, int final_index);
bool emptyLineCounter(string &temp, int start_index, int final_index);

/************************* method definations *************************/

// Finds only comment lines
bool onlyCommentLineFinder(string &temp, int start_index, int final_index)
{

    int len = final_index - 1;
    bool flag2 = false;
    bool count_as_comment_line = false; // for not detecting printf("//");

    if (multiple_line_comment_flag == true)
    {
        count_as_comment_line = true;
    }

    for (int i = start_index; i < len; i++)
    {

        if (temp[i] == ' ')
        {
            continue;
        }
        else if (flag2 == false)
        { // When not inside a (" ");

            if (temp[i] == '/' && temp[i + 1] == '/')
            {
                return true;
            }
            else if (temp[i] == '/' && temp[i + 1] == '*')
            {
                multiple_line_comment_flag = true;
                count_as_comment_line = true;
            }
            else if (temp[i] == '*' && temp[i + 1] == '/')
            {
                multiple_line_comment_flag = false;
            }
            else if (temp[i] == '"')
            {
                flag2 = true;
            }
        }
        else if (temp[i] == '"' && flag2 == true)
        {
            flag2 = false;
        }
    }

    if (count_as_comment_line == true)
    {

        return true;
    }

    return false;
}

// counts the number of empty lines
bool emptyLineCounter(string &temp, int start_index, int final_index)
{

    if (final_index == 0)
    {
        return true;
    }
    else
    {

        for (int i = start_index; i < final_index; i++)
        {

            if (temp[i] == ' ')
            {
                continue;
            }
            else
            {
                return false;
            }
        }

        return true;
    }
}

// find the end of a comment
int findTheIndexAfterComment(string &temp, int start_index, int len)
{

    if (multiple_line_comment_flag == true)
    {

        for (int i = start_index; i < (len - 1); i++)
        {

            if (temp[i] == '*' && temp[i + 1] == '/')
            {

                return (i + 2); // will store the position of first occurring
            }
        }
    }

    return 0;
}

// this will count the logical statements
// logical statements are those which ends with a semicolon
int onlyStatementCounter(string &temp, int start_index, int final_index)
{

    int len = final_index;
    int statement_after_comment_flag = 0; // will store the position of first occurring
    temp_statement_counter_per_line = 0;

    statement_after_comment_flag = findTheIndexAfterComment(temp, start_index, len);

    stack<char> save_symbol;

    for (int i = statement_after_comment_flag; i < len; i++)
    {

        if (save_symbol.empty())
        {

            if (temp[i] == ';' && temp[i - 1] != ')')
            {
                temp_statement_counter_per_line++;
            }
            else if (temp[i] == '(')
            {
                save_symbol.push(temp[i]);
            }
            else if (temp[i] == '"')
            {
                save_symbol.push(temp[i]);
            }
            else if (i != (len - 1) && temp[i] == '/' && temp[i + 1] == '*')
            {
                save_symbol.push('*'); // when we detect  /*  Comment part
            }
            if (i != (len - 1) && temp[i] == '/' && temp[i + 1] == '/')
            {
                return temp_statement_counter_per_line; // when we detect singleLine Comment
            }
        }
        else
        {

            if (temp[i] == ')' && save_symbol.top() == '(')
            {
                save_symbol.pop();
                temp_statement_counter_per_line++;
            }
            else if (temp[i] == '"' && save_symbol.top() == '"')
            {
                save_symbol.pop();
            }
            else if (i != (len - 1) && temp[i] == '*' && temp[i + 1] == '/' && save_symbol.top() == '*')
            {
                save_symbol.pop();
            }
        }
    }

    return temp_statement_counter_per_line;
}

// checks whether a line contains both comment and statement
void assignLineType(bool &flag_statement_line, bool &flag_comment_line)
{

    if (flag_statement_line == true && flag_comment_line == true)
    {

        comment_and_statement_line++;
        only_comment_line--;
    }
    else if (flag_statement_line == true)
    {

        only_statement_line++;
    }
}

// analyze the source code line by line
void singleLineAnalyzer(string &temp, int start_index, int final_index)
{

    if (emptyLineCounter(temp, start_index, final_index) == true)
    {
        blank_line++;
    }
    else
    {

        bool flag_comment_line = false;
        bool flag_statement_line = false;
        physical_line++;

        if (onlyStatementCounter(temp, start_index, final_index) > 0)
        {

            logical_statements += temp_statement_counter_per_line;
            flag_statement_line = true;
        }

        if (onlyCommentLineFinder(temp, start_index, final_index) == true)
        {

            only_comment_line++;
            flag_comment_line = true;
        }

        assignLineType(flag_statement_line, flag_comment_line); // Checks whether each line contains both methods and comment
    }

    /*+++++++++++++++ function call from MethodLevelLoc.h +++++++++++++++*/

    // This portion directs the program to calculate per method result

    // If line contains no comment

    // methodSeparator(temp);
}

void javaAnalyzer(string file_name)
{

    ifstream input_file(file_name);

    if (not input_file.is_open())
    {

        printf("File not found\n");
        return;
    }

    string temp;
    getline(input_file, temp);

    while (not input_file.eof())
    {

        singleLineAnalyzer(temp, 0, temp.size());
        // cout << temp << "\n";
        getline(input_file, temp);
    }

    input_file.close();
}

void initializeAllVariable()
{

    // own variable initialize
    multiple_line_comment_flag = false;
    temp_statement_counter_per_line = 0;
    blank_line = 0;
    only_comment_line = 0;
    only_statement_line = 0;
    logical_statements = 0;
    physical_line = 0;
    comment_and_statement_line = 0;

    // external variable initialize
    total_method = 0;
    // external method call
    clearLOC();
}

void LOCResultPrinter(void)
{

    printf("\n\n");

    printf("Total Physical Lines: %d\n", physical_line);
    printf("Total Blank Lines: %d\n", blank_line);
    printf("Total Logical Statements: %d\n", logical_statements);
    printf("Number of only Statement Line: %d\n", only_statement_line);
    printf("Number of only Comment Line: %d\n", only_comment_line);
    printf("Number of both Comment and Statement Line: %d\n", comment_and_statement_line);
    printf("Total number of Methods: %d\n", total_method - total_constructor_number);
    printf("Total number of Constructors: %d\n\n\n", total_constructor_number);
}

int CalcLOC(string file_name)
{

    initializeAllVariable();
    javaAnalyzer(file_name);
    // LOCResultPrinter();
    methodSeparator(file_name);

    return 0;
}
