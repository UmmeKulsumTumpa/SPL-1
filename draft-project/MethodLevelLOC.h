
#include<bits/stdc++.h>
using namespace std;

/*++++++++++++++++++++++++++++++++++ variable of LOC.h ++++++++++++++++++++++++++++++++++++++ */
int temp_statement_counter_per_line2;

/*+++++++++++++++++++++++++++++++++ methods of LOC.h ++++++++++++++++++++++++++++++++++++++++*/
extern bool emptyLineCounter(string &temp, int start_index, int final_index);

/********************************* Variables to be used **************************************/
int total_method;
bool multiple_line_comment_flag2 = false;

stack <char> second_bracket_store;
stack <char> first_bracket_store;

// structure to store data of every level
struct Node {

    int blank_line_method ;
    int only_comment_line_method ;
    int total_logical_statements ;
    int physical_line;
    int comment_and_statement_lines;
    int only_statment_lines;
    int temp_statement_counter_per_line2;

    string name;

} locNode;

// method wise result calculation
vector <Node> methodResult;


/*********************************** Methods to be used ***********************************/
void clearLOC(void);
void locMethodBasedResult(int i);
void locNodeInitializer (string temp);
void methodSeparator (string &file_name);
void nameAssign (string name ,int method_number);
void assignLineType2(bool &flag_statement_line, bool &flag_comment_line);
void methodLevelCalculation(string &temp , int start_index , int final_index);
bool findPositionOfMethodName(string temp);
bool onlyCommentLineMethodFinder2(string &temp , int start_index, int final_index );
int getLoc(int i);
int doubleQouteContentRemover(string temp, int current_position, int len);
int onlyStatementCounter2(string &temp , int start_index, int final_index );
int findTheEndOfComment2(string &temp , int start_index, int len );


/************************************* method defination ***********************************/

bool findPositionOfMethodName(string temp) {

    int tempLen = temp.size();

    for(int i=0; i<tempLen; i++) {

        if(temp[i] == '{') {
            temp[i] = ' ';
            temp = temp.substr(0, i);
            break;
        }
    }

    stringstream iss(temp);
    string word;
    int counter =0;

    while(iss>>word) {
        counter++;
    }

    if(counter > 1 ){ 
        return true;
    }
    else {
        return false;
    }

}

//Clear data for methods
void clearLOC(void) {
    
    methodResult.clear();
}

//Initializes locNode result to zero
void locNodeInitializer (string temp) {

    if( findPositionOfMethodName(temp) == true ) {
        locNode.total_logical_statements = -1;
    }
    else {
        locNode.total_logical_statements = 0;
    }

    locNode.blank_line_method = 0;
    locNode.only_comment_line_method = 0;
    locNode.physical_line = 0;
    locNode.comment_and_statement_lines = 0;
    locNode.only_statment_lines = 0;
    locNode.temp_statement_counter_per_line2 = 0;

}

/* Assigns the name of the method calculated from cyclomatic complexity*/
void nameAssign (string name ,int method_number) {
    
    methodResult[method_number].name = name;
}

void locMethodBasedResult(int i){

    cout<<"\n\tMethod Name: "<<methodResult[i].name<<"\n\n";
    printf("\t\tTotal Physical Lines: %d\n", methodResult[i].physical_line );
    printf("\t\tTotal Blank Lines: %d\n", methodResult[i].blank_line_method);
    printf("\t\tTotal Lines of Logical Statement: %d\n", methodResult[i].total_logical_statements);
    printf("\t\tNumber of only Comment Lines: %d\n", methodResult[i].only_comment_line_method);
    printf("\t\tNumber of only Statement Lines: %d\n",  methodResult[i].only_statment_lines);
    printf("\t\tNumber of both Comment and Statement Lines: %d\n", methodResult[i].comment_and_statement_lines);

}

int getLoc(int i) {
    return methodResult[i].total_logical_statements;
}

int findTheEndOfComment2(string &temp , int start_index, int len ) {

    if(multiple_line_comment_flag2 == true) {

        for(int i=start_index;  i<(len-1);  i++) {
            
            if(temp[i]=='*' && temp[i+1]=='/') {

                return (i+2);  //will store the position of first occurring
            }
        }
    }

    return 0;
}

/* This method is same as singleLineAnalyzer in file1
    Defined here again because had problem in linking. I should have use OOP because of this -_-
*/
int onlyStatementCounter2(string &temp , int start_index, int final_index ) {

    int len = final_index;
    int statementAfterCommentFlag = 0;  //will store the position of first occurring */
    temp_statement_counter_per_line2=0;

    statementAfterCommentFlag =  findTheEndOfComment2(temp, start_index, len);

    stack <char> saveSymbol;

    for(int i=statementAfterCommentFlag; i<len; i++) {

        if( saveSymbol.empty() ) {

            if(temp[i] ==';'  && temp[i-1] != ')' ) {
                temp_statement_counter_per_line2++;
            }
            else if(temp[i] == '(' ) {
                saveSymbol.push(temp[i]);
            }
            else if(temp[i] == '"' ) {
                saveSymbol.push(temp[i]);
            }
            else if(i != (len-1)  &&  temp[i]=='/'  &&  temp[i+1]=='*') {
                //when we detect  /*  Comment part
                saveSymbol.push('*'); 
            }
            if(i != (len-1) && temp[i] == '/' && temp[i+1] =='/') {
                //when we detect singleLine Comment
                return temp_statement_counter_per_line2; 
            }

        }
        else {

            if(temp[i] == ')' && saveSymbol.top() == '(' ) {
                saveSymbol.pop();
                temp_statement_counter_per_line2++;
            }
            else if(temp[i] == '"' && saveSymbol.top() == '"') {
                saveSymbol.pop();
            }
            else if(i != (len-1) && temp[i] == '*' && temp[i+1] =='/' && saveSymbol.top() == '*') {
                saveSymbol.pop();
            }
        }

    }

    return temp_statement_counter_per_line2;
}

