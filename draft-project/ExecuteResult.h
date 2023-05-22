#include<bits/stdc++.h>

#include "LOC.h"
#include "MethodLevelLOC.h"
#include "CyclomaticComplexity.h"
#include "ComplexityAnalyzer.h"
#include "BuildingControlFlowGraph.h"

using namespace std;

/*+++++++++++++++++++++++++++++ variables & methods of LOC.h +++++++++++++++++++++++++++++*/
extern void LOCResultPrinter();

/*++++++++++++++++++++++++++++ variables & methods of MethodLevelLOC.h ++++++++++++++++++++++++++*/
extern int total_method; // total number of methods detected in the source code
extern void locMethodBasedResult(int i);

/*++++++++++++++++++++++++++++ variables & methods of ComplexityAnalyzer.h ++++++++++++++++++++++++++*/
extern void printComplexityPerMethod(int index_number);
extern float average_complexity;
extern vector<node> method_tracer;

/****************************** Methods to be used *******************************/
void detailedResultPrinter();
void executeCalculation(string file_name);
void overAllResultPrinter();
void userMenuProvider(string file_name);
void methodWiseMetricResultPrinter();
void WMCResultPrinter();

/**************************** method definations ****************************/

void WMCResultPrinter(){

}

void methodWiseMetricResultPrinter(){
    printf("\n\n\t*** Displaying Method Level Result ***\n\n");
    for(int i=0;i<total_method;i++){
        if(method_tracer[i].constructor){
            continue;
        }
        locMethodBasedResult(i);
        printComplexityPerMethod(i);
    }
    printf("\n\n\n");
}

void userMenuProvider(string file_name){

    string key_response;

    do{
        printf("\n\n\tProvided File Name: ");
        cout << file_name << "\n\n";
        printf("\t-> Here is the provided User Menu:\n");
        printf("\t1. Overall Metric Result\n");
        printf("\t2. MethodWise Metric Result\n");
        printf("\t3. WMC Result\n");
        printf("\t4. Exit\n");
        printf("\n\t-> Enter your response: ");

        cin >> key_response;

        if(key_response=="1"){
            overAllResultPrinter();
        }
        else if(key_response=="2"){
            methodWiseMetricResultPrinter();
        }
        else if(key_response=="3"){
            WMCResultPrinter();
        }
        else if(key_response!="4"){
            printf("\n\tPlease check the user menu to select a valid response\n\n");
        }

    }
    while(key_response!="4");

    printf("\n\n");
}

void overAllResultPrinter(){
    printf("\n\n\t*** Displaying OverAll Metric Result ***\n\n");
    LOCResultPrinter();
    printf("\n\n");
}

void detailedResultPrinter(){

    for(int i=0;i<total_method;i++){
        if(method_tracer[i].constructor){
            continue;
        }
        locMethodBasedResult(i);
        printComplexityPerMethod(i);
    }
    printf("\n\n\n");
}



void executeCalculation(string file_name){
    
    CalcLOC(file_name);
    calcComplexity(file_name);
    //LOCResultPrinter();
    //detailedResultPrinter();
    createControlFlowGraph();
    //userMenuProvider(file_name);
}