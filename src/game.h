#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "controller.h"
#include <board.h>
#include "candy.h"
#include <string>
#include <vector>



class Game
{
public:
    Game();

    ~Game();

    void run();
    void update(const Controller& controller);
    void render(GraphicManager& graphics);
    bool dump(const std::string& output_path) const;
    bool load(const std::string& input_path);

    bool operator==(const Game& other) const;

    void generarNuevoBloque();
    bool pucMoureLateral(int xLateral);
    bool potBaixar();
    void aterrarBloc();

    void setBoard(Board* b);
    void setScore(int score) { m_score = score; }
    void setFrameCounter(int frameCounter) { m_frameCounter = frameCounter; }
    void setGameOver(bool gameOver) { m_gameOver = gameOver; }
    void setBlocX(int x) { m_blocX = x; }
    void setBlocY(int y) { m_blocY = y; }
    void setBloqueCandy(int index, CandyType type) {
        if (index >= 0 && index < 3) {
            if (m_bloque[index] != nullptr) delete m_bloque[index];
            m_bloque[index] = new Candy(type);
        }
    }

private:
    Board* m_board;
    int m_score;
    int m_frameCounter;
    bool m_gameOver;

    int m_blocX;
    int m_blocY;
    Candy* m_bloque[3];
};
#endif