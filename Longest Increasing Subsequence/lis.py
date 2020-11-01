from bisect import bisect_left

def lis(A, return_only_length=False):
    B = []
    for a in A:
        i = bisect_left(B, a)
        if i == len(B):
            B.append(a)
        else:
            B[i] = a
    if return_only_length:
        return len(B)
    return B

# Usage
print(lis([3, 1, 5, 2, 4, 3]))
print(lis([1]))
print(lis([2, 1]))
