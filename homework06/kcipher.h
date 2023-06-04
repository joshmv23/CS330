#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
// TODO: Implement this function
class KCipher : public Cipher {
 protected:
    struct CipherCheshire;
    CipherCheshire *smile;
private:
    vector<string> key;
    unsigned int id;

public:
    KCipher();
    KCipher(string key);
    ~KCipher();

    string encrypt(string raw) override;
    string decrypt(string enc) override;
    void add_key(string key);
    void set_id(unsigned int id);
};
unsigned int find_pos(string alpha, char c);
void rotate_string(string& in_str, int rot);          
#endif
