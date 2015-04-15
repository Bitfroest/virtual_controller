#include "virtual_controller.h"
#include "lms/datamanager.h"

#include <cmath>

bool VirtualController::initialize(){
    senseBoard = datamanager()
            ->writeChannel<sense_link::SenseBoard>(this, "SENSE_BOARD");
    return true;
}

bool VirtualController::cycle(){
    using sense_link::SensorData;

    static int time = 0;
    static int16_t servoValue = 90;

    time ++;

    servoValue = (int) (30 * sin(0.1*time)) + 90;
    logger.warn("cycle") << "ServoValue: " << servoValue;
    SensorData data;

    data.MotorVelocity.acceleration = 500;
    senseBoard->setSensor(sense_link::MOTOR_VELOCITY,1,data);

    data.Servo.angle = servoValue;
    senseBoard->setSensor(sense_link::SERVO,1,data);
    return true;
}

bool VirtualController::deinitialize(){
    return true;
}
