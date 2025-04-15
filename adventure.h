#include <iostream>

std::string world[] = {
    "S.........",
    "XXX.XXXXX.",
    "..........",
    "XXXXXXXXX.",
    "X......X..",
    "XX.XXX...X",
    "...X.XXXXX",
    "...X.....E",
    "...X..X...",
    "......X..."
};

using Door = char;

class Room {
public:
    Door getFirstDoor();
    bool isValidDoor(Door d) { return d>='A' && d<='Z'; }
    Door getNextDoor(Door d);

    Room getNextRoom(Door d);
    bool isExit() { return world[row][col]=='E'; }

    Room(int r,int c) : row(r),col(c) {}
    int row,col;
};

Door Room::getFirstDoor() 
{
    if (row>0 && world[row-1][col]!='X') return 'N';
    if (row<9 && world[row+1][col]!='X') return 'S';
    if (col>0 && world[row][col-1]!='X') return 'W';
    if (col<9 && world[row][col+1]!='X') return 'E';
    return '-';
}

Door Room::getNextDoor(Door d) 
{
    if ( d=='N'                      && row<9 && world[row+1][col]!='X') return 'S';
    if ((d=='N' || d=='S')           && col>0 && world[row][col-1]!='X') return 'W';
    if ((d=='N' || d=='S' || d=='W') && col<9 && world[row][col+1]!='X') return 'E';
    return '-';
}

Room Room::getNextRoom(Door d)
{
    if (d=='N') return Room(row-1,col);
    if (d=='S') return Room(row+1,col);
    if (d=='W') return Room(row,col-1);
    return Room(row,col+1);
}

class Path {
public:
    bool add(Door d);

    friend std::ostream & operator<<(std::ostream &out,const Path &p) { out << p.path; return out; }

    std::string path;
};

bool Path::add(Door d) 
{
    int rooms[100];
    int count =0;
    Room r(0,0);
    rooms[count++] = r.row*10+r.col;
    for (auto c : path) {
        r = r.getNextRoom((Door)c);
        rooms[count++] = r.row*10+r.col;
    }
    r = r.getNextRoom(d);
    for (int i=0; i<count; i++)
        if (rooms[i]==r.row*10+r.col) 
            return false;
    path += d; 
    return true;
}

class Adventure {
public: 
    Path getStart() { return Path(); }
    Room getRoom(Path &p);
};

Room Adventure::getRoom(Path &p)
{
    Room r(0,0);
    for (auto c : p.path)
        r = r.getNextRoom((Door)c);
    return r;
}
