#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//int imsi[6] = {0,0,0,0,0,0};
//int arr[6] = {0,0,0,0,0,0};
int imsi[6];
int arr[6];
//vector<int> v[6];
vector<vector<int>> v; 
int m;

vector<vector<int>> w;
int countw = 0;

vector<vector<int>> rebuildingid;
int callstack = 0;
 
vector<vector<int>> u;
int countu = 0;

vector<int> counting;
//int count2 = 0;

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
    //Page page = Page(0,0,0,0,0,0);


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


int main(int argc, char *argv[]) {

    //Page page;
    if (argc==3) manage_board(string(argv[1]), string(argv[2]));
    else cerr << "Wrong arguments" << endl;
    

    return 0; 

}

/*int arr[6];
vector<int[5]> v;
int m;*/

void Page::store(){
    arr[0]=x;
    arr[1]=y;
    arr[2]=width;
    arr[3]=height;
    arr[4]=id;
    arr[5]=content;
    v.push_back({arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]});
}

void Page::takeid(int key){
    for(int i=0; i<(int)v.size(); i++){
        if(v[i][4]==key){
            m = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
        }
    }
}

void Page::setid(){
    setpage(v[m][0],v[m][1],v[m][2],v[m][3],v[m][4],v[m][5]);
}

/*vector<int[6]> w;
int countw = 0;

vector<int[6]> rebuildingid;
int callstack = 0;*/

int findabovepage(int key){
    for(int i=0; i<(int)v.size();i++){
        if(v[i][4]==key){
            m = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
        }
    }

    for(int i=m+1; i<(int)v.size(); i++){
        if((v[m][0]<=v[i][0] && v[i][0]<v[m][0]+v[m][2]) || (v[m][0]<v[i][0]+v[i][2] && v[i][0]+v[i][2]<=v[m][0]+v[m][2]) || (v[m][0]>v[i][0] && v[m][0]+v[m][2]<v[i][0]+v[i][2])){
            if((v[m][1]<=v[i][1] && v[i][1]<v[m][1]+v[m][3]) || (v[m][1]<v[i][1]+v[i][3] && v[i][1]+v[i][3]<=v[m][1]+v[m][3]) || (v[m][1]>v[i][1] && v[m][1]+v[m][3]<v[i][1]+v[i][3])){
                //findabovepage(v[i][4]);
                w.push_back({v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]});
                countw++;
            }
        }
    }

    //aboveid.push_back(w[w.size()-countw]);
    //certified.
    for(int m=(int)w.size()-countw+1; m<(int)w.size(); m++){        
        for(int j=(int)w.size()-countw; j<m; j++){
            if((w[m][0]<=w[j][0] && w[j][0]<w[m][0]+w[m][2]) || (w[m][0]<w[j][0]+w[j][2] && w[j][0]+w[j][2]<=w[m][0]+w[m][2]) || (w[m][0]>w[j][0] && w[m][0]+w[m][2]<w[j][0]+w[j][2])){
                if((w[m][1]<=w[j][1] && w[j][1]<w[m][1]+w[m][3]) || (w[m][1]<w[j][1]+w[j][3] && w[j][1]+w[j][3]<=w[m][1]+w[m][3]) || (w[m][1]>w[j][1] && w[m][1]+w[m][3]<w[j][1]+w[j][3])){
                    
                    //findabovepage(v[i][4]);
                    //aboveid.push_back(w[j][4]);
                    //count1++;
                    w.erase(w.begin()+m);
                    countw--;
                }
            }
        }
    }

    //problem1
    for(int i=0; i<(int)w.size()-countw; i++){
        for(int j=(int)w.size()-countw; j<(int)w.size(); j++){
            if(w[j][4] == w[i][4]){
                w.erase(w.begin()+j);
                countw--;
            }
        }
    }

    for(int i=0; i<countw; i++){
        for (int j=(int)w.size()-countw; j<(int)w.size()-i-1; j++){
            if(w[j][4]>w[j+1][4]){
                //w.swap(j, (j+1));
                //int imsi[6] = w[j+1];
                //w[j+1] = w[j];
                for(int k=0; k<6; k++){
                imsi[k] = w[j+1][k];
                w[j+1][k] = w[j][k];
                w[j][k] = imsi[k];
                }
            }
        }
    }

    //countw = 0;
    //int l = 0;

    for(int i=(int)w.size()-countw; i<(int)w.size(); i++){
        countw = 0;
        //l = w[i];
        findabovepage(w[i][4]);
    }
    countw = 0;


    for(int i=0; i<(int)v.size();i++){
        if(v[i][4]==key){
            m = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
        }
    }

    rebuildingid.push_back({v[m][0],v[m][1],v[m][2],v[m][3],v[m][4],v[m][5]});
    building++;
    callstack++;

    return key;

    

    /*for(int i=0; i<v.size();i++){
        if(v[i][4]==key){
            m = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
        }
    }*/

    /*for (int h = v[m][1]; h < v[m][1]+v[m][3]; h++) {
        for (int w = v[m][0]; w < v[m][0]+v[m][2]; w++) {
            board[h*width + w] = ' ';
        }
    }*/
 
}

