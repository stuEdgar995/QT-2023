#ifndef CONFIG_H
#define CONFIG_H
#include <string>

struct Config {
    bool visible;
    int pro_time;
    std::string map_path;
    Config(bool visible_=false,int pro_time_=0,std::string map_path_="") {
        visible = visible_;
        pro_time = pro_time_;
        map_path = map_path_;
    }
};
#endif // CONFIG_H