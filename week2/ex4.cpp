#include <iostream>
using namespace std;

int daysRequire(int weights[], int n, int capacity){
	int temp_day = 1;
	int sum = 0;
	int i =0;
	while(i<n){
		//đẩy thêm hàng nếu có thể
		if(sum + weights[i]<=capacity){
			sum+=weights[i];
			i++;
		}
		//nếu không thể đẩy thêm hàng thì chuyển sang ngày tiếp
		//đẩy hàng ngay lúc này
		else{
			sum = 0;
			temp_day++;
			sum+=weights[i];
			i++;
		}
	}
	return temp_day;
}

int solution(int weights[],int num_packs,int max_weigh,int total_weight,int day_require){
	int l =max_weigh,r = total_weight,result = 0,m;
	while(l<=r){
		m = (l+r)/2;
		//nếu số ngày quá ít tức lượng hàng quá lớn
		if(daysRequire(weights,num_packs,m)<=day_require){
			//lưu lại result = m
			result = m;
			//giảm lượng hàng
			/*nếu result đang thỏa nhưng chưa phải là tối tiểu
			lượng hàng cũng cần giảm*/
			r = m-1;
		}
		//lượng hàng quá ít làm số ngày nhiều
		else{
			//tăng lượng hàng
			l = m+1;
		}
	}
	return result;
}

int main(){
	int n,day;
	cin>>n;
	int weights[n];
	long long sum_w = 0;
	for(int &x:weights){
		cin>>x;
		sum_w+=x;
	}
	cin>>day;
	cout<<solution(weights,n,4,sum_w,day);
	return 0;
}