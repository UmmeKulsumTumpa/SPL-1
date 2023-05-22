#include<bits/stdc++.h>
using namespace std;

extern string comment_free_file;

/*************** Methods and Variables of ComplexityAnalyzer.h *******************/
extern string getMethodNameFollowedBySequence(int idx);
extern bool getTypeMethodOrConstructorBySequence(int idx);

/******************* Variables to be used ************/
const int MAX_SIZE=3003;
string simplified_file="simplifiedFile.txt";
vector<string> lines;
vector<int>closing_curly_braces(MAX_SIZE);
vector<int>opening_curly_braces(MAX_SIZE);
int control_graph[MAX_SIZE][MAX_SIZE];
vector<int>control_graph_list[MAX_SIZE];

struct graph_node{

    int start_line;
    int finish_line;
    bool constructor=false;
    string name;
    vector<int> count_return;

} temp_graph_node;

vector<graph_node> simplified_method_tracer;

/************* Methods to be used *************/
void createControlFlowGraph();
void segmentationOfCommentFreeFile();
void simplificationOfCommentFreeFile();
void closingCurlyBracesProcessor();
void openingCurlyBracesProcessor();
void connectNodalStatementsAndBuildGraph();
void methodAndConstructorSeparatorOfSimplifiedFile();
void setMethodAndConstructorName();
void setMethodAndConstructorFlag();
void returnStatementProcessor();

/*********** Method definations ***********/

void returnStatementProcessor(){

    int tracer_len=simplified_method_tracer.size();
    for(int i=0;i<tracer_len;i++){

        int first_line=simplified_method_tracer[i].start_line;
        int last_line=simplified_method_tracer[i].finish_line;
        
        for(int j=first_line+2;j<last_line;j++){
            
            if(lines[j-1].find("return ") != string::npos){ // for any return type
                simplified_method_tracer[i].count_return.push_back(j);
            }
            
            if(lines[j-1].find("return;") != string::npos){ // for void return type
                simplified_method_tracer[i].count_return.push_back(j);
            }
        }
    }
}

void setMethodAndConstructorFlag(){

    int len=simplified_method_tracer.size();
    for(int i=0;i<len;i++){
        simplified_method_tracer[i].constructor=getTypeMethodOrConstructorBySequence(i);
    }
}

void setMethodAndConstructorName(){

    int len=simplified_method_tracer.size();
    for(int i=0;i<len;i++){
        simplified_method_tracer[i].name=getMethodNameFollowedBySequence(i);
    }
}

void methodAndConstructorSeparatorOfSimplifiedFile(){

    stack<char> double_quote;
    stack<char> first_bracket;
    int method_first_line;
    simplified_method_tracer.clear();
    int lines_size=lines.size();

    for (int i = 0; i < lines_size; i++) {
        
        int str_len = lines[i].size();

        for (int j = 0; j < str_len; j++) {

            if (first_bracket.size() == 2 and double_quote.empty() && lines[i][j] == '{') {
                temp_graph_node.start_line = method_first_line;
                double_quote.push('{');
            }
            else if (first_bracket.size() == 2 and double_quote.size() == 1 && lines[i][j] == '}') {
                
                temp_graph_node.finish_line = i+1;
                //cout << "strart " << temp_node.start_line << " finish " << temp_node.finish_line << "\n";
                simplified_method_tracer.push_back(temp_graph_node);
                double_quote.pop();
                first_bracket.pop();
                first_bracket.pop();

            }
            else if (lines[i][j] == '{' and first_bracket.empty()==false) {
                double_quote.push('{');
                //cout << i << " " << j << "\n";
            }
            else if (lines[i][j] == '}' and first_bracket.empty()==false) {
                double_quote.pop();
            }
            else if (first_bracket.empty() and double_quote.empty() and lines[i][j] == '(') {
                first_bracket.push('(');
                method_first_line=i+1;
            }
            else if (first_bracket.size() == 1 and double_quote.empty() and lines[i][j] == ')') {
                first_bracket.push(')');
            }
        }
        //cout << "line " << i << " {} size: " << double_quote.size() << " () size: " << first_bracket.size() << "\n";

    }

    setMethodAndConstructorFlag();
    setMethodAndConstructorName();
}

