#include "Ecryp.h"

//-----------------------------AES Encryption core --------------------------------------------------------------------------
void Ecryp::Extractsbox(string sbox_file_name, string invsbox_file_name)
{ //extract sbox from file
    ifstream sbox;
    sbox.open(sbox_file_name);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int n = 0;
            sbox >> hex >> n;
            S_box[i][j] = n;
        }
    }
    ifstream invsbox;
    invsbox.open(invsbox_file_name);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int n = 0;
            invsbox >> hex >> n;
            inv_S_box[i][j] = n;
        }
    }
}

void Ecryp::SubBytes()   //find the bytes value from the table (s-box)
{
    for (int ele = 0; ele < 4 * 4; ele++)
    {
        int r = Matrix[ele]/16;
        int c = Matrix[ele]%16;
        Matrix[ele]=S_box[r][c];
        
    }
}

void Ecryp::ShiftRowCircle(int row_num , int step){ //shifting the row by moving int step
    unsigned char tmp[4];
    row_num *=4;
    int final_position = 0;
    for(int i=0;i<4;i++){
        tmp[i] = Matrix[row_num+i];  
    }
    for(int i=0;i<4;i++){ //find final position and plug the orginal matrix value 
        final_position = i - step;
        if(final_position < 0 )
            final_position+=4;
        Matrix[final_position+row_num]= tmp[i];
    }

}

void Ecryp::ShiftRow(){ //shifting the the row of the input matrix 0, 1 , 2 , 3
    ShiftRowCircle(1,1);
    ShiftRowCircle(2,2);         
    ShiftRowCircle(3,3);
}

void Ecryp::gmix_column(unsigned char *r){  //mix single column 
    
    ///link : https://en.wikipedia.org/wiki/Rijndael_MixColumns#Implementation_example
    
    //============================basic r sets ====================================
    //===Befor=========After===========Before==================After==================
    // db 13 53 45	8e 4d a1 bc	    219 19 83 69	    142 77 161 188
    // f2 0a 22 5c	9f dc 58 9d	    242 10 34 92	    159 220 88 157
    // 01 01 01 01	01 01 01 01	    1   1  1  1	        1    1   1   1
    // c6 c6 c6 c6	c6 c6 c6 c6	    198 198 198 198	    198 198 198 198
    // d4 d4 d4 d5	d5 d5 d7 d6	    212 212 212 213	    213 213 215 214
    // 2d 26 31 4c	4d 7e bd f8	    45 38 49 76	        77 126 189 248
    //=================================================================================

    unsigned char a[4];
    unsigned char b[4];
    unsigned char h;
    unsigned char c;
    for(c =0;c <4;c ++){
        
        a[c]=r[c];
        
        h = (unsigned char)((signed char)r[c] >> 7);
        b[c]=r[c]<<1;
        b[c]^=0x1B&h;

    }
    
    r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; /* 2 * a0 + a3 + a2 + 3 * a1 */
    r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
    r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
    r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */

}

void Ecryp::MixColumns(){ //four bytes of each column is combined with given invertible linear transformation matrix
    


    for(int c=0;c<4;c++){
        unsigned char r[4]= {Matrix[c],Matrix[c+4],Matrix[c+8],Matrix[c+12]};
        gmix_column(r);
        Matrix[c]=r[0];
        Matrix[c+4]=r[1];
        Matrix[c+8]=r[2];
        Matrix[c+12]=r[3];
    }
    
}


void Ecryp::Roundc(unsigned char *r,int size){   //The round constant rconi for round i of the key expansion is the 32-bit word:
    //link:https://en.wikipedia.org/wiki/AES_key_schedule
    unsigned char  c(1);
    r[1]=r[2]=r[3]=0;
    for(int i=0;i<size-1;i++){
        c=(c << 1) ^ (((c >> 7) & 0x01) * 0x1b);

    }
    r[0]=c;

}

