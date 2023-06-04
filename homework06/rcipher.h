#ifndef VCIPHER_H_
#define VCIPHER_H_
#include "cipher.h"
#include "kcipher.h"

using namespace std;

/* A class that implements a
   Vigenere cipher class. It 
   inherts KCipher */
// TODO: Implement this class

class VCipher: public KCipher{
	protected:
		struct CipherCheshire;
		CipherCheshire *smile;
	private:
		string key;
	public:
		VCipher();
		VCipher(string key);
		~VCipher();
		string encrypt(string raw) override;
		string decrypt(string enc) override;

};

#endif

