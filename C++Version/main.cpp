#include<iostream>
#include<map>
#include <vector>
#include<functional>
#include<set>
#define pb emplace_back
using namespace std;

// current standings
// upcoming games
// So ties after final standings
map<string, int> playoffs;
vector<pair<string, string>> games;
int total = 0;
map<string, int> wins;
map <set <string>, int> draw;
void init_wins() {
    wins["MAD"] = 12;
    wins["RGE"] = 11;
    wins["G2"] = 9;
    wins["SK"] = 9;
    wins["XL"] = 8;
    wins["FNC"] = 8;
    wins["VIT"] = 7;
    wins["MSF"] = 6;
    wins["OG"] = 6;
    wins["S04"] = 7;
}

void init_games() {
    //games.pb("VIT", "RGE");
    //games.pb("OG", "XL");
    //games.pb("FNC", "S04");
    //games.pb("MSF", "MAD");
    //games.pb("G2", "SK");
    //games.pb("VIT", "S04");
    //games.pb("OG", "SK");
    //games.pb("FNC", "XL");
    games.pb("MSF", "G2");
    games.pb("MAD", "RGE");
    games.pb("VIT", "MSF");
    games.pb("MAD", "S04");
    games.pb("RGE", "OG");
    games.pb("G2", "XL");
    games.pb("FNC", "SK");
}


void fix_ties(map<string, int> wins) {
    vector<pair<int, string>> standings;
    total++;
    for (auto team : wins) {
        standings.emplace_back(team.second, team.first);
    }
    sort(standings.rbegin(), standings.rend());
    int tie_games = standings[5].first;
    cout << tie_games << " " << wins["SK"] << endl;
    set <string> draws;
    for (auto & standing : standings) {
        if (standing.first >= tie_games)
            playoffs[standing.second]++;
        if(standing.first == tie_games){
            draws.insert(standing.second);
        }
    }
    draw[draws]++;
}


void simulate(int game_no, map<string, int> winsz) {
    if (game_no == games.size()) {
        fix_ties(winsz);
        return;
    }
    winsz[games[game_no].first]++;
    simulate(game_no + 1, winsz);
    winsz[games[game_no].first]--;
    winsz[games[game_no].second]++;
    simulate(game_no + 1, winsz);
}

int main() {
    init_wins();
    init_games();
    simulate(0, wins);
    cout << total << endl;
    cout << games.size() << endl;
    vector<pair<string, int>> playoffs2;
    playoffs2.reserve(10);
    for (const auto &team : playoffs) {
        playoffs2.emplace_back(team.first, team.second);
    }
    sort(playoffs2.begin(), playoffs2.end(), [](const pair<string, int> a, const pair<string, int> b) {
        return a.second > b.second;
    });
    for (const auto &team : playoffs2) {
        cout << team.first << " " << team.second << " " << 1.0 * team.second / total * 100 << endl;
    }
    cout << " ******* Draws ******* " << endl;
    for(auto & a_draw : draw){
        if(a_draw.first.size() <= 1){
            continue;
        }
        for(auto & team : a_draw.first) {
            cout << team << " ";
        }
        cout << 1.0 * a_draw.second / total * 100 << endl;
    }
}
