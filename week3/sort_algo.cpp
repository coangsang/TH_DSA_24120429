#include "sort_support_func.h"
#include "sort_algo.h"

void (*typeOfSort[])(int nums[], int n) = {
    bubble_sort,
    selection_sort,
    insertion_sort,
    quick_sort,
    merge_sort,
    heap_sort,
    shell_sort,
    counting_sort,
    radix_sort,
    shaker_sort,
    flash_sort
};

const char* typeOfSortName[] = {
    "bubble_sort",
    "selection_sort",
    "insertion_sort",
    "quick_sort",
    "merge_sort",
    "heap_sort",
    "shell_sort",
    "counting_sort",
    "radix_sort",
    "shaker_sort",
    "flash_sort"
};

const int nOfSort = sizeof(typeOfSort)/sizeof(typeOfSort[0]);


void selection_sort(int nums[], int n){

}
void insertion_sort(int nums[], int n){

}
void bubble_sort(int nums[], int n){

}
void shaker_sort(int nums[], int n){

}
void shell_sort(int nums[], int n){

}

void heap_sort(int nums[], int n){
    
}

void merge_sort(int nums[], int n){
    int l = 0;
    int r = n -1;
    merge_sort_recursive(nums, l, r);
}
void quick_sort(int nums[], int n){
    int l = 0;
    int r = n - 1;
    quick_sort_recursive(nums, l, r);
}
void counting_sort(int nums[], int n){
    int max = nums[0];
    for(int i = 1; i<n;i++){
        max = max > nums[i] ? max : nums[i];
    }
    int *count = new int[max + 1]();

    for(int i = 0; i < n; i++){
        count[nums[i]]++;
    }
    for(int i = 1; i <= max; i++){
        count[i] += count[i - 1];
    }
    int *output = new int[n];
    for(int i = n - 1; i >= 0; i--){
        output[count[nums[i]] - 1] = nums[i];
        count[nums[i]]--;
    }
    for(int i = 0; i < n; i++){
        nums[i] = output[i];
    }
    delete[] count;
    delete[] output;
}
void radix_sort(int nums[], int n){
    int max = nums[0];
    for(int i = 1; i<n;i++){
        max = max > nums[i] ? max : nums[i];
    }
    int base = 10;
    for(int exp = 1; max/exp > 0; exp *= base){
        counting_sort_for_radix(nums, n, exp, base);
    }
}
void flash_sort(int nums[], int n){
    int max = nums[0];
    int min = nums[0];
    for(int i = 1; i<n;i++){
        max = max > nums[i] ? max : nums[i];
        min = min < nums[i] ? min : nums[i];
    }
    int m = (int)(0.45*n);
    int* l = new int[m]();

    double c1 = (double)(m - 1)/(max - min);

    for(int i = 0; i < n; i++){
        int index = (int)((nums[i] - min)*c1);
        l[index]++;
    }
    for(int i = 1; i < m; i++){
        l[i] += l[i - 1];
    }
    int* output = new int[n];
    for(int i = n - 1; i >= 0; i--){
        int index = (int)((nums[i] - min)*c1);
        while(index > 0 && l[index] == 0){
            index--;
        }
        output[l[index] - 1] = nums[i];
        l[index]--;
    }
    for(int i = 0; i < n; i++){
        nums[i] = output[i];
    }
    delete[] l;
    delete[] output;
}