
#include<bits/stdc++.h>
using namespace std;

/************ Variable from CyclomaticComplexity.h ***************/
extern string comment_free_file;
extern string name_of_input_file_excluding_dot;

/************ Method from MethodLevelLoc.h ***************/
extern void nameAssign (string name ,int method_number);

/************ Variables to be used ***************/
char method_area_file[] = "methodArea.txt";
string saved_file[5000];
int save_file_size=0;
int total_constructor_number;
float average_complexity;

struct node {

    int start_line;
    int finish_line;
    int complexity;
    bool name_flag; // true if exists in the line containing double brace
    bool constructor=false;
    string name;

} temp_node;

vector<node> method_tracer;

/************ Methods to be used ****************/
void measureComplexity();
void methodDetector(string file_name);
void saveInString(string file_name);
void assignName();
void calculation();
void calculateAverageComplexity();
void totalConstructorCounter();
void printComplexityPerMethod(int index_number);
int countPredicates(int first_line, int last_line);
int countDoubleCharacaterPredicates(int first_line, int last_line);
int countSingleCharacterPredicates(int first_line, int last_line);
int loopAndSelectionStatementCounter(int first_line, int last_line);
string findStringBeforeFirstBrace(string line);
string getMethodNameFollowedBySequence(int idx);
bool getTypeMethodOrConstructorBySequence(int idx);
int getComplexityPerMethod(int idx);
/************ Methods definations **************/

int getComplexityPerMethod(int idx){
    return method_tracer[idx].complexity;
}

string getMethodNameFollowedBySequence(int idx){
    return method_tracer[idx].name;
}

bool getTypeMethodOrConstructorBySequence(int idx){
    return method_tracer[idx].constructor;
}

void printComplexityPerMethod(int index_number){
    printf("\t\tCyclomatic Complexity : %d\n\n", method_tracer[index_number].complexity);
}

void calculateAverageComplexity(){

    average_complexity = 0.0;
    int method_and_constructor = method_tracer.size();
    int temp_total_method = method_and_constructor - total_constructor_number;

    for(int i=0; i<method_and_constructor; i++) {
        if(method_tracer[i].constructor==false){
            //average_complexity += method_tracer[i].complexity;
            average_complexity=max(average_complexity, (float)method_tracer[i].complexity);
        }
    }

    // average_complexity = average_complexity / (float)temp_total_method;
    // cout << "average: " << average_complexity << "\n";

}

// Count the occurrences of single character predicates in a range of lines
int countSingleCharacterPredicates(int first_line, int last_line) {

    int temp_complexity = 0;

    for (int i = first_line; i <= last_line; i++) {
        int temp_line_size = saved_file[i].size() - 1; // We are checking one character at a time 
        
        for (int j = 0; j < temp_line_size; j++) {
            if (saved_file[i][j] == '>' && saved_file[i][j + 1] == '>') {
                continue;
            } 
            else if (saved_file[i][j] == '>' && saved_file[i][j + 1] == '=') {
                continue;
            } 
            else if (saved_file[i][j] == '<' && saved_file[i][j + 1] == '=') {
                continue;
            } 
            else if (saved_file[i][j] == '<' && saved_file[i][j + 1] == '<') {
                continue;
            } 
            else if (saved_file[i][j] == '!' && saved_file[i][j + 1] == '=') {
                continue;
            } 
            else if (saved_file[i][j] == '<') {
                temp_complexity++;
            } 
            else if (saved_file[i][j] == '>') {
                temp_complexity++;
            } 
            else if (saved_file[i][j] == '!') {
                temp_complexity++;
            }
        }
    }

    return temp_complexity;
}

int countDoubleCharacaterPredicates(int first_line, int last_line){

    int temp_complexity = 0;

    for (int i = first_line; i <= last_line; i++) {
        int temp_line_size = saved_file[i].size() - 1; // We are checking two characters at a time
        
        for (int j = 0; j < temp_line_size; j++) {
            if (saved_file[i][j] == '=' && saved_file[i][j+1] == '=') {
                temp_complexity++;
            } 
            else if (saved_file[i][j] == '>' && saved_file[i][j+1] == '=') {
                temp_complexity++;
            } 
            else if (saved_file[i][j] == '<' && saved_file[i][j+1] == '=') {
                temp_complexity++;
            } 
            else if (saved_file[i][j] == '!' && saved_file[i][j+1] == '=') {
                temp_complexity++;
            }
        }
    }

    return temp_complexity;
}

