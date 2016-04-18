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

static const unsigned char kReversePi[256] =
{
     0xa5,0x2d,0x32,0x8f,0x0e,0x30,0x38,0xc0,0x54,0xe6,0x9e,0x39,0x55,0x7e,0x52,0x91,
     0x64,0x03,0x57,0x5a,0x1c,0x60,0x07,0x18,0x21,0x72,0xa8,0xd1,0x29,0xc6,0xa4,0x3f,
     0xe0,0x27,0x8d,0x0c,0x82,0xea,0xae,0xb4,0x9a,0x63,0x49,0xe5,0x42,0xe4,0x15,0xb7,
     0xc8,0x06,0x70,0x9d,0x41,0x75,0x19,0xc9,0xaa,0xfc,0x4d,0xbf,0x2a,0x73,0x84,0xd5,
     0xc3,0xaf,0x2b,0x86,0xa7,0xb1,0xb2,0x5b,0x46,0xd3,0x9f,0xfd,0xd4,0x0f,0x9c,0x2f,
     0x9b,0x43,0xef,0xd9,0x79,0xb6,0x53,0x7f,0xc1,0xf0,0x23,0xe7,0x25,0x5e,0xb5,0x1e,
     0xa2,0xdf,0xa6,0xfe,0xac,0x22,0xf9,0xe2,0x4a,0xbc,0x35,0xca,0xee,0x78,0x05,0x6b,
     0x51,0xe1,0x59,0xa3,0xf2,0x71,0x56,0x11,0x6a,0x89,0x94,0x65,0x8c,0xbb,0x77,0x3c,
     0x7b,0x28,0xab,0xd2,0x31,0xde,0xc4,0x5f,0xcc,0xcf,0x76,0x2c,0xb8,0xd8,0x2e,0x36,
     0xdb,0x69,0xb3,0x14,0x95,0xbe,0x62,0xa1,0x3b,0x16,0x66,0xe9,0x5c,0x6c,0x6d,0xad,
     0x37,0x61,0x4b,0xb9,0xe3,0xba,0xf1,0xa0,0x85,0x83,0xda,0x47,0xc5,0xb0,0x33,0xfa,
     0x96,0x6f,0x6e,0xc2,0xf6,0x50,0xff,0x5d,0xa9,0x8e,0x17,0x1b,0x97,0x7d,0xec,0x58,
     0xf7,0x1f,0xfb,0x7c,0x09,0x0d,0x7a,0x67,0x45,0x87,0xdc,0xe8,0x4f,0x1d,0x4e,0x04,
     0xeb,0xf8,0xf3,0x3e,0x3d,0xbd,0x8a,0x88,0xdd,0xcd,0x0b,0x13,0x98,0x02,0x93,0x80,
     0x90,0xd0,0x24,0x34,0xcb,0xed,0xf4,0xce,0x99,0x10,0x44,0x40,0x92,0x3a,0x01,0x26,
     0x12,0x1a,0x48,0x68,0xf5,0x81,0x8b,0xc7,0xd6,0x20,0x0a,0x08,0x00,0x4c,0xd7,0x74
};


static const  unsigned char kB[16] = {148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148, 1};

// ======= преобразование из string в bitset4 ======

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

// ======= преобразование из string в bitset8 ======

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

// ======= преобразование из bitset8 в bitset4 ======

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

vector<bitset<8> > bitset4to8(vector<bitset<4> > in)
{
        vector<bitset<8> > result(16);

        for (int i = 0; i < 16; i++){
        int temp1 = in[i * 2].to_ulong() << 4;
        int temp2 = in[i * 2 + 1].to_ulong();
        int temp = temp1 + temp2;
        result[i] = temp;
    }
        return result;
}


//======== X ==========

vector<bitset<4> > funcX(vector<bitset<4> > a,vector<bitset<4> > k) {
    
    vector<bitset<4> > result(32);
    
    //cout << "X: ";

    for(int i = 0; i < 32; i++)
    {    
        result[i] = a[i] ^ k[i];
        //cout << hex << result[i].to_ulong();
    }
    //cout<<endl;
    return result;
}

//======== S и обратная ==========

vector<bitset<8> > funcS(vector<bitset<4> > in) {
    
    vector<bitset<8> > result(16);
    
    //cout << "S: ";
    
    for (int i = 0; i < 16; i++) {
        
        int temp1 = in[i * 2].to_ulong() << 4;
        int temp2 = in[i * 2 + 1].to_ulong();
        int temp = temp1 + temp2;
        
        result[i] = kPi[temp];
        //cout << hex << result[i].to_ulong();
    }
    
    //cout << endl;
    
    return result;
}

