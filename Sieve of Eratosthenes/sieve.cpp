#include <bits/stdc++.h>
using namespace std;

int isPrime[10000];

void sieveOptimized(int N) {
    for (int i = 2; i <= N; i++)
        isPrime[i] = 1;
    for (int i = 2; i * i <= N; i++) {
            if (isPrime[i]) {
            // For further optimization, You can do instead of j += i, j += (2 * i).
            // Proof is left to reader :)
            for (int j = i * i; j <= N; j += i) 
                isPrime[j] = 0;
        }
    }
}
int main()
{
    sieveOptimized(100);
    for(int j=0;j<100;j++)
    	if(isPrime[j])
    		cout <<j <<"\n";
}
