#ifndef   dtm_rs485_client_esp32_freertos_cpp_d68d838a
#define   dtm_rs485_client_esp32_freertos_cpp_d68d838a

#include <cstdint>
#include <string>
#include <vector>

namespace DTM {
namespace RS485 {
namespace Client{
namespace ESP32 {
namespace FreeRTOS {
namespace CPP {
class D68D838A{
        private:
        uint8_t  U;
        uint8_t  D;
        uint8_t  P;
        uint8_t  S;
        uint8_t  T;
        uint8_t  R;
        uint8_t  X;
        uint64_t B;
        public:
        D68D838A (uint8_t UartHardwareDriver, uint8_t TXPin, uint8_t RXPin, uint8_t RTSPin, uint8_t DataSize, uint8_t ParityBit, uint8_t StopBit, uint64_t BaudRate, uint64_t TxBufferSize, uint64_t RxBufferSize);
       ~D68D838A ();
        int8_t s (std::string &E, std::vector<uint8_t> &S);
        int8_t r (std::string &E, std::vector<uint8_t> &Y , uint64_t S, int64_t T);
};
}
}
}
}
}
}
#endif
