#ifndef UTILS_H
#define UTILS_H
#include <string>

struct Config {
    bool visible;
    int prop_time;
    int end_score;
    std::string map_path;
    Config(bool visible_=false,int prop_time_=10,int end_score_=1,std::string map_path_="") {
        visible = visible_;
        prop_time = prop_time_;
        end_score = end_score_;
        map_path = map_path_;
    }
};

struct Main_Score {
    int player_1_score;
    int player_2_score;
    int end_require_score;
    Main_Score(int end_require_score_=1) : player_1_score(0),player_2_score(0),end_require_score(end_require_score_) {}
    
    void reset() {
        player_1_score = 0;
        player_2_score = 0;
    }

    void reset(int end_require_score_) {
        player_1_score = 0;
        player_2_score = 0;
        end_require_score = end_require_score_;
    }

    bool end() { return (player_1_score >= end_require_score) || (player_2_score >= end_require_score); };
    int winner() {
        if(player_1_score >= end_require_score) {
            return 1;
        }
        else if(player_2_score >= end_require_score) {
            return 2;
        }
        return 0;
    }

    bool add_score(int player_id) {
        if(player_id == 1)  player_1_score++;
        else if(player_id == 2)  player_2_score++;
        return end();
    }

};

#endif // UTILS_H