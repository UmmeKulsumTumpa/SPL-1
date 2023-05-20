#include<bits/stdc++.h>
using namespace std;

extern string comment_free_file;

/******************* Variables to be used ************/
string simplified_file="simplifiedFile.txt";
string segmented_file="segmentedFile.txt";

/************* Methods to be used *************/
void createControlFlowGraph();
void segmentationOfCommentFreeFile();
void simplificationOfCommentFreeFile();

/*********** Method definations ***********/



void segmentationOfCommentFreeFile(){
    ifstream input_file(comment_free_file);
    ofstream output_file(segmented_file); 

    if (not input_file.is_open()){
        printf("File not found\n");
        return;
    }

    string per_line_in_file;
    getline(input_file, per_line_in_file);

    while (not input_file.eof()){
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
}
