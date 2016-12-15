#include "httpd-board-data.h"
#include "stdlib.h"

const char* HttpdBoardDataErrorStr = "Cannot read specified data";

// store pointers to user's data getters functions
static HttpdBoardDataGetterFuncType registeredGettersBuff[NO_BOARD_DATA_GETTER_FUNCTIONS] = {0};


uint32_t registerHttpdBoardDataGetter(HttpdBoardDataGetterFuncType userGetterFunc, HttpdBoardDataGetterType type) {
    uint32_t retVal = 1;

    if (((size_t)type < NO_BOARD_DATA_GETTER_FUNCTIONS) &&
            (NULL != userGetterFunc) &&
            (NULL == registeredGettersBuff[(int)type])) {
        // register and indicate success
        registeredGettersBuff[(int)type] = userGetterFunc;
        retVal = 0;
    }

    return retVal;
}


HttpdBoardDataGetterFuncType getHttpdBoardDataGetter(HttpdBoardDataGetterType type) {
    return registeredGettersBuff[(int)type];
}
