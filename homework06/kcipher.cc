#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include <algorithm>



/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

struct KCipher::CipherCheshire {
    string cipher_alpha; //cipher_alpha represents page in the book
};

KCipher::KCipher() {
    smile = new CipherCheshire;
    smile->cipher_alpha = std::string(MAX_LENGTH, 'a');
    add_key(smile->cipher_alpha);
    set_id(0);
}
KCipher::KCipher(string key) : Cipher() {
    smile = new CipherCheshire;
    smile->cipher_alpha = key;
    add_key(smile->cipher_alpha);
}
KCipher::~KCipher() {
    delete smile;
}
string KCipher::encrypt(std::string raw) {
    cout << "Encrypting..."; 
    string cipher = "";
    string::const_iterator i, j; // string iterators
    for (i = smile->cipher_alpha.begin(), j = raw.begin(); j < raw.end() && i < smile->cipher_alpha.end();) {
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        if (*i == ' ') {
            i++;
            continue;
        } else if (*j == ' ') {
            cipher.push_back(' ');
            j++;
            continue;
        }
        char plaintextChar = *j;
        int pos = find_pos(alphabet, tolower(plaintextChar));
        rotate_string(alphabet, *i - 'a'); // Rotate the key based on the position in the alphabet
        if (*j >= 'A' && *j <= 'Z') { // If the letter was originally uppercase, make the encrypted letter uppercase as well
            cipher.push_back(toupper(alphabet[pos]));
        } else {
            cipher.push_back(tolower(alphabet[pos]));
        }
        i++;
        j++;
    }
    cout << "Done" << endl;
    return cipher;
}
std::string KCipher::decrypt(string enc) {
    cout << "Decrypting..."; 
    string decrypted = "";
    string::const_iterator i, j; // string iterators
    for (i = smile->cipher_alpha.begin(), j = enc.begin(); j < enc.end() && i < smile->cipher_alpha.end();) {
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        if (*i == ' ') {
            i++;
            continue;
        } else if (*j == ' ') {
            decrypted.push_back(' ');
            j++;
            continue;
        }
        int pos = find_pos(alphabet, tolower(*j));
        rotate_string(alphabet, 26 - (*i - 'a')); // Rotate the key based on the position in the alphabet
        if (*j >= 'A' && *j <= 'Z') { // Check if the character was originally uppercase
            decrypted.push_back(toupper(alphabet[pos]));
        } else {
            decrypted.push_back(alphabet[pos]);
        }
        i++;
        j++;
    }
    cout << "Done" << endl;
    return decrypted;
}
void KCipher::add_key(string key) {
    if (key.length() == 0){
	cout << "Invalid Running key: " << key << endl;
        exit(EXIT_FAILURE);
    }
    for (char c : key) {
        if (!isalpha(c) && c != ' '){
            cout << "Invalid Running key: " << key << endl;
            exit(EXIT_FAILURE);
	}
    }
    this->key.push_back(key);
    smile->cipher_alpha = key;
}
void KCipher::set_id(unsigned int tempid) {
    if (tempid < key.size()) {
        id = tempid;
        smile->cipher_alpha = key[id];
    } else {
	cout << "Warning: invalid id: " << tempid << endl;
        exit(EXIT_FAILURE);
    }
}
