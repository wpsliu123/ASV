/*
*******************************************************************************
* controllerdata.h:
* define the data struct used in the controller
* This header file can be read by C++ compilers
*
* by Hu.ZH(CrossOcean.ai)
*******************************************************************************
*/

#ifndef _CONTROLLERDATA_H_
#define _CONTROLLERDATA_H_

#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>

// real-time data in the controller
template <int m, int n = 3>
struct controllerRTdata {
  // Fx, Fy, Mz (desired force) in the body coordinate
  Eigen::Matrix<double, n, 1> tau;
  // Fx, Fy, Mz (estimated generalized force) in the body-fixed coordinates
  Eigen::Matrix<double, n, 1> BalphaU;
  // N, estimated thrust of all propellers
  Eigen::Matrix<double, m, 1> u;
  // rpm, rotation of all propellers
  Eigen::Matrix<int, m, 1> rotation;
  // rad, angle of all propellers
  Eigen::Matrix<double, m, 1> alpha;
  // deg, angle of all propellers
  Eigen::Matrix<int, m, 1> alpha_deg;
};

struct thrustallocationdata {
  const int num_tunnel;      // # of tunnel thruster
  const int num_azimuth;     // # of azimuth thruster
  const int num_mainrudder;  // # of main thruster with rudder
  const std::vector<int> index_thrusters;
  const std::string logpath;  // directory for log file
};

// constant data of tunnel thruster, index = 1
struct tunnelthrusterdata {
  const double lx;  // m
  const double ly;  // m
  const double K_positive;
  const double K_negative;
  const int max_delta_rotation;
  const int max_rotation;
  const double max_thrust_positive;
  const double max_thrust_negative;
};

// constant data of azimuth thruster, index = 2
// Azimuth thruster can be used for fixed thruster, with a fixed alpha
struct azimuththrusterdata {
  const double lx;               // m
  const double ly;               // m
  const double K;                //
  const int max_delta_rotation;  // rpm
  const int max_rotation;        // rpm
  const int min_rotation;        // rpm
  const double max_delta_alpha;  // rad
  const double max_alpha;        // rad
  const double min_alpha;        // rad
  const double max_thrust;       // N
  const double min_thrust;       // N
};

// constant data of main propeller with rudder, index = 3
struct ruddermaindata {
  double lx;                  // m
  double ly;                  // m
  double K;                   //
  double max_delta_rotation;  // rpm
  double max_rotation;        // rpm
  double min_rotation;        // rpm
  double max_delta_alpha;     // rad
  double max_alpha;           // rad
  double min_alpha;           // rad
  double max_thrust;          // N
  double min_thrust;          // N
};

// quasi-static data of pid controller
struct pidcontrollerdata {
  double p;
  double I;
  double D;
  const double allowed_error;
  const double max_output;
  const double min_output;
}
#endif /* _CONTROLLERDATA_H_ */