# X.509数字证书的结构与解析

## 1、什么叫数字签名
数字签名：

将报文按双方约定的HASH算法计算得到一个固定位数的报文摘要。在数学上保证：只要改动报文中任何一位，重新计算出的报文摘要值就会与原先的值不相符。这样就保证了报文的不可更改性。

将该报文摘要值用发送者的私人密钥加密，然后连同原报文一起发送给接收者，而产生的报文即称数字签名

## 2、什么叫数字证书

数字证书：

数字证书就是互联网通讯中标志通讯各方身份信息的一系列数据，提供了一种在Internet上验证您身份的方式，其作用类似于司机的驾驶执照或日常生活中的身份证。它是由一个由权威机构—–CA机构，又称为证书授权，（Certificate Authority）中心发行的，人们可以在网上用它来识别对方的身份。数字证书是一个经证书授权中心数字签名的包含公开密钥拥有者信息以及公开密钥的文件。最简单的证书包含一个公开密钥、名称以及证书授权中心的数字签名。

## 3、PKI
- PKI 是一组服务和策略，提供了一个将公钥和用户身份唯一绑
定的机制，以及如何实施并维护这个绑定相关信息的框架；
- PKI 是一个通过使用公开密钥技术和数字证书来确保系统信息
安全，并负责验证数字证书持有者身份的体系。

### 体系详解
(1) 鲍勃有两把钥匙，一把是公钥，另一把是私钥。 
![image](https://img-blog.csdn.net/20160807210347532)

(2) 鲍勃把公钥送给他的朋友们—-帕蒂、道格、苏珊—-每人一把。 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210405977)
(3) 苏珊要给鲍勃写一封保密的信。她写完后用鲍勃的公钥加密，就可以达到保密的效果 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210420243)
(4) 鲍勃收信后，用私钥解密，就看到了信件内容。这里要强调的是，只要鲍勃的私钥不泄露，这封信就是安全的，即使落在别人手里，也无法解密。 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210804580)
(5) 鲍勃给苏珊回信，决定采用 “数字签名”。他写完后先用Hash函数，生成信件的摘要（digest）。 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210507751)
(6) 然后，鲍勃使用私钥，对这个摘要加密，生成”数字签名”（signature）。 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210529876)
(7) 鲍勃将这个签名，附在信件下面，一起发给苏珊。 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210545845)
(8) 苏珊收信后，取下数字签名，用鲍勃的公钥解密，得到信件的摘要。由此证明，这封信确实是鲍勃发出的。
![在这里插入图片描述](https://img-blog.csdn.net/20160807210601886)
(9) 苏珊再对信件本身使用Hash函数，将得到的结果，与上一步得到的摘要进行对比。如果两者一致，就证明这封信未被修改过。
![在这里插入图片描述](https://img-blog.csdn.net/20160807210619814)
(10) 复杂的情况出现了。道格想欺骗苏珊，他偷偷使用了苏珊的电脑，用自己的公钥换走了鲍勃的公钥。此时，苏珊实际拥有的是道格的公钥，但是还以为这是鲍勃的公钥。因此，道格就可以冒充鲍勃，用自己的私钥做成“数字签名”，写信给苏珊，让苏珊用假的鲍勃公钥进行解密。 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210640793)
(11) 后来，苏珊感觉不对劲，发现自己无法确定公钥是否真的属于鲍勃。她想到了一个办法，要求鲍勃去找”证书中心”（certificate authority，简称CA），为公钥做认证。证书中心用自己的私钥，对鲍勃的公钥和一些相关信息一起加密，生成“数字证书”（Digital Certificate）。
![在这里插入图片描述](https://img-blog.csdn.net/20160807210656731)
(12) 鲍勃拿到数字证书以后，就可以放心了。以后再给苏珊写信，只要在签名的同时，再附上数字证书就行了。 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210712846)
(13) 苏珊收信后，用CA的公钥解开数字证书，就可以拿到鲍勃真实的公钥了，然后就能证明”数字签名”是否真的是鲍勃签的。 
![在这里插入图片描述](https://img-blog.csdn.net/20160807210734721)
## 4、X.509
X.509 是密码学里公钥证书的格式标准。

X.509 标准规定了证书可以包含什么信息，并说明了记录信息的方法（数据格式）。

X.509 证书里含有公钥、身份信息（比如网络主机名，组织的名称或个体名称等）和签名信息（可以是证书签发机构CA的签名，也可以是自签名）。

对于一份经由可信的证书签发机构签名或者可以通过其它方式验证的证书，证书的拥有者就可以用证书及相应的私钥来创建安全的通信，对文档进行数字签名。

另外除了证书本身功能，X.509还附带了证书吊销列表和用于从最终对证书进行签名的证书签发机构直到最终可信点为止的证书合法性验证算法。

X.509是ITU-T标准化部门基于他们之前的ASN.1定义的一套证书标准。

### X.509证书的结构
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181212225519559.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hjbV8wMDc5,size_16,color_FFFFFF,t_70)

#### 1、X.509证书基本部分
**1.1. 版本号(Version)**

——标识证书的版本（版本1、版本2或是版本3）。

**1.2. 序列号(Serial Number)**

——标识证书的唯一整数，由证书颁发者分配的本证书的唯一标识符。

**1.3. 签名(Signature)**

——用于签证书的算法标识，由对象标识符加上相关的参数组成，用于说明本证书所用的数字签名算法。例如，SHA-1和RSA的对象标识符就用来说明该数字签名是利用RSA对SHA-1杂凑加密。

**1.4. 颁发者(Issuer:)**

——证书颁发者的可识别名（DN）。

**1.5. 有效期(Validity)**

——证书有效期的时间段。本字段由”Not Before”和”Not After”两项组成，它们分别由UTC时间或一般的时间表示（在RFC2459中有详细的时间表示规则）。

**1.6. 主体(Subject)**

——证书拥有者的可识别名，这个字段必须是非空的，除非你在证书扩展中有别名。

**1.7. 主体公钥信息(Subject Public Key Info)**

——主体的公钥（以及算法标识符）。

**1.8. 颁发者唯一标识符(Issuer Unique Identifier)**

——标识符—证书颁发者的唯一标识符，仅在版本2和版本3中有要求，属于可选项。

**1.9. 主体唯一标识符(Subject Unique Identifier)**

——证书拥有者的唯一标识符，仅在版本2和版本3中有要求，属于可选项。

#### 2、X.509证书扩展部分(Extensions)

**可选的标准和专用的扩展**（仅在版本2和版本3中使用），扩展部分的元素都有这样的结构：

    Extension ::= SEQUENCE {
        extnID      OBJECT IDENTIFIER,
        critical    BOOLEAN DEFAULT FALSE,
        extnValue   OCTET STRING }
extnID：表示一个扩展元素的OID

critical：表示这个扩展元素是否极重要

extnValue：表示这个扩展元素的值，字符串类型。

**扩展部分包括**：

**2.1. 发行者密钥标识符(Autority Key Identifier)**

——证书所含密钥的唯一标识符，用来区分同一证书拥有者的多对密钥。

**2.2. 密钥使用(Key Usage)**

——一个比特串，指明（限定）证书的公钥可以完成的功能或服务，如：证书签名、数据加密等。

如果某一证书将 KeyUsage 扩展标记为“极重要”，而且设置为“keyCertSign”，则在 SSL 通信期间该证书出现时将被拒绝，因为该证书扩展表示相关私钥应只用于签写证书，而不应该用于 SSL。

**2.3. CRL分布点(CRL Distribution Points)**

——指明CRL的分布地点。

**2.4. 私钥的使用期**

——指明证书中与公钥相联系的私钥的使用期限，它也有Not Before和Not After组成。若此项不存在时，公私钥的使用期是一样的。

**2.5. 证书策略(Certificate Policies)**

——由对象标识符和限定符组成，这些对象标识符说明证书的颁发和使用策略有关。

**2.6. 策略映射**

——表明两个CA域之间的一个或多个策略对象标识符的等价关系，仅在CA证书里存在。

**2.7. 主体别名**

——指出证书拥有者的别名，如电子邮件地址、IP地址等，别名是和DN绑定在一起的。

**2.8. 颁发者别名**

——指出证书颁发者的别名，如电子邮件地址、IP地址等，但颁发者的DN必须出现在证书的颁发者字段。

**2.9. 主体目录属性**

——指出证书拥有者的一系列属性。可以使用这一项来传递访问控制信息。

### X.509 证书实例

https://www.github.com 的证书信息如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181212225035594.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hjbV8wMDc5,size_16,color_FFFFFF,t_70)

调用Openssl库的API对githubcom.pem证书文件解析结果如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2018121222525276.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hjbV8wMDc5,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181212225336275.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hjbV8wMDc5,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181212225358799.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hjbV8wMDc5,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181212225417913.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hjbV8wMDc5,size_16,color_FFFFFF,t_70)

