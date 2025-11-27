/*
Implementare una classe PratoFiorito che permetta di giocare ad una partita
del celebre gioco Minesweeper. 
Il gioco si svolge su una matrice quadrata NxN in cui
ogni cella può contenere oppure no una bomba. 
Se la cella non contiene una bomba,
la cella conserva l’informazione del numero di bombe adiacenti ad essa.
Si richiede di implementare
    - un costruttore che riceva come parametri un vettore di coordinate (delle celle
      contenenti bombe) che, sulla base di queste, inizializzi la matrice;
    - Un metodo “gioca” che permetta di giocare una partita completa del gioco.
*/

#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <math.h>

#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;


string operator*(const string& s, unsigned int n) {
    string out = "";
    out.reserve(s.size() * n);
    while (n--)
        out += s;
    return out;
}

bool is_uint(const string& s) {
    if (s.empty()) return false;
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

unsigned int to_uint(const string& s) {
    size_t pos;
    unsigned long val = stoul(s, &pos);
    return static_cast<unsigned int>(val);
}


class position {
public:
    unsigned x;
    unsigned y;

    position() {}

    position(unsigned x, unsigned y) {
        this->x = x;
        this->y = y;
    } 

    position(int x, int y) {
        this->x = abs(x);
        this->y = abs(y);
    }

    bool is_inside(unsigned x_size, unsigned y_size) {
        return 0 <= x && x < x_size && 0 <= y && y < y_size;
    }

    bool is_inside(unsigned xy_size) {
        return is_inside(xy_size, xy_size);
    }

    vector<position> around(unsigned range_radius) {
        int range = range_radius;
        vector<position> around_positions;
        for (int i = -range; i < range + 1; i++) {
            for (int j = -range; j < range + 1; j++) {
                if (x == j && y == i) {
                    continue;
                }
                around_positions.push_back(position(x + j, y + i));
            }
        }
        return around_positions;
    }

    vector<position> around(unsigned range_radius, unsigned xy_size) {
        vector<position> around_positions = around(range_radius);
        for (auto iter = around_positions.begin(); iter != around_positions.end();) {
            if (!(*iter).is_inside(xy_size)) {
                iter = around_positions.erase(iter);
            } else {
                iter++;
            }
        }
        return around_positions;
    }

    bool operator==(position other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(position other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }

    friend ostream& operator<<(ostream& os, position& p) {
        os << "p(" << p.x << ", " << p.y << ")"; 
        return os;
    }
};


class Minesweeper {
private:
    vector<vector<int>> game_map;
    vector<vector<int>> map_mask;
    vector<position> flags;
    vector<position> bombs;
    unsigned map_size;
    bool running = true;

    static constexpr int UNKNOW = -1;
    static constexpr int OPEN = -2;
    static constexpr int FLAG = -3;
    static constexpr int BOMB = -4;

    inline static const std::map<int, std::string> EMOJI_MAP = {
        {UNKNOW, "\033[4;53;2;100m▏ ▕\033[0m"},
        {BOMB, "(*)"},
        {FLAG, "<F>"},
        {0, "\033[4;53;2m▏ ▕\033[0m"},
        {1, "\033[4;53;2;44m\033[37m▏1▕\033[0m"},
        {2, "\033[4;53;42m\033[37m▏2▕\033[0m"},
        {3, "\033[4;53;41m\033[37m▏3▕\033[0m"},
        {4, "\033[4;53;45m\033[37m▏4▕\033[0m"},
        {5, "\033[4;53;43m\033[37m▏5▕\033[0m"},
        {6, "\033[4;53;36m\033[37m▏6▕\033[0m"},
        {7, "\033[4;53;40m\033[37m▏7▕\033[0m"},
        {8, "\033[4;53;47m\033[37m▏8▕\033[0m"},
    };


    int& at(position pos) {
        return game_map[pos.y][pos.x];  
    }

    int& get_mask(position pos) {
        return map_mask[pos.y][pos.x];  
    }

    void set_mask(position pos, int value) {
        map_mask[pos.y][pos.x] = value;
    }

    int get(position pos) {
        if (pos.is_inside(map_size)) {
            return game_map[pos.y][pos.x];
        }
        return -4;
    }

    void set(position pos, unsigned value) {
        game_map[pos.y][pos.x] = value;
    }

    vector<position> generate_bomb_positions(unsigned map_size, unsigned bombs_quantity) {
        default_random_engine generator;
        uniform_int_distribution<int> distrib(0, map_size - 1);

        vector<position> bomb_positions;
        while (bomb_positions.size() < bombs_quantity) {
            position new_pos(distrib(generator), distrib(generator));
            bool already_inside = false;
            for (auto& pos : bomb_positions) {
                if (pos == new_pos) {
                    already_inside = true;
                    break;
                }
            }
            if (!already_inside) {
                bomb_positions.push_back(new_pos);
            }
        }
        return bomb_positions;
    }

    void generate_map(unsigned map_size, vector<position> bomb_positions) {
        bombs = bomb_positions;
        this->map_size = map_size;
        running = true;
        game_map.resize(map_size, vector<int>(map_size, 0));
        for (auto& bomb_pos : bomb_positions) {
            // cout << "bomb at position: " << bomb_pos << endl;
            vector<position> around_bomb_positions = bomb_pos.around(1, map_size);
            for (auto& around_bomb_pos : around_bomb_positions) {

                at(around_bomb_pos) += 1;
            }
        }

        
        for (auto& bomb_pos : bomb_positions) {
            at(bomb_pos) = BOMB;
        }



        map_mask.resize(map_size, vector<int>(map_size, UNKNOW));
        // for (int i = 0; i < map_size; i++) {
        //     for (int j = 0; j < map_size; j++) {
        //         position pos(j, i);
        //         set(pos, how_many_bombs_around(pos));
        //     }
        // }
    }


    vector<string> read_words() {
        string line;
        getline(cin, line);

        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (iss >> token) {
            tokens.push_back(token);
        }

        return tokens;
    }


public:
    const string COMMANDS_INFO = "Commands:\n\n  - open <x> <y>\n  - flag <x> <y> (toggle)\n  - surrender\n  - new_game <map_size> [bombs_amount] \n\n> ";

    Minesweeper(unsigned map_size) {
        generate_map(map_size, generate_bomb_positions(map_size, map_size - 2));
    }

    Minesweeper(unsigned map_size, vector<position> bomb_positions) {
        generate_map(map_size, bomb_positions);
    }

    Minesweeper(unsigned map_size, unsigned bombs_quantity) {
        generate_map(map_size, generate_bomb_positions(map_size, bombs_quantity));
    }

    void print_raw(vector<vector<int>> what) {
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                cout << what[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void end_game(bool has_win) {
        cout << (has_win ? "\nYOU WON!!" : "\nYOU LOOSE!!") << "\n";
        map_mask.clear();
        map_mask.resize(map_size, vector<int>(map_size, OPEN));
        running = false;
    }

    void open(position pos) {
        set_mask(pos, OPEN);
        if (at(pos) == 0) {
            vector<position> around_zero_pos = pos.around(1, map_size);
            for (position& az_pos : around_zero_pos) {
                if (get_mask(az_pos) != OPEN && at(az_pos) != BOMB) {
                    open(az_pos);
                }
                
            }
            return;
        }
        
        if (at(pos) == BOMB) {
            end_game(false);
            return;
        }

    }

    void flag(position pos) {
        for (auto it = flags.begin(); it != flags.end(); it++) {
            if ((*it) == pos) {
                flags.erase(it);
                set_mask(pos, UNKNOW);
                return;
            }
        }
        flags.push_back(pos);
        set_mask(pos, FLAG);

        if (flags.size() != bombs.size()) {
            return;
        }

        sort(flags.begin(), flags.end());
        sort(bombs.begin(), bombs.end());

        if (flags == bombs) {
            end_game(true);
        }

    }

    void process_input() {
        vector<string> tokens = read_words();

        if (!tokens.size()) {
            cout << "\n\tInput is invalid, retry.\n\n> ";
            process_input();
            return;
        }

        const string action = tokens[0];

        if (action == "open") {
            if (!running) {
                cout << "\n\tgame has ended, start a new one.\n\n> ";
                process_input();
                return;
            }
            if (!is_uint(tokens[1])) {
                cout << "\n\t<x> is not a valid number, retry.\n\n> ";
                process_input();
                return;
            }
            if (!is_uint(tokens[2])) {
                cout << "\n\t<y> is not a valid number, retry.\n\n> ";
                process_input();
                return;
            }
            position pos(to_uint(tokens[1]), to_uint(tokens[2]));
            if (!pos.is_inside(map_size)) {
                cout << "\n\tcoordinate are outside the game map, retry.\n\n> ";
                process_input();
                return;
            }
            if (get_mask(pos) == OPEN) {
                cout << "\n\tposition already opened, retry.\n\n> ";
                process_input();
                return;
            }
            open(pos);
            return;
        }
        if (action == "flag") {
            if (!running) {
                cout << "\n\tgame has ended, start a new one.\n\n> ";
                process_input();
                return;
            }
            if (!is_uint(tokens[1])) {
                cout << "\n\t<x> is not a valid number, retry.\n\n> ";
                process_input();
                return;
            }
            if (!is_uint(tokens[2])) {
                cout << "\n\t<y> is not a valid number, retry.\n\n> ";
                process_input();
                return;
            }
            position pos(to_uint(tokens[1]), to_uint(tokens[2]));
            if (!pos.is_inside(map_size)) {
                cout << "\n\tcoordinate are outside the game map, retry.\n\n> ";
                process_input();
                return;
            }
            if (get_mask(pos) == OPEN) {
                cout << "\n\tposition is opened, retry.\n\n> ";
                process_input();
                return;
            }
            flag(pos);
            return;
        }
        if (action == "surrender") {
            end_game(false);
            return;
        }
        cout << "\n\tnot a valid command, retry.\n\n> ";
        process_input();
        return;
    }
        
    void print_instructions() {
        cout << COMMANDS_INFO;
    }

    friend ostream& operator<<(ostream& os, Minesweeper& ms) {
        os << "\n╭───";
        for (int j = 0; j < ms.map_size; j++) {
            os << " " << j << " ";
        }
        os << "───╮\n│" << string(ms.map_size * 3 + 6, ' ') << "│\n";
        for (int i = 0; i < ms.map_size; i++) {
            for (int j = 0; j < ms.map_size; j++) {
                if (j == 0) {
                    os << i << "   ";
                }

                position pos(j, i);
                os << EMOJI_MAP.at((ms.get_mask(pos) == OPEN) ? ms.at(pos) : ms.get_mask(pos));
            }
            os << "   │\n";
        }
        
        os << "│" << string(ms.map_size * 3 + 6, ' ') << "│\n";
        os << "╰───" << string("───") * (ms.map_size) << "───╯";
        return os;
    }
};


int main() {
    for(int i=0; i < 107; i++) {
        cout << "\033[" << i << "m" << i << "\033[0m ";
    }
    cout << "\033[4m\033[53mA\033[0m";
    Minesweeper game(8);
    while (true) {
        cout << game << "\n\n" << game.COMMANDS_INFO;
        game.process_input();

    }
}