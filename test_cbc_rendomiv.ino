/*------------------------------------------------------------------------------ 
Program:      aesEncDec 
  
Description:  Basic setup to test AES CBC encryption/decryption using different 
              key lengths.
  
Hardware:     Arduino Uno R3 
  
Software:     Developed using Arduino 1.8.2 IDE
  
Libraries:    
              - AES Encryption Library for Arduino and Raspberry Pi: 
                https://spaniakos.github.io/AES/index.html
  
References: 
              - Advanced Encryption Standard by Example: 
              http://www.adamberent.com/wp-content/uploads/2019/02/AESbyExample.pdf
              - AES Class Reference: https://spaniakos.github.io/AES/classAES.html
  
Date:          2023/01/30
  
Author:       G. Gainaru, https://www.arduinolab.net
              (based on AES library documentation and examples)
------------------------------------------------------------------------------*/
#include "AES.h"
 
AES aes ;
 
unsigned int keyLength [3] = {128, 192, 256}; // key length: 128b, 192b or 256b

byte *key = (unsigned char*)"abcdefghijklmnop"; // encryption key
byte plain[] = "1"; // plaintext to encrypt
byte iv [N_BLOCK];
int plainLength = sizeof(plain)-1;
//    unsigned long long int myIv = random(10000000,100000000);

unsigned long long int myIv = 36753562; // CBC initialization vector; real iv = iv x2 ex: 01234567 = 0123456701234567
 
void setup () {
    Serial.begin(115200);
    aes.set_IV(myIv);
    aes.get_IV(iv);
}
 
void loop () {
//    for (int i=0; i < 3; i++) {
        Serial.print("- key length [0]: ");
        Serial.println(keyLength [0]);
        aesTest (keyLength[0]);
        delay(2000);
//    }
}
 
void aesTest (int bits) {

//    aes.iv_inc();
    
    int plainPaddedLength = plainLength + N_BLOCK - plainLength % N_BLOCK; // length of padded plaintext [B]
    byte cipher [plainPaddedLength]; // ciphertext (encrypted plaintext)
    byte check [plainPaddedLength]; // decrypted plaintext
    
    
    printf("- iv:      ");
    aes.printArray(iv,16); //print iv
//    Serial.print("- encryption time [us]: ");
//    unsigned long ms = micros ();


    printf("plainPaddedLength : %d \n",plainPaddedLength);
    printf("N_BLOCK : %d \n",N_BLOCK);
    aes.do_aes_encrypt(plain, plainLength, cipher, key, bits, iv);

    
//    Serial.println(micros() - ms);
    
    printf("(after)plainLength : %d \n",plainLength);
    
//    Serial.print("- decryption time [us]: ");
//    ms = micros ();
    
    printf("get_size() / N_BLOCK : %d \n",aes.get_size() / N_BLOCK);
    printf("- aes.get_size(): %d \n ",aes.get_size());
    printf("- iv:      ");
    aes.printArray(iv,16); //print iv
    
    aes.do_aes_decrypt(cipher,aes.get_size(),check,key,bits,iv); 
//    Serial.println(micros() - ms);
    
    printf("cipher : ");
    aes.printArray(cipher,plainPaddedLength); //print cipher with padding

    printf("- plain:   ");
    aes.printArray(plain,(bool)true); //print plain with no padding

    printf("- check: : ");
    aes.printArray(check,(bool)true); //print decrypted plain with no padding

    printf("- iv:      ");
    aes.printArray(iv,16); //print iv
    
    
    printf("\n-----------------------------------------------------------------------------------\n");
}
