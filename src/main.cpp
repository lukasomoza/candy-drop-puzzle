/// Project entry point
///
/// Usage:
///   CandyDrop                   start a new game
///   CandyDrop <save-file>       resume a game saved with [W] (e.g. data/save.txt)
#include <iostream>
#include "game.h"
#include "../test/test.h"

int main(int argc, const char* argv[])
{
    if (!test())
    {
        std::cout << "Unit tests FAILED." << std::endl;
    }
    else
    {
        std::cout << "All unit tests passed." << std::endl;
    }

    Game game;

    if (argc > 1)
    {
        if (game.load(argv[1]))
            std::cout << "Loaded saved game from " << argv[1] << std::endl;
        else
            std::cerr << "Could not load '" << argv[1] << "', starting a new game." << std::endl;
    }

    // Run until ESC is pressed
    game.run();
    return 0;
}
