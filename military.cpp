#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

static const unsigned char kPi[256] =
{
	252, 238, 221,  17, 207, 110,  49,  22, 251, 196, 250, 218,  35, 197,   4,  77, 
	233, 119, 240, 219, 147,  46, 153, 186,  23,  54, 241, 187,  20, 205,  95, 193,
	249,  24, 101,  90, 226,  92, 239,  33, 129,  28,  60,  66,	139,   1, 142,  79,
	  5, 132,   2, 174, 227, 106, 143, 160,   6,  11, 237, 152, 127, 212, 211,  31,
	235,  52,  44,  81,	234, 200,  72, 171, 242,  42, 104, 162, 253,  58, 206, 204,
	181, 112,  14,  86,   8,  12, 118,  18, 191, 114,  19,  71, 156, 183,  93, 135,
	 21, 161, 150,  41,  16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177,
	 50, 117,  25,  61, 255,  53, 138, 126, 109,  84, 198, 128, 195, 189,  13,  87,
	223, 245,  36, 169,  62, 168,  67, 201, 215, 121, 214, 246, 124,  34, 185,   3,
	224,  15, 236, 222, 122, 148, 176, 188, 220, 232,  40,  80,  78,  51,  10,  74,
	167, 151,  96, 115,  30,   0,  98,  68,  26, 184,  56, 130, 100, 159,  38,  65,
	173,  69,  70, 146,  39,  94,  85,  47, 140, 163, 165, 125, 105, 213, 149,  59,
	  7,  88, 179,  64, 134, 172,  29, 247,  48,  55, 107, 228,	136, 217, 231, 137,
	225,  27, 131,  73,  76,  63, 248, 254, 141,  83, 170, 144, 202, 216, 133,  97,
	 32, 113, 103, 164,  45,  43,   9,  91, 203, 155,  37, 208, 190, 229, 108,  82,
	 89, 166, 116, 210, 230, 244, 180, 192,	209, 102, 175, 194,  57,  75,  99, 182
};


// X

bitset<4>* funcX(char a[33], char k[33]) {
    
    bitset<4>* result = new bitset<4>[32];
    
    cout << "X: ";
    
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
    cout << endl;
    return result;
}

// S

bitset<8>* funcS(bitset<4>* in) {
    
    bitset<8>* temp = new bitset<8>(16);
    bitset<8>* result = new bitset<8>(16);
    
    cout << "S: ";
    
    for (int i = 0; i < 16; i++) {
        
        int temp1 = in[i * 2].to_ulong();
        int temp2 = in[i * 2 + 1].to_ulong() << 4;
        
        temp[i] = temp1 + temp2;
        result[i] = kPi[(int)temp[i].to_ulong()];
        
        cout << hex << result[i].to_ulong();
    }
    
    cout << endl;
    
    return result;
}

int main() {

    char a[33] = "1122334455667700ffeeddccbbaa9988";
    char k[33] = "8899aabbccddeeff0011223344556677";
    
    funcS(funcX(a, k));

    return 0;
}