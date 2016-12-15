#ifndef SRC_UIP_APPS_WEBSERVER_HTTPD_BOARD_DATA_H_
#define SRC_UIP_APPS_WEBSERVER_HTTPD_BOARD_DATA_H_

#include <stdint.h>
#include <stddef.h>

/// How may getter functions can be registered
#define NO_BOARD_DATA_GETTER_FUNCTIONS 4

/** Type of getter function.
 *
 * @param pointer[in,out] address of buffer, where string can be copied.
 * @param maxLen          maximum length of string that can be copied into buffer.
 * @return                length of copied characters, the \0 character should
 *                        not be counted.
 */
typedef size_t (*HttpdBoardDataGetterFuncType)(char* buff, const size_t maxLen);

/// Determine type of getter
/// @Note   Value of enumerations must be always lower than NO_BOARD_DATA_GETTER_FUNCTIONS
typedef enum GETTER_FUNCTION {
      BOARD_DATA_TEMP = 0//!< TEMPERATURE
    , BOARD_DATA_SW1 = 1        //!< SW1
    , BOARD_DATA_SW2 = 2        //!< SW2
    , BOARD_DATA_SW3 = 3        //!< SW3
} HttpdBoardDataGetterType;

/** Registers user's functions that will provide data of specified type.
 *
 * @param userDataGetterFunc    pointer to function that will returns pointer to
 *                              valid string and its length
 * @param type                  specifies what kind of data userDataGetterFunc
 *                              will return
 * @return                      0 on success or other value on invalid input
 *                              arguments or when function cannot be registered
 */
uint32_t registerHttpdBoardDataGetter(HttpdBoardDataGetterFuncType userDataGetterFunc, HttpdBoardDataGetterType type);

/**
 * Returns pinter to user functions specified by given type.
 * @param   type  type of getter
 * @return  pinter to user function, or NULL if function of given type hasn't be
 *          registered yet.
 */
HttpdBoardDataGetterFuncType getHttpdBoardDataGetter(HttpdBoardDataGetterType type);

#endif /* SRC_UIP_APPS_WEBSERVER_HTTPD_BOARD_DATA_H_ */
