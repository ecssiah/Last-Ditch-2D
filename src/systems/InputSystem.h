#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "../components/Input.h"

namespace ld
{

class InputSystem
{
  void left_click(Sint32 mx, Sint32 my);

  Input& input;

public:
  InputSystem(Input& input);

  void update();
};

}


#endif /* INPUTSYSTEM_H */
