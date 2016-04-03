#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

// X

bitset<4>* funcX(char a[33], char k[33]) {
    
    bitset<4>* result = new bitset<4>[32];
    
    for (int i = 0; i < 32; i++) {
        
        int a_temp, k_temp;
        
        string a_string, k_string;
        
        a_string += a[i];
        k_string += k[i];
        
        bitset<4> a_bin;
        bitset<4> k_bin;
        
        // функция переводит строку в поток с атрибутом hex 
        istringstream(a_string) >> hex >> a_temp;
        istringstream(k_string) >> hex >> k_temp;
         
        a_bin = a_temp;
        k_bin = k_temp;

        bitset<4> temp = a_bin ^ k_bin;
        
        // отладочная печать: без to_ulong() распечатает в двоичном виде
        cout << hex << temp.to_ulong();
         
        result[i] = temp;
    }
    
    return result;
}

int main() {

    char a[33] = "1122334455667700ffeeddccbbaa9988";
    char k[33] = "8899aabbccddeeff0011223344556677";
    
    funcX(a, k);
    cout << endl;
    
    return 0;
}