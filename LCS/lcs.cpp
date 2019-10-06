#include <iostream>
#include <string>
#include <vector>

int main()
{
    auto find = [](const std::string& A, const std::string& B) -> int
    {
        std::vector<std::vector<int>> LCS(A.length() + 1);        
        for (unsigned int i = 0; i < LCS.size(); i++)
            LCS[i].resize(B.length() + 1);
            
        for (unsigned int i = 1; i <= A.length(); i++) {
            for (unsigned int j = 1; j <= B.length(); j++) {
                if (A[i - 1] == B[j - 1]) {
                    LCS[i][j] = LCS[i - 1][j - 1] + 1;
                }
                else {
                    LCS[i][j] = std::max(LCS[i - 1][j], LCS[i][j - 1])
                }
            }
        }
        return LCS[A.length()][B.length()];
    };

    std::string s1 = "Tsuki ga kirei desu ne";
    std::string s2 = "Taiyo ga mabushii desu ne";
    int len = 0;
    if (s1.length() > 0 && s2.length() > 0)
        len = find(&s1[0], &s2[0]);
    std::cout << len << std::endl;
}
