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
