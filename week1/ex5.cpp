#include <iostream>
using namespace std;
//hàm xét mảng có được sắp xếp tăng dần hay không

bool isSorted(int arr[], int n) {
	//nếu mảng chỉ có 1 hoặc không có phần tử
	//mảng đã được sắp xếp
	if (n == 1 || n == 0){
		return true;
	}
	//nếu phần tử đầu lớn hơn 
	//mảng không được sắp xếp (tăng dần)
	if(arr[0] > arr[1]){
		return false;
	}
	return isSorted(arr + 1, n - 1);
}

int main(){
	int a[] = {1,2,3,0,6};
	if(isSorted(a,5)){
		cout<<"a is sorted\n";
	}else{
		cout<<"a is not sorted\n";
	}
	int b[] = {1,2,3,5,6};
	if(isSorted(b,5)){
		cout<<"b is sorted\n";
	}else{
		cout<<"b is not sorted\n";
	}
	return 0;
}