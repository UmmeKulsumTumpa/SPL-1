#include<bits/stdc++.h>
using namespace std;

/****************** Methods from BuildingControlFlowGraph.h ***************/
extern vector<string> methodAndConstructorFreeFileCreate();

/**************** Variables to be used ********************/
vector<string> method_free_lines;
vector<string> abstract_methods;
//  datatype    name-of-fields
//    ||           ||
map<string, vector<string> > fields;
bool has_abstract_method;

/*************** Methods to be used ******************/
void classFieldProcessor();
void saveMethodFreeLinesInString();
void fieldSeparatorFromString();
void displayFieldInfo();
void checkForAbstractMethod();
vector<string> reSizingTheAbstractMethodNames();
void printAbstractMethods();
void displayAbstractMethodInfo();

/*************** Method defination ****************/

void displayAbstractMethodInfo(){
    
}

void printAbstractMethods(){

    vector<string> resized_names=reSizingTheAbstractMethodNames();
    printf("\n\n\t*** Displaying Abstract Methods ***\n\n");

    for(string name : resized_names){
        cout << "\t\t" << name << "\n";
    }
    printf("\n\n");
}

vector<string> reSizingTheAbstractMethodNames(){

    vector<string> resized_names;

    for(int i=0;i<abstract_methods.size();i++){

        string temp_name=abstract_methods[i];
        string temp_resized_name="";

        for(char ch : temp_name){
            if(ch=='('){
                break;
            }
            temp_resized_name+=ch;
        }

        resized_names.push_back(temp_resized_name);
    }

    return resized_names;
}

void checkForAbstractMethod(){

    has_abstract_method=false;

    map<string, vector<string> >::iterator itr;
    itr=fields.begin();
    while(itr != fields.end()){
        
        vector<string> names=itr->second;
        for(string name : names){
            
            bool is_abstract_method=false;

            for(char ch : name){
                if(ch=='(' || ch==')'){
                    has_abstract_method=true;
                    is_abstract_method=true;
                    break;
                }
            }

            // if is abstract method, push to the vector
            if(is_abstract_method){
                abstract_methods.push_back(name);
            }
        }

        itr++;
    }
}

void displayFieldInfo(){
    
    printf("\n\n\t*** Displaying Fields with Data Type ***\n\n");
    
    map<string, vector<string> >::iterator itr;
    itr=fields.begin();
    while(itr != fields.end()){
        
        bool is_abstract_method=false;
        vector<string> names=itr->second;

        for(string name : names){
            
            for(string abstract_method : abstract_methods){
                if(abstract_method==name){
                    is_abstract_method=true;
                    break;
                }
            }
        }

        if(!is_abstract_method){

            cout << "\n\tData Type: " << itr->first << "\n";
            cout << "\tFields Name: \n";
            for(int idx=0;idx<itr->second.size();idx++){
                cout << "\t\t";
                cout << itr->second[idx] << "\n";
            }
        }

        itr++;
    }
    printf("\n");
}

