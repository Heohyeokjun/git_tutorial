#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int imsi[6];
int l;

vector<vector<int>> v; 
int m;

vector<vector<int>> none;

vector<vector<int>> w;
int countw = 0;

vector<vector<int>> rebuildingid;
 
vector<vector<int>> u;
int countu = 0;

vector<vector<int>> ub;
int countub = 0;

vector<vector<int>> ubb;


#include "board.h"

void manage_board(string input_file, string output_file) {
    
    int width, height;
    int num_jobs; 
    char job_type;
    ifstream input;
    ofstream output;

    input.open(input_file);

    if (!(input.is_open())) {
        cerr << "Input missing" << endl;
        return;
    }    
    
    input >> width >> height >> num_jobs;

    output.open(output_file, ofstream::trunc);

    if (!(output.is_open())) {
        cerr << "Output missing" << endl;
        return;
    }


    Board board = Board(num_jobs, width, height, output);


    int page_x, page_y, page_width, page_height, page_id;
    char page_content;
    
    for (int job_idx = 1; job_idx <= num_jobs; job_idx++) {
        input >> job_type;

        switch (job_type) {
            case 'i': 
                //insert page
                input >> page_id >> page_x >> page_y >> page_width >> page_height >> page_content;
                board.print_job(job_idx, job_type, page_id);
                board.insert_page(page_x, page_y, page_width, page_height, page_id, page_content);
                //cout << 'i';    
                break;
            case 'd':
                //delete page
                input >> page_id;
                board.print_job(job_idx, job_type, page_id);
                board.delete_page(page_id);
                break;
            case 'm':
                //modify page
                int modify_content;
                input >> modify_content;

                if (modify_content) {
                    //modify content 
                    input >> page_id >> page_content;
                    board.print_job(job_idx, job_type, page_id);
                    board.modify_content(page_id, page_content);
                } else {
                    //modify position
                    input >> page_id >> page_x >> page_y;
                    board.print_job(job_idx, job_type, page_id);
                    board.modify_position(page_id, page_x, page_y);
                }
                break;
            default:
                cerr << "Wrong job type" << endl;
                return;
        }

        cerr << "Job " << job_idx << " Complete!" << endl;

    } 
    

    input.close();
    output.close();
    
}


int main(){//int argc, char *argv[]) {

    /*
    if (argc==3) manage_board(string(argv[1]), string(argv[2]));
    else cerr << "Wrong arguments" << endl;
    */

    ofstream fout;
    fout.open("outputTest.txt");
    //input0
    /*
    Board board(7, 50, 20, fout);
    board.insert_page(0, 1, 10, 15, 8, 'c');
    board.insert_page(5, 2, 5, 18, 1, 'k');
    board.insert_page(2, 7, 3, 2, 2, 'x');
    board.insert_page(6, 3, 10, 10, 32, 'l');
    board.modify_content(32, 'M');
    board.modify_position(2, 1, 2);
    board.delete_page(8);
    */

    //input1
    /*
    Board board(15, 64, 100, fout);
    board.insert_page(11, 57, 32, 11, 18731, 's');
    board.modify_position(18731, 0, 25);
    board.insert_page(7, 20, 41, 79, 8366, 'm');
    board.modify_content(8366, 'g');
    board.delete_page(18731);
    board.modify_content(8366, 'a');
    board.delete_page(8366);
    board.insert_page(6, 19, 18, 28, 14083, 'u');
    board.delete_page(14803);
    board.insert_page(24, 23, 14, 56, 12714, 'y');
    board.delete_page(12714);
    board.insert_page(13, 26, 43, 70, 8277, 'w');
    board.insert_page(25, 1, 21, 84, 14092, 'v');
    board.modify_position(8277, 21, 23);
    board.delete_page(14092);
    */

    //input9
    /*
    Board board(21, 100, 50, fout);
    board.insert_page(5, 2, 48, 24, 13263, 'l');
    board.insert_page(5, 15, 80, 28, 29899, 'n');
    board.modify_position(13263, 29, 8);
    board.modify_content(13263, 't');
    board.insert_page(27, 3, 30, 43, 12999, 'o');
    board.insert_page(48, 9, 1, 24, 1824, 'w');
    board.modify_content(13263, 'a');
    board.modify_content(12999, 'l');
    board.modify_position(1824, 20, 0);
    board.insert_page(5, 36, 94, 6, 1688, 'g');
    board.delete_page(13263);
    board.modify_content(1824, 'l');
    board.delete_page(1824);
    board.delete_page(29899);
    board.insert_page(47, 7, 2, 38, 9966, 't');
    board.modify_content(12999, 'b');
    board.insert_page(42, 29, 27, 9, 5111, 's');
    board.insert_page(11, 32, 56, 9, 6736, 'h');
    board.insert_page(15, 10, 42, 20, 22324, 'i');
    board.insert_page(10, 14, 81, 21, 10387, 's');
    board.delete_page(10387);
    */

    //input6
    
    Board board(21, 100, 120, fout);
    board.insert_page(12, 33, 68, 61, 29258, 'c');
    board.insert_page(8, 114, 71, 0, 18978, 'q');
    board.insert_page(24, 31, 45, 29, 20034, 'o');
    board.insert_page(85, 19, 8, 100, 13581, 'u');
    board.insert_page(0, 7, 97, 11, 18387, 'i');
    board.insert_page(1, 23, 94, 6, 22582, 'r');
    board.insert_page(39, 40, 35, 61, 5166, 'i');
    board.insert_page(85, 39, 12, 64, 5083, 'q');
    board.insert_page(16, 65, 52, 55, 2748, 'a');
    board.modify_content(2748, 'u');
    board.insert_page(0, 17, 58, 67, 17171, 'w');
    board.modify_position(22582, 6, 113);
    board.insert_page(1, 48, 72, 31, 28267, 't');
    board.insert_page(4, 10, 33, 0, 18096, 'o');
    board.modify_position(22582, 3, 17);
    board.insert_page(43, 20, 12, 14, 31634, 'g');
    board.insert_page(17, 12, 35, 32, 28674, 'n');
    board.delete_page(13581);
    board.insert_page(20, 1, 40, 115, 268, 'l');  
    board.delete_page(28674);
    board.modify_position(18978, 14, 61);
    

    fout.close();

    return 0;
    
}

