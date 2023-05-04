
#include<bits/stdc++.h>
using namespace std;

/************ method from other file*************/
extern void measureComplexity(void);

/************ Variables to be used ***************/
bool multiple_comment_line_flag_cc = false;
string comment_free_file = "commentFreeFile.txt";

/************ Methods to be used ************/
void calcComplexity(string file_name);
void createCommentAndContentFreeFile(string file_name);
string createCommentFreeLine(string line);
string createContentFreeLine(string line);
bool lengthForRequiredSubstring(string line, string target_sub_string);

/********** Methods definations *************/

// if line coinains target_sub_string
// the length of find() > 0
bool lengthForRequiredSubstring(string line, string target_sub_string){

    if(line.find(target_sub_string)!=string::npos){
        // If the target substring is found in the line
        // string::npos is the constant representing "not found"
        // If find() does not return npos, it means the substring is found
        return true;
    }
    else{
        return false; // If the target substring is not found in the line
    }

}

// erases the comment between ()
string createContentFreeLine(string line){

    // Variable to store the size of the input line
    int line_size = line.size(); 

    // Boolean flags to track whether a double quote or single quote is currently being processed
    bool flag_double_quote = false;
    bool flag_single_quote = false;

    // Removes the contents between single quote and double quote
    // Loop through each character in the line
    for (int i = 0; i < line_size; i++) {

        /***********************************************/
        // corresponding char for ASCII 39 is <'>
        // as we represent character inside 
        // single quote, so we have to use
        // corresponding ASCII value of <'>
        /***********************************************/

        // Check if the character is a single quote (ASCII value 39) or double quote
        // and If neither single nor double quote is currently being processed
        if ((line[i] == 39 || line[i] == '"') && flag_double_quote == false && flag_single_quote == false) {

            // If the character is a single quote, set the flag_single_quote to true
            if (line[i] == 39){
                flag_single_quote = true;
            }
            // If the character is a double quote, set the flag_double_quote to true
            else if (line[i] == '"') {
                flag_double_quote = true;
            }

            // Replace the character with a space to remove its content
            line[i] = ' ';

            // Continue to the next character
            continue;

        }
        // If a double quote is being processed
        else if (flag_double_quote == true) {
            
            // If the character is a closing double quote, set flag_double_quote to false
            if (line[i] == '"') {
                flag_double_quote = false;
            }

            // Replace the character with a space
            line[i] = ' ';

        }
        // If a single quote is being processed
        else if (flag_single_quote == true) {
            
            // If the character is a closing single quote, set flag_single_quote to false
            if (line[i] == 39) {
                flag_single_quote = false;
            }

            // Replace the character with a space
            line[i] = ' ';

        }
    }

    // Return the modified line with the contents between quotes removed
    return line;

}


/*********************************************************/
// function that removes comments and blank lines
// returns a string that is comment or blank line free
/*********************************************************/

string createCommentFreeLine(string line){

    // This function takes a string 'line' as input 
    // and returns a modified string with comments removed.

    // Declare variables for the target substring and length check.
    string target_sub_string;
    bool len;

    // if the line contains "package" keyword
    // we will ignore the line
    // Set the target_sub_string to "package" which is a keyword to be ignored.
    target_sub_string="package";
    // Check the length of the required substring in the line.
    len=lengthForRequiredSubstring(line, target_sub_string);

    // now if line coinains target_sub_string
    // the length of find() would be greater than 0

    if(len){
        // we found the target string in the line
        // so return
        return "";    
    }

    // if the line contains "import" keyword
    // we will ignore the line
    // Set the target_sub_string to "import" which is a keyword to be ignored.
    target_sub_string="import";
    // Check the length of the required substring in the line.
    len=lengthForRequiredSubstring(line, target_sub_string);

    if(len){
        // we found the target string in the line
        // so return
        return "";
    }

    // ignores blank lines
    // the line is empty, so return an empty string
    if(line.size() == 0){
        return "";
    }

    /***************************************************************/
    /***************************************************************/

    // Keeps the track of first occurrence of a letter in a line
    bool double_quote = false; 

    int line_size = line.size();

    for(int i=0; i < line_size ; i++) {

        // Start of the double quote.
        // We will not consider anything inside double quote
        if(line[i] == '"' && double_quote == false){ 
            double_quote = true;
        }
        else if(double_quote == true) {

            // If the closing double quote is reached
            if(line[i] == '"') {
                double_quote = false;
            }
            else{ 
                // else we ignore the character because it is inside the double quote                             
                continue;  
            }                            

        }
        else if(multiple_comment_line_flag_cc == true) {

            // If the current character is inside of multiple line comment character

            if(line[i]=='*' && line[i+1] =='/') {
                multiple_comment_line_flag_cc = false;
                line[i] = ' ';
                line[i+1]= ' ';
            }
            else {
                line[i]=' ';
            }

        }
        else if(line[i]=='/' && line[i+1] =='*') {
            
            // If the closing of multiple line comment character

            multiple_comment_line_flag_cc = true;
            line[i] = ' ';
            line[i+1] = ' ';

        }
        else if(line[i] == '/' && line[i+1] == '/') {
            
            // If the single line comment character is reached, then we ignore the rest of the line

            for(int j=i ; j<line_size; j++) {
                line[j] = ' ';
            }
            
            break;

        }

    }

    // for(int i=0; i<line_size; i++) {
    //     if(line[i] != ' ' && line[i] != 13) {
    //         return line+"\n"; // carriage return may be present in line
    //     }
    // }

    // This is the case when the whole line is comprised of space or carriage return character
    
    return line;

}

void createCommentAndContentFreeFile(string file_name){

    // read the input file
    ifstream input_file(file_name);

    // create and to write information to output file
    // comment and space free lines
    ofstream output_file(comment_free_file); 

    // return if file cannot be opened
    if(input_file.is_open() == false){
        return;
    }

    // else continue following tasks

    string line;
    getline(input_file, line);

    // until reach the end_of_file
    while(not input_file.eof()){

        // a string that is comment or blank line free
        string temp_line=createCommentFreeLine(line);

        temp_line=createContentFreeLine(temp_line);

        output_file<<temp_line;
        output_file<<"\n";

        getline(input_file, line);

    }

    // closing of temporary comment and space free lines
    output_file.close();
    // closing the input file
    input_file.close();

}

/*************************************************************************/
// Receives the file for which we want to calculate cyclomatic complexity
/*************************************************************************/

void calcComplexity(string file_name){

    /**********************************************/
    multiple_comment_line_flag_cc=false;
    createCommentAndContentFreeFile(file_name);
    measureComplexity();    

}

