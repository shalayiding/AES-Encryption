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
    obj.Print_data();
    obj.Exor();
    obj.Print_data();
    obj.Exor();
    obj.Print_data();


    return 0;
}