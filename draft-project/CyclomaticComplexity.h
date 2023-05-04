
#include<bits/stdc++.h>
using namespace std;

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


/*******************************************/
// if line coinains target_sub_string
// the length of find() > 0
/*******************************************/
bool lengthForRequiredSubstring(string line, string target_sub_string){

    if(line.find(target_sub_string)!=string::npos){
        return true;
    }
    else{
        return false;
    }
    
}

/*********************************************************/
// erases the comment between ()
/*********************************************************/

string createContentFreeLine(string line){

    int line_size = line.size();

    bool flag_double_quote = false;
    bool flag_single_quote = false;

    // Removes the contents between single quote and double quote

    for (int i = 0; i < line_size; i++) {

        // corresponding char for ASCII 39 is <'>
        // as we represent character inside 
        // single quote, so we have to use
        // corresponding ASCII value of <'>

        if ((line[i] == 39 || line[i] == '"') && flag_double_quote == false && flag_single_quote == false) {

            if (line[i] == 39){
                flag_single_quote = true;
            }
            else if (line[i] == '"') {
                flag_double_quote = true;
            }

            line[i] = ' ';

            continue;

        }
        else if (flag_double_quote == true) {
            
            if (line[i] == '"') {
                flag_double_quote = false;
            }

            line[i] = ' ';

        }
        else if (flag_single_quote == true) {
            
            if (line[i] == 39) {
                flag_single_quote = false;
            }

            line[i] = ' ';

        }
    }

    return line;

}

/*********************************************************/
// function that removes comments and blank lines
// returns a string that is comment or blank line free
/*********************************************************/

string createCommentFreeLine(string line){

    string target_sub_string;
    bool len;

    // if the line contains "package" keyword
    // we will ignore the line

    target_sub_string="package";
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

    target_sub_string="import";
    len=lengthForRequiredSubstring(line, target_sub_string);

    if(len){
        // we found the target string in the line
        // so return
        return "";
    }

    // ignores blank lines

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
            
            //if single line comment character is reached, then we ignore the next characters in that line

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
    }
}

/*************************************************************************/
// Receives the file for which we want to calculate cyclomatic complexity
/*************************************************************************/

void calcComplexity(string file_name){

    /**********************************************/

    multiple_comment_line_flag_cc=false;

}

