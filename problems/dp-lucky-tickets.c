#include <stdio.h>
#include "../homeTask1/bn.c"

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    n /= 2;

    int max_sum = n*(m-1);

    bn* dp[n+1][max_sum + 1];

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= max_sum; j++){
            dp[i][j] = bn_new();
        }
    }

    for(int k = 0; k < m; k++)
        bn_init_int(dp[1][k], 1);
    
    for(int i = 1; i <= n; i++){
        for(int k = 0; k <= max_sum; k++){
            for(int j = 0; j < m; j++){
                if(k >= j && k-j <= max_sum)
                    bn_add_to(dp[i][k], dp[i-1][k-j]);
            }
        }
    }

    bn* ans = bn_new();
    for(int k = 0; k <= max_sum; k++){
        bn_square(dp[n][k]);
        bn_add_to(ans, dp[n][k]);
    }

    bn_print(ans, 10, 1);

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= max_sum; j++){
            bn_delete(dp[i][j]);
        }
    }
    bn_delete(ans);
    return 0;
}
