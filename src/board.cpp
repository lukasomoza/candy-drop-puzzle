#include "board.h"
#include "candy.h"
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

Board::Board(int width, int height)
{
    m_width = width;
    m_height = height;
    m_tablero = new Candy * *[m_height];
    for (int i = 0; i < m_height; i++)
    {
        m_tablero[i] = new Candy * [m_width];
        for (int j = 0; j < m_width; j++)
            m_tablero[i][j] = nullptr;
    }

}


Board::~Board()
{
    if (m_tablero)
    {
        for (int i = 0; i < m_height; i++)
        {
            delete[] m_tablero[i];
        }
        delete[] m_tablero;
        m_tablero = nullptr;
    }
}


Board& Board::operator=(const Board& other)
{
    if (this != &other)
    {
        if (m_tablero)
        {
            for (int i = 0; i < m_height; i++)
            {
                delete[] m_tablero[i];
            }
            delete[] m_tablero;
            m_tablero = nullptr;
        }

        m_width = other.m_width;
        m_height = other.m_height;

        m_tablero = new Candy * *[m_height];
        for (int i = 0; i < m_height; ++i)
        {
            m_tablero[i] = new Candy * [m_width];
            for (int j = 0; j < m_width; j++)
            {
                if (other.m_tablero[i][j] != nullptr)
                    m_tablero[i][j] = new Candy(other.m_tablero[i][j]->getType());
                else
                    m_tablero[i][j] = nullptr;
            }
        }
    }
    return *this;
}

bool Board::operator==(const Board& b) const
{
    bool iguals = true;
    int i = 0;

    if (m_width != b.m_width || m_height != b.m_height)
        return false;


    while (i < m_width && iguals)
    {
        int j = 0;
        while (j < m_height && iguals)
        {
            Candy* c1 = m_tablero[i][j];
            Candy* c2 = b.m_tablero[i][j];

            if ((c1 == nullptr && c2 != nullptr) || (c2 == nullptr && c1 != nullptr))
            {
                iguals = false;
            }
            else if (c1 != nullptr && c2 != nullptr)
            {
                if (c1->getType() != c2->getType())
                    iguals = false;
            }
            j++;
        }
        i++;
    }
    return iguals;
}

Candy* Board::getCell(int fila, int columna) const
{
    if (fila < 0 || fila >= m_height || columna < 0 || columna >= m_width)
    {
        return nullptr;
    }

    return m_tablero[fila][columna];
}

void Board::setCell(Candy* candy, int fila, int columna)
{

    if (fila >= 0 && fila < m_height && columna >= 0 && columna < m_width)
    {

        m_tablero[fila][columna] = candy;
    }
}

int Board::getWidth() const
{
    return m_width;
}

int Board::getHeight() const
{
    return m_height;
}

bool Board::comprobarBordes(int x, int y) const
{
    if (y >= 0 && y < m_height && x >= 0 && x < m_width)
        return true;
    return false;
}

