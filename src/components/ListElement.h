#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include <string>

#include "ScrollableElement.h"
#include "TextElement.h"

using namespace std;

namespace ld
{

struct ListElement : public ScrollableElement
{
  ListElement() = default;

  std::vector<TextElement> text_elements;
};

}

#endif /* LISTELEMENT_H */
