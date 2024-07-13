Compilation
Compile the program with OpenSSL libraries:

gcc -o encrypt_decrypt encrypt_decrypt.c -lssl -lcrypto

Encrypting and decrypting with XOR:

/encrypt_decrypt encrypt xor input.txt output.txt
/encrypt_decrypt decrypt xor output.txt decrypted.txt

Encrypting and decrypting with AES:

/encrypt_decrypt encrypt aes input.txt output.txt
/encrypt_decrypt decrypt aes output.txt decrypted.txt


This complete program includes reading and writing files, handling command-line arguments,
and performing encryption and decryption using XOR and AES methods.
