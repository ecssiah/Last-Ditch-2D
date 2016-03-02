#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include <string>

using namespace std;

namespace ld
{

struct ListElement
{
  ListElement()
    : string(std::string()),
      texture(std::string())
  {}

  ListElement(std::string _string, std::string _texture)
    : string(_string),
      texture(_texture)
  {}

  std::string string;
  std::string texture;
};

}

#endif /* LISTELEMENT_H */
