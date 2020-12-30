#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

enum class PlayerToken : char {
    X = 'X',
    Y = 'Y'
};

std::string tokenString(PlayerToken token, int index) {
    std::string token_string = "   ";
    if (PlayerToken::X == token || PlayerToken::Y == token) {
        token_string.at(1) = static_cast<char>(token);
    } else {
        token_string.at(1) = std::to_string(index + 1).at(0);
    }
    return token_string;
}

void draw(std::vector<PlayerToken>& tokens) {
    int row_length = 3;
    std::string board_string;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i % row_length == 0) {
            if (i != 0)
                board_string.append("\n-----------\n");
            board_string.append(tokenString(tokens.at(i), i));
        }
        else {
            board_string.append("|");
            board_string.append(tokenString(tokens.at(i), i));
        }

    }
    std::cout << board_string << "\n";
}

std::vector<std::vector<PlayerToken>> rows(std::vector<PlayerToken>& tokens) {
    int row_size = 3;
    std::vector<std::vector<PlayerToken>> rows(row_size);

    for (size_t i = 0; i < tokens.size(); i++) {
        rows[i / row_size].push_back(tokens[i]);
    }

    return rows;
}

std::vector<std::vector<PlayerToken>> columns(std::vector<PlayerToken>& tokens) {
    int column_size = 3;
    std::vector<std::vector<PlayerToken>> cols(column_size);

    for (size_t i = 0; i < tokens.size(); i++) {
        cols[i % column_size].push_back(tokens[i]);
    }
    return cols;
}

std::vector<std::vector<PlayerToken>> diagonals(std::vector<PlayerToken>& tokens) {
    int size = 3;
    int shift = 1;
    std::vector<std::vector<PlayerToken>> diags(size - shift);

    for (size_t i = 0; i < tokens.size(); i+=(size + shift)) {
        diags[0].push_back(tokens[i]);
    }

    for (size_t i = 6; i > 0; i-=(size - shift)) {
        diags[1].push_back(tokens[i]);
    }

    return diags;
}

bool player_wins(PlayerToken token, std::vector<PlayerToken>& tokens) {
    int consecutive_squares = 3;
    auto rs = rows(tokens);
    auto cols = columns(tokens);
    auto diags = diagonals(tokens);

    for (auto& r : rs) {
        auto contains_three = std::search_n(r.begin(), r.end(), consecutive_squares, token);
        if (contains_three != r.end()) return true;
    }

    for (auto& c : cols) {
        auto contains_three = std::search_n(c.begin(), c.end(), consecutive_squares, token);
        if (contains_three != c.end()) return true;
    }

    for (auto& d : diags) {
        auto contains_three = std::search_n(d.begin(), d.end(), consecutive_squares, token);
        if (contains_three != d.end()) return true;
    }

    return false;
}

bool game_over(std::vector<PlayerToken>& tokens, int turn_count) {
    int max_turns = 9;
    return (
        player_wins(PlayerToken::X, tokens) ||
        player_wins(PlayerToken::Y, tokens) ||
        turn_count == max_turns
    );
}

int main() {
    std::vector<PlayerToken> tokens(9);

    draw(tokens);
    int selected_space = 0;
    int turn_counter = 0;

    while(!game_over(tokens, turn_counter)) {
        PlayerToken token = turn_counter % 2 == 0 ? PlayerToken::X : PlayerToken::Y;
        std::cout << "select a space: ";
        std::cin >> selected_space;

        turn_counter++;
        tokens[--selected_space] = token;

        std::cout << "\n";
        draw(tokens);
    }

    if (player_wins(PlayerToken::X, tokens)) {
        std::cout << "X Wins!\n";
    }
    else if (player_wins(PlayerToken::Y, tokens)) {
        std::cout << "Y Wins!\n";
    }
    else {
        std::cout << "It's a draw\n";
    }
    return 0;
}