/*vector<int[6]> u;
int countu = 0;

vector<int> counting;
//int count2 = 0;*/

void Board::findunderpage(int key){
    for(int i=0; i<(int)v.size();i++){
        if(v[i][4]==key){
            m = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
        }
    }

    for(int i=m-1; i>=0; i--){
        if((v[m][0]<=v[i][0] && v[i][0]<v[m][0]+v[m][2]) || (v[m][0]<v[i][0]+v[i][2] && v[i][0]+v[i][2]<=v[m][0]+v[m][2]) || (v[m][0]>v[i][0] && v[m][0]+v[m][2]<v[i][0]+v[i][2])){
            if((v[m][1]<=v[i][1] && v[i][1]<v[m][1]+v[m][3]) || (v[m][1]<v[i][1]+v[i][3] && v[i][1]+v[i][3]<=v[m][1]+v[m][3]) || (v[m][1]>v[i][1] && v[m][1]+v[m][3]<v[i][1]+v[i][3])){                
                u.push_back({v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]});
                countu++;
            }
        }
    }

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

    for(int i=0; i<(int)u.size()-countu; i++){
        for(int j=(int)u.size()-countu; j<(int)u.size(); j++){
            if(u[j][4] == u[i][4]){
                u.erase(u.begin()+j);
                countu--;
            }
        }
    }

    //counting.push_back(countu);

    int l=0;

    for(int i=(int)u.size()-countu; i<(int)u.size(); i++){
        /*if(l==0){
            counting.push_back(0);
        }*/       
        countu = 0;
        /*if(l==0){
            count = 0;
        }*/    
        findunderpage(u[i][4]);
        l = 1;
        //count++; //problem3
        //counting[]++;
    }
    countu = 0;

    //int n;
    //underpage building
    /*if(l==1){
        for(int i=0; i<u.size();i++){
        if(u[i][4]==v[m][4]){
            n = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
            }
        }

        for (int i=n-count; i<n; i++){
            for (int h = u[i][1]; h < u[i][1]+u[i][3]; h++) {
                for (int w = u[i][0]; w < u[i][0]+u[i][2]; w++) {
                //page.setpage(u[i][0],u[i][1],u[i][2],u[i][3],u[i][4],u[i][5]);
                //board[h*width + w] = page.getcontent(); //버그가능성
                board[h*width + w] = u[i][5];
                }
            }
        }

        count = 0;
    }*/
    if(l==1){
        for(int i=0; i<(int)v.size();i++){
            if(v[i][4]==key){
                m = i;
                break;
                //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
            }
        }

        for(int i=m-1; i>=0; i--){
            if((v[m][0]<=v[i][0] && v[i][0]<v[m][0]+v[m][2]) || (v[m][0]<v[i][0]+v[i][2] && v[i][0]+v[i][2]<=v[m][0]+v[m][2]) || (v[m][0]>v[i][0] && v[m][0]+v[m][2]<v[i][0]+v[i][2])){
                if((v[m][1]<=v[i][1] && v[i][1]<v[m][1]+v[m][3]) || (v[m][1]<v[i][1]+v[i][3] && v[i][1]+v[i][3]<=v[m][1]+v[m][3]) || (v[m][1]>v[i][1] && v[m][1]+v[m][3]<v[i][1]+v[i][3])){                
                    u.push_back({v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]});
                    countu++;
                }
            }
        }

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

        for(int i=0; i<(int)u.size()-countu; i++){
            for(int j=(int)u.size()-countu; j<(int)u.size(); j++){
                if(u[j][4] == u[i][4]){
                    u.erase(u.begin()+j);
                    countu--;
                }
            }
        }

        for (int i=(int)u.size()-countu; i<(int)u.size(); i++){
            for (int h = u[i][1]; h < u[i][1]+u[i][3]; h++) {
                for (int w = u[i][0]; w < u[i][0]+u[i][2]; w++) {
                //page.setpage(u[i][0],u[i][1],u[i][2],u[i][3],u[i][4],u[i][5]);
                //board[h*width + w] = page.getcontent(); //버그가능성
                board[h*width + w] = u[i][5];
                }
            }
        }

    }

    countu = 0;    

    //return key;

    //underpage building
    /*for (int i=u.size()-countu; i<u.size(); i++){
        for (int h = u[i][1]; h < u[i][1]+u[i][3]; h++) {
            for (int w = u[i][0]; w < u[i][0]+u[i][2]; w++) {
                board[h*width + w] = 'u[i][5]';
            }
        }
    }*/

    //currentpage buliding
    /*for (int h = v[m][1]; h < v[m][1]+u[m][3]; h++) {
        for (int w = v[m][0]; w < v[m][0]+v[m][2]; w++) {
            board[h*width + w] = 'v[m][5]';
        }
    }*/


    

}

