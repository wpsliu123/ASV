/*
*******************************************************************************
* testthrust.cpp:
* unit test for thrust allocation
* This header file can be read by C++ compilers
*
* by Hu.ZH(CrossOcean.ai)
*******************************************************************************
*/

#include "thrustallocation.h"
#include "utilityio.h"

INITIALIZE_EASYLOGGINGPP

// test thrust allocation for 4 propellers (fully actuated)
void testonestepthrustallocation() {
  const int m = 4;
  const int n = 3;
  constexpr ACTUATION index_actuation = FULLYACTUATED;

  std::vector<int> index_thrusters{1, 1, 2, 2};

  int num_tunnel =
      std::count(index_thrusters.begin(), index_thrusters.end(), 1);

  int num_azimuth =
      std::count(index_thrusters.begin(), index_thrusters.end(), 2);

  int num_mainrudder =
      std::count(index_thrusters.begin(), index_thrusters.end(), 3);

  thrustallocationdata _thrustallocationdata{num_tunnel, num_azimuth,
                                             num_mainrudder, index_thrusters};

  std::vector<tunnelthrusterdata> v_tunnelthrusterdata;
  v_tunnelthrusterdata.reserve(num_tunnel);
  v_tunnelthrusterdata.push_back({
      1.9,   // lx
      0,     // ly
      1e-6,  // K_positive
      2e-6,  // K_negative
      50,    // max_delta_rotation
      1000,  // max_rotation
      1,     // max_thrust_positive
      2      // max_thrust_negative
  });
  v_tunnelthrusterdata.push_back({
      1,     // lx
      0,     // ly
      1e-6,  // K_positive
      2e-6,  // K_negative
      50,    // max_delta_rotation
      1000,  // max_rotation
      1,     // max_thrust_positive
      2      // max_thrust_negative
  });

  std::vector<azimuththrusterdata> v_azimuththrusterdata;
  v_azimuththrusterdata.reserve(num_azimuth);
  v_azimuththrusterdata.push_back({
      -1.893,         // lx
      -0.216,         // ly
      2e-5,           // K
      10,             // max_delta_rotation
      1000,           // max rotation
      10,             // min_rotation
      0.1277,         // max_delta_alpha
      M_PI / 6,       // max_alpha
      -7 * M_PI / 6,  // min_alpha
      20,             // max_thrust
      2e-3            // min_thrust
  });
  v_azimuththrusterdata.push_back({
      -1.893,        // lx
      0.216,         // ly
      2e-5,          // K
      10,            // max_delta_rotation
      1000,          // max rotation
      10,            // min_rotation
      0.1277,        // max_delta_alpha
      7 * M_PI / 6,  // max_alpha
      -M_PI / 6,     // min_alpha
      20,            // max_thrust
      2e-3           // min_thrust
  });
  std::vector<ruddermaindata> v_ruddermaindata;

  controllerRTdata<m, n> _controllerRTdata{
      (Eigen::Matrix<double, n, 1>() << 0, 0, 1).finished(),       // tau
      Eigen::Matrix<double, n, 1>::Zero(),                         // BalphaU
      (Eigen::Matrix<double, m, 1>() << 0, 0.5, 0, 1).finished(),  // u
      // vectormi()::Zero(),                    // rotation
      (Eigen::Matrix<int, m, 1>() << 100, 500, 400, 300).finished(),
      (Eigen::Matrix<double, m, 1>() << M_PI / 2, -M_PI / 2, M_PI * 2 / 3, 0)
          .finished(),                  // alpha
      Eigen::Matrix<int, m, 1>::Zero()  // alpha_deg

  };

  thrustallocation<m, index_actuation, n> _thrustallocation(
      _thrustallocationdata, v_tunnelthrusterdata, v_azimuththrusterdata,
      v_ruddermaindata);
  _thrustallocation.initializapropeller(_controllerRTdata);
  utilityio _utilityio;

  std::cout << _controllerRTdata.alpha << std::endl;
  std::cout << "upper_delta_alpha: " << _thrustallocation.getupper_delta_alpha()
            << std::endl;
  std::cout << "lower_delta_alpha: " << _thrustallocation.getlower_delta_alpha()
            << std::endl;
  std::cout << "upper_delta_u: " << _thrustallocation.getupper_delta_u()
            << std::endl;
  std::cout << "lower_delta_u: " << _thrustallocation.getlower_delta_u()
            << std::endl;
  std::cout << "Q: " << _thrustallocation.getQ() << std::endl;
  std::cout << "Omega: " << _thrustallocation.getOmega() << std::endl;
  std::cout << "Q_deltau: " << _thrustallocation.getQ_deltau() << std::endl;
  std::cout << "g_deltau: " << _thrustallocation.getg_deltau() << std::endl;
  std::cout << "d_rho: " << _thrustallocation.getd_rho() << std::endl;
  std::cout << "B_alpha: " << _thrustallocation.getB_alpha() << std::endl;
  std::cout << "d_Balpha_u: " << _thrustallocation.getd_Balpha_u() << std::endl;
  std::cout << "lx: " << _thrustallocation.getlx() << std::endl;

  Eigen::MatrixXd vvv(2, 3);
  vvv.setZero();
  _utilityio.write2csvfile("csvfile.csv", vvv);
}

