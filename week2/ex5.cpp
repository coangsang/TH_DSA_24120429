#include <iostream>
using namespace std;

int min(int a,int b){
	if(a<b){
		return a;
	}
	return b;
}

int minSubArrayLen(int a[],  int n,int target) {
    int left = 0, sum = 0, min_length = n;
    
    for (int right = 0; right < n; right++) {
        sum += a[right]; // Tăng tổng
        
        while (sum >= target) { // Khi tổng đủ lớn
            min_length = min(min_length, right - left + 1);
            sum -= a[left]; // Giảm tổng
            left++;
        }
    }

    return min_length;
}


int main(){
	int n;
	cin>>n;
	int a[n];
	int target;
	for(int i =0;i<n;i++){
		cin>>a[i];
	}
	cin>>target;
	cout<<minSubArrayLen(a,n,target);
	return 0;
}