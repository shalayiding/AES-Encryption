//main.cpp

#include<stdio.h>
#include<string>
#include<fstream>
#include<functional>
#include <iostream>
#include "Ecryp.h"
using namespace std;



int main(){
    Ecryp obj("test.txt","test.out","123456");
    obj.Extractsbox("S-box","Inverse S-box");
    obj.SubBytes();
    obj.Print_sbox();

    return 0;
}