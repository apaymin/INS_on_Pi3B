#include <stdio.h>
#include <stdint.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <sys/time.h>

#define SPI_CHANNEL 0
#define SPI_SPEED   1000000 // 1 MHz

// gcc -o spi_example spi_example.c -lwiringPi
// ./spi_example

int main(void) {
    int fd;
    uint8_t data[2] = {0};
    struct timeval currentTime;

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

        // Get the current timestamp
        gettimeofday(&currentTime, NULL);
        printf("Timestamp: %ld.%06ld | Received data: 0x%02X 0x%02X\n",
            currentTime.tv_sec, currentTime.tv_usec, data[0], data[1]);
    }

    return 0;
}