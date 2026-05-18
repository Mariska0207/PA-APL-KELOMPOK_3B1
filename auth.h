#ifndef AUTH_H
#define AUTH_H
#include <iostream>
#include <stdexcept>
#include "global.h"
#include "utils.h"

bool cek_username(string username, int index){
    if(index >= jumlahpengguna){
        return false;
    }
    if(username == pengguna[index].username){
        return true;
    }
    return cek_username(username, index + 1);
}

void registrasi(){
    while(jumlahpengguna < MAX){
        system("cls");
        judulpnjng("REGISTRASI 📝");
        setcolor(14);
        cout << "TEKAN 0 UNTUK KEMBALI KE MENU UTAMA\n" << endl;
        setcolor(7);
        try{
            cout << "masukkan username : "; 
            getline(cin, username);
            if(username == "admin" || username == "Admin" || username == "ADMIN"){
                throw invalid_argument("!!! username tidak boleh digunakan !!!");
            }
            if(username == "0"){
                balik_menu = true;
                return;
            }
            if(username.empty()){
                throw invalid_argument("!!! username tidak boleh kosong !!!");
            }
            validpanjangusn(username);
            if(!validusername(username)){
                throw invalid_argument("!!! username tidak boleh mengandung karakter spesial seperti !@#$%^&*() dll. !!!");
            }
            cout << "masukkan password : "; 
            getline(cin, password);
            if(password.empty()){
                throw invalid_argument("!!! password tidak boleh kosong !!!");
            }
            validpanjangpw(password);
            if(!validpassword(password)){
                throw invalid_argument("!!! password tidak boleh mengandung karakter spesial(!@#$%^&*) dan spasi !!!");
            }
            if(cek_username(username, 0)){
                setcolor(12);
                cout << "!!! username sudah ada !!!" << endl;
                setcolor(7);
                system("pause");
                return;
            }
            progressBar();
            setcolor(10);
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            cout << "        >>>>>> REGISTRASI ANDA BERHASIL ✅ <<<<<<" << endl;
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            setcolor(7);
            pengguna[jumlahpengguna].username = username;
            pengguna[jumlahpengguna].password = password;
            pengguna[jumlahpengguna].saldo = 0;
            jumlahpengguna++;
            system("pause");
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
            system("pause");
        }
    }
    setcolor(12);
    cout << "!!! daftar pengguna penuh !!!" << endl;
    setcolor(7);
    system("pause");
}

bool admin_login(string &username, string &password, bool &balik_menu){
    while(percobaanadmin < 3){
        system("cls");
        judulpnjng("LOGIN ADMIN 💻");
        setcolor(14);
        cout << "TEKAN 0 UNTUK KEMBALI KE MENU UTAMA\n" << endl;
        setcolor(7);
        try{
            cout << "MASUKKAN USERNAME : ";
            getline(cin, username);
            if(username == "0"){
                balik_menu = true;
                return false;
            }
            if(username.empty()){
                throw invalid_argument("!!! username tidak boleh kosong !!!");
            }
            if(!validusername(username)){
                throw invalid_argument("!!! username tidak boleh mengandung karakter spesial seperti !@#$%^&*() dll. !!!");
            }
            cout << "MASUKKAN PASSWORD : ";
            getline(cin, password);
            if(password == "0"){
                balik_menu = true;
                return false;
            }
            if(password.empty()){
                throw invalid_argument("!!! password tidak boleh kosong !!!");
            }
            if(!validpassword(password)){
                throw invalid_argument("!!! password tidak boleh mengandung karakter spesial(!@#$%^&*) dan spasi !!!");
            }
            if(username == "admin" && password == "123"){
                progressBar();
                return true;
            }
            percobaanadmin++;
            if(percobaanadmin < 3){
                setcolor(14);
                cout << "\n⚠️  sisa percobaan " << 3 - percobaanadmin << " kali, coba lagi !!!\n" << endl;
                setcolor(7);
                system("pause");
                continue;
            }
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
            system("pause");
        }
    }
    return false;
}

bool login_pengguna(string &username, string &password, bool &balikmenu){
    while(percobaanuser < 3){
        system("cls");
        judulpnjng("LOGIN USER 👥");
        setcolor(14);
        cout << "TEKAN 0 UNTUK KEMBALI KE MENU UTAMA\n" << endl;
        setcolor(7);
        try{
            cout << "MASUKKAN USERNAME : ";
            getline(cin, username);
            if(username == "0"){
                balikmenu = true;
                return false;
            }
            if(username.empty()){
                throw invalid_argument("!!! username tidak boleh kosong !!!");
            }
            if(!validusername(username)){
                throw invalid_argument("!!! username tidak boleh mengandung karakter spesial seperti !@#$%^&*() dll. !!!");
            }
            cout << "MASUKKAN PASSWORD : ";
            getline(cin, password);
            if(password == "0"){
                balikmenu = true;
                return false;
            }
            if(password.empty()){
                throw invalid_argument("!!! password tidak boleh kosong !!!");
            }
            if(!validpassword(password)){
                throw invalid_argument("!!! password tidak boleh mengandung karakter spesial(!@#$%^&*) dan spasi !!!");
            }
            for(int i = 0; i < jumlahpengguna; i++){
                if(username == pengguna[i].username && password == pengguna[i].password){
                    progressBar();
                    return true;
                }
            }
            percobaanuser++;
            if(percobaanuser < 3){
                setcolor(14);
                cout << "\n⚠️  sisa percobaan " << 3 - percobaanuser << " kali, coba lagi !!!\n" << endl;
                setcolor(7);
                system("pause");
                continue;
            }
        }catch(exception &e){
            setcolor(12);
            cout << "\n[ERROR] " << e.what() << endl;
            setcolor(7);
            system("pause");
        }
    }
    return false;
}

#endif