# https://www.hackerrank.com/contests/infinitum-jul14/challenges/order-of-prime-in-factorial/problem

def S(p,n):
    return 0 if n == 0 else (n%p) + S(p,n/p)

def G(p,L):
    Q,R = divmod(L,p)
    return Q + ((-S(p,Q)) % p < R)

def F_(p,L):
    Q,R = divmod(L,p)
    return p*G(p,Q) + R*(S(p,Q) % p == 0)

def F(p,L):
    return F_(p,L+1) - 1

for cas in xrange(input()):
    p,L = map(int, raw_input().strip().split())
    print F(p,L)