void Board::takeid(int key){
    for(int i=0; i<(int)v.size(); i++){
        if(v[i][4]==key){
            m = i;
            break;
        }
    }
}

void Page::setid(){
    setpage(v[m][0],v[m][1],v[m][2],v[m][3],v[m][4],v[m][5]);
}

/*
bool gyupchim(int m){
    if((v[m][0]<=v[i][0] && v[i][0]<v[m][0]+v[m][2]) || (v[m][0]<v[i][0]+v[i][2] && v[i][0]+v[i][2]<=v[m][0]+v[m][2]) || (v[m][0]>v[i][0] && v[m][0]+v[m][2]<v[i][0]+v[i][2])){
        if((v[m][1]<=v[i][1] && v[i][1]<v[m][1]+v[m][3]) || (v[m][1]<v[i][1]+v[i][3] && v[i][1]+v[i][3]<=v[m][1]+v[m][3]) || (v[m][1]>v[i][1] && v[m][1]+v[m][3]<v[i][1]+v[i][3])){                
                return true;
            }
    }

    else{return false;}
}*/

int Board::findabovepage(int key){
    
    takeid(key);

    for(int i=m+1; i<(int)v.size(); i++){
        if((v[m][0]<=v[i][0] && v[i][0]<v[m][0]+v[m][2]) || (v[m][0]<v[i][0]+v[i][2] && v[i][0]+v[i][2]<=v[m][0]+v[m][2]) || (v[m][0]>v[i][0] && v[m][0]+v[m][2]<v[i][0]+v[i][2])){
            if((v[m][1]<=v[i][1] && v[i][1]<v[m][1]+v[m][3]) || (v[m][1]<v[i][1]+v[i][3] && v[i][1]+v[i][3]<=v[m][1]+v[m][3]) || (v[m][1]>v[i][1] && v[m][1]+v[m][3]<v[i][1]+v[i][3])){                
                w.push_back({v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]});
                countw++;
                cout<<"above page gyupchim ok"<<endl;
            }
        }
    }

    /*
    for(int m=(int)u.size()-countu+1; m<(int)u.size(); m++){        
        for(int j=(int)u.size()-countu; j<m; j++){
            if((u[m][0]<=u[j][0] && u[j][0]<u[m][0]+u[m][2]) || (u[m][0]<u[j][0]+u[j][2] && u[j][0]+u[j][2]<=u[m][0]+u[m][2]) || (u[m][0]>u[j][0] && u[m][0]+u[m][2]<u[j][0]+u[j][2])){
                if((u[m][1]<=u[j][1] && u[j][1]<u[m][1]+u[m][3]) || (u[m][1]<u[j][1]+u[j][3] && u[j][1]+u[j][3]<=u[m][1]+u[m][3]) || (u[m][1]>u[j][1] && u[m][1]+u[m][3]<u[j][1]+u[j][3])){
                    
                    //findabovepage(v[i][4]);
                    //aboveid.push_back(w[j][4]);
                    //count1++;
                    u.erase(u.begin()+m);
                    countu--;
                }
            }
        }
    }
    */

