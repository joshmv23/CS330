#ifndef RCIPHER_H_ 
#define RCIPHER_H_
#include "ccipher.h"

using namespace std;

/* A class that implements a
   ROT13 cipher class. It 
   inherts class CCipher */
// TODO: Implement this class
class RCipher: public CCipher{
public:
   RCipher();
   ~RCipher();
   string encrypt(string raw) override;
   string decrypt(string enc) override;
};

void rotate_string(string& in_str, int rot);
#endif



