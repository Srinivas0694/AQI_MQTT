#ifndef AWS_IOT_HPP
#define AWS_IOT_HPP

#include "sensors.hpp"

void aws_init();
void aws_publish(const SensorData &data);
void aws_loop();

#endif