bool onlyCommentLineMethodFinder2(string &temp , int start_index, int final_index ) {

    int len = final_index-1;
    bool flag2 = false ;
    bool countAsCommentLine = false; //for not detecting print f("//");

    if(multiple_line_comment_flag2 == true) {
        countAsCommentLine = true;
    }

    for(int i=start_index ; i<len; i++) {

        if(temp[i]==' ') {
            continue;
        }
        else if(flag2==false) { //When not inside a (" ");

            if(temp[i]=='/' && temp[i+1]=='/') {
                return true;
            }
            else if(temp[i]=='/' && temp[i+1]=='*') {
                multiple_line_comment_flag2 = true;
                countAsCommentLine = true;
            }
            else if(temp[i]=='*' && temp[i+1]=='/') {
                multiple_line_comment_flag2 = false;
            }
            else if(temp[i]== '"') {
                flag2 = true;
            }

        }
        else if(temp[i]== '"' && flag2 == true) {
            flag2 = false;
        }

    }

    if(countAsCommentLine == true){
        return true;
    }

    return false;

}

// checks whether a line contains both comment and statement
void assignLineType2(bool &flag_statement_line, bool &flag_comment_line) {

    if(flag_statement_line == true && flag_comment_line == true)  {
            
        locNode.comment_and_statement_lines++;
        locNode.only_comment_line_method--;

    }
    else if(flag_statement_line == true) {      
        locNode.only_statment_lines++;
    }

}

void methodLevelCalculation(string &temp , int start_index , int final_index){


    if(emptyLineCounter(temp, start_index, final_index) == true ) {
        locNode.blank_line_method++;
    }
    else {

        bool flag_comment_line  = false;
        bool flag_statement_line = false;
        locNode.physical_line++;

        if(onlyStatementCounter2(temp, start_index, final_index) > 0) {
            
            locNode.total_logical_statements+=temp_statement_counter_per_line2;
            flag_statement_line = true;

        }

        if(onlyCommentLineMethodFinder2(temp, start_index, final_index) == true) {
            
            locNode.only_comment_line_method++;
            flag_comment_line = true;

        }


        // For Detection of lines with both comment & statements and also to count total onlyStatementLines
        // if(flag_statement_line == true && flag_comment_line == true)  {
            
        //     locNode.comment_and_statement_lines++;
        //     locNode.only_comment_line_method--;

        // }
        // else if(flag_statement_line == true) {
            
        //     locNode.only_statment_lines++;
            
        // }

        assignLineType2(flag_statement_line, flag_comment_line);
    }

}

/**
    This method separates the Start point and Endpoint of a method
    Enables to calculate method based LOC metric calculation
*/
/** Ignores the contents inside double quote*/
int doubleQouteContentRemover(string temp, int current_position, int len) {

    for(int i=current_position+1;  i<len;  i++) {
        
        if(temp[i] == '"') {
            
            current_position=i+1;
            return current_position;

        }
    }

    return current_position;
}


void methodSeparator (string &file_name) {

    /*-----------------------------------------------------------------------------------------------*/

    ifstream input_file(file_name);

    if(not input_file.is_open()){
        
        printf("File not found\n");
        return;

    }

    bool start=false, finish=false;

    string temp;
    getline(input_file, temp);

    while(not input_file.eof()){

        for(int i=0;i<temp.size();i++){

            if(first_bracket_store.size()==2 and second_bracket_store.empty() and temp[i]=='{'){
               
                second_bracket_store.push(temp[i]);
                start=true;
                locNodeInitializer(temp);
            } 
            else if(first_bracket_store.size()==2 and second_bracket_store.size()==1 and temp[i]=='}'){
                
                methodLevelCalculation(temp, 0, temp.size());
                methodResult.push_back(locNode);
                total_method++;

                second_bracket_store.pop();
                first_bracket_store.pop();
                first_bracket_store.pop();

                start=false;

            }
            else if(temp[i]=='{' and !first_bracket_store.empty()){
                second_bracket_store.push(temp[i]);
            }
            else if(temp[i]=='}' and !first_bracket_store.empty()){
                second_bracket_store.pop();
            }
            else if(first_bracket_store.empty() and second_bracket_store.empty() and temp[i]=='('){
                first_bracket_store.push(temp[i]);
            }
            else if(first_bracket_store.size()==1 and second_bracket_store.empty() and temp[i]==')'){
                first_bracket_store.push(temp[i]);
            }

        }

        if(start){
            
            methodLevelCalculation(temp, 0, temp.size());
        }

        getline(input_file, temp);
    }

    input_file.close();

}