// test thrust allocation for 3 propellers (fully actuated)
void test_multiplethrusterallocation() {
  // set the parameters in the thrust allocation
  const int m = 3;
  const int n = 3;
  constexpr ACTUATION index_actuation = FULLYACTUATED;

  std::vector<int> index_thrusters{1, 2, 2};

  int num_tunnel =
      std::count(index_thrusters.begin(), index_thrusters.end(), 1);

  int num_azimuth =
      std::count(index_thrusters.begin(), index_thrusters.end(), 2);

  int num_mainrudder =
      std::count(index_thrusters.begin(), index_thrusters.end(), 3);

  thrustallocationdata _thrustallocationdata{num_tunnel, num_azimuth,
                                             num_mainrudder, index_thrusters};

  std::vector<tunnelthrusterdata> v_tunnelthrusterdata;
  v_tunnelthrusterdata.reserve(num_tunnel);
  v_tunnelthrusterdata.push_back(
      {1.9, 0, 3.7e-7, 1.7e-7, 50, 3000, 3.33, 1.53});

  std::vector<azimuththrusterdata> v_azimuththrusterdata;
  v_azimuththrusterdata.reserve(num_azimuth);
  v_azimuththrusterdata.push_back({
      -1.893,            // lx
      -0.216,            // ly
      2e-5,              // K
      20,                // max_delta_rotation
      1000,              // max rotation
      10,                // min_rotation
      0.1277,            // max_delta_alpha
      M_PI * 175 / 180,  // max_alpha
      M_PI / 18,         // min_alpha
      20,                // max_thrust
      0.002              // min_thrust
  });
  v_azimuththrusterdata.push_back({
      -1.893,             // lx
      0.216,              // ly
      2e-5,               // K
      20,                 // max_delta_rotation
      1000,               // max rotation
      10,                 // min_rotation
      0.1277,             // max_delta_alpha
      -M_PI / 18,         // max_alpha
      -M_PI * 175 / 180,  // min_alpha
      20,                 // max_thrust
      0.002               // min_thrust
  });

  std::vector<ruddermaindata> v_ruddermaindata;

  controllerRTdata<m, n> _controllerRTdata{
      Eigen::Matrix<double, n, 1>::Zero(),  // tau
      Eigen::Matrix<double, n, 1>::Zero(),  // BalphaU
      Eigen::Matrix<double, m, 1>::Zero(),  // u
      Eigen::Matrix<int, m, 1>::Zero(),     // rotation
      Eigen::Matrix<double, m, 1>::Zero(),  // alpha
      Eigen::Matrix<int, m, 1>::Zero()      // alpha_deg
  };

  // initialize the thrust allocation
  thrustallocation<m, index_actuation, n> _thrustallocation(
      _thrustallocationdata, v_tunnelthrusterdata, v_azimuththrusterdata,
      v_ruddermaindata);
  _thrustallocation.initializapropeller(_controllerRTdata);

  // data saved for validation and viewer
  const int totalstep = 200;

  Eigen::MatrixXd save_u = Eigen::MatrixXd::Zero(m, totalstep);
  Eigen::MatrixXd save_alpha = Eigen::MatrixXd::Zero(m, totalstep);
  Eigen::MatrixXi save_alpha_deg = Eigen::MatrixXi::Zero(m, totalstep);
  Eigen::MatrixXd save_Balphau = Eigen::MatrixXd::Zero(n, totalstep);
  Eigen::MatrixXd save_tau = Eigen::MatrixXd::Zero(n, totalstep);
  Eigen::MatrixXi save_rotation = Eigen::MatrixXi::Zero(m, totalstep);

  // desired forces
  double angle = 0;
  for (int i = 0; i != 120; ++i) {
    angle = (i + 1) * M_PI / 60;
    save_tau(2, i + 1) = 0.5 * sin(angle) + 0.1 * std::rand() / RAND_MAX;
  }
  save_tau.block(1, 0, 1, 100) = Eigen::MatrixXd::Constant(1, 100, 0.2) +
                                 0.0 * Eigen::MatrixXd::Random(1, 100);
  save_tau.block(1, 100, 1, 100) = Eigen::MatrixXd::Constant(1, 100, -0.2) +
                                   0.0 * Eigen::MatrixXd::Random(1, 100);
  save_tau.row(0) = 0.01 * Eigen::MatrixXd::Random(1, totalstep);
  for (int i = 0; i != totalstep; ++i) {
    // update tau
    _controllerRTdata.tau = save_tau.col(i);
    // thruster allocation
    _thrustallocation.onestepthrustallocation(_controllerRTdata);
    // save variables
    save_u.col(i) = _controllerRTdata.u;
    save_alpha.col(i) = _controllerRTdata.alpha;
    save_alpha_deg.col(i) = _controllerRTdata.alpha_deg;
    save_Balphau.col(i) = _controllerRTdata.BalphaU;
    save_rotation.col(i) = _controllerRTdata.rotation;
  }

  save_tau = save_tau.transpose().eval();
  save_u = save_u.transpose().eval();
  save_alpha = save_alpha.transpose().eval();
  save_alpha_deg = save_alpha_deg.transpose().eval();
  save_Balphau = save_Balphau.transpose().eval();
  save_rotation = save_rotation.transpose().eval();
  // save data to csv file
  utilityio _utilityio;
  std::string _name("../data/");
  _utilityio.write2csvfile(_name + "tau.csv", save_tau);
  _utilityio.write2csvfile(_name + "u.csv", save_u);
  _utilityio.write2csvfile(_name + "alpha.csv", save_alpha);
  _utilityio.write2csvfile(_name + "alpha_deg.csv", save_alpha_deg);
  _utilityio.write2csvfile(_name + "Balpha.csv", save_Balphau);
  _utilityio.write2csvfile(_name + "rotation.csv", save_rotation);
}

