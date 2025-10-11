#include <iostream>
#include <thread>
#include <vector>
#include "PipelineTest.h"
#include "CoarseGrainedLock.h"
#include "FineGrainedLock.h"

int main(){
    /*CoarseGrained* listCoarse = new CoarseGrained();
    PipelineTest testCoarse(listCoarse, 300, 300, 5000);
    testCoarse.runTest();
    
    delete listCoarse;*/
    
    
    FineGrained* listFine = new FineGrained();
    PipelineTest testFine(listFine, 300, 300, 5000);
    testFine.runTest();
    
    delete listFine;

    return 0;
}