void connectNodalStatementsAndBuildGraph(){

    int line_size=lines.size();
    line_size++;
    int i, start, loop_back=0;
    string per_line, word="", word_check="";
    vector<int> loop_store, case_store, switch_store, do_while_store; 

    // every statement has a connection to next statement
    for(int i=1;i<line_size-1;i++){
        control_graph[i][i+1]=1;
    }

    for(i=0;i<lines.size();i++){/*************************** iterate lines *******************/
        
        for(int ele:do_while_store){
            if(ele==i){
                i++;
            }
        }
        
        per_line=lines[i];

        if(loop_store.size()!=0){
            int loop_back_ele=loop_store.back();
            if(closing_curly_braces[loop_back_ele]==0 and i>loop_back_ele){
                loop_store.pop_back();
            }
            else if(closing_curly_braces[loop_back_ele]!=0 and closing_curly_braces[loop_back_ele]<i){
                loop_store.pop_back();
            }
        }

        for(int j=0;j<=per_line.size();j++){/******************** iterate over each line of lines *********************/
            // end of any word in a line
            if(j==per_line.size() || per_line[j]==' ' || per_line[j]=='(' || per_line[j]==')' || per_line[j]=='{' || per_line[j]=='}' || per_line[j]==';'){
                
                vector<string> keywords={
                                        "abstract", "assert", 
                                        "boolean", "break", "byte",
                                        "char", "class", "const","continue", 
                                        "double", 
                                        "enum", "extends", 
                                        "final", "float",
                                        "goto",
                                        "implements", "import", "instanceof", "int", "interface",
                                        "long", 
                                        "native", "new",
                                        "package", "private", "protected", "public",
                                        "return",
                                        "short", "static", "strictfp", "super", "synchronized",
                                        "this", "transient",
                                        "void", "volatile",
                };

                for(string ele : keywords){
                    if(word!=word_check){
                        word_check="";
                    }
                }

                /*-------------------------------------------------- control flow for 'while' and 'for' ---------------------------------------*/
                if(word=="while" || word=="for"){
                    start=i+1;
                    // check for the closing brace
                    while(closing_curly_braces[start]==0){
                        start++;
                        if(start==lines.size()){ // reached end of source code
                            break;
                        }
                    }
                    loop_store.push_back(start); // further use for break or continue
                    if(start!=lines.size()){
                        control_graph[i+1][closing_curly_braces[start]+1]=1;
                        control_graph[closing_curly_braces[start]][closing_curly_braces[start]+1]=0;// in loop, the last line connects to first line
                                                                                                    // for checking the condition to enter loop or break
                        control_graph[closing_curly_braces[start]][i+1]=1;
                    }
                }
                /*-------------------------------------------------- control flow for 'do' ---------------------------------------*/
                else if(word=="do"){
                    start=i+1;
                    while(closing_curly_braces[start]==0){
                        start++;
                        if(start==lines.size()){
                            break;
                        }
                    }
                    
                    string temp_line=lines[closing_curly_braces[start]];
                    string temp_word="";
                    bool got_while=false;

                    for(int idx=0;idx<=temp_line.size();idx++){
                        if(idx==temp_line.size() || temp_line[idx]==' ' || temp_line[idx]=='(' || temp_line[idx]==')' || temp_line[idx]=='{' || temp_line[idx]=='}' || temp_line[idx]==';'){
                            if(temp_word=="while"){
                                got_while=true;
                                temp_word="";
                                break;
                            }
                            else{
                                temp_word="";
                            }
                        }
                        else{
                            temp_word+=temp_line[idx];
                        }
                    }

                    if(got_while){
                        loop_store.push_back(start);
                        do_while_store.push_back(closing_curly_braces[start]);
                    }
                    else{
                        loop_store.push_back(start+1);
                        do_while_store.push_back(closing_curly_braces[start]+1);
                    }

                    if(start!=lines.size()){
                        if(got_while){
                            control_graph[closing_curly_braces[start]][i+1]=1;
                        }
                        else{
                            control_graph[closing_curly_braces[start]+1][i+1]=1;
                        }
                    }
                }
                /*-------------------------------------------------- control flow for 'continue' ---------------------------------------*/
                else if(word=="continue"){
                    loop_back=loop_store.back();
                    if(closing_curly_braces[loop_back]==0){
                        control_graph[i+1][loop_back]=1;
                    }
                    else{
                        control_graph[i+1][loop_back-1]=1;
                    }
                }
                /*-------------------------------------------------- control flow for 'break' ---------------------------------------*/
                else if(word=="break"){
                    loop_back=loop_store.back();
                    if(closing_curly_braces[loop_back]==0){
                        control_graph[i+1][loop_back+1]=1;
                    }
                    else{
                        control_graph[i+1][closing_curly_braces[loop_back]+1]=1;
                    }
                }
                /*-------------------------------------------------- control flow for 'if' ---------------------------------------*/
                else if(word=="if"){
                    
                    int next_else=i, track, idx;
                    bool flag_more_else=true;
                    
                    while(flag_more_else){
                        
                        track=closing_curly_braces[next_else+2];
                        string temp_word="";
                        string compare=lines[track];
                        flag_more_else=false;

                        for(idx=0;idx<=compare.size();idx++){
                            if(idx==compare.size() || compare[idx]==' ' || compare[idx]=='(' || compare[idx]==')' || compare[idx]=='{' || compare[idx]=='}' || compare[idx]==';'){
                                if(temp_word=="else"){
                                    flag_more_else=true;
                                    temp_word="";
                                    control_graph[i+1][track+1]=1;
                                    control_graph[track][track+1]=0;
                                    break;
                                }
                                else{
                                    temp_word="";
                                }
                            }
                            else{
                                temp_word+=compare[idx];
                            }
                        }
                        next_else=track;
                    }
                }
                /*-------------------------------------------------- control flow for 'else' ---------------------------------------*/
                else if(word=="else"){
                    j+=2;
                }
                /*-------------------------------------------------- control flow for 'switch' ---------------------------------------*/
                else if(word=="switch"){
                    bool flag_more_case=true;
                    int outgoing_node=i+2; // flow is from outgoing->incoming
                    int incoming_node=i;
                    int track_last=closing_curly_braces[outgoing_node];
                    // remove nodes from graph
                    control_graph[outgoing_node-1][outgoing_node]=0;
                    control_graph[outgoing_node][outgoing_node+1]=0;

                    while(flag_more_case){

                        string temp_word="";
                        string compare=lines[outgoing_node];
                        flag_more_case=false;

                        for(int idx=0;idx<=compare.size();idx++){
                            
                            if(idx==compare.size() || compare[idx]==' ' || compare[idx]=='(' || compare[idx]==')' || compare[idx]=='{' || compare[idx]=='}' || compare[idx]==':'){
                                
                                if(temp_word=="case" || temp_word=="default"){
                                    flag_more_case=true;
                                    temp_word="";

                                    if(outgoing_node!=i+2){
                                        control_graph[incoming_node+1][outgoing_node+1]=1;
                                    }

                                    incoming_node=outgoing_node;
                                    break;
                                }
                                else if(temp_word=="break"){
                                    flag_more_case=true;
                                    temp_word="";
                                    control_graph[outgoing_node+1][track_last+1]=1;
                                    break;
                                }
                                else{
                                    temp_word="";
                                }
                            }
                            else{
                                temp_word+=compare[idx];
                            }
                        }

                        outgoing_node++;
                        if(outgoing_node==track_last){ // reached the end of switch block
                            break;
                        }
                    }

                    i=track_last+1;
                }
                /*-------------------------------------------------- control flow for 'try' ---------------------------------------*/
                else if(word=="try"){
                    int next_catch=i;
                    bool has_more_catch=true;
                    int incoming_node;

                    while(has_more_catch){

                        incoming_node=closing_curly_braces[next_catch+2];
                        string temp_word="";
                        string compare=lines[incoming_node];
                        has_more_catch=false;

                        for(int idx=0;idx<=compare.size();idx++){

                            if(idx==compare.size() || compare[idx]==' ' || compare[idx]=='(' || compare[idx]==')' || compare[idx]=='{' || compare[idx]=='}'){

                                if(temp_word=="catch"){
                                    has_more_catch=true;
                                    temp_word="";

                                    // add nodes to graph
                                    control_graph[i+1][incoming_node+1]=1;
                                    control_graph[incoming_node][incoming_node+1]=0;
                                    break;
                                }
                                else if(temp_word=="finally"){
                                    temp_word="";
                                    // add nodes to graph
                                    control_graph[i+1][incoming_node+1]=1;
                                    control_graph[i][incoming_node+1]=1; // finally block executes no matter what
                                    break;
                                }
                                else{
                                    temp_word="";
                                }
                            }
                            else{
                                temp_word+=compare[idx];
                            }
                        }

                        next_catch=incoming_node;
                    }
                }
                // reset the word to empty string
                word="";
            }/***************************** end of each probable found word per line ***************************8*/
            else{
                word+=per_line[j];
            }
        }/****************************** end of iterate over each line of lines *****************************/
    }/**************************** end of iterate lines *************************/
}

