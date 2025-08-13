#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;


struct MapTile {
    static int size() { return 2; };
    MapTile(char c = '0') : code(c) {
    }

    char code = '0';
    std::vector<std::vector<char>> data;


    static std::map<char, MapTile> loadJsonData(const std::string& file) {
        std::map<char, MapTile> tiles;
        try {
            std::ifstream inputFile(file);
            if (!inputFile.is_open()) {
                throw std::runtime_error("Could not open file: " + file);
            }
            json j;
            inputFile >> j;

            for (const auto& item : j.items()) {
                char code = item.key()[0];
                MapTile tile(code);
                tile.data = item.value().get<std::vector<std::vector<char>>>();
                tiles[code] = tile;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error loading JSON data: " << e.what() << '\n';
        }
        return tiles;

    }

    static std::map<char, MapTile> createTiles() {
        MapTile a('a');
        a.data = { {'a','a'},{'a','a'} };

        MapTile b('b');
        b.data = { {'b','b'},{'b','b'} };

        MapTile c('c');
        c.data = { {'c','c'},{'c','c'} };

        MapTile d('d');
        d.data = { {'d','d'},{'d','d'} };

        std::map<char, MapTile> tiles = {
          {'a', a},
          {'b', b},
          {'c', c},
          {'d', d}
        };
        return tiles;
    }
};

struct Map {
    std::vector<std::vector<char>> mapPreset;
    std::vector<std::vector<char>> generatedMap;

    void generate(std::map<char, MapTile> tiles) {
        generatedMap.resize(mapPreset.size() * MapTile::size(), std::vector<char>('0'));
        for (size_t i = 0; i < mapPreset.size(); ++i) {
            for (size_t j = 0; j < mapPreset[i].size(); ++j) {
                char tileCode = mapPreset[i][j];
                if (tiles.find(tileCode) != tiles.end()) {
                    const MapTile& tile = tiles[tileCode];
                    for (int ti = 0; ti < MapTile::size(); ++ti) {
                        for (int tj = 0; tj < MapTile::size(); ++tj) {
                            generatedMap[i * MapTile::size() + ti][j * MapTile::size() + tj] = tile.data[ti][tj];
                        }
                    }
                }
            }
        }
    }

    void print() const {
        for (const auto& row : generatedMap) {
            for (char c : row) {
                std::cout << c << ' ';
            }
            std::cout << '\n';
        }
    }
};


int main() {
    std::map<char, MapTile> tiles = MapTile::createTiles();
    Map map;
    map.mapPreset = {
      {'a', 'b'},
      {'c', 'd'}
    };
    map.generate(tiles);
    map.print();
    return 0;
}