vector<bitset<8> > funcReverseS(vector<bitset<4> > in) {
    vector<bitset<8> > result(16);
    
    
    //cout << "reverseS: ";
    for (int i = 0; i < 16; i++) {
        
        int temp1 = in[i * 2].to_ulong() << 4;
        int temp2 = in[i * 2 + 1].to_ulong();
        int temp = temp1 + temp2;
        
        result[i] = kReversePi[temp];
       // cout << hex << result[i].to_ulong();
    }
    //cout << endl;
    
    return result;
}

//======== R и обратная ==========

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

vector<bitset<8> > funcReverseR(vector<bitset<8> > in) {

    vector<bitset<8> > result(16);
    vector<bitset<8> > temp(16);
    int sum = 0;
    
    for (int i = 0; i < 15; i ++)
        temp[i] = in[i + 1];
    
    temp[15] = in[0];

    for(int i = 0; i < 16; ++i) {
        sum ^= multTable[temp[i].to_ulong() * 256 + kB[i]];
    }
    
    for (int i = 0; i < 15; i ++)
        result[i] = temp[i];

    result[15] = sum;
    
    /*cout << "reverseR: ";
    for (int i = 0; i < 16; i++)
        cout << hex << result[i].to_ulong();
    cout << endl;*/

    return result;
}

//======== L и обратная ==========

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

vector<bitset<8> > funcReverseL(vector<bitset<8> > in) {
    vector<bitset<8> > temp(16);
    vector<bitset<8> > result(16);

    result = in;

    for (int i = 0; i < 16; i++) {
        temp = result;
        result = funcReverseR(temp);
    }

    return result;
}

//======== LSX и обратная ==========

vector<bitset<8> > funcLSX(vector<bitset<4> > a, vector<bitset<4> > key) {

    vector<bitset<8> > result(16);
    result = funcL(funcS(funcX(a,key)));

    /*cout << "LSX: ";
    for (int i = 0; i < 16; i++)
        cout << hex << result[i].to_ulong();
    cout << endl;*/

    return result;
}

vector<bitset<8> > funcReverseLSX(vector<bitset<4> > a, vector<bitset<4> > key) {

    vector<bitset<8> > result(16);
    vector<bitset<4> > temp(32);

    temp = funcX(a,key);
    result = bitset4to8(temp);
    result = funcReverseL(result);
    temp = bitset8to4(result);
    result = funcReverseS(temp);

    /*cout << "reverseLSX: ";
    for (int i = 0; i < 16; i++)
        cout << hex << result[i].to_ulong();
    cout << endl;*/

    return result;
}


// ========= C ==============

vector<bitset<8> > funcC(int i) {

    vector<bitset<8> > in(16);
    vector<bitset<8> > result(16);

    for (int i = 0; i < 15; i++)
        in[i] = 0;

    in[15] = i;

    result = funcL(in);
    /*cout << "C: ";
    for (int i = 0; i < 16; i++)
          cout << hex << result[i].to_ulong();
    cout << endl;*/

    return result;
}

// ============= F ================

int funcF(vector<bitset<4> > key1, vector<bitset<4> > key2, vector<bitset<8> > C,vector<bitset<4> >& output_key1, vector<bitset<4> >& output_key2) {
    
    vector<bitset<8> > temp(16);
    vector<bitset<4> > result(32), tempC(32);
    //cout << "F: ";
    output_key2 = key1;
    tempC = bitset8to4(C);
    temp = funcLSX(tempC, key1);
    tempC = bitset8to4(temp);  
    output_key1 = funcX(tempC,key2);
    return 0;
} 

// ============= Функция развертывания ключей ================
vector<vector<bitset<4> > > expandKeys(vector<bitset<4> > key1, vector<bitset<4> > key2)
{
    vector<vector<bitset<4> > > result(10);
    vector<bitset<4> > tempkey1(32), tempkey2(32);
    result[0] = key1;
    result[1] = key2;
    tempkey1 = key1;
    tempkey2 = key2;

    for(int j = 0; j < 4; j++)
    {
            for(int i = 1; i < 9; i++ )
            {
                vector<bitset<8> > C(16);
                C = funcC(j*8+i);
                funcF(tempkey1, tempkey2, C, tempkey1, tempkey2);
            }

        result[2*j+2] = tempkey1;
        result[2*j+3] = tempkey2;
    }

    return result;
}

