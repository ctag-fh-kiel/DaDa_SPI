// Example: DaDa_SPI Basic Usage
// This sketch demonstrates how to use the DaDa_SPI library for SPI DMA transmission on RP2040/RP2350.

#include <DaDa_SPI.h>

// Define SPI settings
#define SPI_PORT spi0
#define SPI_SCK_PIN 18
#define SPI_MOSI_PIN 19
#define SPI_MISO_PIN 16
#define SPI_CS_PIN 17
#define SPI_SPEED 1000000

DaDa_SPI dadaSPI(SPI_PORT, SPI_CS_PIN, SPI_MOSI_PIN, SPI_MISO_PIN, SPI_SCK_PIN, SPI_SPEED);

// Double buffers for transmission and reception
uint8_t txBufferA[16] = {0};
uint8_t txBufferB[16] = {0};
uint8_t rxBufferA[16] = {0};
uint8_t rxBufferB[16] = {0};

// Buffer toggle flag
bool useBufferA = true;
bool dmaInProgress = false;

void setup() {
    Serial.begin(115200);
    Serial.println("DaDa_SPI Example: Starting DMA SPI transfer with double buffering...");
}

void loop() {
    if (!dmaInProgress) {
        // Prepare data for the next transfer
        if (useBufferA) {
            for (int i = 0; i < 16; i++) txBufferA[i] = i + 10; // Example data
            dadaSPI.StartDMA(txBufferA, rxBufferA, sizeof(txBufferA));
        } else {
            for (int i = 0; i < 16; i++) txBufferB[i] = i + 100; // Example data
            dadaSPI.StartDMA(txBufferB, rxBufferB, sizeof(txBufferB));
        }
        dmaInProgress = true;
    }

    // Do other tasks here while DMA is running
    // Example: process the inactive RX buffer while DMA is running
    if (dmaInProgress) {
        if (useBufferA) {
            // Buffer B is inactive, safe to process
            Serial.print("Processing inactive buffer B: ");
            for (int i = 0; i < 16; i++) {
                rxBufferB[i] += 1; // Example processing: increment each byte
                Serial.print(rxBufferB[i]);
                Serial.print(" ");
            }
            Serial.println();
        } else {
            // Buffer A is inactive, safe to process
            Serial.print("Processing inactive buffer A: ");
            for (int i = 0; i < 16; i++) {
                rxBufferA[i] += 1; // Example processing: increment each byte
                Serial.print(rxBufferA[i]);
                Serial.print(" ");
            }
            Serial.println();
        }
        delay(100); // Simulate time spent processing
    }

    // Check if DMA transfer is complete (non-blocking)
    if (dmaInProgress && !dadaSPI.IsBusy()) {
        if (useBufferA) {
            Serial.println("DMA SPI transfer complete (Buffer A). Received data:");
            for (int i = 0; i < 16; i++) {
                Serial.print(rxBufferA[i]);
                Serial.print(" ");
            }
        } else {
            Serial.println("DMA SPI transfer complete (Buffer B). Received data:");
            for (int i = 0; i < 16; i++) {
                Serial.print(rxBufferB[i]);
                Serial.print(" ");
            }
        }
        Serial.println();
        useBufferA = !useBufferA; // Swap buffers
        dmaInProgress = false;
        delay(500); // For demonstration, slow down the loop
    }
}
