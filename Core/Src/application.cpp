#include "application.h"
#include "csp/csp4cmsis.h"
#include <cstdio>

using namespace csp;

// Single process that prints "Hello world" forever
class HelloProcess : public CSProcess {
public:
    void run() override {
        while (true) {
            printf("Hello world\r\n");
            // Optional delay to avoid flooding the console
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
};

// Main application task that builds the static CSP network
void MainApp_Task(void* params) {
    vTaskDelay(pdMS_TO_TICKS(10));
    printf("\r\n--- Single Hello World Process ---\r\n");

    static HelloProcess hello;

    Run(
        InParallel(hello),
        ExecutionMode::StaticNetwork
    );
}

// Entry point called by the CSP4CMSIS runtime
void csp_app_main_init(void) {
    BaseType_t status = xTaskCreate(MainApp_Task, "MainApp", 2048, NULL, tskIDLE_PRIORITY + 3, NULL);
    if (status != pdPASS) {
        printf("ERROR: MainApp_Task creation failed!\r\n");
    }
}
