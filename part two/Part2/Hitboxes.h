#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>

struct Character {
  std::string name;
  int size;
  Character(std::string s, int sz): name(s), size(sz) { std::cout << "init a character: " << s << " of value: " << sz << std::endl; }
};

class Hitboxes{
  public:
    std::map<std::string, int> map_object;
    std::vector<Character> vector_of_characters;
    // constructor
    Hitboxes(std::string filename){
      std::ifstream myfile;
      myfile.open(filename);
      std::string charname, chartype;
      int width, height;
      while(myfile >> charname >> chartype >> width >> height) {
        int sz = width*height;
        map_object[chartype] += sz;
        vector_of_characters.emplace_back(Character(charname, sz));
      }
    }
    std::string smallest_type(){
      auto smallest = map_object.begin();
      for (auto it=map_object.begin(); it != map_object.end(); it++) {
        if (it->second < smallest->second){ smallest = it; }
      }
      return smallest->first;
    }
  std::string smallestCharacter() {
    size_t smallest = 0;
    for (size_t i=0; i < vector_of_characters.size(); i++) {
      if (vector_of_characters[i].size < vector_of_characters[smallest].size) { smallest = i; }
    }
    return vector_of_characters[smallest].name;
  }
};
