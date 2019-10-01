#include<bits/stdc++.h>
using namespace std;

#define pengaliHygiene 10000
#define pengaliEnergy 100

// list aksi
string listAksi[] = {"Tidur Siang","Tidur Malam","Makan Hamburger","Makan Pizza","Makan Steak And Beans","Minum Air","Minum Kopi","Minum Jus","Buang Air Kecil", "Buang Air Besar","Bersosialisasi Ke Kafe","Bermain Media Sosial","Bermain Komputer","Mandi","Cuci Tangan","Mendengarkan Musik Di Radio","Membaca Koran","Membaca Novel"};

bool isVisited[151515+5];   // untuk mengecek apakah state sudah tervisit
int tabelTransisi[151515+5][17+5];      // menyimpan tabel transisi
// atribut: hygiene, energy, fun

// getter atribut hygiene dari state
int getHygiene(int state){
    return (state/10000);
}

// getter atribut energy dari state
int getEnergy(int state){
    return ((state/100)%100);
}

// getter atribut fun dari state
int getFun(int state){
    return state%100;
}

int transisi(int stateAwal, string aksi){
    // fungsi transisi dari state awal ke state lanjutannya setelah melakukan suatu aksi
    if (aksi=="Tidur Siang"){
        return stateAwal+pengaliEnergy*10;
    }
    else if (aksi=="Tidur Malam"){
        return stateAwal+pengaliEnergy*15;
    }
    else if (aksi=="Makan Hamburger"){
        return stateAwal+pengaliEnergy*5;
    }
    else if (aksi=="Makan Pizza"){
        return stateAwal+pengaliEnergy*10;
    }
    else if (aksi=="Makan Steak And Beans"){
        return stateAwal+pengaliEnergy*15;
    }
    else if (aksi=="Minum Air"){
        return stateAwal-pengaliHygiene*5;
    }
    else if (aksi=="Minum Kopi"){
        return stateAwal-pengaliHygiene*10+pengaliEnergy*5;
    }
    else if (aksi=="Minum Jus"){
        return stateAwal-pengaliHygiene*5+pengaliEnergy*10;
    }
    else if (aksi=="Buang Air Kecil"){
        return stateAwal+pengaliHygiene*5;
    }
    else if (aksi=="Buang Air Besar"){
        return stateAwal+pengaliHygiene*10-pengaliEnergy*5;
    }
    else if (aksi=="Bersosialisasi Ke Kafe"){
        return stateAwal+15-pengaliEnergy*10-pengaliHygiene*5;
    }
    else if (aksi=="Bermain Media Sosisal"){
        return stateAwal+10-pengaliEnergy*10;
    }
    else if (aksi=="Bermain Komputer"){
        return stateAwal+15-pengaliEnergy*10;
    }
    else if (aksi=="Mandi"){
        return stateAwal+pengaliHygiene*15-pengaliEnergy*5;
    }
    else if (aksi=="Cuci Tangan"){
        return stateAwal + pengaliHygiene*5;
    }
    else if (aksi=="Mendengarkan Musik Di Radio"){
        return stateAwal+10-pengaliEnergy*5;
    }
    else if (aksi=="Membaca Koran"){
        return stateAwal+5-pengaliEnergy*5;
    }
    else { // membaca novel
        return stateAwal+10-pengaliEnergy*5;
    }
}

int enumerateAksi(string aksi){
    // fungsi untuk mengonvert aksi dari string ke integer, agar bisa mengakses array
    if (aksi=="Tidur Siang"){
        return 0;
    }
    else if (aksi=="Tidur Malam"){
        return 1;
    }
    else if (aksi=="Makan Hamburger"){
        return 2;
    }
    else if (aksi=="Makan Pizza"){
        return 3;
    }
    else if (aksi=="Makan Steak And Beans"){
        return 4;
    }
    else if (aksi=="Minum Air"){
        return 5;
    }
    else if (aksi=="Minum Kopi"){
        return 6;
    }
    else if (aksi=="Minum Jus"){
        return 7;
    }
    else if (aksi=="Buang Air Kecil"){
        return 8;
    }
    else if (aksi=="Buang Air Besar"){
        return 9;
    }
    else if (aksi=="Bersosialisasi Ke Kafe"){
        return 10;
    }
    else if (aksi=="Bermain Media Sosisal"){
        return 11;
    }
    else if (aksi=="Bermain Komputer"){
        return 12;
    }
    else if (aksi=="Mandi"){
        return 13;
    }
    else if (aksi=="Cuci Tangan"){
        return 14;
    }
    else if (aksi=="Mendengarkan Musik Di Radio"){
        return 15;
    }
    else if (aksi=="Membaca Koran"){
        return 16;
    }
    else if (aksi == "Membaca Novel") {
        return 17;
    }
    else{
        return -1;
    }
}

