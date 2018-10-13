#include "ethcrack.h"

void worker() {
	while(TRUE) {
	
		uint8_t priv[32];
		memset(priv, 0, 32);
		generate_privatekey(priv);
		
		uint8_t ethaddress[20];
		ethaddress_calculate(priv, ethaddress);
		
		char hex[40];
		memset(hex, 0, 40);
		
		
		for(int i = 0; i < 20; i++) {
			char tmp[2];
			sprintf(tmp, "%02x", ethaddress[i]);
			strcat(hex, tmp);
		}
		
		char address[40];
		memcpy(address, hex, 40);
		
		if(check_balance(hex) == TRUE) {
			printf("\n\n!!!! KEY WITH BALANCE FOUND !!!!\n\n");
			
			printf("Private Key: ");
			for(int i = 0; i < 32; i++) {
				printf("%02x", priv[i]);
			}
			printf("\n");
			
			printf("Eth address: 0x");
			printf("%s\n", hex);
			
			exit(0);
		}
	}
}

int main () {
	
	printf("\n%s[*]%s Wallet mining will be started in %i seconds ...", ANSI_COLOR_CYAN, ANSI_COLOR_RESET, SLEEP_TIME);
	sleep(SLEEP_TIME);
	
	printf("\n%s[*]%s Initializing %i threads ...", ANSI_COLOR_CYAN, ANSI_COLOR_RESET, THREADS);
	pthread_t threads[THREADS];
	
	for(int i = 0; i < THREADS; i++) {
		int ret = pthread_create( &threads[i], NULL, worker, NULL);
		
		if(ret) {
			printf("pthread_create() error: %i\n", ret);
			return 1;
		}
	}
	
	printf("\n%s[+]%s Wallet mining started!", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
	
	getchar();
	return 0;
}