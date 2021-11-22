#include <iostream>
#include <vector>
using namespace std;

int main(){
    string s;
    cin >> s;

    int n = s.size();
    int dp[n][n] = {};

    for(int k = 0; k < n; k++)
        dp[k][k] = 1;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l <= n-len; l++) {
            int r = len + l - 1;
            if (s[l] == s[r])
                dp[l][r] = dp[l][r - 1] + dp[l + 1][r] + 1;
            else
                dp[l][r] = dp[l][r - 1] + dp[l + 1][r] - dp[l + 1][r - 1];
        }
    }
    cout << dp[0][n-1] << '\n';

    return 0;
}