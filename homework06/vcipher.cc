#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

struct VCipher::CipherCheshire{
	string cipher_alpha;
};

VCipher::VCipher() : KCipher() {
	smile = new CipherCheshire;
	smile->cipher_alpha = string(100, 'a');
	add_key(smile->cipher_alpha);
}

VCipher::VCipher(string key) : KCipher(){
    if (key.length() == 0) {
        cout << "Error: not a valid Vigenere key word" << endl;
        exit(EXIT_FAILURE);
    }
    for (char c : key) {
        if (!islower(c)) {
            cout << "Error: not a valid Vigenere key word" << endl;
            exit(EXIT_FAILURE);
        }
    }
    smile = new CipherCheshire;
    smile->cipher_alpha = key;
    add_key(smile->cipher_alpha);
}

VCipher::~VCipher() {
	delete smile;
}

string VCipher::encrypt(string raw) {
    cout << "Encrypting..."; 
    string encryptedText = "";
    int keyLength = smile->cipher_alpha.length();
    int index = 0;
    
    for (char c : raw) {
        if (!isalpha(c)) {
            encryptedText += c;
            continue;
        }

        char currentKeyChar = smile->cipher_alpha[index % keyLength];
        int shift = currentKeyChar - 'a';

        if (islower(c)) {
            encryptedText += (c - 'a' + shift) % 26 + 'a';
        }else {
            encryptedText += (c - 'A' +  shift) % 26 + 'A';
        }

        index++;
    }
    cout << "Done" << endl;
    return encryptedText;
}

string VCipher::decrypt(string enc) {
    cout << "Decrypting..."; 
    string decryptedText = "";
    int keyLength = smile->cipher_alpha.length();
    int index = 0;

    for (char c : enc) {
        if (!isalpha(c)) {
            decryptedText += c;
            continue;
        }

        char currentKeyChar = smile->cipher_alpha[index % keyLength];
        int shift = currentKeyChar - 'a';

        if (islower(c)) {
            decryptedText += (c - 'a' - shift + 26) % 26 + 'a';
        } else {
            decryptedText += (c - 'A' - shift + 26) % 26 + 'A';
        }

        index++;
    }
    cout << "Done" << endl;
    return decryptedText;
}
