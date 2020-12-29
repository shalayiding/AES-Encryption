#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<functional>
using namespace std;

class Ecryp
{
private:
    string outfile, infile, password,key;
    vector<int> data;
    int Error_code;
    void ErrorMessage(int Error_code);
    string Generate_hash();
public:
    Ecryp(string argv1, string argv2, string argv3);
    void Exor();
    void Print_data();
    
};