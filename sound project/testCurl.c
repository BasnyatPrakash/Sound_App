#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#define SZ 1

int curl(void){
        CURL *curl;
        CURLcode res;
        char name[30], email[40];
        char postdata[100] = "v1=1&v2=1&v3=1&v4=1&v5=1&v6=1&v7=1&v8=1";
        double v1[SZ], v2[SZ], v3[SZ], v4[SZ], v5[SZ], v6[SZ], v7[SZ], v8[SZ];

		for(;;){
			sprintf(postdata, "v1=%f&v2=%fv3=%fv4=%fv5=%fv6=%fv7=%fv8=%f", v1, v2, v3, v4, v5, v6, v7, v8);

			curl_global_init(CURL_GLOBAL_ALL);
			curl = curl_easy_init();

			if(curl){ //of initialize is okay
					printf("curl is initialize");
					curl_easy_setopt(curl, CURLOPT_URL, "http://www.cc.puv.fi/~e1500942/php/testCurl.php");
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
					res = curl_easy_perform(curl);

					if(res != CURLE_OK){
							printf("Cannot send! \n");
					}
					curl_easy_cleanup(curl); //tear down the communication
			}
			curl_global_cleanup();

			if(strcmp(name, email)); break;
		}
}
