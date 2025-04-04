#include <stdio.h>
#include "sort_algo.h"
void swap(int&a,int&b){
	int temp = b;
	b = a;
	a = temp;
}

void selection_sort(int nums[],int n){
	for(int i =0;i<n;i++){
		int min_pos = i;
		for(int j = i+1;j<n;j++){
			if(nums[j]<nums[min_pos]){
				min_pos = j;
			}
		}
		swap(nums[i],nums[min_pos]);
	}
}
void insertion_sort(int nums[], int n){
	for(int i =1;i<n;i++){
		int temp = nums[i];
		int j = i;
		while(j>0&&nums[j]<nums[j-1]){
			nums[j] = nums[j-1];
			--j;
		}
		nums[j] = temp;
	}
}
void bubble_sort(int nums[], int n){
	for(int i =0;i<n-1;i++){
		bool swapped = false;
		for(int j = 0;j<n-i-1;j++){
			if(nums[j]>nums[j+1]){
				swap(nums[j],nums[j+1]);
				swapped = true;
			}
		}
		if(!swapped)
			break;
	}
}

void shaker_sort(int nums[], int n){
	int left = 0;
	int right = n - 1;
	int k = 0;
	while(left<right){
		for(int i = left;i<right;i++){
			if(nums[i]>nums[i+1]){
				swap(nums[i],nums[i+1]);
				k = i;
			}
		}
		right = k;
		for(int i = right;i>left;i--){
			if(nums[i]<nums[i-1]){
				swap(nums[i],nums[i-1]);
				k = i;
			}
		}
		left = k;
	}
}
void shellSort(int nums[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = nums[i];
            int j;
            for (j = i; j >= gap && nums[j - gap] > temp; j -= gap) {
                nums[j] = nums[j - gap];
            }
            nums[j] = temp;
        }
    }
}
void heapify(int nums[], int n, int i){
	int  largest = i;
	int left = 2*i+1;
	int right = 2*i+2;
	if(left<n&&nums[left]>nums[largest])
		largest = left;
	if(right<n&&nums[right]>nums[largest])
		largest = right;
	if(largest!=i){
		swap(nums[i],nums[largest]);
		heapify(nums,n,largest);
	}
}
void heap_sort(int nums[],int n){
	for(int i = n/2 - 1;i>=0;i--){
		heapify(nums,n,i);
	}
	for(int i =n-1;i>=0;i--){
		swap(nums[i],nums[0]);
		heapify(nums,i,0);
	}
}
void quick_sort(int* nums, int n) {
	printf("NICE");
}
void merge_sort(int* nums, int n) {
	printf("NICE");
}
void shell_sort(int* nums, int n) {
	printf("NICE");
}
void counting_sort(int* nums, int n) {
	printf("NICE");
}
void radix_sort(int* nums, int n) {
	printf("NICE");
}
void flash_sort(int* nums, int n) {
	printf("NICE"); 
}
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
    "bubble-sort",
    "selection-sort",
    "insertion-sort",
    "quick-sort",
    "merge-sort",
    "heap-sort",
    "shell-sort",
    "counting-sort",
    "radix-sort",
    "shaker-sort",
    "flash-sort"
};
const int nOfSort = sizeof(typeOfSort)/sizeof(typeOfSort[0]);