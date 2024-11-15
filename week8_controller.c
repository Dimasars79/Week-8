/*
 * File:          week8_controller.c
 * Date:
 * Description:   Robot memutari bola secara statis
 * Author:        Your Name
 * Modifications: 
 */

#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

#define TIME_STEP 64

int main(int argc, char **argv) {
  wb_robot_init();

  // Deklarasi dan inisialisasi motor
  WbDeviceTag motor_kanan = wb_robot_get_device("right wheel motor");
  WbDeviceTag motor_kiri = wb_robot_get_device("left wheel motor");
  wb_motor_set_position(motor_kanan, INFINITY);
  wb_motor_set_position(motor_kiri, INFINITY);

  // Deklarasi dan inisialisasi sensor jarak
  WbDeviceTag sensor_depan = wb_robot_get_device("front distance sensor");
  wb_distance_sensor_enable(sensor_depan, TIME_STEP);

  // Kecepatan statis untuk memutari bola
  double kecepatan_motor_kanan = 2.0; // Lebih cepat
  double kecepatan_motor_kiri = 1.0;  // Lebih lambat

  while (wb_robot_step(TIME_STEP) != -1) {
    // Membaca nilai sensor jarak depan
    double jarak_depan = wb_distance_sensor_get_value(sensor_depan);

    // Jika bola terdeteksi di depan, robot mulai memutar
    if (jarak_depan < 800) { 
      wb_motor_set_velocity(motor_kanan, kecepatan_motor_kanan);
      wb_motor_set_velocity(motor_kiri, kecepatan_motor_kiri);
    } else {
      // Jika bola tidak terdeteksi, berhenti
      wb_motor_set_velocity(motor_kanan, 0.0);
      wb_motor_set_velocity(motor_kiri, 0.0);
    }
  }

  wb_robot_cleanup();

  return 0;
}
