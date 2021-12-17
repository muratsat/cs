#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int> &a, int l, int r, long long *inversions){
    int len = r - l + 1;
    int mid = l + (r-l)/2;
    vector<int> t(len);

    for(int i = 0; i < len; i++)
        t[i] = a[l+i];
    
    int i = l, j = mid+1, k = 0;
    while(i <= mid && j <= r){
        if(a[i] > a[j]){
            *inversions += mid - i + 1;
            t[k] = a[j];
            j++; k++;
        }
        else{
            t[k] = a[i];
            i++; k++;
        }
    }

    while(i <= mid){
        t[k] = a[i];
        i++; k++;
    } 

    while(j <= r){
        t[k] = a[j];
        j++; k++;
    } 

    for(int i = 0; i < len; i++)
        a[l+i] = t[i];
}

void mergesort(vector<int> &a, int l, int r, long long *inversions){
    if(l < r){
        int mid = l + (r-l)/2;
        mergesort(a, l, mid, inversions);
        mergesort(a, mid+1, r, inversions);

        merge(a, l, r, inversions);
    }
}

int main(){ 
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    
    long long inversions = 0;
    mergesort(a, 0, n-1, &inversions);
    cout << inversions;
    return 0;
}