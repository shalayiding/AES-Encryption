#include<stdio.h>
#include<string>
#include<fstream>
#include<functional>
#include <iostream>
using namespace std;

string Generate_hash(string password){ //generate hash using password string 
    hash<string> result;
    return to_string(result(password));

}

void Encryp(ifstream& input,ofstream& output,string hash_value){  //encryp the file by each recive byte
    
    char c;
    int first, second,result;
    while(input.get(c)){
        
        first = (int)c;
        
        for(int i=0;i<hash_value.length();i++){ //xor each byte with hash value 
            second = (int)hash_value[i];
            int orx = first^second;
            first = orx;
            
        }
        while(first>=255){
            output<<(char)first;
            first-=255;
        }
        
        output<<(char)first;

    }
    input.close();
    output.close();

}


void Decryp(ifstream &input,ofstream &output,string hash_value){  //decryp
    char c;
    int first, second;
    while(input.get(c)){
        first = (int)c;
        while(first>=255 && input.get(c)){
            input.get(c);
            first+=(int)c;
        }
        for(int i=0;i<hash_value.length();i++){ //xor each byte with hash value 
            second = (int)hash_value[i];
            int orx = first^second;
            first = orx;
        }
        
        output<<(char)first;

    }



}

int main(int argc,char **argv){
    string type(argv[4]);
    if(argc!=5 || type!="-e" ){ //
        if(type=="-d"){
            goto jump;
        }    
        cout<<"check your input , output , password, operation  -- > argvments "<<endl;
        cout<<"Example for encryp: ./encryp inputfilename outputfilename password -e "<<endl;
        cout<<"Example for encryp: ./decryp inputfilename outputfilename password -d "<<endl;
        return 0;
    }
    
    jump:
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string key(argv[3]);
    if(!(input.is_open()&& output.is_open())){
        cout<<"input and open file is not open"<<endl;
        return 0;
    }
    
    if(type=="-e"){
        key  += string(key.rbegin(),key.rend());
        string hash_key = Generate_hash(key);
        Encryp(input,output,hash_key);
    }
    if(type=="-d"){
        key  += string(key.rbegin(),key.rend());
        string hash_key = Generate_hash(key);     
        Decryp(input,output,hash_key);

    }
    
    return 0;
}
