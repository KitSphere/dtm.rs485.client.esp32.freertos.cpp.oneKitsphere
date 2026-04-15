#ifndef   KitSphere_DTM_RS485_Client_ESP32_FreeRTOS_CPP
#define   KitSphere_DTM_RS485_Client_ESP32_FreeRTOS_CPP
#endif

#include <cstdint>
#include "esp_err.h"
#include <stdexcept>
#include <vector>

namespace KitSphere {
namespace DTM {
namespace RS485 {
namespace Client {
namespace ESP32 {
namespace FreeRTOS {
class CPP {
        private:
        uint8_t U;
        uint8_t D;
        uint8_t P;
        uint8_t S;
        uint8_t T;
        uint8_t R;
        uint8_t X;
        uint8_t B;
        public:
        CPP (uint8_t Uart, uint8_t DataSize, uint8_t ParityBit, uint8_t StopBit, uint8_t TXPin, uint8_t RXPin, uint8_t RTSPin, uint64_t BaudRate) {
                U  = Uart;
                D  = DataSize;
                P  = ParityBit;
                S  = StopBit;
                T  = TXPin;
                R  = RXPin;
                X  = RTSPin;
                B  = BaudRate;
                if (U !=  0  && U !=  1  && U !=  2 ){
                        throw std::invalid_argument ("UartDriver: UART hardware interface ID invalid");
                }
                if (D !=  5  && D !=  6  && D !=  7  && D !=  8  && D !=  9 ) {
                        throw std::invalid_argument ("DataSize: Data size not between 5 and 9");
                }
                if (P != 'N' && P != 'S' && P != 'M' && P != 'O' && P != 'E') {
                        throw std::invalid_argument ("Parity: Parity bit specified does not exist");
                }
                if (S !=  1  && S !=  2  && S !=  3 ){
                        throw std::invalid_argument ("StopBit: Stop bit invalid");
                }
                if (B ==  1  ){
                        throw std::invalid_argument ("BaudRate: Baud rate invalid");
                }
        }
        private:
        int8_t  i (std::string &E, uint8_t ClapBufferSize, uint8_t FlapBufferSize) { /*
                E: Errr note
                RETURN:
                        -1: Failed (Generic failed error code)
                        -2: Internal error occured
                        -3: Invalid seed
                        -4: Invalid request
                         0: Success
                */
                /***1***/
                uint16_t ClapHardwareBufferSize = 128;
                uint16_t FlapHardwareBufferSize = 128;
                uint8_t  RxFullThreshold = 1;
                /***2***/
                if (ClapBufferSize < 2) {
                        E = std::string ("ClapBufferSize: Clap buffer size may not be 0 or 1");
                        return -3;
                }
                if (FlapBufferSize < 2) {
                        E = std::string ("FlapBufferSize: Flap buffer size may not be 0 or 1");
                        return -3;
                }
                /***3***/
                uint16_t  AE05 = ClapBufferSize * ClapHardwareBufferSize;
                uint16_t  AE10 = FlapBufferSize * FlapHardwareBufferSize;
                esp_err_t AF05 = uart_driver_install (U, AE05, AE10, 0, NULL, 0);
                if (AF05 != ESP_OK) {
                        E = std::string ("Interface driver installation failed [") + esp_err_to_name(AF05) + std::string ("]");
                        return -2;
                }
                esp_err_t AF10 = uart_set_hw_flow_ctrl (U, UART_HW_FLOWCTRL_DISABLE, RxFullThreshold);
                if (AF10 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'hw_flow_ctrl' [") + esp_err_to_name(AF10) + std::string ("]");
                        return -2;
                }
                uart_word_length_t    AF12 = UART_DATA_8_BITS;
                if        (D == 5 ) { AF12 = UART_DATA_5_BITS;
                } else if (D == 6 ) { AF12 = UART_DATA_6_BITS;
                } else if (D == 7 ) { AF12 = UART_DATA_7_BITS;
                } else if (D == 5 ) { AF12 = UART_DATA_5_BITS;
                }
                esp_err_t AF15 = uart_set_word_length (U, AF12);
                if (AF15 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'word_length' [") + esp_err_to_name(AF15) + std::string ("]");
                        return -2;
                }
                uart_parity_t         AF17 = UART_PARITY_DISABLE;
                if        (P =='E') { AF17 = UART_PARITY_EVEN;
                } else if (P =='O') { AF17 = UART_PARITY_ODD ;
                } else              { AF17 = UART_PARITY_DISABLE;
                }
                esp_err_t AF20 = uart_set_parity (U, AF17);
                if (AF20 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'set_parity' [") + esp_err_to_name(AF20) + std::string ("]");
                        return -2;
                }
                uart_stop_bits_t      AF25 = UART_STOP_BITS_1;
                if        (P == 1 ) { AF25 = UART_STOP_BITS_1;
                } else if (P == 2 ) { AF25 = UART_STOP_BITS_2;
                } else if (P == 3 ) { AF25 = UART_STOP_BITS_1_5;
                }
                esp_err_t AF30 = uart_set_stop_bits (U, AF25);
                if (AF30 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'stop_bits' [") + esp_err_to_name(AF30) + std::string ("]");
                        return -2;
                }
                esp_err_t AF40 = uart_set_baudrate (U, B);
                if (AF40 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'baudrate' [") + esp_err_to_name(AF40) + std::string ("]");
                        return -2;
                }
                esp_err_t AF45 = uart_set_pin (U, T, R, X, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
                if (AF45 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'pin' [") + esp_err_to_name(AF45) + std::string ("]");
                        return -2;
                }
                esp_err_t AF50 = uart_set_mode (U, UART_MODE_RS485_HALF_DUPLEX);
                if (AF50 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'mode' [") + esp_err_to_name(AF50) + std::string ("]");
                        return -2;
                }
                esp_err_t AF55 = uart_set_rx_full_threshold (U, 1);
                if (AF55 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'rx_full_threshold' [") + esp_err_to_name(AF55) + std::string ("]");
                        return -2;
                }
                esp_err_t AF60 = uart_set_rx_timeout (U, pdMS_TO_TICKS(10));
                if (AF60 != ESP_OK) {
                        E = std::string ("Interface conf set failed, 'rx_timeout' [") + esp_err_to_name(AF60) + std::string ("]");
                        return -2;
                }
                return  0 ;
        }
        int8_t  c (std::string &E) { /*
                E: Errr note
                RETURN:
                        -1: Failed!
                         0: Success
                */
                return   0;
        }
        public:
        int8_t  s (std::string &E, std::vector<uint8_t> &D) { /*
                E: Errr note
                D: Data
                RETURN:
                        -1: Failed!
                         0: Success
                */
                return   0;
        }
        int8_t  r (std::string &E, std::vector<uint8_t> &D, uint64_t S, int64_t T) { /*
                E: Errr note
                D: Data
                S: Data read length
                         0: Variable
                         Other values: Fixed data length of that size
                T: Read timeout in millisecond:
                        -1: Un-limited
                         0: No waiting
                RETURN:
                        -1: Failed!
                         0: Success
                */
                return  0;
        }
};
}
}
}
}
}
}