// ============= Зашифрование ================
vector<bitset<4> > Encrypt(vector<bitset<4> > a_binary, vector<bitset<4> > k1_binary, vector<bitset<4> > k2_binary)
{
    vector<vector<bitset<4> > > keys(10);
    vector<bitset<4> > tempLSX4(32), result(32);
    vector<bitset<8> > tempLSX8(16);


    keys = expandKeys(k1_binary, k2_binary);
    tempLSX8 = funcLSX(a_binary,keys[0]);
    for(int i = 1; i < 9; i++)
    {
        tempLSX4 = bitset8to4(tempLSX8);
        tempLSX8 = funcLSX(tempLSX4,keys[i]);
    }
    tempLSX4 = bitset8to4(tempLSX8);
    result = funcX(tempLSX4, keys[9]);

    for (int i = 0; i < 32; i++)
          cout << hex << result[i].to_ulong();
    cout << endl;

    return result;
}

// ============= Расшифрование ================
vector<bitset<4> > Decrypt(vector<bitset<4> > a_binary, vector<bitset<4> > k1_binary, vector<bitset<4> > k2_binary)
{
    vector<vector<bitset<4> > > keys(10);
    vector<bitset<4> > tempLSX4(32), result(32);
    vector<bitset<8> > tempLSX8(16);

    keys = expandKeys(k1_binary, k2_binary);
    tempLSX8 = funcReverseLSX(a_binary,keys[9]);
    for(int i = 8; i > 0; i--)
    {
        tempLSX4 = bitset8to4(tempLSX8);
        tempLSX8 = funcReverseLSX(tempLSX4,keys[i]);
    }
    tempLSX4 = bitset8to4(tempLSX8);
    result = funcX(tempLSX4, keys[0]);

    for (int i = 0; i < 32; i++)
          cout << hex << result[i].to_ulong();
    cout << endl;

    return result;
}

// ============= Режим простой замены с зацеплением ================
int CBC_encrypt(int m, string plaintext, string k1, string k2)
{
    vector<vector<bitset<4> > > PlainTextBitsets(m), CipherTextBitsets(1);
    vector<bitset<4> > plaintext_binary(32),syncmessage_binary(32),k1_binary(32), k2_binary(32), temp(32);
    string SyncMessage1 = "1234567890abcef0a1b2c3d4e5f00112", SyncMessage2 = "23344556677889901213141516171819";

    plaintext_binary = CharToBitset4(plaintext);
    syncmessage_binary = CharToBitset4(SyncMessage1);
    k1_binary = CharToBitset4(k1);
    k2_binary = CharToBitset4(k2);

    for(int i = 0; i < 32; i++)
    {
        temp[i] = plaintext_binary[i] ^ syncmessage_binary[i];
        cout << hex << temp[i].to_ulong();
    }
    cout<<endl;

    CipherTextBitsets[0] = Encrypt(temp,k1_binary,k2_binary);

    return 0;
}



int main() {
    string a = "1122334455667700ffeeddccbbaa9988";
    string b = "7f679d90bebc24305a468d42b9d4edcd";
    string P1 = "1122334455667700ffeeddccbbaa9988", P2 = "00112233445566778899aabbcceeff0a", P3 = "112233445566778899aabbcceeff0a00", P4 = "2233445566778899aabbcceeff0a0011";
    string k1 = "8899aabbccddeeff0011223344556677";
    string k2 = "fedcba98765432100123456789abcdef";
           
    vector<bitset<4> > a_binary(32),b_binary(32),a_temp4(32), test1(32), test3(32);
    vector<bitset<4> > k1_binary(32),k1_temp4(32);
    vector<bitset<4> > k2_binary(32),k2_temp4(32);
    vector<bitset<8> > a_temp8(16), C(16), test2(16), test4(16);

    a_binary = CharToBitset4(a);
    b_binary = CharToBitset4(b);
    k1_binary = CharToBitset4(k1);
    k2_binary = CharToBitset4(k2);

    Encrypt(a_binary,k1_binary,k2_binary);
    Decrypt(b_binary,k1_binary,k2_binary);
    CBC_encrypt(256, P1,k1,k2);

    return 0;
}