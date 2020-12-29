#include"Ecryp.h"
Ecryp::Ecryp(string argv1, string argv2, string argv3)  //default  
{
    infile = argv1;
    outfile = argv2;
    password = argv3;
    
    ifstream input(infile);
    input.seekg(0, ios::end);
    int file_size = input.tellg();
    input.seekg(0,ios::beg);
    if(file_size>=data.max_size()){
        ErrorMessage(1);
    }
    char c;
    while(input.get(c)){
        data.push_back((int)c);
    }
}


void Ecryp::ErrorMessage(int Error_code){   //general error message provide
    if(Error_code==1){
        cout<<" The file size is too big to process Error type is : "<<Error_code<<endl;
        exit(Error_code);       
    }

}

string Ecryp::Generate_hash(){//Generate hash using password 

    hash<string> result;
    return to_string(result(password));

}

void Ecryp::Exor(){ //simple xor encryp
    string key = Generate_hash();

    for(int i=0;i<data.size();i++){
        for(int j=0;j<key.length();j++){
            data[i]^=(int)key[j];
        }

    }
}



void Ecryp::Print_data(){
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<",";

    }
    cout<<endl;


}