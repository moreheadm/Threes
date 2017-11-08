/*
 *
 *
 *
 *
 */

#include <string>
#include "board.h"

int main () {
    Board board;
    
    std::cout << board << "\n\n" << std::flush;
    
    mainloop:
    while(true) {
        std::string s;
        std::cin >> s;
            
        switch(s[0]) {
            case 'u':
            case 'U':
                board.move(BoardMove::UP);
                break;
            case 'l':
            case 'L':
                board.move(BoardMove::LEFT);
                break;
            case 'd':
            case 'D':
                board.move(BoardMove::DOWN);
                break;
            case 'r':
            case 'R':   
                board.move(BoardMove::RIGHT);
                break;
            case 'e':
            case 'E':
                break mainloop;
            default:
                continue mainloop;
        }
        std::cout << board << "\n\n" << std::flush;

        if (board.isGameOver()) {
            std::cout << "GAME OVER!" << std::endl;
            std::cout << "Score: " << board.getScore() << std::endl;
            break;
        }
    }
    return 0;
}
