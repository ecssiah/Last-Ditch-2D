#ifndef WINDOW_H
#define WINDOW_H

#include "Scalable.h"
#include "Text.h"

namespace ld
{

struct Window : public Scalable
{
  Window() = default;

  Text title;
};

}

#endif /* WINDOW_H */
