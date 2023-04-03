#include <stdio.h>
#include <stdint.h>
#include <wiringPiSPI.h>
#include <unistd.h>

// gcc -o spi_example spi_example.c -lwiringPi
// ./spi_example

#define SPI_CHANNEL 0
#define SPI_SPEED   1000000 // 1 MHz

int main(void) {
    int fd;
    uint8_t data[2] = {0};

    // Initialize WiringPi SPI
    if ((fd = wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED)) < 0) {
        fprintf(stderr, "Failed to initialize SPI: %s\n", strerror(errno));
        return 1;
    }

    // Send and receive example data
    while (1) {
        data[0] = 0xAA; // Replace this value with the data you want to send
        data[1] = 0xBB;

        if (wiringPiSPIDataRW(SPI_CHANNEL, data, sizeof(data)) < 0) {
            fprintf(stderr, "SPI transaction failed: %s\n", strerror(errno));
            return 1;
        }

        printf("Received data: 0x%02X 0x%02X\n", data[0], data[1]);
        sleep(1); // Wait for a second
    }

    return 0;
}