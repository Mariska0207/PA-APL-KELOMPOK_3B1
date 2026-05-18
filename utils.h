#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <stdexcept>
#include <windows.h>
#include <cctype>

void setcolor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void progressBar(){
    setcolor(10);
    cout << "\n[";
    for(int i = 0; i < 20; i++){
        cout << "▮";
        Sleep(50);
    }
    cout << " ]\n";
    setcolor(7);
}

bool validusername(const string& str){
    for(char c : str){
        if(!isalnum((unsigned char)c) && c != '_' && c != '.'){
            return false;
        }
    }
    return true;
}

bool validpassword(const string& str){
    for(char c : str){
        if(!isalnum((unsigned char)c) && c != '_' && c != '.'){
            return false;
        }
    }
    return true;
}

bool validNamaBuah(const string& str){
    for(char c : str){
        if(!isalpha((unsigned char)c) && c != ' '){
            return false;
        }
        if(!isalnum((unsigned char)c) && c != ' '){
            return false;
        }
    }
    return true;
}

void validpanjangpw(const string& str, int panjangmin = 3, int panjangmax = 8){
    if(str.length() < panjangmin || str.length() > panjangmax){
            throw invalid_argument("!!! panjang password minimal 3 karakter dan maksimal 8 karakter !!!");
    }
}

void validpanjangusn(const string& str, int panjangmin = 3, int panjangmax = 20){
    if(str.length() < panjangmin || str.length() > panjangmax){
            throw invalid_argument("!!! panjang username minimal 3 karakter dan maksimal 20 karakter !!!");
    }
}

void takvalid(){
    setcolor(12);
    cout << "!!! ⚠️  pilihan tidak valid !!!" << endl;
    setcolor(7);
    system("pause");
}

void judulpnjng(string judul){
    setcolor(11);
    int lebar = 57;
    int panjang = judul.length();
    int kiri = (lebar - panjang) / 2;

    cout << string(lebar, '=') << endl;
    cout << string(kiri, ' ') << judul << endl;
    cout << string(lebar, '=') << endl;
    setcolor(7);
}

#endif