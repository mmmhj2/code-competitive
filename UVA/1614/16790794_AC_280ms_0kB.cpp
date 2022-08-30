#include<iostream>
#include<algorithm>
#include<iterator>
using namespace std;
const int maxn=100010;
struct q{
    int num,id;
    friend ostream& operator << (ostream &out,const q& x){
        cout<<x.num;
        return out;
    }
};
q a[maxn];
int main(){
    int n;
    while(cin>>n){
        long long sum=0;
        for(int i=0;i<n;++i){
            a[i].id=i;
            cin>>a[i].num;
            sum+=a[i].num;
        }
        if(sum&1) {cout<<"No\n";continue;}
        sum>>=1;
        sort(a,a+n,[](q& a,q& b){return a.num>b.num;});
        for(int i=0;i<n;++i){
            if(a[i].num<=sum){
                sum-=a[i].num;
                a[i].num=1;
            }
            else a[i].num=-1;
        }
        sort(a,a+n,[](q& a,q& b){return a.id<b.id;});
        cout<<"Yes\n";
        copy(a,a+n,ostream_iterator<q>(cout," "));
        cout<<endl;
    }
    return 0;
}
