class Page {
    public:
        //Page(int x, int y, int width, int height, int id, int content):x(x),y(y),width(width),height(height),id(id),content(content){}
        Page(){x=0;y=0;width=0,height=0;id=0;content=0;}
        void setpage(int newx, int newy, int newwidth, int newheight, int newid, int newcontent)
        {x=newx; y=newy; width=newwidth; height=newheight; id=newid; content=newcontent; count2++;};
        void store();
        void takeid(int key);
        void setid();
        //void findabovepage(int key);
        int getx(){return x;}
        int gety(){return y;}
        int getwidth(){return width;}
        int getheight(){return height;}
        int getid(){return id;}
        char getcontent(){return content;}
        static int getstatic(){return count2;}
        //static void onemore();
        
    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content;
        static int count2;
};

int Page::count2 = 0;
//int Page::getstatic(){return count;}
//void Page::onemore(){count++;}

/*int arr[6];
vector<int[6]> v;
int m;

void Page::store(){
    arr[0]=x;
    arr[1]=y;
    arr[2]=width;
    arr[3]=height;
    arr[4]=id;
    arr[5]=content;
    v.push_back(arr[6]);
}

void Page::takeid(int key){
    for(int i=0; i<v.size();i++){
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
*/