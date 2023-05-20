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



/**************************** method definations ****************************/

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
    LOCResultPrinter();
    detailedResultPrinter();
    createControlFlowGraph();
}