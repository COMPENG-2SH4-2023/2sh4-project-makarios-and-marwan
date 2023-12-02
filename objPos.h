#ifndef OBJPOS_H
#define OBJPOS_H

class objPos
{
    public:
        objPos();
        objPos(objPos &o); // copy constructor
        objPos(int xPos, int yPos, char sym);

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  
        void getObjPos(objPos &returnPos);
        char getSymbol();

        bool isPosEqual(const objPos* refPos);
        
        char getSymbolIfPosEqual(const objPos* refPos);

        int getX();
        int getY();

        int setX(int input);
        int setY(int input);

    private:
        int x;
        int y;
        char symbol;
};

#endif