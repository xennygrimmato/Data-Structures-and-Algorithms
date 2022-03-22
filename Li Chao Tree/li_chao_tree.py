# Problem: https://atcoder.jp/contests/abc244/tasks/abc244_h
# AC Submission from Editorial: https://atcoder.jp/contests/abc244/submissions/30307939

class LiChaoTree:
    # Min Query
    def __init__(self, X): # X: 調べる可能性のある x 座標のリスト
        X = sorted(list(set(X)))
        self.inf = 10 ** 50
        self.n = 1 << (len(X) - 1).bit_length()
        self.X = X + [self.inf] * (self.n - len(X))
        self.D = {a: i for i, a in enumerate(X)}
        self.lmr = [(0, 0, 0)] * self.n + [(x, x, x) for x in self.X]
        for i in range(1, self.n)[::-1]:
            self.lmr[i] = (self.lmr[i*2][0], self.lmr[i*2][2], self.lmr[i*2^1][2])
        self.F = [None] * (self.n * 2)
    
    def calc(self, f, x):
        return f[0] * x + f[1]
    
    def update(self, i, f):
        while 1:
            l, m, r = self.lmr[i]
            fi = self.F[i]
            if fi is None:
                self.F[i] = f
                return
            cl = (fi[0] - f[0]) * l + fi[1] - f[1] > 0
            cr = (fi[0] - f[0]) * r + fi[1] - f[1] > 0
            
            if cl and cr:
                self.F[i] = f
                return
            if not cl and not cr:
                return
            if (fi[0] - f[0]) * m + fi[1] - f[1] > 0:
                self.F[i], f = f, fi
                cl = not cl
            if cl:
                i *= 2
            else:
                i = i * 2 + 1
    
    def query(self, x):
        i = self.D[x] + self.n
        mi = self.inf
        while i > 0:
            if self.F[i]:
                mi = min(mi, self.calc(self.F[i], x))
            i >>= 1
        return mi
    
    def add_line(self, a, b): # y = ax + b
        f = (a, b)
        self.update(1, f)
    
    def debug(self):
        print("F =", self.F)
        print("X =", self.X)
        print("D =", self.D)
        print("lmr =", self.lmr)
