class Page {
    public:
        //Page(int x, int y, int width, int height, int id, int content):x(x),y(y),width(width),height(height),id(id),content(content){}
        Page(){x=0;y=0;width=0,height=0;id=0;content=0;}
        void setpage(int newx, int newy, int newwidth, int newheight, int newid, int newcontent)
        {x=newx; y=newy; width=newwidth; height=newheight; id=newid; content=newcontent;};
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
        
    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content;
};