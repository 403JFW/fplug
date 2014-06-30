#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "fplug.h"

double get_temp(int fd);
int get_humid(int fd);
int get_illum(int fd);
double get_rwatt(int fd);

int main(int argc, char *argv[]) {
    int fd;
    struct termios oldtio, newtio;

    time_t timer;
    struct tm *now;

    double temp, rwatt;
    int humid, illum;

    if (argc < 2) {
        return 1;
    }

    // Open serial port
    if ((fd = open(argv[1], O_RDWR)) == 1) {
        return 1;
    }

    // Get current date&time
    time(&timer);
    now = localtime(&timer);

    printf("%d/%02d/%02d ", 1900+now->tm_year, now->tm_mon+1, now->tm_mday);
    printf("%02d:%02d:%02d,", now->tm_hour, now->tm_min, now->tm_sec);

    // Initialize
    tcgetattr(fd, &oldtio);
    newtio = oldtio;
    newtio.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    tcsetattr(fd, TCSANOW, &newtio);

    // Get values
    temp = get_temp(fd);
    humid = get_humid(fd);
    illum = get_illum(fd);
    rwatt = get_rwatt(fd);
    printf("%f,%d,%d,%f\n", temp, humid, illum, rwatt);

    // Close serial port
    tcsetattr(fd, TCSANOW, &oldtio);
    close(fd);

    return 0;
}

double get_temp(int fd) {
    double result;
    unsigned char buffer[256];

    // Write
    write(fd, Temp, sizeof(Temp));
    // Read
    read(fd, buffer, 256);
    // Calc
    result = (buffer[14] + (buffer[15] << 8)) / 10;

    return result;
}

int get_humid(int fd) {
    int result;
    unsigned char buffer[256];

    // Write
    write(fd, Humid, sizeof(Humid));
    // Read
    read(fd, buffer, 256);
    result = buffer[14];

    return result;
}

int get_illum(int fd) {
    int result;
    unsigned char buffer[256];

    // Write
    write(fd, Illum, sizeof(Illum));
    // Read
    read(fd, buffer, 256);
    // Calc
    result = buffer[14] + (buffer[15] << 8);

    return result;
}

double get_rwatt(int fd) {
    double result;
    unsigned char buffer[256];

    // Write
    write(fd, RWatt, sizeof(RWatt));
    // Read
    read(fd, buffer, 256);
    // Calc
    result = ((double)buffer[14] + (double)(buffer[15] << 8)) / 10;

    return result;
}
