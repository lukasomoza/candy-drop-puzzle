#include "game.h"
#include <random>
#include "graphics.h"
#include "candy.h"
#include "util.h"

Game::Game()

{
    m_board = new Board(DEFAULT_BOARD_WIDTH, DEFAULT_BOARD_HEIGHT);
    m_score = 0;
    m_frameCounter = 0;
    m_gameOver = false;

    m_bloque[0] = nullptr;
    m_bloque[1] = nullptr;
    m_bloque[2] = nullptr;

    generarNuevoBloque();
}

Game::~Game()
{
    for (int i = 0; i < 3; ++i)
    {
        if (m_bloque[i] != nullptr)
        {
            delete m_bloque[i];
            m_bloque[i] = nullptr;
        }
    }
}

void Game::setBoard(Board* board)
{
    if (board != nullptr)
    {
        delete m_board;
    }
    m_board = board;
}


void Game::generarNuevoBloque()
{
    for (int i = 0; i < 3; ++i)
    {
        if (m_bloque[i] != nullptr)
        {
            delete m_bloque[i];
            m_bloque[i] = nullptr;
        }
    }

    m_blocX = m_board->getWidth() / 2;
    m_blocY = 2;

    for (int i = 0; i < 3; ++i)
    {
        int numeroAleatorio = rand() % 6;
        CandyType tipoAleatorio = static_cast<CandyType>(numeroAleatorio);

        m_bloque[i] = new Candy(tipoAleatorio);
    }

    if (m_board->getCell(m_blocX, m_blocY) != nullptr)
    {
        m_gameOver = true;
    }
}

void Game::update(const Controller& controller)
{
    if (m_gameOver)
        return;

    m_frameCounter++;

    if (controller.isLeftPressed())
    {
        if (pucMoureLateral(m_blocX - 1))
            m_blocX--;
    }

    if (controller.isRightPressed())
    {
        if (pucMoureLateral(m_blocX + 1))
            m_blocX++;
    }

    if (controller.isKey1Pressed())
    {
        Candy* aux = m_bloque[0];
        m_bloque[0] = m_bloque[1];
        m_bloque[1] = m_bloque[2];
        m_bloque[2] = aux;
    }

    if (controller.isKey2Pressed())
        dump(getDataDirPath() + "/save.txt");

    bool haDeCaer = false;
    if (m_frameCounter % 60 == 0 || controller.isDownPressed())
        haDeCaer = true;

    if (haDeCaer)
    {
        if (potBaixar())
            m_blocY++;
        else
        {
            aterrarBloc();
            vector<Candy*> explotats = m_board->explodeAndDrop();
            m_score += explotats.size();

            generarNuevoBloque();

            if (!potBaixar() && m_blocY <= 2)
                m_gameOver = true;
        }
    }
}

bool Game::pucMoureLateral(int xLateral)
{
    if (xLateral < 0 || xLateral >= m_board->getWidth())
        return false;

    for (int i = 0; i < 3; i++)
    {
        int yLateral = m_blocY - i;
        if (yLateral >= 0 && m_board->getCell(xLateral, yLateral) != nullptr)
            return false;
    }
    return true;
}

bool Game::potBaixar()
{
    if (m_blocY + 1 >= m_board->getHeight())
        return false;

    if (m_blocY + 1 >= 0)
        if (m_board->getCell(m_blocX, m_blocY + 1) != nullptr)
            return false;

    return true;
}

void Game::aterrarBloc()
{
    for (int i = 0; i < 3; i++)
    {
        int y = m_blocY - i;
        if (y >= 0 && y < m_board->getHeight())
        {
            m_board->setCell(m_bloque[i], m_blocX, y);
        }
        else
        {
            delete m_bloque[i];
        }
        m_bloque[i] = nullptr;
    }
}

void Game::render(GraphicManager& graphics)
{
    int files = m_board->getHeight();
    int columnes = m_board->getWidth();
    const int board_padding = 3;

    graphics.drawRectangle(CANDY_IMAGE_WIDTH * board_padding, CANDY_IMAGE_HEIGHT * board_padding, CANDY_IMAGE_WIDTH * columnes, CANDY_IMAGE_HEIGHT * files, 5, 150, 150, 150);

    for (int i = 0; i < files; i++)
    {
        for (int j = 0; j < columnes; j++)
        {
            Candy* caramel = m_board->getCell(j, i);
            if (caramel != nullptr)
            {
                graphics.drawImage(caramel->getResourceName(), CANDY_IMAGE_WIDTH * (j + 3), CANDY_IMAGE_HEIGHT * (i + 3));
            }
        }
    }

    if (!m_gameOver)
    {
        for (int i = 0; i < 3; i++)
        {
            if (m_bloque[i] != nullptr)
            {
                int fila = m_blocY - i;
                int col = m_blocX;

                int pixel_x = CANDY_IMAGE_WIDTH * (col + board_padding);
                int pixel_y = CANDY_IMAGE_HEIGHT * (fila + board_padding);
                graphics.drawImage(m_bloque[i]->getResourceName(), pixel_x, pixel_y);
            }
        }
    }
    else
    {
        graphics.drawText("GAME OVER", 280, 350, 40, 255, 0, 0);
    }

    graphics.drawImage("img/logo_small.png", 10, 10);

    graphics.drawText("Movement: [Left] [Right] [Down]  --  "
        "Rotate: [Q]  --  Save: [W]  --  Exit [ESC]",
        25, 700, 20, 100, 100, 100);

    std::string texto_puntuacion = "Score: " + std::to_string(m_score);
    graphics.drawText(texto_puntuacion, 450, 10, 50, 125, 200, 125);
}