bool isTransisiValid(int stateAwal, string aksi){
    // fungsi untuk mengecek apakah suatu transisi valid atau tidak
    int nextState = transisi(stateAwal,aksi);
    int hygieneNow = getHygiene(nextState);
    int energyNow = getEnergy(nextState);
    int funNow = getFun(nextState);
    if (hygieneNow<0 || hygieneNow>15 || energyNow<0 || energyNow>15 || funNow<0 || funNow>15) return false;
    return true;
}

bool isEndState(int state){
    // fumgsi untuk mengecek apakah suatu state merupakan end state atau bukan
    return (state==0 ||state==151515);
}

void stateGenerator(int stateNow){
    // prosedur untuk menggenerate semua state yang possible
    for (int i = 0; i<=17; ++i){
        if (isTransisiValid(stateNow,listAksi[i])){
            int nextState = transisi(stateNow,listAksi[i]);
            tabelTransisi[stateNow][i] = nextState;
            if (!isVisited[nextState]){
                isVisited[nextState] = true;
                stateGenerator(nextState);
            }
        }
    }
}

int transisiDFA(int stateNow,string aksi){
    /* prekondisi aksi valid */
    return tabelTransisi[stateNow][enumerateAksi(aksi)];
}

bool isAksiValid(int stateNow, string aksi){
    if (enumerateAksi(aksi)==-1) return false;
    return (tabelTransisi[stateNow][enumerateAksi(aksi)]!=-1);
}

void printState(int stateNow){
    printf("Hygiene = %d\n",getHygiene(stateNow));
    printf("Energy = %d\n",getEnergy(stateNow));
    printf("Fun = %d\n",getFun(stateNow));
}

void writeToCsv(){
    // prosedur untuk menuliskan semua state yang telah di generate ke dalam csv
    ofstream myfile;
    myfile.open("tabel_transisi.csv");
    myfile<<"state awal"<<", ,";
    for (int i = 0; i<=17; ++i){
        myfile<<listAksi[i]<<",";
    }
    myfile<<"\n";
    for (int i = 0; i<=15; i+=5){
        for (int j = 0; j<=15; j+=5){
            for (int k = 0; k<=15; k+=5){
                int stateNow = i*pengaliHygiene+j*pengaliEnergy+k;
                myfile<<"( "<<getHygiene(stateNow)<<" "<<getEnergy(stateNow)<<" "<<getFun(stateNow)<<" )"<<", ,";
                for (int l = 0; l<=17; ++l){
                    if (tabelTransisi[stateNow][l]!=-1){
                        myfile<<"( "<<getHygiene(tabelTransisi[stateNow][l])<<" "<<getEnergy(tabelTransisi[stateNow][l])<<" "<<getFun(tabelTransisi[stateNow][l])<<" )"<<",";
                    }
                    else{
                        myfile<<"(-1 -1 -1),";
                    }
                }
                myfile<<"\n";
            }
        }
    }
    myfile<<"(-1 -1 -1), ,";
    for (int i = 0; i<=17; ++i){
        myfile<<"(-1 -1 -1),";
    }
}

void preProcess(){
    // prosedur untuk melakukan pre- processing yang mencakup inisialisasi array dan call prosedur stateGenerator
    memset(tabelTransisi,-1,sizeof(tabelTransisi)); //inisialisasi
    stateGenerator(1000);
    //cout<<"preprocessing selesai\n";
    //writeToCsv();     // cukup dilakukan 1 kali saja
}

void printListAksi(){
    cout<<"Berikut aksi yang tersedia:"<<endl;
    for (int i=0; i<18; i++){
        cout<<"- "<<listAksi[i]<<endl;
    }
}

void judulProgram(){
    ifstream fin("Judul.txt");
    string s;
    while (getline(fin,s)){
        cout<<s<<endl;
    }
}


int main(){
    int stateNow=1000;
    string aksi;
    preProcess();
    
    judulProgram();
    cout<<"Selamat datang di The Sims Simulator"<<endl;
    cout<<"Kondisi awal:"<<endl;
    printState(stateNow);
    cout<<endl;
    
    printListAksi();
    cout<<endl;
    
    // operasi
    do {
        cout<<"Masukkan aksi: ";

        getline(cin,aksi);

        if (!isAksiValid(stateNow,aksi)){
            cout<<"Aksi tidak valid\n";
        }
        else{
            stateNow = transisiDFA(stateNow,aksi);
            printState(stateNow);
        }
        cout<<'\n';
    }while(!isEndState(stateNow));

    if (stateNow == 0){
        cout<<"Game Over. Anda Mati\n";
    }
    else{
        cout<<"Selamat, Anda menang!!!!!!\n";
    }

    return 0;
}
