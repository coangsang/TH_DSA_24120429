#include <iostream>
using namespace std;

int minElementInRotatedArray(int a[],int left, int right){
	int mid = 0;
	while(left<right){
		mid = (left+right)/2;
		//nếu tại mid a < a tại right: chuyển right = mid (vị trí min <= mid)
		if(a[mid]<a[right]){
			right = mid;
		}
		//a[mid]>=a[right]
		else{
			left = mid+1;
		}
	}
	return a[left];//a[right] cũng là đáp án đúng 
}

int main(){
	int a[] = { 2, 3, 4, 5, 6, 7, 8, 1};
	int n = 8;
	cout<<minElementInRotatedArray(a,0,n-1);
	return 0;
}