bool Board::comprobarDiagonal(const CandyType& tipus, int x, int y) const
{
    //2 POR DIAGONAL \*
    bool porArribaIzq = false;
    if (comprobarBordes(x - 2, y - 2) && m_tablero[x - 1][y - 1] != nullptr && m_tablero[x - 2][y - 2] != nullptr)
    {
        if (m_tablero[x - 2][y - 2]->getType() == tipus && m_tablero[x - 1][y - 1]->getType() == tipus)
            porArribaIzq = true;
    }

    bool porAbajoDer = false;
    if (comprobarBordes(x + 2, y + 2) && m_tablero[x + 1][y + 1] != nullptr && m_tablero[x + 2][y + 2] != nullptr)
    {
        if (m_tablero[x + 2][y + 2]->getType() == tipus && m_tablero[x + 1][y + 1]->getType() == tipus)
            porAbajoDer = true;
    }

    //2 por DIAGONAL /*
    bool porArribaDer = false;
    if (comprobarBordes(x + 2, y - 2) && m_tablero[x + 1][y - 1] != nullptr && m_tablero[x + 2][y - 2] != nullptr)
    {
        if (m_tablero[x + 2][y - 2]->getType() == tipus && m_tablero[x + 1][y - 1]->getType() == tipus)
            porArribaDer = true;
    }

    bool porAbajoIzq = false;
    if (comprobarBordes(x - 2, y + 2) && m_tablero[x - 1][y + 1] != nullptr && m_tablero[x - 2][y + 2] != nullptr)
    {
        if (m_tablero[x - 2][y + 2]->getType() == tipus && m_tablero[x - 1][y + 1]->getType() == tipus)
            porAbajoIzq = true;
    }

    //DIAGONAL \ 1 por Arriba y 1 por abajo*
    bool medioIzq = false;
    if (comprobarBordes(x - 1, y - 1) && comprobarBordes(x + 1, y + 1) && m_tablero[x - 1][y - 1] != nullptr && m_tablero[x + 1][y + 1] != nullptr)
    {
        if (m_tablero[x + 1][y + 1]->getType() == tipus && m_tablero[x - 1][y - 1]->getType() == tipus)
            medioIzq = true;
    }

    //DIAGONAL / 1 por Arriba y 1 por abajo*
    bool medioDer = false;
    if (comprobarBordes(x - 1, y + 1) && comprobarBordes(x + 1, y - 1) && m_tablero[x - 1][y + 1] != nullptr && m_tablero[x + 1][y - 1] != nullptr)
    {
        if (m_tablero[x + 1][y - 1]->getType() == tipus && m_tablero[x - 1][y + 1]->getType() == tipus)
            medioDer = true;
    }
    return porArribaIzq || porAbajoDer || porArribaDer || porAbajoIzq || medioDer || medioIzq;
}

bool Board::comprobarHorizontal(const CandyType& tipus, int x, int y) const
{
    // 2 por IZQUIERDA
    bool porIzquierda = false;
    if (comprobarBordes(x - 2, y) && m_tablero[x - 1][y] != nullptr && m_tablero[x - 2][y] != nullptr)
    {
        if (m_tablero[x - 1][y]->getType() == tipus && m_tablero[x - 2][y]->getType() == tipus)
            porIzquierda = true;
    }


    //2 por DERECHA
    bool porDerecha = false;
    if (comprobarBordes(x + 2, y) && m_tablero[x + 1][y] != nullptr && m_tablero[x + 2][y] != nullptr)
    {
        if (m_tablero[x + 1][y]->getType() == tipus && m_tablero[x + 2][y]->getType() == tipus)
            porDerecha = true;
    }


    //1 por IZQUIERDA y 1 por DERECHA
    bool porMedio = false;
    if (comprobarBordes(x + 1, y) && comprobarBordes(x - 1, y) && m_tablero[x - 1][y] != nullptr && m_tablero[x + 1][y] != nullptr)
    {
        if (m_tablero[x + 1][y]->getType() == tipus && m_tablero[x - 1][y]->getType() == tipus)
            porMedio = true;
    }

    return porIzquierda || porDerecha || porMedio;
}

bool Board::comprobarVertical(const CandyType& tipus, int x, int y) const
{
    // 2 por ARRIBA
    bool porArriba = false;
    if (comprobarBordes(x, y - 2) && m_tablero[x][y - 1] != nullptr && m_tablero[x][y - 2] != nullptr)
    {
        if (m_tablero[x][y - 1]->getType() == tipus && m_tablero[x][y - 2]->getType() == tipus)
            porArriba = true;
    }


    //2 por ABAJO
    bool porAbajo = false;
    if (comprobarBordes(x, y + 2) && m_tablero[x][y + 1] != nullptr && m_tablero[x][y + 2] != nullptr)
    {
        if (m_tablero[x][y + 1]->getType() == tipus && m_tablero[x][y + 2]->getType() == tipus)
            porAbajo = true;
    }


    //1 por ARRIBA y 1 por ABAJO
    bool porMedio = false;
    if (comprobarBordes(x, y - 1) && comprobarBordes(x, y + 1) && m_tablero[x][y + 1] != nullptr && m_tablero[x][y - 1] != nullptr)
    {
        if (m_tablero[x][y + 1]->getType() == tipus && m_tablero[x][y - 1]->getType() == tipus)
            porMedio = true;
    }

    return porArriba || porAbajo || porMedio;
}

