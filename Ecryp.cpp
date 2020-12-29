#include "Ecryp.h"
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
void Ecryp::Print_sbox()
{ //print sbox

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
        cout << Matrix[i]<< ",";
        cout << endl;
    }


}

void Ecryp::SubBytes()
{
    for (int ele = 0; ele < 4 * 4; ele++)
    {
        int r = Matrix[ele][7] * 8 + Matrix[ele][6] * 4 + Matrix[ele][5] * 2 + Matrix[ele][4];
        int c = Matrix[ele][3] * 8 + Matrix[ele][2] * 4 + Matrix[ele][1] * 2 + Matrix[ele][0];
        Matrix[ele]=S_box[r][c];
        
    }
}

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