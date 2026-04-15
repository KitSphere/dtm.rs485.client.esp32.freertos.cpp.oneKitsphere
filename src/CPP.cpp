#ifndef   KitSphere_DTM_RS485_Client_ESP32_FreeRTOS_CPP
#define   KitSphere_DTM_RS485_Client_ESP32_FreeRTOS_CPP
#endif

#include <cstdint>
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
        uint8_t D;
        uint8_t P;
        uint8_t S;
        uint8_t T;
        uint8_t R;
        uint8_t X;
        uint8_t B;
        public:
        CPP (uint8_t DataSize, uint8_t ParityBit, uint8_t StopBit, uint8_t TXPin, uint8_t RXPin, uint8_t RTSPin, uint64_t BaudRate) {
                D  = DataSize;
                P  = ParityBit;
                S  = StopBit;
                D  = TXPin;
                P  = RXPin;
                X  = RTSPin;
                B  = BaudRate;
                if (D !=  5  && D !=  6  && D !=  7  && D !=  8  && D !=  9 ) {
                        throw std::invalid_argument ("DataSize: Data size not between 5 and 9");
                }
                if (P != 'N' && P != 'S' && P != 'M' && P != 'O' && P != 'E') {
                        throw std::invalid_argument ("Parity: Parity bit specified does not exist");
                }
                if (D !=  1  && D !=  2  && D !=  3 ){
                        throw std::invalid_argument ("StopBit: Stop bit invalid");
                }
                if (B ==  1  ){
                        throw std::invalid_argument ("BaudRate: Baud rate invalid");
                }
        }
        int8_t  s (std::string &E, std::vector<uint8_t> &D, int64_t T) { /*
                D: Data
                T: Send timeout in millisecond:
                        -1: Un-limited
                         0: No waiting
                RETURN
                        -1: Failed!
                         0: Success
                */
                return   0;
        }
        int8_t  r (std::string &E, std::vector<uint8_t> &D, int64_t T, uint64_t S) { /*
                D: Data
                T: Read timeout in millisecond:
                        -1: Un-limited
                         0: No waiting
                S: Data length
                RETURN
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
