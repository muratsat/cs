#include <stdio.h>

unsigned long long pow(unsigned long long a, unsigned long long n, unsigned long long m){
	if(n == 0)
		return 1;
	
	unsigned long long res = 1;
	
	while(n > 0){
		if(n%2 == 1){
			res *= a;
			res %= m;
		}
		
		a = (a*a)%m;
		n /= 2;
	}

	return (res + m)%m;
}

int main(){
	unsigned long long p, q, m;
	scanf("%lld%lld", &p, &m);

	q = pow(p, m-2, m);
	printf("%lld\n", q);

    return 0;
}