
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
        //static int getstatic(){return count;};
        //static void onemore(){count++;};
        void findunderpage(int id);
        void deleting(int id);
        void rebuilding();

    private:
        int num_jobs, width, height; 
        ofstream& output; 
        char* board;
        //static int count;
        Page page;
};

//int Board::count = 0;


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
    page.store();
    
    for (int h = page.gety(); h < page.gety()+height; h++) {
        for (int w = page.getx(); w < page.getx()+width; w++) {
            board[h*width + w] = page.getcontent();
        }
    }

    print_board();

}

int building = 0;

void Board::delete_page(int id) {
    deleting(id);
    //building

    //지금 작성중인 findunderpage에 대해서 필요없는 코드
    /*for(int i=0; i<v.size();i++){
        if(v[i][4]==id){
            m = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
        }
    }

    for (int h = v[m][1]; h < v[m][1]+v[m][3]; h++) {
        for (int w = v[m][0]; w < v[m][0]+v[m][2]; w++) {
            board[h*width + w] = ' ';
        }
    }*/

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
    deleting(id);

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

    v[m][5]=content;

    rebuilding();
    building = 0;

}

void Board::modify_position(int id, int x, int y) {
    deleting(id);
    
    for(int i=0; i<(int)v.size();i++){
        if(v[i][4]==id){
            m = i;
            break;
            //setpage(v[i][0],v[i][1],v[i][2],v[i][3],v[i][4],v[i][5]);
        }
    }

    for (int h = v[m][1]; h < v[m][1]+v[m][3]; h++) {
        for (int w = v[m][0]; w < v[m][0]+v[m][2]; w++) {
            board[h*width + w] = v[m][5];
        }
    }

    v[m][0]=x;
    v[m][1]=y;

    rebuilding();
    building = 0;
}


