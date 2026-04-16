#ifndef   one_kitsphere_dtm_rs485_client_esp32_freertos_cpp
#define   one_kitsphere_dtm_rs485_client_esp32_freertos_cpp

namespace One {
namespace KitSphere {
namespace DTM {
namespace RS485 {
namespace Client {
namespace ESP32 {
namespace FreeRTOS {
class CPP {
        public:
        CPP (uint8_t Uart, uint8_t DataSize, uint8_t ParityBit, uint8_t StopBit, uint8_t TXPin, uint8_t RXPin, uint8_t RTSPin, uint64_t BaudRate);
        int8_t  s (std::string &E, std::vector<uint8_t> &D);
        int8_t  r (std::string &E, std::vector<uint8_t> &D, uint64_t S, uint64_t T);
};
}
}
}
}
}
}
}
#endif