int loopAndSelectionStatementCounter(int first_line, int last_line){

    vector<string> required_keywords = {"if", "while", "for", "||", "&&"};
    int temp_complexity=0;

    for(int i=first_line;i<last_line;i++){

        string word="";
        string temp_line=saved_file[i];

        for(int j=0;j<=temp_line.size();j++){

            if(j==temp_line.size() || temp_line[j]==' ' || temp_line[j]=='(' || temp_line[j]==')' || temp_line[j]=='{' || temp_line[j]=='}' || temp_line[j]==';'){
                //cout << word << " ";
                for(string ele : required_keywords){
                    if(word==ele){
                        temp_complexity++;
                        break;
                    }
                }

                word="";
            }
            else{
                word+=temp_line[j];
            }
        }
    }
    //cout << "in func: " << temp_complexity << "\n";

    return temp_complexity;
}

int countPredicates(int first_line, int last_line){

    int temp_complexity=0;
    int double_char_logic_count=countDoubleCharacaterPredicates(first_line, last_line);
    int single_char_logic_count=countSingleCharacterPredicates(first_line, last_line);
    temp_complexity+=(double_char_logic_count+single_char_logic_count);
    temp_complexity+=loopAndSelectionStatementCounter(first_line, last_line);

    // count each case in switch statements
    for(int i=first_line;i<last_line;i++){
        if(saved_file[i].find("case") != string::npos){
            temp_complexity++;
        }
    }

    // count each try-catch block
    int try_complexity=0;
    for(int i=first_line;i<last_line;i++){
        if(saved_file[i].find("try") != string::npos){
            try_complexity++;
        }
        if(saved_file[i].find("catch") != string::npos){
            try_complexity++;
        }
    }
    temp_complexity+=try_complexity;

    temp_complexity++; // CC=D+1

    return temp_complexity;
}

void calculation(void){

    int temp_size = method_tracer.size();

    for (int i=0;i<temp_size;i++){

        int first_line=method_tracer[i].start_line;
        int last_line=method_tracer[i].finish_line;
        int complexity_per_method=countPredicates(first_line, last_line);
        method_tracer[i].complexity=complexity_per_method;
        // cout << "Double char logical st count: ";
        // int double_char_logic_count=countDoubleCharacaterPredicates(first_line, last_line);
        // cout << method_tracer[i].name << " " << double_char_logic_count << "\n";
        // cout << "Single char logical st count: ";
        // int single_char_logic_count=countSingleCharacterPredicates(first_line, last_line);
        // cout << method_tracer[i].name << " " << single_char_logic_count << "\n";
    }
}

void assignName(){

    int temp_size = method_tracer.size(); // Size of total methods
    for (int i = 0; i < temp_size; i++) {

        int first_line = method_tracer[i].start_line; // First line number of a method
        string temp_words[10]; // To store words obtained from analyzing the lines

        int counter;
        string word;

        // If we found the method name in the line of the second brace
        // Check whether the name exists within the second brace
        istringstream iss(findStringBeforeFirstBrace(saved_file[first_line]));
        for (counter = 0; iss >> word; counter++) {
            temp_words[counter] = word;
            // cout << word << "\n";
        }

        if (counter > 1) {
            if(temp_words[counter-1]==name_of_input_file_excluding_dot){
                method_tracer[i].constructor=true;
            }
            method_tracer[i].name = temp_words[counter-1]; // Method name will exist as the second word
            nameAssign(temp_words[counter-1], i);
            method_tracer[i].name_flag = true;
            continue;

        }

        // If we found the method name before the line of the second brace
        // Check whether the name exists above the second brace
        istringstream iss1(findStringBeforeFirstBrace(saved_file[first_line - 1]));
        for (counter = 0; iss1 >> word; counter++) {
            
            temp_words[counter] = word;

        }
        if (counter > 1) {
            if(temp_words[counter-1]==name_of_input_file_excluding_dot){
                method_tracer[i].constructor=true;
            }
            nameAssign(temp_words[counter-1], i);
            method_tracer[i].name = temp_words[counter-1]; // Method name will exist as the second word
            method_tracer[i].name_flag = false;
            
        }
    }

}

