#ifndef _input_h_
#define _input_h_

#include <GL/glut.h>

//Translaet glut key-constant names to our own independent names
#define C_KEY(id) KEY_##id = GLUT_KEY_##id
enum InputKeyNums{
  C_KEY(UP),
  C_KEY(DOWN),
  C_KEY(LEFT),
  C_KEY(RIGHT),
  C_KEY(PAGE_UP), 
  C_KEY(PAGE_DOWN), 
  C_KEY(HOME), 
  C_KEY(END), 
  C_KEY(INSERT), 
  C_KEY(F1), 
  C_KEY(F2), 
  C_KEY(F3), 
  C_KEY(F4), 
  C_KEY(F5), 
  C_KEY(F6), 
  C_KEY(F7), 
  C_KEY(F8), 
  C_KEY(F9), 
  C_KEY(F10), 
  C_KEY(F11), 
  C_KEY(F12), 
};

//En klass för att ta reda på tangentbordstryckningar och dylikt
class Input{
 protected:
  static bool keys[256];

 public:
  static bool key(unsigned char k){return keys[k];};
};

//En klass som ser till att ställa in värdet på datan i Input
class InputControl: public Input{
 public:
  static inline void setKey(unsigned char k, bool v){keys[k] = v;};
  static void resetKeys(){
    //Återställer alla knappar
    for (int i = 0; i < 256; i++){
      keys[i] = 0;
    }
  };
};


#endif
