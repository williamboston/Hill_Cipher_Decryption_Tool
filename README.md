# Hill_Cipher_Decryption_Tool

A limited scope Hill Cipher Decrypter to complement the Hill Encrypter I made.

To Use:
  - By some means obtain two suspect ciphertext bigrams and their corresponding plaintext bigrams.
  - Input whole ciphertext as argv (no need to worry about spaces)
  - Input supposed bigrams
  - If invertible, ouput will be written to terminal
  - If not invertible, output will be garbage and bigrams need to be reselected

Notes:
  - Currently only decrypts modulo 27. This can be changed at the #define MOD.
  - Assumes bigram frequency analysis has been performed on ciphertext to determine possible bigrams
  - Non invertible matricies will still produce output, please note it will be garbage!
  - Ideally works in tandem with the 27 char alphabet as used in the Simple C Encrypter in another repo
  - If you did need to decrypt 26 char cipher, just alter the #define MOD, remove the spaces (if needed) and run using known bigrams
