#ifndef MD5_H //该头文件用于进行数据的加密
#define MD5_H //该头文件与源文件的独立性较强
//以下是MD5头文件的声明部分（写得很工整 但是我对原理不是很明白）
//但是该说不说 非常好用
typedef struct {
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;
#define F(x, y, z)  ((x & y) | (~x & z))
#define G(x, y, z)  ((x & z) | (y & ~z))
#define H(x, y, z)  (x ^ y ^ z)
#define I(x, y, z)  (y ^ (x | ~z))
#define ROTATE_LEFT(x, n)   ((x << n) | (x >> (32 - n)))
#define FF(a, b, c, d, x, s, ac) \
        { \
        a += F(b, c, d) + x + ac; \
        a = ROTATE_LEFT(a, s); \
        a += b; \
        }
#define GG(a, b, c, d, x, s, ac) \
        { \
        a += G(b, c, d) + x + ac; \
        a = ROTATE_LEFT(a, s); \
        a += b; \
        }
#define HH(a, b, c, d, x, s, ac) \
        { \
        a += H(b, c, d) + x + ac; \
        a = ROTATE_LEFT(a, s); \
        a += b; \
        }
#define II(a, b, c, d, x, s, ac) \
        { \
        a += I(b, c, d) + x + ac; \
        a = ROTATE_LEFT(a, s); \
        a += b; \
        }
void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputlen);
void MD5Final(MD5_CTX *context, unsigned char digest[16]);
void MD5Transform(unsigned int state[4], unsigned char block[64]);
void MD5Encode(unsigned char *output, unsigned int *input, unsigned int len);
void MD5Decode(unsigned int *output, unsigned char *input, unsigned int len);
//MD5Function
void MD5Function (unsigned char encrypt[],char *crypt1);
#endif // MD5_H
