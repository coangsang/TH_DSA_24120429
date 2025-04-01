#include <iostream>
#include <string>
using namespace std;

bool binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return true;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

string solution(int a[], int n, int target) {
    for (int i = 0; i < n - 1; i++) {
        // Tìm xem có phần tử x nào thỏa a[i] + x = target
        if (binarySearch(a, i + 1, n - 1, target - a[i])){
        	//Trả về YES ngay nếu tồn tại 
        	return "YES";
        }
    }
    return "NO";
}
int main(){
	int a[] = {1,2,3,4,6};
	cout<<solution(a,5,5);
	return 0;
}