/*
    for(int i=0; i<(int)w.size()-countw; i++){
        for(int j=(int)w.size()-countw; j<(int)w.size(); j++){
            if(w[j][4] == w[i][4]){
                w.erase(w.begin()+j);
                countw--;
                cout<<"above erase"<<endl;
            }
        }
    }
    */

    for(int i=0; i<countw; i++){
        for (int j=(int)w.size()-countw; j<(int)w.size()-i-1; j++){
            if(w[j][4]>w[j+1][4]){
                for(int k=0; k<6; k++){
                imsi[k] = w[j+1][k];
                w[j+1][k] = w[j][k];
                w[j][k] = imsi[k];
                }
            }
        }
    }

    int c = (int)w.size(); //error possible
    for(int i=c-countw; i<c; i++){ 
        countw = 0;

        cout<<"above recursion"<<endl;    
        findabovepage(w[i][4]);

    }
    countw = 0;

    for(int i=0; i<(int)ubb.size(); i++){
        if(ubb[i][4]==key){
            return -1;
        }
    }  

    takeid(key);

    for (int h = v[m][1]; h < v[m][1]+v[m][3]; h++) {
        for (int w = v[m][0]; w < v[m][0]+v[m][2]; w++) {
            board[h*width + w] = ' ';
        }
    }
    
    rebuildingid.push_back({v[m][0],v[m][1],v[m][2],v[m][3],v[m][4],v[m][5]});
    building++;

    findunderpage(key);
    print_board();

    return key;
}

