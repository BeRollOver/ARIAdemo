#include "Aria.h"
#include <stdio.h>
#include <iostream>

/*
----------------------------------------------------------
Print raw sonar data
----------------------------------------------------------
*/
void getSonar(ArRobot *thisRobot)
{

	int numSonar; //Number of sonar on the robot
	int i; //Counter for looping
	numSonar = thisRobot->getNumSonar(); //Get number of sonar
	ArSensorReading* sonarReading; //To hold each reading
	for (i = 0; i < numSonar; i++) //Loop through sonar
	{
		sonarReading = thisRobot->getSonarReading(i);
		//Get each sonar reading
		std::cout << "Sonar reading " << i << "=" << sonarReading->getRange()
			<< " Angle " << i << " = " <<
			sonarReading->getSensorTh() << "\n";
	}
}

/* Main method */
int main(int argc, char **argv)
{

	/* The robot and its devices */

	Aria::init(); //Initialise ARIA library

	ArRobot robot; //Instantiate robot
	ArSick laser; //Instantiate its laser
	ArSonarDevice sonar; //Instantiate its sonar
	ArBumpers bumpers; //Instantiate its bumpers

	robot.addRangeDevice(&sonar); //Add sonar to robot
	robot.addRangeDevice(&laser); //Add laser to robot
	robot.addRangeDevice(&bumpers); //Add bumpers to robot

	ArArgumentParser parser(&argc, argv); //Instantiate argument parser
	ArSimpleConnector connector(&parser); //Instantiate connector

	/* Connection to robot */
	parser.loadDefaultArguments(); //Load default values

	if (!connector.parseArgs()) //Parse connector arguments
	{
		std::cout << "Unknown settings\n"; //Exit for errors 
		Aria::exit(0);
		exit(1);
	}

	if (!connector.connectRobot(&robot)) //Connect to the robot 
	{
		std::cout << "Unable to connect\n"; //Exit for errors 
		Aria::exit(0);
		exit(1);
	}

	robot.runAsync(true); //Run in asynchronous mode 

	robot.lock(); //Lock robot during set up 
	robot.comInt(ArCommands::ENABLE, 1); //Turn on the motors
	robot.unlock(); //Unlock the robot 

	//getSonar(&robot);d
	double reading, readingAngle; //To hold minimum reading and angle
	reading = sonar.currentReadingPolar(0, 90, &readingAngle); //Get minimum reading and angle
	double x = robot.getX();
	double y = robot.getY();
	//ArUtil::sleep(3000);

	robot.setVel(100); //Set translational velocity to 100 mm/s
	//robot.setRotVel(20); //Set rotational velocity to 20 degrees/s
	//robot.setVel2(100, 150); //Set left wheel speed at 100 mm/s
	//Set right wheel speed at 150 mm/s
	//robot.setHeading(30); //30 degrees relative to start position
	//ArUtil::sleep(3000);
	//robot.setDeltaHeading(60); //60 degrees relative to current orientation
	//ArUtil::sleep(3000);
	robot.move(150); //Move 150 mm forwards
	ArUtil::sleep(3000);
	double readingAngle2;
	double reading2 = sonar.currentReadingPolar(0, 90, &readingAngle); //Get minimum reading and angle

	//std::cout << "\nNew sonar data:\n";
	//getSonar(&robot);

	//char c;
	//std::cin >> c;
	Aria::exit(0); //Exit Aria 
} //End main