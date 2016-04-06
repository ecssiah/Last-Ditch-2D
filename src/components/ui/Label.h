#ifndef LABEL_H
#define LABEL_H

#include "Scalable.h"
#include "Text.h"

namespace ld
{

struct Label : public Scalable
{
  Label()
    : text()
  {}

  Text text;
};

}

#endif /* LABEL_H */