int Board::findunderpage(int key){
    cout<<"under is start"<<endl;
    countu = 0;

    takeid(key);

    ubb.push_back({v[m][0],v[m][1],v[m][2],v[m][3],v[m][4],v[m][5],m});

    cout<<v[m][5]<<endl;
    
    for(int i=0; i<m; i++){
        if((v[m][0]<=v[i][0] && v[i][0]<v[m][0]+v[m][2]) || (v[m][0]<v[i][0]+v[i][2] && v[i][0]+v[i][2]<=v[m][0]+v[m][2]) || (v[m][0]>v[i][0] && v[m][0]+v[m][2]<v[i][0]+v[i][2])){
            if((v[m][1]<=v[i][1] && v[i][1]<v[m][1]+v[m][3]) || (v[m][1]<v[i][1]+v[i][3] && v[i][1]+v[i][3]<=v[m][1]+v[m][3]) || (v[m][1]>v[i][1] && v[m][1]+v[m][3]<v[i][1]+v[i][3])){                
                u.push_back({v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5],i});
                countu++;
                cout<<"under page gyupchim ok 1"<<endl;
            }
        }
    }
    
    for(int j=0; j<(int)u.size(); j++){
        cout<<"In u ";
        cout<<u[j][5]<<endl;
    }

    int usize=(int)u.size();
    for(int i=0; i<usize; i++){
        for(int j=u[i][6]+1; j<(int)v.size(); j++){
            //cout<<j<<endl;
            //cout<<m<<endl;
            if(j!=m){
                if((u[i][0]<=v[j][0] && v[j][0]<u[i][0]+u[i][2]) || (u[i][0]<v[j][0]+v[j][2] && v[j][0]+v[j][2]<=u[i][0]+u[i][2]) || (u[i][0]>v[j][0] && u[i][0]+u[i][2]<v[j][0]+v[j][2])){
                    if((u[i][1]<=v[j][1] && v[j][1]<u[i][1]+u[i][3]) || (u[i][1]<v[j][1]+v[j][3] && v[j][1]+v[j][3]<=u[i][1]+u[i][3]) || (u[i][1]>v[j][1] && u[i][1]+u[i][3]<v[j][1]+v[j][3])){
                        u.push_back({v[j][0],v[j][1],v[j][2],v[j][3],v[j][4],v[j][5],j}); 
                        countu++;
                        cout<<"all above ok 2"<<endl;
                    }
                }
            }
        }
    }
    //cout<<"??"<<endl;
    //problem: key의 above까지도 u벡터에 저장되버림. 
    //따라서 key의 above를 예외처리해야함.
    //의문:key above는 (모든 under의 above의 합집합)의 교집합인가? -> 아니다.

    //countub=0;
    //같은 원소 빼주기

    /*
    for(int j=0; j<(int)u.size(); j++){
        cout<<"In u ";
        cout<<u[j][5]<<endl;
    }
    */

    for(int i=0; i<(int)u.size()-1; i++){
        cout<<"next i"<<endl;
        for(int j=i+1; j<(int)u.size(); j++){
            cout<<"next j"<<endl;
            if(u[i][6]==u[j][6]){
                do{
                cout <<u[j][5] << endl;
                u.erase(u.begin()+j);
                cout<<"same elements ok 3"<<endl;
                //countub++
                if(i+1==(int)u.size()){
                    break;
                }
                }while(u[i][6]==u[j][6] && j<(int)u.size());
            }     
        }
    }

    countub = 0;
    for(int i=m+1; i<(int)v.size(); i++){
        if((v[m][0]<=v[i][0] && v[i][0]<v[m][0]+v[m][2]) || (v[m][0]<v[i][0]+v[i][2] && v[i][0]+v[i][2]<=v[m][0]+v[m][2]) || (v[m][0]>v[i][0] && v[m][0]+v[m][2]<v[i][0]+v[i][2])){
            if((v[m][1]<=v[i][1] && v[i][1]<v[m][1]+v[m][3]) || (v[m][1]<v[i][1]+v[i][3] && v[i][1]+v[i][3]<=v[m][1]+v[m][3]) || (v[m][1]>v[i][1] && v[m][1]+v[m][3]<v[i][1]+v[i][3])){                
                ub.push_back({v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5],i});
                countub++;
            }
        }
        cout<<"In findunder, above page gyupchim ok 4"<<endl;
    }

    for(int i=0; i<(int)ub.size(); i++){
        for(int j=0; j<(int)u.size(); j++){
            if(ub[i][6]==u[j][6]){
                u.erase(u.begin()+j);
            }
        }
        cout<<"find key above=all above and erase ok 5"<<endl;
    } //error possible low

    for(int i=0; i<(int)ubb.size(); i++){
        for(int j=0; j<(int)u.size(); j++){
            if(ubb[i][6]==u[j][6]){
                u.erase(u.begin()+j);
            }
        }
        cout<<"find key above=all above and erase ok 5.1"<<endl;
    } //error possible low

    //sorting하기
    for(int i=0; i<(int)u.size(); i++){
        for (int j=0; j<(int)u.size()-i-1; j++){
            if(u[j][6]>u[j+1][6]){
                for(int k=0; k<7; k++){
                imsi[k] = u[j+1][k];
                u[j+1][k] = u[j][k];
                u[j][k] = imsi[k];
                }
            }
        cout<< "In findunder, sorting ok 6" << endl;   
        }
    }

    //출력하기
    for (int i=0; i<(int)u.size(); i++){
        for (int h = u[i][1]; h < u[i][1]+u[i][3]; h++) {
            for (int w = u[i][0]; w < u[i][0]+u[i][2]; w++) {
                board[h*width + w] = u[i][5];
            }
        }
            cout<<"under building 7"<<endl;
    }

    u.clear();
    ub.clear();

        /*
        for (int i=0; i<m; i++){
            for (int h = v[i][1]; h < v[i][1]+v[i][3]; h++) {
                for (int w = v[i][0]; w < v[i][0]+v[i][2]; w++) {
                board[h*width + w] = v[i][5];
                }
            }
            cout<<"under building"<<endl;
        }
        */

       /*
       for (int i=(int)u.size()-1; i>=(int)u.size()-countu; i--){
            for (int h = u[i][1]; h < u[i][1]+u[i][3]; h++) {
                for (int w = u[i][0]; w < u[i][0]+u[i][2]; w++) {
                //page.setpage(u[i][0],u[i][1],u[i][2],u[i][3],u[i][4],u[i][5]);
                //board[h*width + w] = page.getcontent(); //버그가능성
                board[h*width + w] = u[i][5];
                }
            }
            cout<<"under building"<<endl;
        }
        */

    cout<<"under is end"<<endl;
    return key;
}

int Board::deleting(int id){
    
    findabovepage(id); 
    w.clear();
    ubb.clear();
    //cout << "print above deleted id"<<endl;
    return id;        
    
    
}

void Board::rebuilding(){
    for(int i=(int)rebuildingid.size()-2; i>=(int)rebuildingid.size()-building; i--){   
        for (int h = rebuildingid[i][1]; h < rebuildingid[i][1]+rebuildingid[i][3]; h++) {
            for (int w = rebuildingid[i][0]; w < rebuildingid[i][0]+rebuildingid[i][2]; w++) {
                board[h*width + w] = rebuildingid[i][5];
            }
        }
        print_board();
        cout<< "print rebuilding page" << endl;
    }

    rebuildingid.clear();
    building = 0;
    //벡터초기화 필요 // ok
}
