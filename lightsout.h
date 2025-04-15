class LightsOut{
    bool grid[25];
public:
    LightsOut();
    void on (int row, int col);
    bool get (int row,int col);
    void toggle (int row,int col);
    bool success();
};