void Game::run()
{
    const int screen_width = 750;
    const int screen_height = 750;
    const int bg_red = 255;
    const int bg_green = 255;
    const int bg_blue = 255;

    runGraphicGame(*this, screen_width, screen_height, bg_red, bg_green, bg_blue);
}

bool Game::dump(const string& output_path) const
{
    ofstream fitxer(output_path);

    if (!fitxer.is_open())
        return false;

    int t0 = (m_bloque[0] != nullptr) ? (int)m_bloque[0]->getType() : -1;
    int t1 = (m_bloque[1] != nullptr) ? (int)m_bloque[1]->getType() : -1;
    int t2 = (m_bloque[2] != nullptr) ? (int)m_bloque[2]->getType() : -1;

    fitxer << m_score << " " << m_gameOver << " " << m_blocX << " " << m_blocY << " " << t0 << " " << t1 << " " << t2 << " " << m_frameCounter << endl;

    fitxer << m_board->getWidth() << " " << m_board->getHeight() << endl;

    for (int i = 0; i < m_board->getHeight(); i++)
    {
        for (int j = 0; j < m_board->getWidth(); j++)
        {
            Candy* c = m_board->getCell(j, i);
            if (c == nullptr)
                fitxer << "-1 ";
            else
                fitxer << (int)c->getType() << " ";
        }
        fitxer << endl;
    }
    return true;
}

bool Game::load(const string& input_path)
{
    ifstream fitxer(input_path);

    if (!fitxer.is_open())
        return false;

    int t0, t1, t2;

    if (!(fitxer >> m_score >> m_gameOver >> m_blocX >> m_blocY >> t0 >> t1 >> t2 >> m_frameCounter))
    {
        return false;
    }

    for (int i = 0; i < 3; i++) {
        if (m_bloque[i] != nullptr)
        {
            delete m_bloque[i];
            m_bloque[i] = nullptr;
        }
    }

    if (t0 != -1)
        m_bloque[0] = new Candy((CandyType)t0);
    if (t1 != -1)
        m_bloque[1] = new Candy((CandyType)t1);
    if (t2 != -1)
        m_bloque[2] = new Candy((CandyType)t2);

    int w, h;
    if (!(fitxer >> w >> h))
        return false;

    if (m_board)
        delete m_board;

    m_board = new Board(w, h);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int cnd;
            if (fitxer >> cnd)
            {
                if (cnd != -1)
                    m_board->setCell(new Candy((CandyType)cnd), j, i);
                else
                    m_board->setCell(nullptr, j, i);
            }
        }
    }
    return true;
}

bool Game::operator==(const Game& other) const
{
    if (m_score != other.m_score || m_gameOver != other.m_gameOver || m_frameCounter != other.m_frameCounter)
        return false;

    if (m_blocX != other.m_blocX || m_blocY != other.m_blocY)
        return false;

    for (int i = 0; i < 3; ++i)
    {
        Candy* b1 = m_bloque[i];
        Candy* b2 = other.m_bloque[i];

        if ((b1 == nullptr && b2 != nullptr) || (b1 != nullptr && b2 == nullptr))
            return false;


        if (b1 != nullptr && b2 != nullptr)
        {
            if (b2->getType() != b1->getType())
                return false;
        }
    }

    if (m_board->getWidth() != other.m_board->getWidth() || m_board->getHeight() != other.m_board->getHeight())
        return false;

    for (int i = 0; i < m_board->getHeight(); i++)
    {
        for (int j = 0; j < m_board->getWidth(); j++)
        {
            Candy* c1 = m_board->getCell(j, i);
            Candy* c2 = other.m_board->getCell(j, i);

            if (c1 == nullptr && c2 != nullptr)
                return false;


            if (c1 != nullptr && c2 == nullptr)
                return false;


            if (c1 != nullptr && c2 != nullptr && c1->getType() != c2->getType())
                return false;
        }
    }
    return true;
}