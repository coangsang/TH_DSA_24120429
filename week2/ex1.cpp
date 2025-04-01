#include <iostream>
using namespace std;

int linearSearch(int a[],int n,int k){
	for(int i =0;i<n;i++){
		if(a[i]==k)
			return i;
	}
	return -1;
}

int main(){
	int a[] = {1,3,5,7,9};
	cout<<linearSearch(a,5,5);
	return 0;
}