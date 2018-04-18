// cpu_bench.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<iostream>
#include <conio.h>
#include "cpu_queen.hpp"
#include "julia_mandel.hpp"
#include "stream_process.hpp"
int main()
{/*
	double time;
//	cpu_queen queen_test;
//	double time = queen_test.runtest();
	julia_mandel ju_man(1024,1024);
//	time=ju_man.julia_test();
	time = ju_man.mandel_test();
	cout << "time is " << time << '\n' << endl;
	_getch();
	*/
	/*
	CStopWatch timer;
	double compress_time, decompress_time;
	uLong memsize = 100 * 1024 * 1024;
	uLong temp = 0;
	int err;
	Byte *source, *dest, *uncompr;
	source = (Byte *)malloc(memsize);
	if (source == NULL) {
		fprintf(stderr, "Unable to allocate memory \n");
		exit(-1);
	}
	dest = (Byte *)malloc(memsize);
	if (dest == NULL) {
		fprintf(stderr, "Unable to allocate memory \n");
		exit(-1);
	}
	uncompr = (Byte *)malloc(memsize );
	if (uncompr == NULL) {
		fprintf(stderr, "Unable to allocate memory \n");
		exit(-1);
	}

	uLong comprLen=memsize, uncomprLen, uncomprLen2=memsize;

	const char* hello = "12345678901234567890123456789012345678901234567890";

	uLong len = strlen(hello) + 1;

	while ((temp += len) <= (memsize - 2 * len))
	{
		memcpy(source + temp, hello, len);
		memcpy(uncompr + temp, hello, len);
	}
	uncomprLen = temp + len;

	timer.start();
	err = compress(dest, &comprLen, (const Bytef*)source, uncomprLen);
	timer.stop();
	compress_time = timer.getElapsedTime();

	if (err != Z_OK)
	{
		free(dest);
		free(source);
		free(uncompr);
		cerr << "compess error: " << err << '\n';
		exit(1);
	}
	cout << "orignal size: " << uncomprLen << " , compressed size : " << comprLen << '\n' << "compress_time:" << compress_time << '\n';

	
	timer.start();
	err = uncompress(uncompr, &uncomprLen2, dest, comprLen);
	timer.stop();
	decompress_time = timer.getElapsedTime();
	
	if (err != Z_OK) {
		free(dest);
		free(source);
		free(uncompr);

		cerr << "uncompess error: " << err << '\n';

		exit(1);

	}
	
	if (strcmp((char*)uncompr, (char*)source)) {

		cerr << "BAD uncompress!!!\n";

		exit(1);

	}
	else {

		cout << "uncompress() succeed: \n"
			<< "decompress_time:" << decompress_time << '\n';

	}
	free(dest);
	free(source);
	free(uncompr);
	Sleep(5000);
	*/
	/*
	AES_KEY aes;
	unsigned char key[AES_BLOCK_SIZE];        // AES_BLOCK_SIZE = 16  
	unsigned char iv[AES_BLOCK_SIZE];        // init vector  
	unsigned char* input_string;
	unsigned char* encrypt_string;
	unsigned char* decrypt_string;
	ULONG32 memsize = 100 * 1024 * 1024;
	ULONG32 temp = 0;
	double  encrypt_speed, decrypt_speed, sha256_speed;
	CStopWatch timer;

	unsigned int len;        // encrypt length (in multiple of AES_BLOCK_SIZE)  
	unsigned int i = 0;

	const char* argv = "12345678901234567890123456789012345678901234567890";
	// set the encryption length  
	len = sizeof(argv);
	// set the input string  
	input_string = (unsigned char*)calloc(memsize, sizeof(unsigned char));
	if (input_string == NULL) {
		fprintf(stderr, "Unable to allocate memory for input_string\n");
		exit(-1);
	}

	while (1)
	{
		memcpy(input_string + temp, argv, len);
		if ((temp += len) >= memsize)
			break;
	}

	// Generate AES 128-bit key  
	for (i = 0; i<16; ++i) {
		key[i] = 32 + i;
	}

	// Set encryption key  
	for (i = 0; i<AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
	}
	if (AES_set_encrypt_key(key, 128, &aes) < 0) {
		free(input_string);
		fprintf(stderr, "Unable to set encryption key in AES\n");
		exit(-1);
	}

	// alloc encrypt_string  
	encrypt_string = (unsigned char*)calloc(memsize, sizeof(unsigned char));
	if (encrypt_string == NULL) {
		fprintf(stderr, "Unable to allocate memory for encrypt_string\n");
		exit(-1);
	}

	// encrypt (iv will change)  
	timer.start();

	AES_cbc_encrypt(input_string, encrypt_string, memsize, &aes, iv, AES_ENCRYPT);

	timer.stop();
	encrypt_speed = (double)(memsize / (1024 * 1024)) / timer.getElapsedTime();
	// alloc decrypt_string  
	decrypt_string = (unsigned char*)calloc(memsize, sizeof(unsigned char));
	if (decrypt_string == NULL) {

		fprintf(stderr, "Unable to allocate memory for decrypt_string\n");
		exit(-1);
	}

	// Set decryption key  
	for (i = 0; i<AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
	}
	if (AES_set_decrypt_key(key, 128, &aes) < 0) {
		fprintf(stderr, "Unable to set decryption key in AES\n");
		exit(-1);
	}

	// decrypt  
	timer.start();
	AES_cbc_encrypt(encrypt_string, decrypt_string, memsize, &aes, iv, AES_DECRYPT);
	timer.stop();

	decrypt_speed = (double)(memsize / (1024 * 1024)) / timer.getElapsedTime();
	printf("encrytp_speed=%f\n decrytp_speed=%f \n", encrypt_speed, decrypt_speed);
	free(encrypt_string);
	free(decrypt_string);

	unsigned char mdstr[33] = { 0 };
	timer.start();
	SHA256(input_string, memsize, mdstr);
	timer.stop();
	sha256_speed = (double)(memsize / (1024 * 1024)) / timer.getElapsedTime();
	free(input_string);
	printf("sha256_speed=%f\n ", sha256_speed);
	return 0;
	*/
double time,time2,time3;
// zlib_test test(100*1024*1024);
crypto_test cry_test(100*1024*1024);
time = cry_test.aes_decrypto();
time2 = cry_test.aes_encrypto();
time3 = cry_test.sha_256();
cry_test.~crypto_test();
 printf("%f\n",time);
 printf("%f\n", time2);
 printf("%f\n", time3);
 Sleep(5000);

}

