#include <iostream>
#include <sstream>
#include <bitset>

using namespace std;

int main() {
    
    int n;
    
    const char a[33] = "1122334455667700ffeeddccbbaa9988";
    const char k[33] = "8899aabbccddeeff0011223344556677";
    
    istringstream("2A") >> hex >> n;
    cout << std::bin << "Parsing \"2A\" as hex gives " << n << '\n';
    
    for (int i = 0; i < 32; i++) {
        
         bitset<4> a_temp;
         bitset<4> k_temp;
         
         istringstream(a[i]) >> std::hex >> a_temp;
         istringstream(k[i]) >> std::hex >> k_temp;
         
         cout << a[i] << " " << k[i]<< endl;
         cout << a_temp << " " << k_temp << endl;
         bitset<4> res = a_temp ^ k_temp;
         cout << res << endl;
    }
    
    return 0;
}