#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wiringPi.h>
#include <math.h>

#define ledx 0
#define ledy 2

/* Skeleton Code Provided By: github.com/sunfounder/Sunfounder_SuperKit_C_code_for_RaspberryPi/blob/master/14_ADXL345/adxl345.c */

#define DevAddr 0x53

struct acc_dat {
  int x;
  int y;
  int z;
};

//Initializes the accelerometer
void adx1345_init(int fd) {
  wiringPiI2CWriteReg8(fd, 0x31, 0x0B);
  wiringPiI2CWriteReg8(fd, 0x2D, 0x08);
  wiringPiI2CWriteReg8(fd, 0x1E, 0x00);
  wiringPiI2CWriteReg8(fd, 0x1F, 0x00);
  wiringPiI2CWriteReg8(fd, 0x20, 0x00);
  wiringPiI2CWriteReg8(fd, 0x21, 0x00);
  wiringPiI2CWriteReg8(fd, 0x22, 0x00);
  wiringPiI2CWriteReg8(fd, 0x23, 0x00);
  wiringPiI2CWriteReg8(fd, 0x24, 0x01);
  wiringPiI2CWriteReg8(fd, 0x25, 0x0F);
  wiringPiI2CWriteReg8(fd, 0x26, 0x2B);
  wiringPiI2CWriteReg8(fd, 0x27, 0x00);
  wiringPiI2CWriteReg8(fd, 0x28, 0x09);
  wiringPiI2CWriteReg8(fd, 0x29, 0xFF);
  wiringPiI2CWriteReg8(fd, 0x2A, 0x80);
  wiringPiI2CWriteReg8(fd, 0x2C, 0x0A);
  wiringPiI2CWriteReg8(fd, 0x2F, 0x00);
}

//Reads the input from the accelerometer
struct acc_dat adx1345_read_xyz(int fd) {
  char x0, y0, z0, x1, y1, z1;
  struct acc_dat acc_xyz;
  x0 = 0xFF - wiringPiI2CReadReg8(fd, 0x32);
  x1 = 0xFF - wiringPiI2CReadReg8(fd, 0x33);
  y0 = 0xFF - wiringPiI2CReadReg8(fd, 0x34);
  y1 = 0xFF - wiringPiI2CReadReg8(fd, 0x35);
  z0 = 0xFF - wiringPiI2CReadReg8(fd, 0x36);
  z1 = 0xFF - wiringPiI2CReadReg8(fd, 0x37);
  acc_xyz.x = (int)(x1 << 8) + (int)x0;
  acc_xyz.y = (int)(y1 << 8) + (int)y0;
  acc_xyz.z = (int)(z1 << 8) + (int)z0;
  return acc_xyz;
}

int main() {
  int fd;
  struct acc_dat acc_xyz;
  fd = wiringPiI2CSetup(DevAddr);
  if (fd == -1) {
    perror("I2C device setup error");
  }
  if (wiringPiSetup() == -1) {
    printf("Wiring Setup Failed");
    return 1;
  }
  pinMode(ledx, OUTPUT);
  pinMode(ledy, OUTPUT);
  adx1345_init(fd);
  while(1) {
    acc_xyz = adx1345_read_xyz(fd);
    //printf("x: %d, y: %d, z: %d, max: %d\n", acc_xyz.x, acc_xyz.y, acc_xyz.z, 0xFFFF);

/* My Code */

    //printf("x degree: %f, y degree: %f\n", 180 * (double)acc_xyz.x/0xFFFF, 180 * (double)acc_xyz.y/0xFFFF);
    //Light the red LED if the X plane is level
    if ((int)(180 * (1 - (double)acc_xyz.x/0xFFFF)) >= 179) {
      digitalWrite(ledx, LOW);
    } else {
      digitalWrite(ledx, HIGH);
    }
    //Light the green LED if the Y plane is level
    if ((int)(180 * (1 - (double)acc_xyz.y/0xFFFF)) >= 179) {
      digitalWrite(ledy, LOW);
    } else {
      digitalWrite(ledy, HIGH);
    }
    delay(1000);
  }
  return 0;
}
