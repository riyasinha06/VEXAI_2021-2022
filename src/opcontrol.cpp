#include "main.h"
#include "Robot.h"
#include "system/Serial.h"
using namespace pros;

/* Creates all tasks required for our Robot's driver control period */

void opcontrol() {

	lcd::initialize();
	delay(100);
	serial_initialize();
	lib7405x::Serial::Instance()->send(lib7405x::Serial::STDOUT, "#continue#true#camera#l515_back#mode#false#@#");
	//Robot::start_task("GPS", Robot::gps_fps);
	Robot::start_task("DRIVE", Robot::drive);
	Robot::start_task("CONTROLLER", Robot::controller_print);

	Robot::IMU.reset();
	delay(2500);
	Robot::start_task("FPS", Robot::fps);
	Robot::start_task("DISPLAY", Robot::display);
	lib7405x::Serial::Instance()->onReceive("fps", Robot::receive_fps);
	lib7405x::Serial::Instance()->onReceive("mogo", Robot::receive_mogo);
	lib7405x::Serial::Instance()->onReceive("ring", Robot::receive_ring);
	//Robot::start_task("MOVETO", Robot::move_to);
	Robot::start_task("IMU", Robot::imu_clamp);

}