void closingCurlyBracesProcessor(){
    
    closing_curly_braces.clear();
    vector<int> open_brace_store;
    int idx, idx_open_brace;

    for(idx=0;idx<lines.size();idx++){
        string temp_line=lines[idx];

        for(char ele : temp_line){
            if(ele=='{'){
                opening_curly_braces[idx+1]=1;
                open_brace_store.push_back(idx+1);
                //cout << idx+1 << "\n";
            }
            else if(ele=='}'){
                idx_open_brace=open_brace_store.back();
                open_brace_store.pop_back();
                closing_curly_braces[idx_open_brace]=idx+1;
            }
        }
    }
}

void openingCurlyBracesProcessor(){
    
    for(int idx=0;idx<lines.size();idx++){
        if(closing_curly_braces[idx]!=0){
            opening_curly_braces[idx]=1;
        }
    }
}

void segmentationOfCommentFreeFile(){
    
    ifstream input_file(simplified_file);
    lines.clear();

    if (not input_file.is_open()){
        printf("File not found\n");
        return;
    }

    string per_line_in_file;
    getline(input_file, per_line_in_file);

    while (not input_file.eof()){
        lines.push_back(per_line_in_file);
        getline(input_file, per_line_in_file);
    }

    input_file.close();
}

void simplificationOfCommentFreeFile(){
    
    ifstream input_file(comment_free_file);
    ofstream output_file(simplified_file); 

    if (not input_file.is_open()){
        printf("File not found\n");
        return;
    }

    string per_line_in_file;
    getline(input_file, per_line_in_file);

    while (not input_file.eof()){
        
        bool only_space=true;
        for(int i=0;i<per_line_in_file.size();i++){
            if(per_line_in_file[i]!=' '){
                only_space=false;
                break;
            }
        }

        if(per_line_in_file=="" || only_space){
            getline(input_file, per_line_in_file);
            continue;
        }

        bool has_braces=false;
        for(char ele:per_line_in_file){
            if(ele=='{' || ele=='}'){
                has_braces=true;
                break;
            }
        }

        if(!has_braces){
            output_file<<per_line_in_file;
            output_file<<"\n";
            getline(input_file, per_line_in_file);
            continue;
        }

        only_space=true;
        string temp="";
        for(int i=0;i<per_line_in_file.size();i++){
            
            if(per_line_in_file[i]=='{'){
                if(temp!="" and !only_space){
                    output_file<<temp;
                    output_file<<"\n";
                }
                output_file<<"{\n";
                temp=""; only_space=true;
                continue;
            }
            
            if(per_line_in_file[i]=='}'){
                if(temp!="" and !only_space){
                    output_file<<temp;
                    output_file<<"\n";
                }
                output_file<<"}\n";
                temp=""; only_space=true;
                continue;
            }
            
            if(per_line_in_file[i]!=' '){
                only_space=false;
            }

            temp+=per_line_in_file[i];
        }

        if(temp!=""){
            output_file<<temp;
            output_file<<"\n";
        }

        getline(input_file, per_line_in_file);
    }

    input_file.close();
    output_file.close();
}

