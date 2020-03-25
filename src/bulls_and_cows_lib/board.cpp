
#include "board.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp


    // Create a board and with a new random secret code composed of allowed characters
    Board create_board(const GameOptions& game_options)
    {
      
        char tableau_test[GameOptions];   // créé un tableau dont la taille dépend de la variable "game_option"
                                           // ne marche pas  message d'erreur : - Type name not allowed
                                           //                                   - bulls_and_cows::GameOptions': illegal use of this type as an expression

    }


    // Compare a user-entered code with the secret code and give the corresponding number of bulls and cows
    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    { 
    }

} // namespace bulls_and_cows
