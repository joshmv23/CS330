#include "cipher.h"

/* Cheshire smile implementation.
   It only contains the cipher alphabet
 */
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

/* This function checks the cipher alphabet
   to make sure it's valid
 */
bool is_valid_alpha(string alpha);


// -------------------------------------------------------
// Cipher implementation
/* Default constructor
   This will actually not encrypt the input text
   because it's using the unscrambled alphabet
 */
Cipher::Cipher()
{
    // TODO: Implement this default constructor
    smile = new CipherCheshire;
    smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz"; 
}
//
/* This constructor initiates the object with a
   input cipher key
 */
Cipher::Cipher(string cipher_alpha)
{
    // TODO: Implement this constructor
    if(is_valid_alpha(cipher_alpha)){
	    smile = new CipherCheshire;
	    smile->cipher_alpha = cipher_alpha;
    } else {
	   cout << "Invalid cipher alphabet/key: " << cipher_alpha << endl;
	   exit(EXIT_FAILURE);
    } 
}

/* Destructor
 */
Cipher::~Cipher()
{
    // TODO: Implement this constructor
    delete smile;
}

/* This member function encrypts the input text 
   using the intialized cipher key
 */
string Cipher::encrypt(string raw)
{
    cout << "Encrypting...";
    string retStr;
    string orig_alphabet = "abcdefghijklmnopqrstuvwxyz";
    // TODO: Finish this function
    for(unsigned int i = 0; i < raw.length(); i++){
	    //cases when we have a space
	    if(raw[i] == ' '){
		    retStr.push_back(' '); //push back appends the give argument to the string/vector
		    continue;
	    }
	    
	    unsigned int j = find_pos(orig_alphabet, LOWER_CASE(raw[i])); //make letter lowercase and get its index
	   char newChar = smile->cipher_alpha[j]; //encrypted letter

	   if('A' <= raw[i] && raw[i] <= 'Z'){ //if letter was originally uppercase make the encrpyted uppercase so it's easier to decrypt 
		   newChar = UPPER_CASE(newChar);
	   }
	   retStr.push_back(newChar);
    }

    cout << "Done" << endl;

    return retStr;
}


/* This member function decrypts the input text 
   using the intialized cipher key
 */
string Cipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrypting...";
    string orig_alphabet = "abcdefghijklmnopqrstuvwxyz";
    // TODO: Finish this function
    for(unsigned int i = 0; i < enc.length(); i++){
            //cases when we have a space
            if(enc[i] == ' '){
                    retStr.push_back(' '); //push back appends the give argument to the string/vector
                    continue;
            }
            unsigned int j = find_pos(smile->cipher_alpha, LOWER_CASE(enc[i])); //make letter lowercase and get its index
           char oldChar = orig_alphabet[j]; //original letter
           if('A' <= enc[i] && enc[i] <= 'Z'){ //if letter was originally uppercase make the encrpyted uppercase so it's easier to decrypt
                   oldChar = UPPER_CASE(oldChar);
           }
           retStr.push_back(oldChar);
    }


    cout << "Done" << endl;

    return retStr;

}
// -------------------------------------------------------


//  Helper functions 
/* Find the character c's position in the cipher alphabet/key
 */
unsigned int find_pos(string alpha, char c)
{
    unsigned int pos = 0;

    // TODO: You will likely need this function. Finish it.
    int size = (int)ALPHABET_SIZE;
    for(int i = 0; i < size; i++){
        if(alpha[i] == c){
            pos = i;
            break;
        }
    }
    return pos;
}

/* Make sure the cipher alphabet is valid - 
   a) it must contain every letter in the alphabet 
   b) it must contain only one of each letter 
   c) it must be all lower case letters 
   ALL of the above conditions must be met for the text to be a valid
   cipher alphabet.
 */
bool is_valid_alpha(string alpha)
{
    bool is_valid = true;
    if(alpha.size() != ALPHABET_SIZE) {
        is_valid = false; 
    } else {
        unsigned int letter_exists[ALPHABET_SIZE];
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            letter_exists[i] = 0;
        }
        for(unsigned int i = 0; i < alpha.size(); i++) {
            char c = alpha[i];
            if(!((c >= 'a') && (c <= 'z'))) {
                is_valid = false;
            } else {
                letter_exists[(c - 'a')]++;
            }
        }
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            if(letter_exists[i] != 1) {
                is_valid = false;
            }
        }
    }

    return is_valid;
}
