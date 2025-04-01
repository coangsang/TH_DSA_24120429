#include <iostream>
using namespace std;

int linearSearchWithSentinel(int a[],int n,int k){
	int last = a[n-1];//Lưu phần tử cuối vào last
	a[n-1] = k;//đặt phần tử cuối = k
	int i = 0;
	//duyệt mảng cho đến khi gặp k hoặc a[n-1]
	while(a[i]!=k){
		i++;
	}
	a[n-1] = last;//gán lại last cho a[n-1]
	//trả về chỉ số i nếu xuất hiện k trong mảng ban đầu
	if(i<n-1||a[n-1]==k){
		return i;
	}
	//trả về -1 nếu không tồn tại
	return -1;
}

int main(){
	int a[] = {1,3,5,7,9};
	cout<<linearSearchWithSentinel(a,5,5);
	return 0;
}