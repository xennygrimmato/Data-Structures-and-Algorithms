#include <iostream>
#include <string>

extern int lcs(const std::string&, const std::string&);

int main()
{
    std::string s1 = "Tsuki ga kirei desu ne";
    std::string s2 = "Taiyo ga mabushii desu ne";
    std::cout << lcs(s1, s2) << std::endl;
}
