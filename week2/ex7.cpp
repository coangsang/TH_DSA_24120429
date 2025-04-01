#include <iostream>
#include <vector>
using namespace std;
void quickSort(vector<int>&v,int l,int r){
	if(l<r){
		int pivot = v[r];
		int i = l -1;
		for (int j = l; j < r; j++) {
        	if (v[j] < pivot) {
        	    i++; 
        	    swap(v[i], v[j]);
        	}
    	}
    	i++;
    	swap(v[i], v[r]);
    	quickSort(v, l, i - 1); 
        quickSort(v, i + 1, r);
	}
}

vector<vector<int>> solution(vector<int>&input){
	int n = input.size();
	quickSort(input,0,n-1);//sắp xếp tăng dần
	vector<vector<int>> res;
	int sum;
	for (int i = 0; i < n; i++) {
		//bỏ qua i hiện tại nếu nó đã được kiểm tra trước đó
       if (i > 0 && input[i] == input[i-1]) {
           continue;
       }
       int j = i + 1;
       int k = n - 1;
       while (j < k) {
           sum = input[i] + input[j] + input[k];
           if (sum > 0) {
               k--;//input[k]>input[k-1] nên giảm k xuống
           } else if (sum < 0) {
               j++;//input[j]<input[j+1] nên tăng j lên
           } else {
           	//nếu tổng 3 phần tử =0
               res.push_back({input[i], input[j], input[k]});
               j++;
               //bỏ qua toàn bộ j trùng lặp
               while (input[j] == input[j-1] && j < k) {
                   j++;
               }
               //có thể dùng với k
               /*
               k--;
               while ((k==n-1||(input[k] == input[k+1])) && j < k) {
                   k--;
               }
               */
           }
        }
	}
	return res;
}
int main(){
	vector<int> v = {-1,0,1,2,-1,-4};
	quickSort(v,0,v.size()-1);
	vector<vector<int>>res = solution(v);
	for(auto x:res){
		for(int y:x){
			cout<<y<<" ";
		}cout<<endl;
	}
	return 0;
}