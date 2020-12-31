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
    bitset<8> S_box[16][16];
    bitset<8> inv_S_box[16][16];
    bitset<8> Matrix[4*4]={0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b}; //input matrix 16bytes in 4*4 matrix

    void ErrorMessage(int Error_code);
    void ShiftRowCircle(int row_num, int step);
    void gmix_column(unsigned char *r);

public:
    Ecryp(string argv1, string argv2, string argv3);
    void Exor();
    void Print_data();
    void Extractsbox(string sbox,string invsbox);
    void Print_sbox();
    void SubBytes();
    void ShiftRow();
    void MixColumns();
    



};