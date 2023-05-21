#include<bits/stdc++.h>
using namespace std;

extern string comment_free_file;

/******************* Variables to be used ************/
const int MAX_SIZE=3003;
string simplified_file="simplifiedFile.txt";
vector<string> lines;
vector<int>closing_curly_braces(MAX_SIZE);
vector<int>opening_curly_braces(MAX_SIZE);
int control_graph[MAX_SIZE][MAX_SIZE];
vector<int>control_graph_list[MAX_SIZE];

/************* Methods to be used *************/
void createControlFlowGraph();
void segmentationOfCommentFreeFile();
void simplificationOfCommentFreeFile();
void closingCurlyBracesProcessor();
void openingCurlyBracesProcessor();
void connectNodalStatementsAndBuildGraph();

/*********** Method definations ***********/

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

    for(i=0;i<lines.size();i++){
        
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

        for(int j=0;j<=per_line.size();j++){
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

                // check for while/for
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
                else if(word=="continue"){
                    loop_back=loop_store.back();
                    if(closing_curly_braces[loop_back]==0){
                        control_graph[i+1][loop_back]=1;
                    }
                    else{
                        control_graph[i+1][loop_back-1]=1;
                    }
                }
                else if(word=="break"){
                    loop_back=loop_store.back();
                    if(closing_curly_braces[loop_back]==0){
                        control_graph[i+1][loop_back+1]=1;
                    }
                    else{
                        control_graph[i+1][closing_curly_braces[loop_back]+1]=1;
                    }
                }
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
                else if(word=="else"){
                    j+=2;
                }
                else if(word=="switch"){
                    bool flag_more_case=true;
                    
                }
                // reset the word to empty string
                word="";
            }
            else{
                word+=per_line[j];
            }
        }
    }
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
        getline(input_file, per_line_in_file);
        lines.push_back(per_line_in_file);
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

    for(int i=1;i<=lines.size();i++){
        cout << i << " -> ";
        for(int j=1;j<=lines.size();j++){
            if(control_graph[i][j]){
                cout << j << " ";
            }
        }
        cout << "\n";
    }

    // for(int i=0;i<lines.size();i++){
    //     cout << "opening: " << i << " closing: " << closing_curly_braces[i] << "\n";
    // }
}
