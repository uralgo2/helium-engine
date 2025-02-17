//
// Created by uralg on 16.02.2025.
//

#ifndef INPUT_HPP
#define INPUT_HPP
#include <GLFW/glfw3.h>
namespace He::App::Input {
enum class Keys {
  		Unknown,
  		A,
  		W,
  		S,
  		D,
		P,
		C,
  		Space,
		LeftShift,
		Escape
	};
	const char* GetKeyName(Keys key);
	Keys GLFW3KeyMap(int key);

     struct KeyModifiers {
     	bool Shift:1;
        bool Control:1;
        bool Alt:1;
        bool Super:1;
        bool CapsLock:1;
        bool NumLock:1;
        bool Repeat:1;
     };
}
#endif //INPUT_HPP
