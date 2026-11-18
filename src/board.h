#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <unordered_map>
#include <vector>
#include "candy.h"
#include <fstream>
using namespace std;

const int DEFAULT_BOARD_WIDTH = 10;
const int DEFAULT_BOARD_HEIGHT = 10;

const int SHORTEST_EXPLOSION_LINE = 3;

class Board
{
public:
    Board(int width = DEFAULT_BOARD_WIDTH, int height = DEFAULT_BOARD_HEIGHT);
    ~Board();

    bool operator==(const Board& b) const;
    Board& operator=(const Board& other);

    bool shouldExplode(int x, int y) const;
    vector<Candy*> explodeAndDrop();

    bool dump(const string& output_path) const;
    bool load(const string& input_path);

    Candy* getCell(int fila, int columna) const;
    void setCell(Candy* candy, int fila, int columna);

    int getWidth() const;
    int getHeight() const;

    bool comprobarBordes(int x, int y) const;
    bool comprobarDiagonal(const CandyType& tipus, int x, int y) const;
    bool comprobarHorizontal(const CandyType& tipus, int x, int y) const;
    bool comprobarVertical(const CandyType& tipus, int x, int y) const;

private:

    Candy*** m_tablero;
    int m_height;
    int m_width;
};

#endif
