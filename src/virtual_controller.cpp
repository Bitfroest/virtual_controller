#include "virtual_controller.h"
#include "lms/datamanager.h"
#include "gamepad/gamepad.h"

#include <cmath>

bool VirtualController::initialize(){
    senseBoard = datamanager()
            ->writeChannel<sense_link::SenseBoard>(this, "SENSE_BOARD");
    gamePad = datamanager()
            ->readChannel<Gamepad>(this,"360");
    return true;
}

bool VirtualController::cycle(){
    using sense_link::SensorData;

    static int time = 0;
    static int16_t servoValue = 90;

    time ++;

    Gamepad::axis ls = gamePad->getAxis("LS");
    Gamepad::axis rt = gamePad->getAxis("RT");
    Gamepad::axis lt = gamePad->getAxis("LT");

    servoValue = (int) (ls.x*3000);
    logger.warn("cycle") << "ServoValue: " << servoValue;
    SensorData data;

    data.MotorVelocity.acceleration = ((rt.x-lt.x)*10000);
    senseBoard->setSensor(sense_link::MOTOR_VELOCITY,1,data);

    data.Servo.angle = servoValue;
    senseBoard->setSensor(sense_link::SERVO,1,data);
    return true;
}

bool VirtualController::deinitialize(){
    return true;
}
