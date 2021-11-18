#include <iostream>
#include <vector>
using namespace std;

void recur(int n, long long f, long long k, vector<int> &a, vector<int> &ans){
    int id = k/f;
    k %= f;
    n--;
    f /= n;

    ans.push_back(a[id]);
    a.erase(a.begin() + id);
    if(n == 1)
        ans.push_back(a[0]);
    if(n > 1)
        recur(n, f, k, a, ans);
}

int main(){
    int n;
    long long f = 1, k;
    cin >> n >> k;

    vector<int> a(n);
    for(int i = 0; i < n; i++)
        a[i] = i+1;
    for(int i = 1; i < n; i++)
        f *= i;

    vector<int> ans;
    k--;
    recur(n, f, k, a, ans);

    for(int t : ans)
        cout << t << ' ';
    return 0;
}