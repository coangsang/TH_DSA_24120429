#include <bits/stdc++.h>
#include "sort_algo.h"
#include "DataGenerator.cpp"
using namespace std;


int main(){
    int dataSize[] = {1000, 10000, 100000, 1000000};
    // 0: random data
    // 1: sorted data
    // 2: reverse data
    // 3: nearly sorted data
    int dataOrder[] = {0, 1, 2, 3};

    int nOfDataSize = sizeof(dataSize)/sizeof(dataSize[0]);
    int nOfDataOrder = sizeof(dataOrder)/sizeof(dataOrder[0]);
    int nOfSort = sizeof(typeOfSort)/sizeof(typeOfSort[0]);

    for(int i = 0; i < nOfDataOrder; i++){
        for(int j = 0; j < nOfDataSize;j++){
            int n = dataSize[j];
            int* nums = new int[n];
            GenerateData(nums, n, dataOrder[i]);
            for(int k = 0; k < nOfSort; k++){
                clock_t start = clock();
                typeOfSort[k](nums, n);
                clock_t end = clock();
                double timeTaken = double(end - start) / CLOCKS_PER_SEC;
                cout << "Data size: " << n << ", Data order: " << dataOrder[i] << ", Sort type: " << typeOfSortName[k] << ", Time taken: " << timeTaken << " seconds" << endl;
            }
            delete[] nums;
        }
    }
    return 0;
}