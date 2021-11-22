#include <stdio.h>
#include <string.h>

int main(){
    char s[31];
    scanf("%s", s);
    int n = strlen(s);

    int dp[30][30] = {};

    for(int i = 0; i < n; i++)
        dp[i][i] = 1;
    
    for(int len = 1; len < n; len++){
        for(int l = 0; l < n-len; l++){
            int r = l + len;
            if (s[l] == s[r])
                dp[l][r] = dp[l][r - 1] + dp[l + 1][r] + 1;
            else
                dp[l][r] = dp[l][r - 1] + dp[l + 1][r] - dp[l + 1][r - 1];
        }
    }

    printf("%d\n", dp[0][n-1]);
}