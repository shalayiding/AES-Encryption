#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<functional>
#include<bitset>
using namespace std;




class Ecryp
{
private:
    string outfile, infile, password,key;
    string Generate_hash();
    vector<int> data;
    int Error_code;
    const int key_len_1=16,key_len_2=24,key_len_3=32;
    unsigned char S_box[16][16];
    unsigned char inv_S_box[16][16];
    unsigned char Matrix[16]={0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b}; //input matrix 16bytes in 4*4 matrix
    unsigned char AES_key[16]={0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b};
    void ErrorMessage(int Error_code);
    void ShiftRowCircle(int row_num, int step);
    void gmix_column(unsigned char *r);
    unsigned char Multi_byte(unsigned char a, unsigned char b);
    //------------------key schedule ----------------------
    void Roundc(unsigned char *r,int size);
    void RotWord(unsigned char *r);
    void SubWord(unsigned char *r);


public:
    Ecryp(string argv1, string argv2, string argv3);
    void Exor();
    void Print_data();
    void Extractsbox(string sbox,string invsbox);
    void Print_sbox();
    //-----------------encryption --------------------
    void SubBytes();
    void ShiftRow();
    void MixColumns();
    void AddRoundKey();

    
    //-----------------decryption --------------------
    void Inv_MixColumns();
    



};