void fieldSeparatorFromString(){

    int len=method_free_lines.size();

    for(int i=0;i<len;i++){

        int temp_size=method_free_lines[i].size();
        string temp_line=method_free_lines[i];
        vector<string> temp_field_store;
        string data_type;
        string word="";
        int end_type;

        // find datatype first
        vector<string> keywords={
            "default", "public", "private", "protected",
            "static", "final", "abstrct", "transient", "synchronized", "volatile"
        };

        for(int j=0;j<temp_size;j++){
            
            if(temp_line[j]==' '){
                
                bool is_keyword=false;
                for(string ele : keywords){
                    if(ele == word){
                        is_keyword=true;
                        break;
                    }
                }

                if(!is_keyword and word!="" and word!=" "){
                    data_type=word;
                    break;
                }

                word="";
            }
            else{
                word+=temp_line[j];
            }
        }

        //cout << "data_type: " << data_type << "\n";
        word="";
        string word_comma="";
        bool in_parenthesis=false;

        for(int j=temp_size-2; j>=0; j--){

            if(temp_line[j]==')'){
                in_parenthesis=true;
            }
            
            if(temp_line[j]==' '){
                
                reverse(word.begin(), word.end());
                if(word==data_type){
                    
                    reverse(word_comma.begin(), word_comma.end());
                    word_comma.erase(0, word.size()); // remove the part of data type
                    temp_field_store.push_back(word_comma);
                    break;
                }
                word="";
            }
            else{
                word+=temp_line[j];
            }

            if(temp_line[j]==','){
                
                if(!in_parenthesis){ // it may be in abstract class parameter list, we won't add it
                    reverse(word_comma.begin(), word_comma.end());
                    //cout << "word_comma " << word_comma << "\n";
                    temp_field_store.push_back(word_comma);
                    word_comma="";
                }
            }
            else{
                word_comma+=temp_line[j];
            }

            if(temp_line[j]=='('){
                in_parenthesis=false;
            }
        }

        vector<string> temp_final_fields;
        // now process temp fields
        for(int j=0;j<temp_field_store.size();j++){
            
            bool has_equal_sign=false;
            string word=temp_field_store[j];

            for(int k=0;k<word.size();k++){
                if(word[k]=='='){
                    has_equal_sign=true;
                    break;
                }
            }

            if(!has_equal_sign){
                
                string final_word="";
                for(int k=0;k<word.size();k++){
                    if(word[k]!=' '){
                        final_word+=word[k];
                    }
                }
                temp_final_fields.push_back(final_word);
                continue;
            }

            // if word has = sign
            string temp_word="";
            for(int k=0;k<word.size();k++){
                if(word[k]=='='){
                    break;
                }
                temp_word+=word[k];
            }

            string final_word="";
            for(int k=0;k<temp_word.size();k++){
                if(temp_word[k]!=' '){
                    final_word+=temp_word[k];
                }
            }
            temp_final_fields.push_back(final_word);
        }
        // reverse temp fields
        reverse(temp_final_fields.begin(), temp_final_fields.end());
        // cout << "fields: " << "\t";
        // for(auto ele : temp_final_fields){
        //     cout << ele << " ";
        // }
        // cout << "\n";

        map<string, vector<string> >::iterator itr;
        itr=fields.find(data_type);

        if(itr==fields.end()){
            fields.insert({data_type, temp_final_fields});
            continue;
        }

        // has a list of that data_type already
        for(string ele : temp_final_fields){
            itr->second.push_back(ele);
        }
    }
}

void saveMethodFreeLinesInString(){
    
    vector<string> temp_store;
    vector<string> draft_lines;
    temp_store=methodAndConstructorFreeFileCreate();

    // now separate lines by semicolons
    string temp_line="";

    for(int i=0;i<temp_store.size();i++){
        
        string per_line=temp_store[i];

        for(int j=0;j<per_line.size();j++){
            
            if(per_line[j]==';'){// it will add a line to draft_lines
                temp_line+=per_line[j];
                draft_lines.push_back(temp_line);
                temp_line="";
            }
            else{
                temp_line+=per_line[j];
            }
        }
    }

    temp_line="";
    for(int i=0;i<draft_lines.size();i++){

        string temp_str="";
        for(int j=0;j<draft_lines[i].size();j++){
            
            if(draft_lines[i][j]=='{'){
                while(draft_lines[i][j]!='}'){
                    j++;
                }
            }
            else{
                temp_str+=draft_lines[i][j];
            }
        }

        method_free_lines.push_back(temp_str);
    }

    //method_free_lines=draft_lines;
}

void classFieldProcessor(){

    saveMethodFreeLinesInString();
    fieldSeparatorFromString();
    checkForAbstractMethod();

    // for(auto itr : fields){
    //     cout << itr.first << "\t";
    //     for(auto ele : itr.second){
    //         cout << ele << " ";
    //     }
    //     cout << "\n";
    // }

    // for(int i=0;i<method_free_lines.size();i++){
    //     cout << method_free_lines[i] << "\n";
    // }
}
