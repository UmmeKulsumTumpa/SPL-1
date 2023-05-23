#include<bits/stdc++.h>

#include "LOC.h"
#include "MethodLevelLOC.h"
#include "CyclomaticComplexity.h"
#include "ComplexityAnalyzer.h"
#include "BuildingControlFlowGraph.h"
#include "FieldCounter.h"

using namespace std;

/*+++++++++++++++++++++++++++++ variables & methods of LOC.h +++++++++++++++++++++++++++++*/
extern void LOCResultPrinter();

/*++++++++++++++++++++++++++++ variables & methods of MethodLevelLOC.h ++++++++++++++++++++++++++*/
extern int total_method; // total number of methods detected in the source code
extern void locMethodBasedResult(int i);

/*++++++++++++++++++++++++++++ variables & methods of ComplexityAnalyzer.h ++++++++++++++++++++++++++*/
extern void printComplexityPerMethod(int index_number);
extern void calculateAverageComplexity();
extern float average_complexity;
extern vector<node> method_tracer;

/******************* Methods & Variables of BuildingControlFlowGraph.h *********************/
extern void displayControlFlowGraph();
extern int getComplexityCalculatedByCFG();

/**************** Methods & variables of FieldCounter.h *********************/
extern void displayFieldInfo();

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
        printf("\t4. Display The CFG\n");
        printf("\t5. Display Fields Info\n");
        printf("\t6. Exit\n");
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
        else if(key_response=="4"){
            displayControlFlowGraph();
        }
        else if(key_response=="5"){
            displayFieldInfo();
        }
        else if(key_response!="6"){
            printf("\n\n\tPlease check the user menu to select a valid response\n\n");
        }

    }
    while(key_response!="6");

    printf("\n\n");
}

void overAllResultPrinter(){
    printf("\n\n\t*** Displaying OverAll Metric Result ***\n\n");
    LOCResultPrinter();
    int temp_complexity=getComplexityCalculatedByCFG();
    int actual_complexity=max((int)average_complexity, temp_complexity);
    printf("\tAverage Complexity: %d\n", actual_complexity);
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
    calculateAverageComplexity();
    classFieldProcessor();
    userMenuProvider(file_name);
}
