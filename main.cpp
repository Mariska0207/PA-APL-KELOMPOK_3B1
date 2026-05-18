#include <iostream>
#include <stdexcept>
#include <windows.h>
using namespace std;

#include "global.h"
#include "utils.h"
#include "auth.h"
#include "admin.h"
#include "user.h"

int main(){
    SetConsoleOutputCP(65001);
    while(true){
        while(!login_admin && !login_user){
            system("cls");
            judulpnjng("SELAMAT DATANG DI TOKO BUAH KICAW 🍎");
            cout << "1. 🖥️  LOGIN SEBAGAI ADMIN " << endl;
            cout << "2. ​👥​ LOGIN SEBAGAI PENGGUNA BIASA" << endl;
            cout << "3. 📝 REGISTER" << endl;
            cout << "4. 🚪 KELUAR" << endl;
            setcolor(11);
            cout << "=========================================================\n";
            setcolor(9);
            cout << "MASUKKAN PILIHAN ANDA : ";
            try {
                string input;
                getline(cin, input);
                setcolor(7);
            if(input.empty()) throw invalid_argument("!!! input tidak boleh kosong !!!");
            for(char c : input) {
                if(!isdigit(c)) throw invalid_argument("!!! input tidak valid !!!");
            }
            pilihan = stoi(input);
            system("cls");
            switch(pilihan){
                case 1:
                    if(admin_login(username, password, balik_menu)){
                        setcolor(10);
                        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                        cout << "             >>>>>> LOGIN BERHASIL ✅ <<<<<<" << endl;
                        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                        setcolor(7);
                        system("pause");
                        login_admin = true;
                        login_user = false;
                        percobaanadmin = 0;
                        menuadmin();
                        break;
                    }else if(percobaanadmin == 3){
                        setcolor(13);
                        cout << "\npercobaan login anda habis, program keluar 💀" << endl;
                        setcolor(7);
                        return 0;
                    }else{
                        balik_menu = true;
                        continue;
                    }
                case 2:
                    if(login_pengguna(username, password, balik_menu)){
                        setcolor(10);
                        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                        cout << "             >>>>>> LOGIN BERHASIL ✅ <<<<<<" << endl;
                        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                        setcolor(7);
                        system("pause");
                        login_admin = false;
                        login_user = true;
                        percobaanuser = 0;
                        menuuser();
                        break;
                    }else if(percobaanuser == 3){
                        setcolor(13);
                        cout << "\npercobaan login anda habis, program keluar 💀" << endl;
                        setcolor(7);
                        return 0;
                    }else{
                        balik_menu = true;
                        continue;
                    }
                case 3:
                    registrasi();
                    balik_menu = true;
                    continue;
                case 4:             
                    setcolor(14);         
                    cout << "TERIMA KASIH TELAH  MENGGUNAKAN PROGRAM INI 👋 \n" << endl;
                    cout << R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⠞⢛⣟⢛⠻⣿⣛⣛⣟⣛⠳⣦⣤⣤⣴⠶⠿⠛⢛⣻⣟⣻⣿⣿⣷⣶⣶⣤⣀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠾⠛⢉⣠⡾⣿⡿⢿⣷⣶⣤⡈⠉⠉⠛⠻⢯⣥⡀⠀⣀⣤⠶⣻⣿⢻⣿⣿⣯⡍⠙⠻⢿⣿⣦⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⠿⠟⢀⣴⠞⠋⠁⢰⣿⡿⢿⣯⣉⣿⣷⠀⠀⠀⠀⠀⠈⣿⠟⠉⠀⢰⣿⣿⢿⣿⣉⣿⣿⡄⠀⠀⠀⠉⣿
⠀⠀⠀⠀⠀⠀⢀⣤⡾⠋⠃⠀⠀⠻⣧⡀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⣸⡇⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⢀⣴⡟
⠀⠀⠀⠀⢀⣴⠟⠉⠀⠀⠀⠀⠀⠀⠀⠙⠳⢦⣤⣙⣻⠿⠿⠟⠋⣁⣀⣠⣤⣶⠾⠋⠳⠶⣤⣤⣤⣙⣻⣿⣿⣿⣯⣥⣶⡶⣿⡿⠟⠀
⠀⠀⠀⣴⣿⠁⠀⠀⠀⠀⢀⣤⠶⠶⠶⠶⣦⣤⣤⣉⡉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀
⠀⢠⣾⠋⠀⠀⠀⠀⠀⠀⢿⣧⡀⠀⠰⣤⣀⣀⠀⠉⠙⠛⠛⠷⠶⢶⣦⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣶⠾⠛⣷⡄⠀
⣰⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠷⣦⣄⡀⠉⠛⠒⠶⢤⣄⠀⠀⠀⠀⠀⠈⠉⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠉⠉⠀⠀⣀⣴⣿⠁⠀
⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠳⢶⣤⣄⣀⠀⠀⠈⠉⠉⠛⠓⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡇⢻⡆⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠻⠷⢶⣤⣤⣤⣤⣤⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣴⠿⠁⠈⢿⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠉⠙⠛⠉⠉⠁⠀⠀⠀⠘⣧
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⠉⠛⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⡇⠀⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡇⠀⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡿⠁⢀⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠛⠁⠀⠘⠿⠶⠶⣦⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠈⢉⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢋⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠟⠁⠀⠀⠀⣀⣤⣤⣀⣀⠀⠀⣀⣴⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠟⠁⠀⠀⠀⣠⣾⠟⠁⠀⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡾⠛⠁⠀⠀⠀⣠⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡶⠋⠁⠀⠀⠀⠀⣠⣾⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)";
                    setcolor(7);
                    return 0;
                default:
                    takvalid();
                    continue;
                }
            } catch(out_of_range &e) {
                setcolor(12);
                cout << "\n[ERROR] input terlalu panjang." << endl;
                setcolor(7);
                system("pause");
            }catch(exception &e){
                setcolor(12);
                cout << "\n[ERROR] " << e.what() << endl;
                setcolor(7);
                system("pause");
            }
        }
    }
}