void testrudder() {
  // set the parameters in the thrust allocation
  constexpr int m = 2;
  constexpr int n = 3;
  constexpr ACTUATION index_actuation = UNDERACTUATED;

  std::vector<int> index_thrusters{3, 3};

  int num_tunnel =
      std::count(index_thrusters.begin(), index_thrusters.end(), 1);

  int num_azimuth =
      std::count(index_thrusters.begin(), index_thrusters.end(), 2);

  int num_mainrudder =
      std::count(index_thrusters.begin(), index_thrusters.end(), 3);

  thrustallocationdata _thrustallocationdata{num_tunnel, num_azimuth,
                                             num_mainrudder, index_thrusters};

  std::vector<tunnelthrusterdata> v_tunnelthrusterdata;
  v_tunnelthrusterdata.reserve(num_tunnel);

  std::vector<azimuththrusterdata> v_azimuththrusterdata;
  v_azimuththrusterdata.reserve(num_azimuth);

  std::vector<ruddermaindata> v_ruddermaindata;
  v_ruddermaindata.reserve(num_mainrudder);
  v_ruddermaindata.push_back({
      -1.893,  // lx
      0,       // ly
      2e-5,    // K
      0.0126,  // Cy
      20,      // max_delta_rotation (no less than 1)
      500,     // max rotation
      1,       // min_rotation
      50,      // max_thrust (effective thrust)
      2e-4,    // min_thrust
      M_PI,    // max_alpha
      -M_PI,   // min_alpha
      5,       // max_delta_varphi (no less than 1)
      30,      // max_varphi
      -30      // min_varphi
  });
  v_ruddermaindata.push_back({
      -1.893,  // lx
      0,       // ly
      2e-5,    // K
      0.0126,  // Cy
      20,      // max_delta_rotation
      500,     // max rotation
      1,       // min_rotation
      0,       // max_thrust
      2e-5,    // min_thrust
      M_PI,    // max_alpha
      -M_PI,   // min_alpha
      1,       // max_delta_varphi
      30,      // max_varphi
      -30      // min_varphi
  });

  controllerRTdata<m, n> _controllerRTdata{
      Eigen::Matrix<double, n, 1>::Zero(),  // tau
      Eigen::Matrix<double, n, 1>::Zero(),  // BalphaU
      Eigen::Matrix<double, m, 1>::Zero(),  // u
      Eigen::Matrix<int, m, 1>::Zero(),     // rotation
      Eigen::Matrix<double, m, 1>::Zero(),  // alpha
      Eigen::Matrix<int, m, 1>::Zero()      // alpha_deg
  };

  // initialize the thrust allocation
  thrustallocation<m, index_actuation, n> _thrustallocation(
      _thrustallocationdata, v_tunnelthrusterdata, v_azimuththrusterdata,
      v_ruddermaindata);
  _thrustallocation.initializapropeller(_controllerRTdata);

  const int totalstep = 200;

  Eigen::MatrixXd save_u = Eigen::MatrixXd::Zero(m, totalstep);
  Eigen::MatrixXd save_alpha = Eigen::MatrixXd::Zero(m, totalstep);
  Eigen::MatrixXi save_alpha_deg = Eigen::MatrixXi::Zero(m, totalstep);
  Eigen::MatrixXd save_Balphau = Eigen::MatrixXd::Zero(n, totalstep);
  Eigen::MatrixXd save_tau = Eigen::MatrixXd::Zero(n, totalstep);
  Eigen::MatrixXi save_rotation = Eigen::MatrixXi::Zero(m, totalstep);

  // desired forces
  double angle = 0;
  for (int i = 0; i != 120; ++i) {
    angle = (i + 1) * M_PI / 60;
    save_tau(2, i + 1) = 0.5 * sin(angle) + 0.1 * std::rand() / RAND_MAX;
  }
  save_tau.block(0, 0, 1, 100) = Eigen::MatrixXd::Constant(1, 100, 0.2) +
                                 0.0 * Eigen::MatrixXd::Random(1, 100);
  // save_tau.block(0, 100, 1, 100) = Eigen::MatrixXd::Constant(1, 100, -0.2) +
  //                                  0.0 * Eigen::MatrixXd::Random(1, 100);
  save_tau.row(1) = 0.01 * Eigen::MatrixXd::Random(1, totalstep);
  for (int i = 0; i != totalstep; ++i) {
    // update tau
    _controllerRTdata.tau = save_tau.col(i);
    // thruster allocation
    _thrustallocation.onestepthrustallocation(_controllerRTdata);
    // save variables
    save_u.col(i) = _controllerRTdata.u;
    save_alpha.col(i) = _controllerRTdata.alpha;
    save_alpha_deg.col(i) = _controllerRTdata.alpha_deg;
    save_Balphau.col(i) = _controllerRTdata.BalphaU;
    save_rotation.col(i) = _controllerRTdata.rotation;
  }

  save_tau = save_tau.transpose().eval();
  save_u = save_u.transpose().eval();
  save_alpha = save_alpha.transpose().eval();
  save_alpha_deg = save_alpha_deg.transpose().eval();
  save_Balphau = save_Balphau.transpose().eval();
  save_rotation = save_rotation.transpose().eval();
  // save data to csv file
  utilityio _utilityio;
  std::string _name("../data/");
  _utilityio.write2csvfile(_name + "tau.csv", save_tau);
  _utilityio.write2csvfile(_name + "u.csv", save_u);
  _utilityio.write2csvfile(_name + "alpha.csv", save_alpha);
  _utilityio.write2csvfile(_name + "alpha_deg.csv", save_alpha_deg);
  _utilityio.write2csvfile(_name + "Balpha.csv", save_Balphau);
  _utilityio.write2csvfile(_name + "rotation.csv", save_rotation);
}

