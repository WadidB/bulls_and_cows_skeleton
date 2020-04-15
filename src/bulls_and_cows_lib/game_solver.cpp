
#include "game_solver.hpp"

namespace bulls_and_cows {
    // TODO: define the body of the functions declared in game_solver.cpp
    void all_possible_code(int num, int max, const GameOptions& game_options, PossibleSolutions& var_all_possible_codes,
                           Code codes)
    {
        std::string all_allowed_char;

        for (char c = game_options.minimum_allowed_character; c <= game_options.maximum_allowed_character; c++)
        {
            all_allowed_char.push_back(c);
        }

        for (char temp : all_allowed_char)
        {
            if (num <= max)
            {
                codes.value.push_back(temp);
                num++;
                all_possible_code(num, max, game_options, var_all_possible_codes, codes);
                codes.value.pop_back();
            }
            else if (num > max)
            {
                var_all_possible_codes.codes.push_back(codes);
                break;
            }
            num--;
        }
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        int min = 0;
        int max = (int)possible_solutions.codes.size() - 1; // cast
        int rand = generate_random_integer(min, max);

        return possible_solutions.codes[rand];
    }

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions var_all_possible_codes{}; // contiendra tous les codes possibles (doublons compris)
        PossibleSolutions final_possible_code{};    // contiendra tous les codes autorisés
        Code code;
        auto nb_char_code = game_options.number_of_characters_per_code;

        all_possible_code(1, nb_char_code, game_options, var_all_possible_codes,
                          code); // on genère tous les codes possibles ici (on les stock dans var_all_possible_code)

        for (unsigned int i = 0; i < var_all_possible_codes.codes.size(); i++)
        {
            final_possible_code.codes.push_back(
                var_all_possible_codes.codes[i]); // on insert le code valide dans le vecteur final
        }

        return final_possible_code;
    }
} // namespace bulls_and_cows
