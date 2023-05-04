#include<bits/stdc++.h>

#include "LOC.h"
#include "MethodLevelLOC.h"
#include "CyclomaticComplexity.h"
#include "ComplexityAnalyzer.h"

using namespace std;

/*+++++++++++++++++++++++++++++ variables & methods of LOC.h +++++++++++++++++++++++++++++*/
extern void LOCResultPrinter();

/*++++++++++++++++++++++++++++ variables & methods of MethodLevelLOC.h ++++++++++++++++++++++++++*/

extern int total_method; // total number of methods detected in the source code

extern void locMethodBasedResult(int i);



/****************************** Methods to be used *******************************/

void detailedResultPrinter();
void executeCalculation(string file_name);



/**************************** method definations ****************************/

void detailedResultPrinter(){

    for(int i=0;i<total_method;i++){

        locMethodBasedResult(i);
    }
}



void executeCalculation(string file_name){
    
    CalcLOC(file_name);
    LOCResultPrinter();
    calcComplexity(file_name);
    detailedResultPrinter();
}