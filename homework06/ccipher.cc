#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation
//constructors and destructor

struct CCipher::CipherCheshire {
    int cipher_alpha;
};


CCipher::CCipher(){
	smile = new CipherCheshire;
	smile->cipher_alpha = 0;
}


CCipher::CCipher(int offset){
	if(offset >= 0){
		smile = new CipherCheshire;
		smile->cipher_alpha = offset;
	} else {
		cout << "Error: Caesar cipher is less than 0" << endl;
		exit(EXIT_FAILURE);
	}
}



CCipher::~CCipher(){
	delete smile;
}

string CCipher::encrypt(string raw){ //encrypt
	cout << "Encrypting..."; 
	rotate_string(raw, smile->cipher_alpha);
	cout << "Done" << endl;
	return raw;
}

string CCipher::decrypt(string enc){ //decrypt
	cout << "Decrypting..."; 
	rotate_string(enc, 26 - (smile->cipher_alpha % 26));
	cout << "Done" << endl;
	return enc;
}

// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.
   int n =  in_str.length();
    for(int i = 0; i < n; i++) {
        if (isupper(in_str[i])) {
	   in_str[i] = char(int(in_str[i] + rot - 'A') % 26 + 'A');
	} else if (islower(in_str[i])){
		in_str[i] = char(int(in_str[i] + rot - 'a') % 26 + 'a');
	}
    }
}

