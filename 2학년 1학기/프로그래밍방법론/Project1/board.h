
#include <fstream>

#include "page.h"

using std::endl;
using std::ofstream;

class Board {
    public:
        Board(int num_jobs, int width, int height, ofstream& output_stream);
        ~Board();

        void print_board();
        void print_job(int job_idx, char job_type, int id);

        //job functions
        void insert_page(int x, int y, int width, int height, int id, int content);
        void delete_page(int id);
        void modify_content(int id, char content);
        void modify_position(int id, int x, int y);
        int getwidth(){return width;}        
        int findabovepage(int id);
        int findunderpage(int id);
        int deleting(int id);
        void rebuilding();
        void takeid(int key);
        void erase(vector<vector<int>>,vector<vector<int>>);

    private:
        int num_jobs, width, height; 
        ofstream& output; 
        char* board;
        Page page;
};

Board::Board(int num_jobs, int width, int height, ofstream& output_stream): output(output_stream) {
    this->width = width;
    this->height = height;
    this->num_jobs = num_jobs;

    board = new char[width*height];

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h*width + w] = ' ';
        }
    }

}

Board::~Board() {
    delete board;
    
}


void Board::print_board() {
    int h, w;
    for (w = 0; w < width+2; w++) output << "- ";
    output << endl;
    
    for (h = 0; h < height; h++) {
        output << "| ";
        for (w = 0; w < width; w++) {
            output << board[h*width + w] << " ";
        }
        output << "| " << endl;
    }

    for (w = 0; w < width+2; w++) output << "- ";
    output << endl;
}

void Board::print_job(int job_idx, char job_type, int id) {
    output << ">> (" << job_idx <<") ";
    switch(job_type) {
        
        case 'i':
            output << "Insert ";
            break;
        case 'd':
            output << "Delete ";
            break;
        case 'm':
            output << "Modify ";
            break;
    }

    output << id << endl;
}

void Board::insert_page(int x, int y, int width, int height, int id, int content) {    
    if(width>0 && height>0){
        page.setpage(x,y,width,height,id,content); 
        v.push_back({page.getx(),page.gety(),page.getwidth(),page.getheight(),page.getid(),page.getcontent()});
    
        for (int h = page.gety(); h < page.gety()+page.getheight(); h++) {
            for (int w = page.getx(); w < page.getx()+page.getwidth(); w++) {
                board[h*getwidth() + w] = page.getcontent();
            }
        }
    }

    else{
        none.push_back({x,y,width,height,id,content});
    }

        print_board();
    
}

int building = 0;

void Board::delete_page(int id) {
    for(int i=0; i<(int)none.size();i++){
            if(none[i][4]==id){
                
                print_board();
                return;
            }
        }
    
    cout<<"-----delete_page-----"<<endl;
    deleting(id);
    cout<<"deleting(id) output is now in delete_page"<<endl;
        
        rebuilding();
        takeid(id);
        v.erase(v.begin()+m);
}

void Board::modify_content(int id, char content) {
    for(int i=0; i<(int)none.size();i++){
            if(none[i][4]==id){
                print_board();
                print_board();
                return;     
            }
        }

    cout<<"-----modify_content-----"<<endl;
    deleting(id);
    cout<<"deleting(id) output is now in modify_content"<<endl;
        takeid(id);

        for (int h = v[m][1]; h < v[m][1]+v[m][3]; h++) {
            for (int w = v[m][0]; w < v[m][0]+v[m][2]; w++) {
                board[h*width + w] = content;
            }
        }

        v[m][5] = content;

        print_board();
        cout<<"print modifyied page"<<endl;
        rebuilding();
}

void Board::modify_position(int id, int x, int y) {
    for(int i=0; i<(int)none.size();i++){
            if(none[i][4]==id){
                print_board();
                print_board();
                return;
            }
        }
    
    cout<<"-----modify_position-----"<<endl;
    deleting(id);
    cout<<"deleting(id) output is now in modify_position"<<endl;

        takeid(id);

        //v[m][0]=x;
        //v[m][1]=y;
        
        for (int h = y; h < y+v[m][3]; h++) {
            for (int w = x; w < x+v[m][2]; w++) {
                board[h*width + w] = v[m][5];
            }
        }

        
        for(int i=0; i<(int)rebuildingid.size(); i++){
            for(int j=0; j<(int)v.size(); j++){
                if(rebuildingid[i][4]==v[j][4]){
                    v.erase(v.begin()+j);
                }
            }
            cout<<"v-rebuilding"<<endl;
        } //error possible low
        

        //erase(v, rebuildingid);

        int m = (int)rebuildingid.size()-1;
        v.push_back({x, y, rebuildingid[m][2], rebuildingid[m][3], rebuildingid[m][4], rebuildingid[m][5]});

        for(int i=(int)rebuildingid.size()-2; i>=0; i--){
            v.push_back({rebuildingid[i][0], rebuildingid[i][1], rebuildingid[i][2], rebuildingid[i][3], rebuildingid[i][4], rebuildingid[i][5]});
        }

        print_board();
        cout<<"print modifyied page"<<endl;
        rebuilding();
}


void Board::takeid(int key){
    for(int i=0; i<(int)v.size(); i++){
        if(v[i][4]==key){
            m = i;
            break;
        }
    }
}

/*
void Board::erase(vector<vector<int>> a, vector<vector<int>> b){
    for(int i=0; i<(int)b.size(); i++){
        for(int j=0; j<(int)a.size(); j++){
            if(b[i][4]==a[j][4]){
                a.erase(a.begin()+j);
            }
        }
        cout<<"find key above=all above and erase ok 5"<<endl;
    } //error possible low
}
*/

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
    //building++;

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
    for(int i=(int)rebuildingid.size()-2; i>=0; i--){   
        for (int h = rebuildingid[i][1]; h < rebuildingid[i][1]+rebuildingid[i][3]; h++) {
            for (int w = rebuildingid[i][0]; w < rebuildingid[i][0]+rebuildingid[i][2]; w++) {
                board[h*width + w] = rebuildingid[i][5];
            }
        }
        print_board();
        cout<< "print rebuilding page" << endl;
    }

    rebuildingid.clear();
    //building = 0;
    //벡터초기화 필요 // ok
}


