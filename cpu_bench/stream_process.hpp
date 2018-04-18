#pragma once
#include "common.h"
#define ZLIB_WINAPI
#include "zconf.h"
#include "zlib.h"
#include<iostream>
#include "openssl\aes.h"
#include "openssl\sha.h"
class zlib_test
{
public:
	//测试大小，一般100MB
	zlib_test(uLong size);
	~zlib_test();
	//返回压缩/解压缩速度（单位：MB/s）
	double compress();
	double uncompress();

private:
	CStopWatch timer;
	uLong memsize, len, temp, comprLen, uncomprLen, uncomprLen2;
	const char* hello;
	Byte *source, *dest, *uncompr;
};

zlib_test::zlib_test(uLong size):memsize(size),
								 hello("12345678901234567890123456789012345678901234567890")
{
	temp = 0;
	comprLen = memsize;
	uncomprLen = memsize;
	uncomprLen2 = memsize;
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
	uncompr = (Byte *)malloc(memsize);
	if (uncompr == NULL) {
		fprintf(stderr, "Unable to allocate memory \n");
		exit(-1);
	}

	len = strlen(hello) + 1;
	while ((temp += len) <= (memsize - 2 * len))
	{
		memcpy(source + temp, hello, len);
	}
	uncomprLen = temp + len;
}

zlib_test::~zlib_test()
{	
	if (dest != NULL)
	{
		free(dest);
		dest = NULL;
	}
	if (source != NULL)
	{
		free(source);
		source = NULL;
	}
	if (uncompr != NULL)
	{
		free(uncompr);
		uncompr = NULL;
	}
}
double zlib_test::compress()
{
	int err;
	double compress_speed;
	timer.start();
	err = ::compress(dest, &comprLen, (const Bytef*)source, uncomprLen);
	timer.stop();
	compress_speed = (double)(memsize / (1024 * 1024)) / timer.getElapsedTime();

	if (err != Z_OK)
	{
		free(dest);
		free(source);
		free(uncompr);
		std::cerr << "compess error: " << err << '\n';
		exit(1);
	}
	return compress_speed;
}

double zlib_test::uncompress()
{
	double decompress_speed;
	int err;
	timer.start();
	err = ::uncompress(uncompr, &uncomprLen2, dest, comprLen);
	timer.stop();
	decompress_speed = (double)(memsize / (1024 * 1024)) / timer.getElapsedTime();

	if (err != Z_OK) {
		free(dest);
		free(source);
		free(uncompr);

	std:: cerr << "uncompess error: " << err << '\n';

		exit(1);

	}
	return decompress_speed;

}


class crypto_test
{
public:
	//测试大小，一般100MB
	crypto_test(ULONG32 size);
	~crypto_test();
	//返回加密/解密的处理速度（单位：MB/s）
	double aes_encrypto();
	double aes_decrypto();
	double sha_256();

private:
	CStopWatch timer;
	AES_KEY aes;
	unsigned char key[AES_BLOCK_SIZE];        // AES_BLOCK_SIZE = 16  
	unsigned char iv[AES_BLOCK_SIZE];        // init vector  
	unsigned char* input_string;
	unsigned char* encrypt_string;
	unsigned char* decrypt_string;
	ULONG32 memsize;
	ULONG32 temp ;
	const char* argv;

};

crypto_test::crypto_test(ULONG32 size):memsize(size),
									   argv("12345678901234567890123456789012345678901234567890")
{
	int i;
	for (i = 0; i<16; ++i) {
		key[i] = 32 + i;
	}
	
	input_string = (unsigned char*)calloc(memsize, sizeof(unsigned char));
	if (input_string == NULL) {
		fprintf(stderr, "Unable to allocate memory for input_string\n");
		exit(-1);
	}
	encrypt_string = (unsigned char*)calloc(memsize, sizeof(unsigned char));
	if (encrypt_string == NULL) {
		fprintf(stderr, "Unable to allocate memory for encrypt_string\n");
		exit(-1);
	}
	decrypt_string = (unsigned char*)calloc(memsize, sizeof(unsigned char));
	if (decrypt_string == NULL) {

		fprintf(stderr, "Unable to allocate memory for decrypt_string\n");
		exit(-1);
	}

	int len = sizeof(argv);
	while (1)
	{
		memcpy(input_string + temp, argv, len);
		if ((temp += len) >= memsize)
			break;
	}

}

crypto_test::~crypto_test()
{
	if (input_string != NULL)
	{
		free(input_string);
		input_string = NULL;
	}
	if (encrypt_string != NULL)
	{
		free(encrypt_string);
		encrypt_string = NULL;
	}
	if (decrypt_string != NULL)
	{
		free(decrypt_string);
		decrypt_string = NULL;
	}
}

double crypto_test::aes_encrypto()
{
	int i;
	double encrypt_speed;
	for (i = 0; i<AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
	}
	if (AES_set_encrypt_key(key, 128, &aes) < 0) {
		free(input_string);
		fprintf(stderr, "Unable to set encryption key in AES\n");
		exit(-1);
	}
	// encrypt (iv will change)  
	timer.start();

	AES_cbc_encrypt(input_string, encrypt_string, memsize, &aes, iv, AES_ENCRYPT);

	timer.stop();
	encrypt_speed = (double)(memsize / (1024 * 1024)) / timer.getElapsedTime();
	return encrypt_speed;
}
double crypto_test::aes_decrypto()
{
	int i;
	double decrypt_speed;
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

	return decrypt_speed;
}
double crypto_test::sha_256()
{	
	double sha256_speed;
	unsigned char mdstr[33] = { 0 };
	timer.start();
	SHA256(input_string, memsize, mdstr);
	timer.stop();
	sha256_speed = (double)(memsize / (1024 * 1024)) / timer.getElapsedTime();
	return sha256_speed;
}