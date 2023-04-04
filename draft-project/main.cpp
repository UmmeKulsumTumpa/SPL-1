#include<bits/stdc++.h>
#include "ExecuteResult.h"
using namespace std;

// this method detects the file type of the given file
// if the file is .java it will return TRUE
bool fileTypeDetector(string file_name){
    int temp_file_size=file_name.size();
    int dot_position=-1;

    for(int i=0;i<temp_file_size;i++){

        if(file_name[i]=='.'){
            dot_position=i;
            break;
        }
    }

    string type_name=file_name.substr(dot_position, temp_file_size-dot_position);

    if(type_name == ".java"){
        return true;
    }

    return false;
}

int main()
{
    string input_file_name="SourceCodeJava.java";
    // char *input_file_name;

    // printf("Enter input file name: ");
    // cin>>input_file_name;

    bool flag=fileTypeDetector(input_file_name);

    if(!flag){
        printf("Sorry, Your input provides invalid file type.\n");
        return 0;
    }

    executeCalculation(input_file_name);

    return 0;
}

