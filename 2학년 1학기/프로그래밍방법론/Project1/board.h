
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
        static int getabovestatic(){return abovecallstack;}
        static int getunderstatic(){return undercallstack;}
        static void abovestaticplus(){abovecallstack++;}
        static void understaticplus(){undercallstack++;}
        int findabovepage(int id);
        int findunderpage(int id);
        int findunderpage2(int id);
        int deleting(int id);
        void rebuilding();

    private:
        int num_jobs, width, height; 
        ofstream& output; 
        char* board;
        //static int count;
        Page page;
        static int abovecallstack;
        static int undercallstack;
};

int Board::abovecallstack = 0;
int Board::undercallstack = 0;


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
    
    page.setpage(x,y,width,height,id,content); 
    v.push_back({page.getx(),page.gety(),page.getwidth(),page.getheight(),page.getid(),page.getcontent()});
    
    for (int h = page.gety(); h < page.gety()+page.getheight(); h++) {
        for (int w = page.getx(); w < page.getx()+page.getwidth(); w++) {
            board[h*getwidth() + w] = page.getcontent();
        }
    }

    print_board();

}

int building = 0;

void Board::delete_page(int id) {
    cout<<"-----delete_page-----"<<endl;
    deleting(id);
    cout<<"deleting(id) output is now in delete_page"<<endl;
        
        rebuilding();
    
        building = 0;

        for(int i=0; i<(int)v.size();i++){
            if(v[i][4]==id){
                m = i;
                break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
            }
        }

        v.erase(v.begin()+m);
    
    
}

void Board::modify_content(int id, char content) {
    cout<<"-----modify_content-----"<<endl;
    deleting(id);
    cout<<"deleting(id) output is now in modify_content"<<endl;
        for(int i=0; i<(int)v.size();i++){
            if(v[i][4]==id){
                m = i;
                break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
            }
        }

        for (int h = v[m][1]; h < v[m][1]+v[m][3]; h++) {
            for (int w = v[m][0]; w < v[m][0]+v[m][2]; w++) {
                board[h*width + w] = content;
            }
        }

        v[m][5] = content;

        print_board();
        cout<<"print modifyied page"<<endl;

        rebuilding();
        building = 0;

}

void Board::modify_position(int id, int x, int y) {
    cout<<"-----modify_position-----"<<endl;
    if(id==deleting(id)){
        cout<<"deleting(id) output is now in modify_position"<<endl;
        for(int i=0; i<(int)v.size();i++){
            if(v[i][4]==id){
                m = i;
                break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
            }
        }

        for (int h = y; h < y+v[m][3]; h++) {
            for (int w = x; w < x+v[m][2]; w++) {
                board[h*width + w] = v[m][5];
            }
        }

        v.push_back({x, y, v[m][2], v[m][3], v[m][4], v[m][5]});
        v.erase(v.begin()+m);

        print_board();
        cout<<"print modifyied page"<<endl;

        rebuilding();
        building = 0;
    }
}


