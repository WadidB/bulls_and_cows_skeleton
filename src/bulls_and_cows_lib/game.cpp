
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <windows.h>

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        // Create a board with a randomly generated secret code\n"
        Board mon_board{};
        AttemptAndFeedback my_feedback{};
        mon_board = create_board(game_options);

         do
        {
            std::cout << "\n";
            display_board(std::cout, game_options, mon_board);

            my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, mon_board);

            while (!validate_attempt(game_options, my_feedback.attempt))
            {
                std::cout << "Your attempt is not valid, try again\n";
                my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, mon_board);
            }

            my_feedback.feedback = compare_attempt_with_secret_code(my_feedback.attempt, mon_board.secret_code);
            mon_board.attempts_and_feedbacks.push_back(my_feedback);

        } while (!(is_end_of_game(game_options, mon_board)) && !(is_win(game_options, mon_board)));

         std::cout << "\n";
        display_board(std::cout, game_options, mon_board);

        if (is_win(game_options, mon_board))
        {
            std::cout << "\n"
                      << "You won ! The secret code is : " << mon_board.secret_code.value << "\n";
        }
        else
        {
            std::cout << "\n"
                      << "You lost ! The secret code is : " << mon_board.secret_code.value << "\n";
        }
    }

   void computer_plays_against_computer(const GameOptions& game_options)
    {
        Board IAboard = create_board(game_options); // Create a board with a randomly generated secret code
        PossibleSolutions all_codes =
            generate_all_possible_codes(game_options); // Generate the list of all the possible codes
        AttemptAndFeedback IA_af{};

        do
        {
            std::cout << "\n";
            display_board(std::cout, game_options, IAboard); // Display the board and the list of attempts so far

            std::cout << "\n" << all_codes.codes.size() << " Remaining possible codes.\n";

            Sleep(2000); // Wait for 2 seconds

            IA_af.attempt = pick_random_attempt(all_codes);
            IA_af.feedback = compare_attempt_with_secret_code(IA_af.attempt, IAboard.secret_code);
            IAboard.attempts_and_feedbacks.push_back(IA_af);

        } while (!(is_end_of_game(game_options, IAboard)) && !(is_win(game_options, IAboard)));

        std::cout << "\n";
        display_board(std::cout, game_options, IAboard);

        if (is_win(game_options, IAboard))
        {
            std::cout << "\n"
                      << "Computer won ! The secret code is : " << IAboard.secret_code.value << "\n";
        }
        else
        {
            std::cout << "\n"
                      << "Computer lost ! The secret code is : " << IAboard.secret_code.value << "\n";
        }
    }
    void configure_game_options(GameOptions& game_options)
    {
        std::cout << "TODO:\n"
                     "    DO\n"
                     "       Display the current game options\n"
                     "       Display the game options menu\n"
                     "       Ask the user to type its choice\n"
                     "       Treat the user's choice\n"
                     "    UNTIL user's choice is to go back to main menu\n";
    }

    void play_game()
    {
        GameOptions game_options{};

        while (true)
        {
            std::cout << "\n#################################\n";
            display_main_menu(std::cout);

            const auto user_choice = ask_main_menu_choice(std::cin);
            switch (user_choice)
            {
            case MainMenuChoice::Quit:
                std::cout << "\nBye bye!\n";
                return;
            case MainMenuChoice::UserPlaysAgainstComputer:
                user_plays_against_computer(game_options);
                break;
            case MainMenuChoice::ComputerPlaysAgainstComputer:
                computer_plays_against_computer(game_options);
                break;
            case MainMenuChoice::ConfigureOptions:
                configure_game_options(game_options);
                break;
            case MainMenuChoice::Error:
                std::cout << "\nYou did not enter a valid choice, please try again\n";
                break;
            }
        }
    }

} // namespace bulls_and_cows
