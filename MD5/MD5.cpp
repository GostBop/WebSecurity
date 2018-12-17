//本代码从MD5百度百科上摘录，因为位操作处理得很巧妙，自愧不如，所以主要学习，分析，吸收该代码

#include<iostream>
#include<string>
#include<cmath>
using namespace std;

//循环左移N位，即意味着X左移N位后，前N个被挤占的位数，移动到X的后N位，相当于X右移32-N位
//右移的时候，高位一定要补零，而不是补充符号位
#define CLS(x, n) (((x) << (n)) | ((x) >> (32-(n))))

//MD5有四轮运算，将原先数据分为4个32位分组组成，选其中三个进行运算
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))    
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476//初始化变量，用于第一轮   
//strBaye的长度
unsigned int strlength;
//A,B,C,D的临时变量
unsigned int atemp;
unsigned int btemp;
unsigned int ctemp;
unsigned int dtemp;
//常量ti unsigned int(abs(sin(i+1))*(2pow32))
const unsigned int T[] = {
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
    0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,
    0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,
    0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,
    0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,
    0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,
    0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,
    0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
    0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,
    0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
    0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,
    0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391 };
//向左位移数
const unsigned int s[] = { 7,12,17,22,7,12,17,22,7,12,17,22,7,
12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,
15,21,6,10,15,21,6,10,15,21,6,10,15,21 };

const char str16[] = "0123456789abcdef";

void HMD5(unsigned int X[]) {
    unsigned int g, k;
    unsigned int a = atemp;
    unsigned int b = btemp;
    unsigned int c = ctemp;
    unsigned int d = dtemp;
    for (unsigned int i = 0; i < 64; i++) {
        if (i < 16) {
            g = F(b, c, d);
            k = i;
        }
        else if (i < 32) {
            g = G(b, c, d);
            k = (5 * i + 1) % 16;
        }
        else if (i < 48) {
            g = H(b, c, d);
            k = (3 * i + 5) % 16;
        }
        else {
            g = I(b, c, d);
            k = (7 * i) % 16;
        }
        unsigned int temp = d;
        d = c;
        c = b;
        b = b + CLS((a + g + T[i] + X[k]), s[i]);
        a = temp;
    }
    atemp = a + atemp;
    btemp = b + btemp;
    ctemp = c + ctemp;
    dtemp = d + dtemp;
}


unsigned int* padding(string str) {
    //分块：
    //由于char类型存储长度为8bits，因此 TotalBits = str.length() * 8 为原始消息数据位数
    //假设 TotalBits / 512 = PreBlock 为未填充前的块数，理论上填充后 block = PreBlock + 1
    //所以 block = (TotalBits + 64) / 512 + 1，64为str的低64位，约分后得下式
    unsigned int block = ((str.length() + 8) / 64) + 1;
    
    //由于unsigned int类型存储长度为32位， 因此存放填充后的消息数据需要block * 512 / 32个unsigned int
    //即 strlength = block * 16
    strlength = block * 16;
    unsigned int *strByte = new unsigned int[strlength];
    
    for (unsigned int i = 0; i < strlength; i++)
        strByte[i] = 0; //初始化strByte数组
    
    //由于unsigned int类型存储长度为32位，因此能存储四个char类型
    //因此每四个str[i % 4]: ([i], [i + 1], [i + 2], [i + 3]), 存放在一个strByte[i >> 2]里
    //str[i]存放在strByte[i >> 2]的0-7位，[i+1]存放在8-15位，
    //[i+2]存放在16-23位，[i+3]存放在24-31位
    for (unsigned int i = 0; i < str.length(); i++) {
        strByte[i >> 2] |= (str[i]) << ((i % 4) * 8);
    }

    //在尾部添加1，因为str长度为字节数，转换为位数肯定为8的位数，
    //所以可以直接在尾部添加0x80，其余位数由于初始化已为0，不需要再补0
    strByte[str.length() >> 2] |= 0x80 << (((str.length() % 4)) * 8);
                                                                     
    //添加原长度，长度指位的长度，所以要乘8，由于是小端模式，所以放在倒数第二个,这里长度只用了32位
    strByte[strlength - 2] = str.length() * 8;
    return strByte;
}

string changeHex(int a) {
    int b;
    string str1;
    string str = "";
    for (int i = 0; i < 4; i++) {
        str1 = "";
        b = ((a >> i * 8) % (1 << 8)) & 0xff;   //逆序处理每个字节
        for (int j = 0; j < 2; j++) {
            str1.insert(0, 1, str16[b % 16]);
            b = b / 16;
        }
        str += str1;
    }
    return str;
}

string getMD5(string source) {
    atemp = A;    //初始化
    btemp = B;
    ctemp = C;
    dtemp = D;
    //填充
    unsigned int *strByte = padding(source);

    //strlength存储单位为unsigned int, 因此block_num = strlength * 32 / 512
    for (unsigned int i = 0; i < strlength / 16; i++) {
        //16个unsigned int存储512位数
        unsigned int block[16];
        //将每一块数据存储到block里
        for (unsigned int j = 0; j < 16; j++)
            block[j] = strByte[i * 16 + j];
        //循环迭代每一块数据，每一次迭代得到的128位数据（a,b,c,d）将提供给下一次迭代
        HMD5(block);
    }

    return changeHex(atemp).append(changeHex(btemp)).append(changeHex(ctemp)).append(changeHex(dtemp));
}

int main() {
    string s = getMD5("This is a message that would be used to test MD5");
    cout << s << endl;

    cin.get();
    return 0;
}