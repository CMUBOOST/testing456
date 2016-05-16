#include <ros/ros.h>
#include "epos_hardware/utils.h"
#include "epos_library/Definitions.h"
#include <boost/foreach.hpp>

int main(int argc, char** argv){
  uint64_t serial_number;
  if(argc == 2){
    if(!SerialNumberFromHex(argv[1], &serial_number)) {
      std::cerr << "Expected a serial number" << std::endl;
      return 1;
    }
  }
  else {
    std::cerr << "Expected exactly one argument that is a serial number" << std::endl;
    return 1;
  }

  std::string error_string;
  unsigned int error_code = 0;

  unsigned int ProfileVelocity = 1000;
  unsigned int ProfileAcceleration = 1000;
  unsigned int ProfileDeceleration = 1000;
  int Immediately = 1;
  int Absolute = 0;
  long TargetPosition = 10000;
  char* pOperationMode;
  char OperationMode = -2;
  unsigned int MaxFollowingError = 2000;
  unsigned int* pMaxFollowingError;
  unsigned short* pMotorType;


  std::cout << "Searching for USB EPOS2: 0x" << std::hex << serial_number << std::endl;

  std::string port_name;

  EposFactory epos_factory;

  NodeHandlePtr handle;
  if(handle = epos_factory.CreateNodeHandle("EPOS2", "MAXON SERIAL V2", "USB", serial_number, &error_code)) {
    int position;
    std::cout << handle << std::endl;
    //VCS_GetMotorType(handle->device_handle->ptr, handle->node_id, pMotorType, &error_code);


    if(VCS_ActivateProfilePositionMode(handle->device_handle->ptr, handle->node_id, &error_code)){
      std::cout << "Activated Profile Position" << std::endl;
    }

    else {
      if(GetErrorInfo(error_code, &error_string)){
    std::cerr << "Could not get position: " << error_string << std::endl;
      } else {
    std::cerr << "Could not get position" << std::endl;
      }
    }


    if(VCS_SetPositionProfile(handle->device_handle->ptr, handle->node_id, ProfileVelocity, ProfileAcceleration, ProfileDeceleration, &error_code)){
      std::cout << "Set Position Profile" << std::endl;
    }

    else {
      if(GetErrorInfo(error_code, &error_string)){
    std::cerr << "Could not get position: " << error_string << std::endl;
      } else {
    std::cerr << "Could not get position" << std::endl;
      }
    }


    if(VCS_MoveToPosition(handle->device_handle->ptr, handle->node_id, TargetPosition, Absolute, Immediately, &error_code)){
      std::cout << "Moving to position!" << std::endl;
    }

    else {
      if(GetErrorInfo(error_code, &error_string)){
    std::cerr << "Could not get position: " << error_string << std::endl;
      } else {
    std::cerr << "Could not get position" << std::endl;
      }
    }


    if(VCS_GetPositionIs(handle->device_handle->ptr, handle->node_id, &position, &error_code)){
      std::cout << "Position: " << std::dec << position << std::endl;
    }
    else {
      if(GetErrorInfo(error_code, &error_string)){
	std::cerr << "Could not get position: " << error_string << std::endl;
      } else {
	std::cerr << "Could not get position" << std::endl;
      }

    }

    if(VCS_SetOperationMode(handle->device_handle->ptr, handle->node_id, OperationMode, &error_code)){
      std::cout << "Getting Operation Mode:" << std::endl;
      std::cout << VCS_GetOperationMode(handle->device_handle->ptr, handle->node_id, pOperationMode, &error_code) << std::endl;
    }
    else {
      if(GetErrorInfo(error_code, &error_string)){
    std::cerr << "Could not get position: " << error_string << std::endl;
      } else {
    std::cerr << "Could not get position" << std::endl;
      }

    }

    /*
    if(VCS_GetMaxFollowingError(handle->device_handle->ptr, handle->node_id, pMaxFollowingError, &error_code)){
      std::cout << "Getting Operation Mode:" << std::endl;
      //std::cout << VCS_GetMaxFollowingError(handle->device_handle->ptr, handle->node_id, pMaxFollowingError, &error_code) << std::endl;
    }
    else {
      if(GetErrorInfo(error_code, &error_string)){
    std::cerr << "Could not get position: " << error_string << std::endl;
      } else {
    std::cerr << "Could not get position" << std::endl;
      }

    }
    */

    int velocity;
    if(VCS_GetVelocityIs(handle->device_handle->ptr, handle->node_id, &velocity, &error_code)){
      std::cout << "Velocity: " << std::dec << velocity << std::endl;
    }
    else {
      if(GetErrorInfo(error_code, &error_string)){
	std::cerr << "Could not get velocity: " << error_string << std::endl;
      } else {
	std::cerr << "Could not get velocity" << std::endl;
      }
    }

    short current;
    if(VCS_GetCurrentIs(handle->device_handle->ptr, handle->node_id, &current, &error_code)){
      std::cout << "Current: " << std::dec << current << std::endl;
    }
    else {
      if(GetErrorInfo(error_code, &error_string)){
	std::cerr << "Could not get current: " << error_string << std::endl;
      } else {
	std::cerr << "Could not get current" << std::endl;
      }
    }

  }
  else {
    if(GetErrorInfo(error_code, &error_string)){
      std::cerr << "Could not open device: " << error_string << std::endl;
    } else {
      std::cerr << "Could not open device" << std::endl;
    }
    return 1;
  }
}
