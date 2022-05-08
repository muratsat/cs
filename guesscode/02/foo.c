// int foo(int rdi, int esi, int rdx){
// int foo(int* rdi, int esi, long long rdx){
//     if(esi <= 0)
//         return 0;

//     int eax = 0; 
//     long long rcx = (long long)esi;
//     do {
//         eax += rdi[rdx];
//         rdx += 2;
//     } while(rdx < rcx);

//     return eax;
// }

int foo(int a[], int n){
    if(n <= 0)
        return 0;

    int ans = a[0];
    for(int i = 2; i < n; i += 2)
        ans += a[i];
    
    return ans;
}