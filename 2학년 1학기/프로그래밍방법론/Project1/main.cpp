#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int imsi[6];

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
    /*
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
    */

    //input3
    
    Board board(30, 103, 90, fout);
    board.insert_page(52, 12, 15, 54, 19221, 'g');
    board.delete_page(19221);
    board.insert_page(83, 49, 4, 2, 19861, 'a'); 
    board.modify_position(19861, 26, 58);
    board.modify_position(19861, 53, 27);
    board.insert_page(5, 17, 93, 61, 13394, 'w'); 
    board.delete_page(13394);
    board.modify_position(19861, 2, 55);
    board.insert_page(84, 6, 5, 82, 8558, 'u');
    board.modify_position(8558, 34, 2);
    board.delete_page(8558);
    board.delete_page(19861);
    board.insert_page(2, 70, 94, 19, 21491, 'x');
    board.modify_position(21491, 3, 46);
    board.insert_page(24, 64, 27, 20, 6905, 'u');
    board.modify_position(21491, 0, 71);
    board.insert_page(23, 1, 57, 77, 26431, 'b');
    board.insert_page(83, 19, 4, 47, 18874, 'w');
    board.modify_content(26431, 'w');
    board.insert_page(3, 24, 83, 27, 11430, 'j'); 
    board.delete_page(26431);
    board.insert_page(36, 25, 5, 62, 30233, 'a');
    board.modify_position(18874, 97, 15);
    board.insert_page(11, 23, 43, 21, 13481, 'g'); 
    board.modify_content(21491, 'f');
    board.modify_position(21491, 6, 16);
    board.insert_page(19, 39, 73, 37, 27415, 'f'); 
    board.modify_position(21491, 7, 20);
    board.modify_position(11430, 12, 62);
    board.modify_position(13481, 36, 6);

    fout.close();

    return 0;
    
}