void Ecryp::RotWord(unsigned char *r){ //move to 1step front 
    unsigned char tmp = r[0];
    r[0]=r[1];
    r[1]=r[2];
    r[2]=r[3];
    r[3]=tmp;

}

void Ecryp::SubWord(unsigned char *r){  //look up the value from s-box
    

}


void Ecryp::AddRoundKey(){ //add round key to the matrix 


}




//-----------------------------AES Decryption core --------------------------------------------------------------------------
unsigned char Ecryp::Multi_byte(unsigned char a, unsigned char b){  //multiply numbers in Rijndael's finite field
    //link : https://en.wikipedia.org/wiki/Finite_field_arithmetic
    unsigned char result = 0;
    unsigned char highbit = 0;


    for (int i = 0; i < 8; i++) {
      if (b & 1)
        result ^= a;

      highbit = a & 0x80;
      a <<= 1;
      if (highbit)
        a ^= 0x1B;
      b >>= 1;
    }

    return result;



}

void Ecryp::Inv_MixColumns(){  //reverse of the mixcolumns using Finite field arithmetic
    
    for(int c=0;c<4;c++){
        unsigned char r[4]= {Matrix[c],Matrix[c+4],Matrix[c+8],Matrix[c+12]};
        unsigned char result[4];
        result[0]=  Multi_byte(0x0e, r[0]) ^ Multi_byte(0x0b, r[1]) ^ Multi_byte(0x0d, r[2]) ^ Multi_byte(0x09, r[3]);
        result[1] = Multi_byte(0x09, r[0]) ^ Multi_byte(0x0e, r[1]) ^ Multi_byte(0x0b, r[2]) ^ Multi_byte(0x0d, r[3]);
        result[2] = Multi_byte(0x0d, r[0]) ^ Multi_byte(0x09, r[1]) ^ Multi_byte(0x0e, r[2]) ^ Multi_byte(0x0b, r[3]);
        result[3] = Multi_byte(0x0b, r[0]) ^ Multi_byte(0x0d, r[1]) ^ Multi_byte(0x09, r[2]) ^ Multi_byte(0x0e, r[3]);
        Matrix[c]=result[0];
        Matrix[c+4]=result[1];
        Matrix[c+8]=result[2];
        Matrix[c+12]=result[3];

    }
    

}

void Ecryp::Print_sbox(){ //print sbox

    // for (int i = 0; i < 16; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         cout << S_box[i][j] << ",";
    //     }
    //     cout << endl;
    // }
    // cout << endl
    //      << endl;
    // for (int i = 0; i < 16; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         cout << inv_S_box[i][j] << ",";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < 16; i++)
    {
        if(i%4==0)
            cout<<endl;
        
        cout << (int)Matrix[i]<< ",";
    }
    cout<<endl;


}






// -----------------------------------simple xor encryption with default hash ------------------------------------------------
void Ecryp::Exor()
{ //simple xor encryp
    string key = Generate_hash();

    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < key.length(); j++)
        {
            data[i] ^= (int)key[j];
        }
    }
}

void Ecryp::Print_data()
{
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << ",";
    }
    cout << endl;
}

Ecryp::Ecryp(string argv1, string argv2, string argv3) //default
{
    infile = argv1;
    outfile = argv2;
    password = argv3;

    ifstream input(infile);
    input.seekg(0, ios::end);
    int file_size = input.tellg();
    input.seekg(0, ios::beg);
    if (file_size >= data.max_size())
    {
        ErrorMessage(1);
    }
    char c;
    while (input.get(c))
    {
        data.push_back((int)c);
    }
}

void Ecryp::ErrorMessage(int Error_code)
{ //general error message provide
    if (Error_code == 1)
    {
        cout << " The file size is too big to process Error type is : " << Error_code << endl;
        exit(Error_code);
    }
}

string Ecryp::Generate_hash()
{ //Generate hash using password

    hash<string> result;
    return to_string(result(password));
}