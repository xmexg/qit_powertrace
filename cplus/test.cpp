#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "./cpp-httplib/httplib.h"
#include "./urltil.cpp"

using namespace std;
using json = nlohmann::json;

/**
 * 测试获取全部校区全部用电
 */

// 将 JSON 响应解析为 vector<string>
vector<string> parseJsonArray(const string& json_str) {
    vector<string> result;
    try {
        json j = json::parse(json_str);
        if (j.is_array()) {
            for (const auto& item : j) {
                result.push_back(item.get<string>());
            }
        }
    } catch (const json::parse_error& e) {
        cout << "JSON Parse Error: " << e.what() << endl;
    }
    return result;
}

int main() {
    
    // 写入文件,文件名是xxxx年xx月xx日xx时xx分.txt
    FILE *fp;
    char filename[100];
    time_t now = time(0);
    tm *ltm = localtime(&now);
    sprintf(filename, "%d_%d_%d-%d_%d.txt", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min);
    fp = fopen(filename , "a");

    httplib::Client cli("http://dkdj.qlit.edu.cn:9901");

    // 获取校区信息
    auto area_res = cli.Get("/api/getArea");
    if (!area_res) {
        cout << "Cannot get Area" << endl;
        return 1;
    }
    cout << "Area response: " << area_res->body << endl;
    vector<string> area_data = parseJsonArray(area_res->body);  // 解析校区列表

    for (string& area : area_data) {
        cout << ">>> Area: " << area << endl;

        // 获取楼栋信息
        auto building_res = cli.Get("/api/getBuilding?xiaoqu=" + urlEncode(area));
        if (!building_res) {
            cout << "Cannot get Building" << endl;
            continue;
        }
        vector<string> building_data = parseJsonArray(building_res->body);

        for (string& building : building_data) {
            cout << ">>>> Building: " << building << endl;

            // 获取房间信息
            auto room_res = cli.Get("/api/getRoom?xiaoqu=" + urlEncode(area) + "&loudong=" + urlEncode(building));
            if (!room_res) {
                cout << "Cannot get Room" << endl;
                continue;
            }
            vector<string> room_data = parseJsonArray(room_res->body);

            for (string& room : room_data) {
                // cout << ">>>>> Room: " << room << endl;

                // 获取剩余电量信息
                auto sydl_res = cli.Get("/api/getSydl?xiaoqu=" + urlEncode(area) + "&loudong=" + urlEncode(building) + "&room=" + urlEncode(room));
                if (!sydl_res) {
                    cout << "Cannot get Sydl" << endl;
                    continue;
                }
                cout << ">>>>> 校区: " << area << "  楼栋: " << building << "  Room: " << room << "  电量: " << sydl_res->body << endl;
                fprintf(fp, ">>>>> 校区: %s  楼栋: %s  Room: %s  电量: %s\n", area.c_str(), building.c_str(), room.c_str(), sydl_res->body.c_str());
            }
        }
    }
    // 关闭文件
    fclose(fp);
    return 0;
}