void Board::deleting(int id){
    do{
    int abovepageid = findabovepage(id);

    //delete code
    for(int i=0; i<(int)v.size();i++){
        if(v[i][4]==abovepageid){
            m = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
        }
    }

    for (int h = v[m][1]; h < v[m][1]+v[m][3]; h++) {
        for (int w = v[m][0]; w < v[m][0]+v[m][2]; w++) {
            board[h*width + w] = ' ';
        }
    }

    findunderpage(abovepageid);
    print_board();
    callstack--;
    }while(callstack>0);
}

/*void sortingandrecursion(){
    for(int i=aboveid.size()-count1; i<aboveid.size(); i++){
        for (int j=aboveid.size()-count1; j<aboveid.size()-i-1; j++){
            if(aboveid[j]>aboveid[j+1]){
                int imsi = aboveid[j+1];
                aboveid[j+1] = aboveid[j];
                aboveid[j] = imsi;
            }
        }
    }

    for(int i=aboveid.size()-count1; i<aboveid.size(); i++){
        findabovepage(aboveid[i]);
    }

    count1 = 0;
}*/

void Board::rebuilding(){
    for(int i=(int)rebuildingid.size()-2; i>=(int)rebuildingid.size()-building; i--){   
        for (int h = rebuildingid[i][1]; h < rebuildingid[i][1]+rebuildingid[i][3]; h++) {
            for (int w = rebuildingid[i][0]; w < rebuildingid[i][0]+rebuildingid[i][2]; w++) {
                //page.setpage(rebuildingid[i][0],rebuildingid[i][1],rebuildingid[i][2],rebuildingid[i][3],rebuildingid[i][4],rebuildingid[i][5]);
                //board[h*width + w] = page.getcontent();
                board[h*width + w] = rebuildingid[i][5];
            }
            print_board();
        }
    }
    
    //벡터초기화 필요 // ok
}