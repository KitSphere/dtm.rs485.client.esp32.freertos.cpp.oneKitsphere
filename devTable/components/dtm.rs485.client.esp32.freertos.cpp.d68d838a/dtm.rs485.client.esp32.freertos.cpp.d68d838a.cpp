#include "dtm.rs485.client.esp32.freertos.cpp.d68d838a.h"
#include <chrono>
#include <cstdint>
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_err.h"
#include <stdexcept>
#include <vector>

#include <iostream>

namespace DTM {
namespace RS485 {
namespace Client{
namespace ESP32 {
namespace FreeRTOS {
namespace CPP {
        D68D838A::D68D838A (uint8_t UartHardwareDriver, uint8_t TXPin, uint8_t RXPin, uint8_t RTSPin, uint8_t DataSize, uint8_t ParityBit, uint8_t StopBit, uint64_t BaudRate, uint64_t TxBufferSize, uint64_t RxBufferSize) {
                /***1***/
                U  = UartHardwareDriver;
                T  = TXPin;
                R  = RXPin;
                X  = RTSPin;
                D  = DataSize;
                P  = ParityBit;
                S  = StopBit;
                B  = BaudRate;
                if (U !=  0  && U !=  1  && U !=  2) {
                        std::string BE05 = std::string ("UartDriver: UART hardware interface ID invalid");
                        throw std::invalid_argument (BE05);
                }
                if (D !=  5  && D !=  6  && D !=  7  && D !=  8  && D !=  9 ) {
                        std::string BE05 = std::string ("DataSize: Data size not between 5 and 9");
                        throw std::invalid_argument (BE05);
                }
                if (P != 'N' && P != 'S' && P != 'M' && P != 'O' && P != 'E') {
                        std::string BE05 = std::string ("Parity: Parity bit specified does not exist");
                        throw std::invalid_argument (BE05);
                }
                if (S !=  1  && S !=  2  && S !=  3) {
                        std::string BE05 = std::string ("StopBit: Stop bit invalid");
                        throw std::invalid_argument (BE05);
                }
                if (B ==  0) {
                        std::string BE05 = std::string ("BaudRate: Baud rate invalid");
                        throw std::invalid_argument (BE05);
                }
                /***2***/
                uint64_t TxBufferSizeMin = 0;
                uint64_t RxBufferSizeMin = 1;
                uint8_t  RxFullThreshold = 1;
                if (TxBufferSize < TxBufferSizeMin) {
                        std::string BE05 = std::format ("TxBufferSize: Buffer size may not be less than {}", TxBufferSizeMin);
                        throw std::invalid_argument (BE05);
                }
                if (RxBufferSize < RxBufferSizeMin) {
                        std::string BE05 = std::format ("RxBufferSize: Buffer size may not be less than {}", RxBufferSizeMin);
                        throw std::invalid_argument (BE05);
                }
                /***3***/
                uart_port_t           AE01 = UART_NUM_2;
                if        (U == 0 ) { AE01 = UART_NUM_0;
                } else if (U == 1 ) { AE01 = UART_NUM_1;
                } else if (U == 2 ) { AE01 = UART_NUM_2;
                }
                esp_err_t AF05 = uart_driver_install (AE01, RxBufferSize, TxBufferSize, 0, NULL, 0);
                if (AF05 != ESP_OK) {
                        std::string BE05 = std::string ("Interface driver installation failed [") + esp_err_to_name(AF05) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                esp_err_t AF10 = uart_set_hw_flow_ctrl (AE01, UART_HW_FLOWCTRL_DISABLE, RxFullThreshold);
                if (AF10 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'hw_flow_ctrl' [") + esp_err_to_name(AF10) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                uart_word_length_t    AF12 = UART_DATA_8_BITS;
                if        (D == 5 ) { AF12 = UART_DATA_5_BITS;
                } else if (D == 6 ) { AF12 = UART_DATA_6_BITS;
                } else if (D == 7 ) { AF12 = UART_DATA_7_BITS;
                } else if (D == 8 ) { AF12 = UART_DATA_8_BITS;
                }
                esp_err_t AF15 = uart_set_word_length (AE01, AF12);
                if (AF15 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'word_length' [") + esp_err_to_name(AF15) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                uart_parity_t         AF17 = UART_PARITY_DISABLE;
                if        (P =='E') { AF17 = UART_PARITY_EVEN;
                } else if (P =='O') { AF17 = UART_PARITY_ODD ;
                } else              { AF17 = UART_PARITY_DISABLE;
                }
                esp_err_t AF20 = uart_set_parity (AE01, AF17);
                if (AF20 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'set_parity' [") + esp_err_to_name(AF20) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                uart_stop_bits_t      AF25 = UART_STOP_BITS_1;
                if        (S == 1 ) { AF25 = UART_STOP_BITS_1;
                } else if (S == 2 ) { AF25 = UART_STOP_BITS_2;
                } else if (S == 3 ) { AF25 = UART_STOP_BITS_1_5;
                }
                esp_err_t AF30 = uart_set_stop_bits (AE01, AF25);
                if (AF30 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'stop_bits' [") + esp_err_to_name(AF30) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                esp_err_t AF40 = uart_set_baudrate (AE01, B);
                if (AF40 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'baudrate' [") + esp_err_to_name(AF40) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                esp_err_t AF45 = uart_set_pin (AE01, T, R, X, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
                if (AF45 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'pin' [") + esp_err_to_name(AF45) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                esp_err_t AF50 = uart_set_mode (AE01, UART_MODE_RS485_HALF_DUPLEX);
                if (AF50 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'mode' [") + esp_err_to_name(AF50) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                esp_err_t AF55 = uart_set_rx_full_threshold (AE01, 1);
                if (AF55 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'rx_full_threshold' [") + esp_err_to_name(AF55) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
                esp_err_t AF60 = uart_set_rx_timeout (AE01, 1);
                if (AF60 != ESP_OK) {
                        std::string BE05 = std::string ("Interface conf set failed, 'rx_timeout' [") + esp_err_to_name(AF60) + std::string ("]");
                        throw std::invalid_argument (BE05);
                }
        }
        D68D838A::~D68D838A() {
                uart_port_t           AE01 = UART_NUM_2;
                if        (U == 0 ) { AE01 = UART_NUM_0;
                } else if (U == 1 ) { AE01 = UART_NUM_1;
                } else if (U == 2 ) { AE01 = UART_NUM_2;
                }
                uart_driver_delete (AE01);
        }
        int8_t  D68D838A::s (std::string &E, std::vector<uint8_t> &S) { /*
                E: Error note
                D: Seed  data
                RETURN:
                        -1: Generic failed error code
                        -2: Internl error occured
                        -3: Invalid seed
                        -4: Invalid request
                         0: Success
                */
                uart_port_t           AE01 = UART_NUM_2;
                if        (U == 0 ) { AE01 = UART_NUM_0;
                } else if (U == 1 ) { AE01 = UART_NUM_1;
                } else if (U == 2 ) { AE01 = UART_NUM_2;
                }
                for (std::string::size_type  BE05 = 1; BE05 <=S.size(); BE05++) {
                        char BE10 = S.at (BE05-1);
                        int  BE15 = uart_write_bytes ( AE01, &BE10, 1);
                        if ( BE15 < 0) {
                                E = std::format ("Data char send failed [{}]", BE15);
                                return -2;
                        }
                }
                return  0;
        }
        int8_t  D68D838A::r (std::string &E, std::vector<uint8_t> &Y, uint64_t Z, int64_t T) { /*
                E: Errr note
                Y: Read data (Yield)
                Z: Read data size
                         0: All immediately available data
                         Other values: Fixed data length of that size
                T: Read timeout in millisecond:
                        -1: Un-limited
                         0: No waiting
                RETURN:
                        -1: Generic failed error code
                        -2: Internl error occured
                        -3: Invalid seed
                        -4: Invalid request
                         0: Success
                         1: Timeout
                */
                uart_port_t           AE01 = UART_NUM_2;
                if        (U == 0 ) { AE01 = UART_NUM_0;
                } else if (U == 1 ) { AE01 = UART_NUM_1;
                } else if (U == 2 ) { AE01 = UART_NUM_2;
                }
                std::chrono::time_point AE05 = std::chrono::steady_clock::now ();
                int AE10[1] = {0};
                while(true) {
                        /***1***/
                        int BE05 = uart_read_bytes (AE01, AE10,1, 1);
                        /***2***/
                        if         (BE05 < 0) {
                                E = std::string ("Data read failed");
                                return -2;
                        } else  if (BE05 == 0) {
                                if (   Z == 0) { return 0; }
                        } else  {
                                Y.push_back (AE10[0]);
                                if (Y.size() == Z) { return 0; }
                        }
                        /***3***/
                        if(    T < 0) { continue; }
                        std::chrono::time_point  BE10 = std::chrono::steady_clock::now ();
                        std::chrono::duration<double> BE15 = BE10 - AE05;
                        std::chrono::nanoseconds BE20 = std::chrono::duration_cast<std::chrono::nanoseconds> (BE15);
                        uint64_t BE25 = static_cast<uint64_t>(BE20.count ());
                        BE25 = BE25 / 1000 / 1000 ;
                        if( BE25 > T) { return 1; }
                }
        }
};
}
}
}
}
}
