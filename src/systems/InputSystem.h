#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "../components/Input.h"

namespace ld
{

class InputSystem
{
  Input& input;

public:
  InputSystem(Input& input);

  void update();
};

}


#endif /* INPUTSYSTEM_H */
