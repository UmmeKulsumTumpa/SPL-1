#include<bits/stdc++.h>
#include"headers.h"

using namespace std;

int main()
{
    printf("\t*** WELCOME to CMC(Code Metric Calculator) ***\n\n\n");
    printf("Below showing the related topic of LOC of a java source code:\n\n");
    
    countPhysicalLines();
    countLogicalLines();
    countCommentLines();

    printf("\n\n");
    printf("\t    *** Thank you for using CMC! ***\n\n\n");
}