void createControlFlowGraph(){
    
    simplificationOfCommentFreeFile();
    segmentationOfCommentFreeFile();
    closingCurlyBracesProcessor();
    openingCurlyBracesProcessor();
    connectNodalStatementsAndBuildGraph();
    methodAndConstructorSeparatorOfSimplifiedFile();
    returnStatementProcessor();

    // for(auto ele:lines){
    //     cout << ele << "\n";
    // }

    // for(int i=1;i<=lines.size();i++){
    //     cout << i << " -> ";
    //     for(int j=1;j<=lines.size();j++){
    //         if(control_graph[i][j]){
    //             cout << j << " ";
    //         }
    //     }
    //     cout << "\n";
    // }

    // for(int i=0;i<lines.size();i++){
    //     if(closing_curly_braces[i]==0){
    //         continue;
    //     }
    //     cout << "opening: " << i << " closing: " << closing_curly_braces[i] << "\n";
    // }

    for(int i=0;i<simplified_method_tracer.size();i++){
        cout << simplified_method_tracer[i].name << " " << simplified_method_tracer[i].constructor << "\t\t";
        cout << simplified_method_tracer[i].start_line << " " << simplified_method_tracer[i].finish_line << "\n";
        cout << "return at line: ";
        for(auto ele:simplified_method_tracer[i].count_return){
            cout << ele << " ";
        }
        cout << "\n\n";
    }
}