bool Board::shouldExplode(int x, int y) const
{
    CandyType tipus;
    if (comprobarBordes(x, y) && m_tablero[x][y] != nullptr)
        tipus = m_tablero[x][y]->getType();
    else
        return false;

    bool hor = comprobarHorizontal(tipus, x, y);
    if (hor == false)
    {
        bool vert = comprobarVertical(tipus, x, y);
        if (vert == false)
        {
            bool diag = comprobarDiagonal(tipus, x, y);
            if (diag != false)
                return true;
        }
        else
            return true;
    }
    else
        return true;

    return false;

}

vector<Candy*> Board::explodeAndDrop()
{
    vector<Candy*> carmelsExplotats;
    bool hiHaExplosio = true;

    while (hiHaExplosio)
    {
        hiHaExplosio = false;

        bool** carmelsPerExplotar = new bool* [m_width];

        for (int i = 0; i < m_width; i++)
        {
            carmelsPerExplotar[i] = new bool[m_height];
            for (int j = 0; j < m_height; j++)
            {
                carmelsPerExplotar[i][j] = false;
            }
        }

        for (int x = 0; x < m_width; x++)
        {
            for (int y = 0; y < m_height; y++)
            {
                if (m_tablero[x][y] != nullptr && shouldExplode(x, y))
                {
                    carmelsPerExplotar[x][y] = true;
                    hiHaExplosio = true;
                }
            }
        }

        if (hiHaExplosio)
        {
            for (int x = 0; x < m_width; x++)
            {
                for (int y = 0; y < m_height; y++)
                {
                    if (carmelsPerExplotar[x][y])
                    {
                        carmelsExplotats.push_back(m_tablero[x][y]);
                        m_tablero[x][y] = nullptr;
                    }
                }
            }

            for (int x = 0; x < m_width; x++)
            {
                for (int y = m_height - 1; y >= 0; y--)
                {
                    if (m_tablero[x][y] == nullptr)
                    {
                        for (int k = y - 1; k >= 0; k--)
                        {
                            if (m_tablero[x][k] != nullptr)
                            {
                                m_tablero[x][y] = m_tablero[x][k];
                                m_tablero[x][k] = nullptr;
                                break;
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < m_width; i++)
        {
            delete[] carmelsPerExplotar[i];
        }
        delete[] carmelsPerExplotar;
    }

    return carmelsExplotats;
}

bool Board::dump(const string& output_path) const
{
    ofstream fitxer(output_path);

    if (!fitxer.is_open())
        return false;

    fitxer << m_width << " " << m_height << endl;

    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            if (m_tablero[i][j] == nullptr)
                fitxer << "-1 ";
            else
                fitxer << (int)m_tablero[i][j]->getType() << " ";
        }
        fitxer << endl;
    }
    return true;
}

bool Board::load(const string& input_path)
{
    ifstream fitxer(input_path);

    if (!fitxer.is_open())
        return false;

    int w, h;

    if (!(fitxer >> w >> h))
        return false;

    m_width = w;
    m_height = h;
    m_tablero = new Candy * *[m_height];

    for (int i = 0; i < m_height; i++)
    {
        m_tablero[i] = new Candy * [m_width];

        for (int j = 0; j < m_width; j++)
        {
            int cnd;
            if (fitxer >> cnd && cnd != -1)
                m_tablero[i][j] = new Candy((CandyType)cnd);
            else
                m_tablero[i][j] = nullptr;
        }
    }
    return true;
}