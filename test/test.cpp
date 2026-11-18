#define _HAS_STD_BYTE 0
#include <filesystem>
#include "board.h"
#include "candy.h"
#include "controller.h"
#include "game.h"
#include "util.h"

bool test()
{
    // ==========================================================
    // 1. TESTS DE CONTROL DE BORDES Y CASOS INVÁLIDOS (BOARD)
    // ==========================================================
    cout << "-----TESTS CASOS INVALIDOS (BOARD)-----" << endl;
    Board B_limites(5, 5);

    // Intentar acceder a coordenadas fuera de rango (Negativas y excedidas)
    if (B_limites.getCell(-1, 2) == nullptr && B_limites.getCell(5, 5) == nullptr && B_limites.getCell(10, 0) == nullptr)
    {
        cout << "Test 1 - Limites fuera de rango - CORRECTE" << endl;
    }
    else
    {
        cout << "Test 1 - Limites fuera de rango - INCORRECTE" << endl;
        return false;
    }

    // Intentar cargar un fichero que no existe
    if (!B_limites.load("fichero_fantasma_seguro_que_no_existe.txt"))
    {
        cout << "Test 2 - Cargar tablero inexistente - CORRECTE" << endl;
    }
    else
    {
        cout << "Test 2 - Cargar tablero inexistente - INCORRECTE" << endl;
        return false;
    }
    cout << endl;


    // ==========================================================
    // 2. TESTS CONSTRUCTOR (BOARD)
    // ==========================================================
    cout << "-----TESTS CONSTRUCTOR-----" << endl;
    Board B1(10, 10);
    bool test1Mal = false;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (B1.getCell(i, j) != nullptr)
                test1Mal = true;
        }
    }
    if (test1Mal)
    {
        cout << "Test 1 - Comprovar Constructor - INCORRECTE" << endl;
        return false;
    }
    else
        cout << "Test 1 - Comprovar Constructor - CORRECTE" << endl;

    Board B2(5, 5);
    Candy* rojo = new Candy(CandyType::TYPE_RED);
    B2.setCell(rojo, 2, 3);
    int cont = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (B2.getCell(i, j) != nullptr)
                cont++;
        }
    }
    if (cont == 1)
    {
        cout << "Test 2 - Comprovar Constructor - CORRECTE" << endl;
    }
    else
    {
        cout << "Test 2 - Comprovar Constructor - INCORRECTE" << endl;
        return false;
    }
    cout << endl;


    // ==========================================================
    // 3. TESTS GETTERS (BOARD)
    // ==========================================================
    cout << "-----TESTS GETTERS-----" << endl;
    Board B3(5, 2);
    if (B3.getHeight() == 2 && B3.getWidth() == 5)
        cout << "Test 1 - Comprovar GETTERS - CORRECTE" << endl;
    else
    {
        cout << "Test 1 - Comprovar GETTERS - INCORRECTE" << endl;
        return false;
    }

    Board B4(7, 7);
    Candy* naranja = new Candy(CandyType::TYPE_ORANGE);
    B4.setCell(naranja, 4, 4);
    if (B4.getCell(4, 4) == naranja && B4.getCell(2, 3) == nullptr)
        cout << "Test 2 - Comprovar GETTERS - CORRECTE" << endl;
    else
    {
        cout << "Test 2 - Comprovar GETTERS - INCORRECTE" << endl;
        return false;
    }
    cout << endl;


    // ==========================================================
    // 4. TESTS SETTERS (BOARD)
    // ==========================================================
    cout << "-----TESTS SETTERS-----" << endl;
    Board B5(3, 3);
    Candy* amarillo = new Candy(CandyType::TYPE_YELLOW);
    Candy* amarillo2 = new Candy(CandyType::TYPE_YELLOW);
    Candy* amarillo3 = new Candy(CandyType::TYPE_YELLOW);
    B5.setCell(amarillo2, 2, 2);
    B5.setCell(amarillo, 1, 1);
    B5.setCell(amarillo3, 0, 0);

    int cont2 = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            if (B5.getCell(i, j) != nullptr)
                cont2++;
    }
    if (cont2 == 3)
    {
        cout << "Test 1 - Comprovar SETTERS - CORRECTE" << endl;
    }
    else
    {
        cout << "Test 1 - Comprovar SETTERS - INCORRECTE" << endl;
        return false;
    }

    if (B5.getCell(2, 2) != nullptr && B5.getCell(0, 1) == nullptr)
    {
        cout << "Test 2 - Comprovar SETTERS - CORRECTE" << endl;
    }
    else
    {
        cout << "Test 2 - Comprovar SETTERS - INCORRECTE" << endl;
        return false;
    }
    cout << endl;


    // ==========================================================
    // 5. TESTS SHOULD EXPLODE (BOARD) - CORREGIDOS
    // ==========================================================
    cout << "-----TESTS SHOULD EXPLODE-----" << endl;

    // VERTICAL
    Board B6(5, 5);
    Candy* azul = new Candy(CandyType::TYPE_BLUE);
    Candy* azul2 = new Candy(CandyType::TYPE_BLUE);
    Candy* azul3 = new Candy(CandyType::TYPE_BLUE);
    B6.setCell(azul, 0, 2);
    B6.setCell(azul2, 0, 1);
    B6.setCell(azul3, 0, 0);

    if (B6.shouldExplode(0, 0))
        cout << "Test 1 - Should Explode (VERTICAL) - CORRECTE" << endl;
    else
    {
        cout << "Test 1 - Should Explode (VERTICAL) - INCORRECTE" << endl;
        return false;
    }

    // HORIZONTAL
    Board B7(5, 5);
    Candy* verde = new Candy(CandyType::TYPE_GREEN);
    Candy* verde2 = new Candy(CandyType::TYPE_GREEN);
    Candy* verde3 = new Candy(CandyType::TYPE_GREEN);
    B7.setCell(verde, 0, 0);
    B7.setCell(verde2, 0, 1);
    B7.setCell(verde3, 0, 2);

    if (B7.shouldExplode(0, 1))
        cout << "Test 2 - Should Explode (HORIZONTAL) - CORRECTE" << endl;
    else
    {
        cout << "Test 2 - Should Explode (HORIZONTAL) - INCORRECTE" << endl;
        return false;
    }

    // DIAGONAL 1
    Board B8(5, 5);
    Candy* purpura = new Candy(CandyType::TYPE_PURPLE);
    Candy* purpura2 = new Candy(CandyType::TYPE_PURPLE);
    Candy* purpura3 = new Candy(CandyType::TYPE_PURPLE);
    B8.setCell(purpura, 2, 2);
    B8.setCell(purpura2, 1, 1);
    B8.setCell(purpura3, 0, 0);

    if (B8.shouldExplode(1, 1))
        cout << "Test 3.1 - Should Explode (DIAGONAL 1) - CORRECTE" << endl;
    else
    {
        cout << "Test 3.1 - Should Explode (DIAGONAL 1) - INCORRECTE" << endl;
        return false;
    }

    // DIAGONAL 2 
    Board B9(5, 5);
    Candy* groc = new Candy(CandyType::TYPE_YELLOW);
    Candy* groc2 = new Candy(CandyType::TYPE_YELLOW);
    Candy* groc3 = new Candy(CandyType::TYPE_YELLOW);
    B9.setCell(groc, 2, 0);
    B9.setCell(groc2, 1, 1);
    B9.setCell(groc3, 0, 2);

    if (B9.shouldExplode(0, 2))
        cout << "Test 3.2 - Should Explode (DIAGONAL 2) - CORRECTE" << endl;
    else
    {
        cout << "Test 3.2 - Should Explode (DIAGONAL 2) - INCORRECTE" << endl;
        return false;
    }
    cout << endl;


    // ==========================================================
    // 6. TESTS EXPLODE & DROP (BOARD)
    // ==========================================================
    cout << "-----TESTS EXPLODE & DROP-----" << endl;
    Board B10(5, 5);
    Candy* vermell = new Candy(CandyType::TYPE_RED);
    Candy* vermell2 = new Candy(CandyType::TYPE_RED);
    Candy* vermell3 = new Candy(CandyType::TYPE_RED);
    Candy* azulEncima = new Candy(CandyType::TYPE_BLUE);

    B10.setCell(vermell, 0, 4);
    B10.setCell(vermell2, 1, 4);
    B10.setCell(vermell3, 2, 4);
    B10.setCell(azulEncima, 1, 3);

    vector<Candy*> explotados = B10.explodeAndDrop();

    if (explotados.size() == 3)
        cout << "Test 1 - Cantidad explotados - CORRECTE" << endl;
    else
    {
        cout << "Test 1 - Cantidad explotados - INCORRECTE" << endl;
        return false;
    }
    cout << endl;


    // ==========================================================
    // 7. TEST OPERATOR== (GAME)
    // ==========================================================
    cout << "-----TESTS OPERATOR==-----" << endl;

    Game juego1;
    Board* B11 = new Board(5, 5);
    Candy* grocGame1_1 = new Candy(CandyType::TYPE_YELLOW);
    Candy* grocGame1_2 = new Candy(CandyType::TYPE_YELLOW);
    Candy* grocGame1_3 = new Candy(CandyType::TYPE_YELLOW);
    B11->setCell(grocGame1_1, 2, 0);
    B11->setCell(grocGame1_2, 1, 1);
    B11->setCell(grocGame1_3, 0, 2);
    juego1.setBoard(B11);
    juego1.setScore(6);
    juego1.setFrameCounter(10);
    juego1.setGameOver(true);
    juego1.setBlocX(2);
    juego1.setBlocY(2);
    juego1.setBloqueCandy(0, CandyType::TYPE_YELLOW);
    juego1.setBloqueCandy(1, CandyType::TYPE_YELLOW);
    juego1.setBloqueCandy(2, CandyType::TYPE_YELLOW);

    Game juego2;
    Board* B12 = new Board(5, 5);
    Candy* grocGame2_1 = new Candy(CandyType::TYPE_YELLOW);
    Candy* grocGame2_2 = new Candy(CandyType::TYPE_YELLOW);
    Candy* grocGame2_3 = new Candy(CandyType::TYPE_YELLOW);
    B12->setCell(grocGame2_1, 2, 0);
    B12->setCell(grocGame2_2, 1, 1);
    B12->setCell(grocGame2_3, 0, 2);
    juego2.setBoard(B12);
    juego2.setScore(6);
    juego2.setFrameCounter(10);
    juego2.setGameOver(true);
    juego2.setBlocX(2);
    juego2.setBlocY(2);
    juego2.setBloqueCandy(0, CandyType::TYPE_YELLOW);
    juego2.setBloqueCandy(1, CandyType::TYPE_YELLOW);
    juego2.setBloqueCandy(2, CandyType::TYPE_YELLOW);

    bool sonIguales = false;
    if (juego1 == juego2)
        sonIguales = true;

    if (sonIguales)
    {
        cout << "Test 1 - Comparacion Games - CORRECTE" << endl;
    }
    else
    {
        cout << "Test 1 - Comparacion Games - INCORRECTE" << endl;
        return false;
    }


    Game juego3;
    Board* B13 = new Board(5, 5);
    Candy* grocGame3_1 = new Candy(CandyType::TYPE_YELLOW);
    Candy* grocGame3_2 = new Candy(CandyType::TYPE_YELLOW);
    Candy* grocGame3_3 = new Candy(CandyType::TYPE_YELLOW);
    B13->setCell(grocGame3_1, 2, 0);
    B13->setCell(grocGame3_2, 1, 1);
    B13->setCell(grocGame3_3, 0, 2);
    juego3.setBoard(B13);
    juego3.setScore(6);
    juego3.setFrameCounter(10);
    juego3.setGameOver(true);

    Game juego4;
    Board* B14 = new Board(5, 5);
    Candy* grocGame4_1 = new Candy(CandyType::TYPE_YELLOW);
    Candy* grocGame4_2 = new Candy(CandyType::TYPE_YELLOW);
    Candy* grocGame4_3 = new Candy(CandyType::TYPE_YELLOW);
    B14->setCell(grocGame4_1, 2, 0);
    B14->setCell(grocGame4_2, 1, 1);
    B14->setCell(grocGame4_3, 0, 2);
    juego4.setBoard(B14);
    juego4.setScore(16);
    juego4.setFrameCounter(50);
    juego4.setGameOver(false);

    bool sonDiferentes = true;
    if (juego3 == juego4)
        sonDiferentes = false;

    if (sonDiferentes)
    {
        cout << "Test 2 - Comparacion Games - CORRECTE" << endl;
    }
    else
    {
        cout << "Test 2 - Comparacion Games - INCORRECTE" << endl;
        return false;
    }


    Game juego5;
    Board* B15 = new Board(5, 5);
    Candy* verdGame5_1 = new Candy(CandyType::TYPE_GREEN);
    Candy* verdGame5_2 = new Candy(CandyType::TYPE_GREEN);
    Candy* verdGame5_3 = new Candy(CandyType::TYPE_GREEN);
    B15->setCell(verdGame5_1, 2, 0);
    B15->setCell(verdGame5_2, 1, 1);
    B15->setCell(verdGame5_3, 0, 2);
    juego5.setBoard(B15);
    juego5.setScore(6);
    juego5.setFrameCounter(10);
    juego5.setGameOver(true);

    Game juego6;
    Board* B16 = new Board(5, 5);
    Candy* vermellGame6_1 = new Candy(CandyType::TYPE_RED);
    Candy* vermellGame6_2 = new Candy(CandyType::TYPE_RED);
    Candy* vermellGame6_3 = new Candy(CandyType::TYPE_RED);
    B16->setCell(vermellGame6_1, 2, 0);
    B16->setCell(vermellGame6_2, 1, 1);
    B16->setCell(vermellGame6_3, 0, 2);
    juego6.setBoard(B16);
    juego6.setScore(6);
    juego6.setFrameCounter(10);
    juego6.setGameOver(true);

    bool sonDiferentes2 = true;
    if (juego6 == juego5)
        sonDiferentes2 = false;

    if (sonDiferentes2)
    {
        cout << "Test 3 - Comparacion Games - CORRECTE" << endl;
    }
    else
    {
        cout << "Test 3 - Comparacion Games - INCORRECTE" << endl;
        return false;
    }


    cout << endl;

    // ==========================================================
    // 8. TEST DUMP/LOAD (GAME)
    // ==========================================================

    cout << "-----TESTS DUMP/LOAD-----" << endl;

    Game g1;
    g1.setScore(25);
    g1.setFrameCounter(120);
    g1.setGameOver(false);

    bool guardado = g1.dump(getDataDirPath() + "/test_save.txt");
    if (guardado)
        cout << "Test 1 - Dump - CORRECTE" << endl;
    else
    {
        cout << "Test 1 - Dump - INCORRECTE" << endl;
        return false;
    }

    Game g2;
    bool cargado = g2.load(getDataDirPath() + "/test_save.txt");
    if (cargado)
        cout << "Test 2 - Load - CORRECTE" << endl;
    else
    {
        cout << "Test 2 - Load - INCORRECTE" << endl;
        return false;
    }

    if (g1 == g2)
        cout << "Test 3 - Dump/Load - CORRECTE" << endl;
    else
    {
        cout << "Test 3 - Dump/Load - INCORRECTE" << endl;
        return false;
    }

    return true;
}