### X.509 C语言解析源码
```c
#include <fstream>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <iostream>
#include <sstream>

using namespace std;
//----------------------------------------------------------------------*/
void parseCert(X509* x509)
{
    cout <<"--------------------" << endl;
    BIO *bio_out = BIO_new_fp(stdout, BIO_NOCLOSE);
    //PEM_write_bio_X509(bio_out, x509);//STD OUT the PEM
    X509_print(bio_out, x509);//STD OUT the details
    //X509_print_ex(bio_out, x509, XN_FLAG_COMPAT, X509_FLAG_COMPAT);//STD OUT the details
    BIO_free(bio_out);
}

//----------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    OpenSSL_add_all_algorithms();

    std::ifstream t;
    int length;
    t.open("./githubcom.pem");      // open input file
    t.seekg(0, std::ios::end);    // go to the end
    length = t.tellg();           // report location (this is the length)
    t.seekg(0, std::ios::beg);    // go back to the beginning
    char*  buffer = new char[length];    // allocate memory for a buffer of appropriate dimension
    t.read(buffer, length);       // read the whole file into the buffer
    t.close();                    // close file handle
 
    BIO *bio_mem = BIO_new(BIO_s_mem());
    BIO_puts(bio_mem, buffer);
    X509 * x509 = PEM_read_bio_X509(bio_mem, NULL, NULL, NULL);
    parseCert(x509);
    BIO_free(bio_mem);
    X509_free(x509);
}
//----------------------------------------------------------------------
```

参考资料：
[X.509数字证书的结构与解析](https://blog.csdn.net/xy010902100449/article/details/52145009)
[x.509数字证书编码详解](https://blog.csdn.net/kesay/article/details/46874699)


