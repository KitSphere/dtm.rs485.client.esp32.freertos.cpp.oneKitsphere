#include <chrono>
#include <cstdlib>
#include "dtm.rs485.client.esp32.freertos.cpp.d68d838a.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void    TS01 ();
void    TS02 ();
extern "C" void app_main ()  {
        while(true){
                TS02 ();
        }
        vTaskDelete(NULL  );
}
void    TS01 () {
        try{
                DTM::RS485::Client::ESP32::FreeRTOS::CPP::D68D838A BE05 (
                        1, 21, 23, 4, 8, 'O', 1, 9600, 256, 256
                );
                std::string BE10 = std::string ("Hello world\r\n");
                while(true) {
                        std::string  CE01;
                        std::vector<uint8_t> CE05 (BE10.begin(), BE10.end());
                        int8_t CE10= BE05.s (CE01, CE05);
                        if (CE10 < 0) {
                                std::string  DE05 = std::format ("Data send failed [{}: {}]", CE10, CE01);
                                std::cout << DE05<< std::endl;
                                std::this_thread::sleep_for (std::chrono::seconds (1));
                                continue;
                        }
//                      std::cout << "Message sent!" << std::endl;
                        std::this_thread::sleep_for (std::chrono::seconds (1));
                }
        } catch (std::exception &E) {
                std::string BE05 = std::format ("Program crashed [Something went wrong [{}]]", E.what());
                std::cout <<BE05<< std::endl;
                return;
        } catch (...) {
                std::string BE05 = std::string ("Program crashed [A strange exception occured]");
                std::cout <<BE05<< std::endl;
                return;
        }
}
void    TS02 () {
        try{
                DTM::RS485::Client::ESP32::FreeRTOS::CPP::D68D838A BE05 (
                        1, 21, 23, 4, 8, 'N', 1, 9600, 256, 256
                );
                while(true) {
                        std::string CE01;
                        std::vector<uint8_t> CE05;
                        int8_t CE10 = BE05.r(CE01, CE05, 8, -1);
                        if (CE10 != 0) {
                                std::string  DE05 = std::format ("Data read failed [{}: {}]", CE10, CE01);
                                std::cout << DE05<< std::endl;
                                std::this_thread::sleep_for (std::chrono::seconds (1));
                                continue;
                        }
                        if (CE05.size() != 0) {
                                std::string  DE15 (CE05.begin(), CE05.end());
                                std::cout << DE15 << " " << CE05.size () << std::endl;
                        }
                }
        } catch (std::exception &E) {
                std::string BE05 = std::format ("Program crashed [Something went wrong [{}]]", E.what());
                std::cout <<BE05<< std::endl;
                return;
        } catch (...) {
                std::string BE05 = std::string ("Program crashed [A strange exception occured]");
                std::cout <<BE05<< std::endl;
                return;
        }
}
