/*
 * Vehicle Control System.c
Author: Omar Saad
Name : Mini Project C 1
Description : Vehicle Control System
Created on: Aug 24, 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//preprocessor directive to control execution or not of engine temperature codes
#define WITH_ENGINE_TEMP_CONTROLLER 1
//Structure contains variables related to vehicle
struct vehicle{
	bool engine;
	unsigned short speed;
	bool AC;
	short room_temperature;
#if (WITH_ENGINE_TEMP_CONTROLLER)
	bool engine_temp_controller;
	short engine_temperature;
#endif
}v;
//Functions Prototypes
void set_initial_vehicle_values();
void initialize_system();
void sensors_set_menu();
void traffic_light();
void room_temperature();
void check_speed();
void dispay_vehicle_state();

#if (WITH_ENGINE_TEMP_CONTROLLER)
void engine_temperature();
#endif

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0); setvbuf(stderr, NULL, _IONBF, 0);
//	Initialize vehicle values with average values
	set_initial_vehicle_values();
//	Start the system
	initialize_system();
	return 0;
}

//Function to ask the user to open or close the system
void initialize_system(){
	printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n\n");
	char state ='b';
	scanf(" %c",&state);
	switch(state){
	case 'A':	//Turn ON
	case 'a':
		printf("Turn on the vehicle engine\n\n");
		v.engine= true;
		sensors_set_menu();
		break;
	case 'B':	//Turn OFF
	case 'b':
		printf("Turn off the vehicle engine\n\n");
		initialize_system();
		v.engine= false;
		break;
	case 'C':	//End System
	case 'c':
		printf("Quit the system\n\n");
		exit(0);
	default:
		printf("Please enter valid state\n\n");
		initialize_system();
		break;
	}
}
//Function to open Menu of setting sensors
void sensors_set_menu(){
	printf("a. Turn off the engine\nb. Set the traffic light color.\nc. Set the room temperature (Temperature Sensor)\n");
#if (WITH_ENGINE_TEMP_CONTROLLER)
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif
	printf("\n");
	char menu_state ='a';
	scanf(" %c",&menu_state);
	switch(menu_state){
	case 'A':	//Turn OFF
	case 'a':
		printf("Turn off the vehicle engine\n\n");
		initialize_system();
		break;
	case 'B':	//Traffic light
	case 'b':
		traffic_light();
		break;
	case 'C':	//Room temperature
	case 'c':
		room_temperature();
		break;
#if (WITH_ENGINE_TEMP_CONTROLLER)
	case 'D':	//Engine temperature
	case 'd':
		engine_temperature();
		break;
#endif
	default:
		printf("Please enter valid option\n\n");
		sensors_set_menu();
		break;
	}
}
//Function to take input traffic light state to decide vehicle speed
void traffic_light(){
	printf("Enter The Required Color\n\n");
	char color ='R';
	scanf(" %c",&color);
	switch(color){
	case 'G':	//Green traffic color
	case 'g':
		v.speed=100;
		break;
	case 'O':	//Orange traffic color
	case 'o':
		v.speed=30;
		break;
	case 'R':	//Red traffic color
	case 'r':
		v.speed=0;
		break;
	default:
		printf("Please enter valid color\n\n");
		traffic_light();
		break;
	}
	dispay_vehicle_state();
}
//Function to take room temperature input to set AC state and temperature
void room_temperature(){
	printf("Enter The Required Room Temperature\n\n");
	short room_temp ='R';
	scanf(" %hi",&room_temp);
//	If room temperature less than 10 set AC to 20 degrees C
	if (room_temp<10){
		v.AC= true;
		v.room_temperature= 20;
	}
//	If room temperature more than 30 set AC to 20 degrees C
	else if (room_temp>30){
		v.AC= true;
		v.room_temperature= 20;
	}
//If temperature is between 10 and 30 Turn OFF AC
	else{
		v.AC= false;
	}
	dispay_vehicle_state();
}
/*Function to take engine temperature  as input and
 set the engine temperature controller state and temperature */
#if (WITH_ENGINE_TEMP_CONTROLLER)
void engine_temperature(){
	printf("Enter The Required Engine Temperature\n");
	short engine_temp ='R';
	scanf(" %hi",&engine_temp);
//If engine temperature less than 100 set engine temperature to 125
	if (engine_temp<100){
		v.engine_temp_controller= true;
		v.engine_temperature= 125;
	}
//If engine temperature more than 150 set engine temperature to 125
	else if (engine_temp>150){
		v.engine_temp_controller= true;
		v.engine_temperature= 125;
	}
//If engine temperature between 100 and 150 Close engine temperature controller
	else{
		v.engine_temp_controller= false;
	}
	dispay_vehicle_state();
}
#endif
/*Function to check speed and if speed is 30 Km/Hr Open the
AC and the Engine temperature controller
and set their temperature values */
void check_speed(){
	if (v.speed==30){
		v.AC= true;
		v.room_temperature=v.room_temperature* 5/4 +1;
#if (WITH_ENGINE_TEMP_CONTROLLER)
		v.engine_temp_controller= true;
		v.engine_temperature=v.engine_temperature* 5/4 +1;
#endif
	}
}
//Function to display all the values of the vehicle variables to the user
void dispay_vehicle_state(){
//	Check Speed each time before displaying
	check_speed();
	v.engine? printf("Engine is ON\n") : printf("Engine is OFF\n");
	v.AC? printf("AC is ON\n") : printf("AC is OFF\n");
	printf("Vehicle Speed: %hu Km\\Hr\n",v.speed);
	printf("Room Temperature: %hi C\n",v.room_temperature);
#if (WITH_ENGINE_TEMP_CONTROLLER)
	v.engine_temp_controller? printf("Engine Temp Controller is ON\n") : printf("Engine Temp Controller is OFF\n");
	printf("Engine Temperature: %hi C\n",v.engine_temperature);
#endif
	printf("\n");
	sensors_set_menu();
}
//Function to set initial values to vehicle structure variables
void set_initial_vehicle_values(){
	v.engine=false;
	v.speed=0;
	v.AC= false;
	v.room_temperature=35;
#if (WITH_ENGINE_TEMP_CONTROLLER)
	v.engine_temp_controller=false;
	v.engine_temperature=95;
#endif
}
