
#include<bits/stdc++.h>
using namespace std;

/************ Variable from CyclomaticComplexity.h ***************/
extern string comment_free_file;

/************ Method from MethodLevelLoc.h ***************/
extern void nameAssign (string name ,int method_number);

/************ Variables to be used ***************/

string method_area_file = "methodArea.txt";
string saved_file[5000];
int save_file_size=0;
float average_complexity;

struct node {

    int start_line;
    int finish_line;
    int complexity;
    bool name_flag; // true if exists in the line containing double brace
    string name;

} temp_node;

vector<node> method_tracer;


/************ Methods to be used ****************/
void measureComplexity();
void methodDetector(string file_name);
void saveInString(string file_name);
void assignName();
string findStringBeforeFirstBrace(string line);

/************ Methods definations **************/

void assignName(){

    // Size of total methods
    int temp_size = method_tracer.size();
    for (int i = 0; i < temp_size; i++) {

        // First line number of a method
        int first_line = method_tracer[i].start_line;
        // To store words obtained from analyzing the lines
        string temp_words[10];

        int counter;
        string word;

        // If we found the method name in the line of the second brace
        // Check whether the name exists within the second brace
        istringstream iss(findStringBeforeFirstBrace(saved_file[first_line]));
        for (counter = 0; iss >> word; counter++) {
            temp_words[counter] = word;
        }

        if (counter > 1) {
            
            // Method name will exist as the second word
            method_tracer[i].name = temp_words[1];
            nameAssign(temp_words[1], i);
            method_tracer[i].name_flag = true;
            continue;

        }

        // If we found the method name before the line of the second brace
        // Check whether the name exists above the second brace
        istringstream iss1(findStringBeforeFirstBrace(saved_file[first_line - 1]));
        for (counter = 0; iss1 >> word; counter++) {
            
            temp_words[counter] = word;
            nameAssign(temp_words[1], i);

        }
        if (counter > 1) {
            
            // Method name will exist as the second word
            method_tracer[i].name = temp_words[1];
            method_tracer[i].name_flag = false;
            
        }
    }

}

string findStringBeforeFirstBrace(string line){

    // Location of the first opening parenthesis '('
    int first_brace_position = -1;
    int len = line.size();

    for (int i = 0; i < len; i++) {

        if (line[i] == '(') {
            first_brace_position = i;
        }
        else if (line[i] == '{') {
            // Replace the opening brace with a space
            line[i] = ' ';
            // Exit the loop since we found the first opening brace
            break;
        }
    }

    // Check if an opening parenthesis was found
    if (first_brace_position != -1) {
        // Return the substring before the first opening parenthesis
        return line.substr(0, first_brace_position);
    } else {
        // Return an empty string if no opening parenthesis was found
        return "";
    }

}

void saveInString(string file_name){

    // Initialize the number of lines in the file
    int save_file_size = 0;
    // Opening the input file with ifstream
    ifstream input_file(file_name);  

    //Check if the input file was successfully opened
    if(input_file.is_open()) {

        string line;
        getline(input_file, line);  

        while(!input_file.eof()){
            
            saved_file[save_file_size++] = line; 
            getline(input_file, line);

        }

        input_file.close();
    }
    else {
        // Print an error message if the input file was not found
        printf("File not found\n");
    }

}

void methodDetector(string file_name){

    saveInString(comment_free_file);

    stack<char> double_quote;
    stack<char> first_bracket;
    method_tracer.clear();

    for (int i = 0; i < save_file_size; i++) {
        
        int str_len = saved_file[i].size();

        for (int j = 0; j < str_len; j++) {
            // Check for the opening brace '{' when double quotes stack is empty and the first bracket stack size is 2
            if (double_quote.empty() && saved_file[i][j] == '{' && first_bracket.size() == 2) {
                
                temp_node.start_line = i;
                double_quote.push('{');

            }
            // Check for the closing brace '}' when double quotes stack size is 1 and the first bracket stack size is 2
            else if (double_quote.size() == 1 && saved_file[i][j] == '}' && first_bracket.size() == 2) {
                
                temp_node.finish_line = i;
                method_tracer.push_back(temp_node);
                double_quote.pop();
                first_bracket.pop();
                first_bracket.pop();

            }
            // Check for the opening brace '{' and push it to the double quotes stack
            else if (saved_file[i][j] == '{') {
                double_quote.push('{');
            }
            // Check for the closing brace '}' and pop it from the double quotes stack
            else if (saved_file[i][j] == '}') {
                double_quote.pop();
            }
            // Check for '()' when double quotes stack is empty and first bracket stack is empty
            // (Assuming it is checking for parentheses used in function calls)
            else if (saved_file[i][j] == '(' && double_quote.empty() && first_bracket.empty()) {
                first_bracket.push('(');
            }
            else if (saved_file[i][j] == ')' && double_quote.empty() && first_bracket.size() == 1) {
                first_bracket.push(')');
            }
        }

    }

    // Detect methods and push the nodes keeping that information

    // Assign a name to each method
    assignName();


}

void measureComplexity(){



}

