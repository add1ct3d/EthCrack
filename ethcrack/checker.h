#include <curl/curl.h>
#include "../cjson/cJSON.h"
#include "datatypes.h"

#define CHECKBALANCE_URL "http://localhost:8545/"
#define BAD_BALANCE "0x0"

unsigned short check_balance(char* address);