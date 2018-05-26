// compute prime numbers to N really fast (Sieve)
#define N 10000100
vector<int> primes; 
char p[N/8]; 

void GeneratePrimes() 
{        
	primes.push_back(2);        
	int i,j;        
	for(i=1;((i*i)<<1)+(i<<1)<N;++i)        
	{                
		if((p[i>>3]&(1<<(i&7)))==0)                
		{                        
			primes.push_back((i<<1)+1);                        
			for(j=((i*i)<<1)+(i<<1),k=(i<<1)+1;(j<<1)+1<N;j+=k)   
			{                                
				p[j>>3] |=(1<<(j&7));                        
			}                
		}        
	}        

	for(;(i<<1)+1<N;++i)        
	{                
		if((p[i>>3]&(1<<(i&7)))==0)                
		{                        
			primes.push_back((i<<1)+1);                
		}        
	} 
}
