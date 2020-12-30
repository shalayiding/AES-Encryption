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
        int r = Matrix[ele][7] * 8 + Matrix[ele][6] * 4 + Matrix[ele][5] * 2 + Matrix[ele][4];
        int c = Matrix[ele][3] * 8 + Matrix[ele][2] * 4 + Matrix[ele][1] * 2 + Matrix[ele][0];
        Matrix[ele]=S_box[r][c];
        
    }
}

void Ecryp::ShiftRowCircle(int row_num , int step){ //shifting the row by moving int step
    bitset<8> tmp[4];
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

void Ecryp::MixColumns(){ //four bytes of each column is combined with given invertible linear transformation matrix
    vector<vector<int>> trans_matrix = {
        {2,3,1,1},
        {1,2,3,1},
        {1,1,2,3},
        {3,1,1,2}
    };
    vector<int> tmp;
    for(int i=0;i<16;i++){
        tmp.push_back(Matrix[i].to_ulong());
    }

    // for(int i=0;i<4;i++){
    //     Matrix[i]

    //     Matrix[i+4]
    //     Matrix[i+8]
    //     Matrix[i+12]

    // }



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
        
        cout << Matrix[i].to_ulong()<< ",";
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