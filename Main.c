#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

void print_usage() {
    printf("Usage: ./encrypt_decrypt <encrypt/decrypt> <method> <input_file> <output_file>\n");
    printf("Methods: xor, aes\n");
}

void read_file(const char *filename, unsigned char **buffer, size_t *length) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *buffer = (unsigned char *)malloc(*length);
    fread(*buffer, 1, *length, file);
    fclose(file);
}

void write_file(const char *filename, unsigned char *buffer, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    fwrite(buffer, 1, length, file);
    fclose(file);
}

void xor_encrypt_decrypt(unsigned char *data, size_t length, unsigned char key) {
    for (size_t i = 0; i < length; ++i) {
        data[i] ^= key;
    }
}

void aes_encrypt(unsigned char *input, unsigned char *output, size_t length, unsigned char *key) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_encrypt(input, output, &enc_key);
}

void aes_decrypt(unsigned char *input, unsigned char *output, size_t length, unsigned char *key) {
    AES_KEY dec_key;
    AES_set_decrypt_key(key, 128, &dec_key);
    AES_decrypt(input, output, &dec_key);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        print_usage();
        return 1;
    }

    char *operation = argv[1];
    char *method = argv[2];
    char *input_file = argv[3];
    char *output_file = argv[4];

    if ((strcmp(operation, "encrypt") != 0 && strcmp(operation, "decrypt") != 0) ||
        (strcmp(method, "xor") != 0 && strcmp(method, "aes") != 0)) {
        print_usage();
        return 1;
    }

    unsigned char *buffer;
    size_t length;
    read_file(input_file, &buffer, &length);

    if (strcmp(method, "xor") == 0) {
        unsigned char key = 0xAA; // Example key
        xor_encrypt_decrypt(buffer, length, key);
    } else if (strcmp(method, "aes") == 0) {
        unsigned char key[16] = "examplekey123456"; // Example key
        unsigned char *output_buffer = (unsigned char *)malloc(length);

        if (strcmp(operation, "encrypt") == 0) {
            aes_encrypt(buffer, output_buffer, length, key);
        } else {
            aes_decrypt(buffer, output_buffer, length, key);
        }

        free(buffer);
        buffer = output_buffer;
    }

    write_file(output_file, buffer, length);
    free(buffer);

    printf("Operation %s with method %s completed.\n", operation, method);
    return 0;
}