string findStringBeforeFirstBrace(string line){

    int first_brace_position = -1; // Location of the first opening parenthesis '('
    int len = line.size();

    for (int i = 0; i < len; i++) {

        if (line[i] == '(') {
            first_brace_position = i;
        }
        else if (line[i] == '{') {
            line[i] = ' '; // Replace the opening brace with a space
            break; // Exit the loop since we found the first opening brace
        }
    }

    // Check if an opening parenthesis was found
    if (first_brace_position != -1) {
        return line.substr(0, first_brace_position); // Return the substring before the first opening parenthesis
    } else {
        return ""; // Return an empty string if no opening parenthesis was found
    }

}

void saveInString(string file_name){

    save_file_size = 0; // Initialize the number of lines in the file
    ifstream input_file(file_name);  // Opening the input file with ifstream

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
        printf("File not found\n"); // Print an error message if the input file was not found
    }

}

void totalConstructorCounter(){
    
    total_constructor_number=0;
    int temp_total_method=method_tracer.size();
    
    for(int i=0;i<temp_total_method;i++){
        if(method_tracer[i].constructor){
            total_constructor_number++;
        }
    }
}

void methodDetector(string file_name){

    saveInString(comment_free_file);

    stack<char> double_quote;
    stack<char> first_bracket;
    int method_first_line;
    method_tracer.clear();

    for (int i = 0; i < save_file_size; i++) {
        
        int str_len = saved_file[i].size();

        for (int j = 0; j < str_len; j++) {

            if(first_bracket.size()==2 and double_quote.empty() and saved_file[i][j]=='('){
                first_bracket.pop();
                method_first_line=i+1;
                continue;
            }
            // Check for the opening brace '{' when double quotes stack is empty and the first bracket stack size is 2
            if (first_bracket.size() == 2 and double_quote.empty() && saved_file[i][j] == '{') {
                
                temp_node.start_line = method_first_line;
                double_quote.push('{');

            }
            // Check for the closing brace '}' when double quotes stack size is 1 and the first bracket stack size is 2
            else if (first_bracket.size() == 2 and double_quote.size() == 1 && saved_file[i][j] == '}') {
                
                temp_node.finish_line = i;
                //cout << "strart " << temp_node.start_line << " finish " << temp_node.finish_line << "\n";
                method_tracer.push_back(temp_node);
                double_quote.pop();
                first_bracket.pop();
                first_bracket.pop();

            }
            // Check for the opening brace '{' and push it to the double quotes stack
            else if (saved_file[i][j] == '{' and first_bracket.empty()==false) {
                double_quote.push('{');
                //cout << i << " " << j << "\n";
            }
            // Check for the closing brace '}' and pop it from the double quotes stack
            else if (saved_file[i][j] == '}' and first_bracket.empty()==false) {
                double_quote.pop();
            }
            // Check for '()' when double quotes stack is empty and first bracket stack is empty
            // (Assuming it is checking for parentheses used in function calls)
            else if (first_bracket.empty() and double_quote.empty() and saved_file[i][j] == '(') {
                first_bracket.push('(');
                method_first_line=i;
                // cout << method_first_line << "\n";
            }
            else if (first_bracket.size() == 1 and double_quote.empty() and saved_file[i][j] == ')') {
                first_bracket.push(')');
            }
        }
        //cout << "line " << i << " {} size: " << double_quote.size() << " () size: " << first_bracket.size() << "\n";

    }

    // Detect methods and push the nodes keeping that information

    // Assign a name to each method
    assignName();
}

void measureComplexity(){

    methodDetector(comment_free_file);
    // for(int i=0;i<method_tracer.size();i++){
    //     cout << method_tracer[i].name << "\n";
    // }
    totalConstructorCounter();

    calculation();

}

