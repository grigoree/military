#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include "table.h"

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


static const  unsigned char kB[16] = {148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148, 1};

vector<bitset<4> > CharToBitset4(string a)
{
    vector<bitset<4> > result(32);
    for (int i = 0; i < 32; i++) 
    {
        string a_string, k_string;
        
        a_string += a[i];

        bitset<4> a_bin;
        int a_temp;
        istringstream(a_string) >> hex >> a_temp;
        a_bin = a_temp;
        // отладочная печать: без to_ulong() распечатает в двоичном виде
        //cout << hex << a_bin.to_ulong()<<endl;
        result[i] = a_bin;
    }
    return result;
}

vector<bitset<8> > CharToBitset8(string a)
{
    vector<bitset<8> > result(16);
    for (int i = 0; i < 16; i++) 
    {
        string a_string, k_string;
        
        a_string += a[2 * i];
        a_string += a[2 * i + 1];

        bitset<8> a_bin;
        int a_temp;
        istringstream(a_string) >> hex >> a_temp;
        a_bin = a_temp;
        // отладочная печать: без to_ulong() распечатает в двоичном виде
        //cout << hex << a_bin.to_ulong()<<endl;
        result[i] = a_bin;
    }
    return result;
}

string Bitset8ToChar(vector<bitset<8> > in) {
    string result;
    
    for (int i = 0; i < in.size(); i++){
        std::stringstream stream;
        stream << std::hex << in[i].to_ulong();
        std::string temp( stream.str() );
        result += temp;
    }
    
    return result;
}

vector<bitset<4> > bitset8to4(vector<bitset<8> > in){
    vector<bitset<4> > result(32);
    
    for (int i = 0; i < 16; i++){
        int temp1 = (in[i].to_ulong() >> 4) % 16 ;
        int temp2 = in[i].to_ulong() % 16;
        
        result[2 * i] = temp1;
        result[2 * i + 1] = temp2;
    }
    
    return result;
}


// X

vector<bitset<4> > funcX(vector<bitset<4> > a,vector<bitset<4> > k) {
    
    vector<bitset<4> > result(32);
    
    cout << "X: ";

    for(int i = 0; i < 32; i++)
    {    
        result[i] = a[i] ^ k[i];
        cout << hex << result[i].to_ulong();
    }
    cout<<endl;
    return result;
}

// S

vector<bitset<8> > funcS(vector<bitset<4> > in) {
    
    vector<bitset<8> > temp(16);
    vector<bitset<8> > result(16);
    
    cout << "S: ";
    
    for (int i = 0; i < 16; i++) {
        
        int temp1 = in[i * 2].to_ulong() << 4;
        int temp2 = in[i * 2 + 1].to_ulong();
        
        temp[i] = temp1 + temp2;
        result[i] = kPi[(int)temp[i].to_ulong()];
        cout << hex << result[i].to_ulong();
    }
    
    cout << endl;
    
    return result;
}

vector<bitset<8> > funcR(vector<bitset<8> > in) {

    vector<bitset<8> > result(16);

    int sum = 0;

    for(int i = 0; i < 16; ++i) {
        sum ^= multTable[in[i].to_ulong() * 256 + kB[i]];
    }

    result[0] = sum;

    for (int i = 0; i < 15; ++i) {
        result[i + 1] = in[i];
    }

    return result;

}

vector<bitset<8> > funcL(vector<bitset<8> > in) {
    vector<bitset<8> > temp(16);
    vector<bitset<8> > result(16);

    result = in;

    for (int i = 0; i < 16; i++) {
        temp = result;
        result = funcR(temp);
    }

    return result;
}

vector<bitset<8> > funcLSX(vector<bitset<4> > a, vector<bitset<4> > key) {

    vector<bitset<8> > result(16);
    result = funcL(funcS(funcX(a,key)));

    cout << "LSX: ";
    for (int i = 0; i < 16; i++)
        cout << hex << result[i].to_ulong();
    cout << endl;

    return result;
}

vector<bitset<8> > funcC(int i) {

    vector<bitset<8> > in(16);
    vector<bitset<8> > result(16);

    for (int i = 0; i < 15; i++)
        in[i] = 0;

    in[15] = i;

    result = funcL(in);
    cout << "C: ";
    for (int i = 0; i < 16; i++)
          cout << hex << result[i].to_ulong();
    cout << endl;

    return result;
}

int funcF(vector<bitset<4> > key1, vector<bitset<4> > key2, vector<bitset<8> > C) {
    
    vector<bitset<8> > temp(16);
    vector<bitset<4> > result(32), tempC(32);
    
    tempC = bitset8to4(C);
    temp = funcLSX(tempC, key1);  
    
    return 0;
} 

int main() {

    string a = "1122334455667700ffeeddccbbaa9988";
    string k1 = "8899aabbccddeeff0011223344556677";
    string k2 = "fedcba98765432100123456789abcdef";
    string a_string, k1_string, k2_string, ktemp1, ktemp2;
           
    vector<bitset<4> > a_binary(32),a_temp4(32), test1(32), test3(32);
    vector<bitset<4> > k1_binary(32),k1_temp4(32);
    vector<bitset<4> > k2_binary(32),k2_temp4(32);
    vector<bitset<8> > a_temp8(16), C(16), test2(16);


    a_binary = CharToBitset4(a);
    k1_binary = CharToBitset4(k1);
    k2_binary = CharToBitset4(k2);
    
    //funcLSX(a_binary,k1_binary);
    C = funcC(1);
    
    funcF(k1_binary, k2_binary, C);


    return 0;
}