void testbiling() {
  // set the parameters in the thrust allocation
  const int m = 6;
  const int n = 3;
  constexpr ACTUATION index_actuation = FULLYACTUATED;

  std::vector<int> index_thrusters{2, 2, 2, 2, 2, 2};

  int num_tunnel =
      std::count(index_thrusters.begin(), index_thrusters.end(), 1);

  int num_azimuth =
      std::count(index_thrusters.begin(), index_thrusters.end(), 2);

  int num_mainrudder =
      std::count(index_thrusters.begin(), index_thrusters.end(), 3);

  thrustallocationdata _thrustallocationdata{num_tunnel, num_azimuth,
                                             num_mainrudder, index_thrusters};

  std::vector<tunnelthrusterdata> v_tunnelthrusterdata;
  v_tunnelthrusterdata.reserve(num_tunnel);

  std::vector<azimuththrusterdata> v_azimuththrusterdata;
  v_azimuththrusterdata.reserve(num_azimuth);
  v_azimuththrusterdata.push_back({
      2,           // lx
      0,           // ly
      2.8E-6,      // K
      100,         // max_delta_rotation
      1500,        // max rotation
      5,           // min_rotation
      0.1277,      // max_delta_alpha
      1.5 * M_PI,  // max_alpha
      0.5 * M_PI,  // min_alpha
      20,          // max_thrust
      0.05         // min_thrust
  });
  v_azimuththrusterdata.push_back({
      0.63,    // lx
      -0.83,   // ly
      2.8e-6,  // K
      100,     // max_delta_rotation
      1500,    // max rotation
      5,       // min_rotation
      0.1277,  // max_delta_alpha
      M_PI,    // max_alpha
      0,       // min_alpha
      20,      // max_thrust
      0.05     // min_thrust
  });
  v_azimuththrusterdata.push_back({
      0.63,    // lx
      0.83,    // ly
      2.8e-6,  // K
      100,     // max_delta_rotation
      1500,    // max rotation
      5,       // min_rotation
      0.1277,  // max_delta_alpha
      0,       // max_alpha
      -M_PI,   // min_alpha
      20,      // max_thrust
      0.05     // min_thrust
  });
  v_azimuththrusterdata.push_back({
      -0.64,   // lx
      -0.83,   // ly
      2.8E-6,  // K
      100,     // max_delta_rotation
      1500,    // max rotation
      5,       // min_rotation
      0.1277,  // max_delta_alpha
      M_PI,    // max_alpha
      0,       // min_alpha
      20,      // max_thrust
      0.05     // min_thrust
  });
  v_azimuththrusterdata.push_back({
      -0.64,   // lx
      0.83,    // ly
      2.8E-6,  // K
      100,     // max_delta_rotation
      1500,    // max rotation
      5,       // min_rotation
      0.1277,  // max_delta_alpha
      0,       // max_alpha
      -M_PI,   // min_alpha
      20,      // max_thrust
      0.05     // min_thrust
  });
  v_azimuththrusterdata.push_back({
      -1.72,        // lx
      0,            // ly
      2.8E-6,       // K
      100,          // max_delta_rotation
      1500,         // max rotation
      5,            // min_rotation
      0.1277,       // max_delta_alpha
      0.5 * M_PI,   // max_alpha
      -0.5 * M_PI,  // min_alpha
      20,           // max_thrust
      0.05          // min_thrust
  });
  std::vector<ruddermaindata> v_ruddermaindata;

  controllerRTdata<m, n> _controllerRTdata{
      Eigen::Matrix<double, n, 1>::Zero(),  // tau
      Eigen::Matrix<double, n, 1>::Zero(),  // BalphaU
      Eigen::Matrix<double, m, 1>::Zero(),  // u
      Eigen::Matrix<int, m, 1>::Zero(),     // rotation
      Eigen::Matrix<double, m, 1>::Zero(),  // alpha
      Eigen::Matrix<int, m, 1>::Zero()      // alpha_deg
  };

  // initialize the thrust allocation
  thrustallocation<m, index_actuation, n> _thrustallocation(
      _thrustallocationdata, v_tunnelthrusterdata, v_azimuththrusterdata,
      v_ruddermaindata);
  _thrustallocation.initializapropeller(_controllerRTdata);

  const int totalstep = 200;

  Eigen::MatrixXd save_u = Eigen::MatrixXd::Zero(m, totalstep);
  Eigen::MatrixXd save_alpha = Eigen::MatrixXd::Zero(m, totalstep);
  Eigen::MatrixXi save_alpha_deg = Eigen::MatrixXi::Zero(m, totalstep);
  Eigen::MatrixXd save_Balphau = Eigen::MatrixXd::Zero(n, totalstep);
  Eigen::MatrixXd save_tau = Eigen::MatrixXd::Zero(n, totalstep);
  Eigen::MatrixXi save_rotation = Eigen::MatrixXi::Zero(m, totalstep);

  // desired forces
  double angle = 0;
  for (int i = 0; i != 120; ++i) {
    angle = (i + 1) * M_PI / 60;
    save_tau(2, i + 1) = 0.0 * sin(angle) + 0.0 * std::rand() / RAND_MAX;
  }
  save_tau.block(0, 0, 1, 100) = Eigen::MatrixXd::Constant(1, 100, 20) +
                                 0.0 * Eigen::MatrixXd::Random(1, 100);
  save_tau.block(0, 100, 1, 100) = Eigen::MatrixXd::Constant(1, 100, 20) +
                                   0.0 * Eigen::MatrixXd::Random(1, 100);
  save_tau.row(1) = 0.00 * Eigen::MatrixXd::Random(1, totalstep);
  for (int i = 0; i != totalstep; ++i) {
    // update tau
    _controllerRTdata.tau = save_tau.col(i);
    // thruster allocation
    _thrustallocation.onestepthrustallocation(_controllerRTdata);
    // save variables
    save_u.col(i) = _controllerRTdata.u;
    save_alpha.col(i) = _controllerRTdata.alpha;
    save_alpha_deg.col(i) = _controllerRTdata.alpha_deg;
    save_Balphau.col(i) = _controllerRTdata.BalphaU;
    save_rotation.col(i) = _controllerRTdata.rotation;
  }

  save_tau = save_tau.transpose().eval();
  save_u = save_u.transpose().eval();
  save_alpha = save_alpha.transpose().eval();
  save_alpha_deg = save_alpha_deg.transpose().eval();
  save_Balphau = save_Balphau.transpose().eval();
  save_rotation = save_rotation.transpose().eval();
  // save data to csv file
  utilityio _utilityio;
  std::string _name("../data/");
  _utilityio.write2csvfile(_name + "tau.csv", save_tau);
  _utilityio.write2csvfile(_name + "u.csv", save_u);
  _utilityio.write2csvfile(_name + "alpha.csv", save_alpha);
  _utilityio.write2csvfile(_name + "alpha_deg.csv", save_alpha_deg);
  _utilityio.write2csvfile(_name + "Balpha.csv", save_Balphau);
  _utilityio.write2csvfile(_name + "rotation.csv", save_rotation);
}

int main() {
  el::Loggers::addFlag(el::LoggingFlag::CreateLoggerAutomatically);
  LOG(INFO) << "The program has started!";
  testbiling();

  LOG(INFO) << "Shutting down.";
  return 0;
}