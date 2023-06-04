#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// ROT13 Cipher implementation
// -------------------------------------------------------
struct RCipher::CipherCheshire {
  int cipher_alpha;
};


RCipher::RCipher(){
	smile->cipher_alpha = 13;
}

// destructor
RCipher::~RCipher(){
}

string RCipher::encrypt(string raw) {
    cout << "Encrypting..."; 
    rotate_string(raw, smile->cipher_alpha);
    cout << "Done" << endl;
    return raw;
}

string RCipher::decrypt(string enc) {
    cout << "Decrypting..."; 
    rotate_string(enc, 26 - (smile->cipher_alpha % 26));
    cout << "Done" << endl;
    return enc;
}
