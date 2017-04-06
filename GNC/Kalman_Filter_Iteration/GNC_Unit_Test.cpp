// Navigation Unit Test Script
// Author:  Cameron Maywood

#include <stdio.h>
#include "../../include/Exception/OSPRE_Exceptions.h"
#include <iostream>

#include "Kalman_Filter_Iteration_rtwutil.cpp"
#include "sind.cpp"
#include "tand.cpp"
#include "cosd.cpp"
#include "norm.cpp"
#include "State_Error.cpp"
#include "Kalman_Filter_Iteration.cpp"
#include "Quaternion_To_Attitude.cpp"
#include "Position_From_Earth_Range.cpp"
#include "Position_From_Moon_Range.cpp"
#include "Position_From_Angles_Slew.cpp"
#include "Earth_SC_Moon_Angle.cpp"
using namespace std;

int main(int, const char * const [])
{
  string test = "pass";

  cout << "\n";
  cout << "############# NAVIGATION UNIT TEST SCRIPT ################################################\n\n";

  ////////////////////////////////// TEST #1 ////////////////////////////////////////////////////////////////////
  cout << "                 Test #1: Nominal Case\n";
  cout << "------------------------------------------------------------------------------------------\n";

  // ******************** Kalman_Filter_Iteration ********************
  double x_hat1[6] = {4.987918, 28.550259, 10.236165, 0.000040, 0.001859, 0.000699};
  double phi1[36] = {0.619906, 0.660809, 0.226899, -0.000041, 0.000050, 0.000018, 0.470692, 2.077250, 0.615783, 0.000016, 0.000109, 0.000060, 0.155343, 0.600820, 0.556651, 0.000005, 0.000057, -0.000033, 14580.430011, 859.468163, 287.954931, 0.729040, 0.000087, -0.003782, 520.242826, 21006.268949, 2547.500488, -0.074063, 1.574033, 0.342109, 160.277904, 2520.800513, 15065.175466, -0.031690, 0.336272, 0.809632};
  double P1[36] = {134.365128, 727.266598, 263.134382, 0.001202, 0.047403, 0.017745, 727.266598, 3937.596436, 1424.711328, 0.006504, 0.256651, 0.096079, 263.134382, 1424.711328, 515.560033, 0.002353, 0.092863, 0.034766, 0.001202, 0.006504, 0.002353, 0.000000, 0.000000, 0.000000, 0.047403, 0.256651, 0.092863, 0.000000, 0.000017, 0.000006, 0.017745, 0.096079, 0.034766, 0.000000, 0.000006, 0.000002};
  double Y1[3] = {-64688.683187, 70219.593190, 31504.696328};
  double R1[9] = {3126.039954, 0.000000, 0.000000, 0.000000, 8098.891319, 0.000000, 0.000000, 0.000000, 496.755804};
  double X_ref1[6] = {-64632.772186, 70129.599350, 31482.408309, -2.394162, 0.445166, 0.355992};
  double time1;
  double X_est1[6];
  try {
      Kalman_Filter_Iteration(x_hat1, phi1, P1, Y1, R1, X_ref1, time1, X_est1);
      if((abs(X_est1[0] + 64621.5809781001) < 10) &
        (abs(X_est1[1] - 70192.1507903567) < 10) &
        (abs(X_est1[2] - 31505.0701585269) < 10) &
        (abs(X_est1[3] + 2.39406404052048) < 0.0001) &
        (abs(X_est1[4] - 0.449218330702293) < 0.0001) &
        (abs(X_est1[5] - 0.357517902031816) < 0.0001)) {
          cout << "SUCCESS: Kalman_Filter_Iteration() ran without error.\n";
      }
      else {
          cout << "Error: Kalman_Filter_Iteration() did not run successfully.\n";
          test = "Kalman_Filter_Iteration";
      }
  }
  catch (...) {
      cout << "Error: Kalman_Filter_Iteration() unknown exception caught.\n";
      throw;
  }    

  // ******************** State_Error ********************
  double X_ref2[6] = {100000, 200000, 300000, 2, 3, 4};
  double X_est2[6] = {150000, 250000, 350000, 2.2, 3.2, 4.3};
  double posError2[3];
  double velError2[3];
  try {
      State_Error(X_ref2, X_est2, posError2, velError2);
      if(posError2[0] == -50000 & posError2[1] == -50000 & posError2[2] == -50000 &
         velError2[0] == 2-2.2 & velError2[1] == 3-3.2 & velError2[2] == 4-4.3) {
          cout << "SUCCESS: State_Error() ran without error.\n";
      }
      else {
          cout << "ERROR: State_Error() did not run successfully.\n";
          test = "State_Error";
      }
  }
  catch (...) {
      cout << "ERROR: State_Error() unknown exception caught.\n";
      throw;
  }   

  // ******************** Quaternion_To_Attitude ********************
  double q3[4] = {0.334941634079673, 0.842369351135588, -0.294006359946667, -0.302965737895159};
  double r_SC_body3[3];
  try {
      Quaternion_To_Attitude(q3, r_SC_body3);
      if((abs(r_SC_body3[0] - 0.643544043945106) < 0.0001) &
        (abs(r_SC_body3[1] + 0.698275571957536) < 0.0001) &
        (abs(r_SC_body3[2] + 0.313468162833413) < 0.0001)) {
          cout << "SUCCESS: Quaternion_To_Attitude() ran without error.\n";        
      }
      else {
          cout << "ERROR: Quaternion_To_Attitude() did not run successfully.\n";
          test = "Quaternion_To_Attitude";
      }
  }
  catch (...) {
      cout << "ERROR: Quaternion_To_Attitude() unknown exception caught.\n";
      throw;
  }
 
  // ******************** Position_From_Earth_Range ********************
  double q_E4[4] = {0.101917349793177, 0.900769046861452, -0.36326204898361, -0.215101515093865};
  double alpha4 = 1;
  double beta4 = 1;
  double theta4 = 5;
  double r_E_SC4[3];
  try {
      Position_From_Earth_Range(q_E4, alpha4, beta4, theta4, r_E_SC4);
      if((abs(r_E_SC4[0] + 94963.6287429297) < 10) &
        (abs(r_E_SC4[1] - 100364.380041258) < 10) &
        (abs(r_E_SC4[2] - 47426.2257842745) < 10)) {
          cout << "SUCCESS: Position_From_Earth_Range() ran without error.\n";        
      }
      else {
          cout << "ERROR: Position_From_Earth_Range() did not run successfully.\n";
          test = "Position_From_Earth_Range";
      }
  }
  catch (...) {
      cout << "ERROR: Position_From_Earth_Range() unknown exception caught.\n";
      throw;
  }

  // ******************** Position_From_Moon_Range ********************
  double r_E_M5[3] = {-359315.580848855, -88352.137962462, -4764.96675056363};
  double q_M5[4] = {0.205017971355707, -0.288507455573134, 0.877605881575736, -0.323324907985114};
  double alpha5 = 0;
  double beta5 = 0;
  double theta5 = 30;
  double r_E_SC5[3];
  try {
      Position_From_Moon_Range(r_E_M5, q_M5, alpha5, beta5, theta5, r_E_SC5);
      if((abs(r_E_SC5[0] + 354454.061518498) < 10) &
        (abs(r_E_SC5[1] + 84207.3682523436) < 10) &
        (abs(r_E_SC5[2] + 3640.91205808498) < 10)) {
          cout << "SUCCESS: Position_From_Moon_Range() ran without error.\n";        
      }
      else {
          cout << "ERROR: Position_From_Moon_Range() did not run successfully.\n";
          test = "Position_From_Moon_Range";
      }
  }
  catch (...) {
      cout << "ERROR: Position_From_Moon_Range() unknown exception caught.\n";
      throw;
  }

  // ******************** Position_From_Angles_Slew ********************

  // ******************** Earth_SC_Moon_Angle ********************
  double r_E_SC7[3] = {-64632.7721864894, 70129.5993496471, 31482.4083087272};
  try {
      double angle7 = Earth_SC_Moon_Angle(r_E_SC7, r_E_M5);
      if(abs(angle7 - 101.589842830945) < 0.1) {
          cout << "SUCCESS: Earth_SC_Moon_Angle() ran without error.\n";        
      }
      else {
          cout << "ERROR: Earth_SC_Moon_Angle() did not run successfully.\n";
          test = "Earth_SC_Moon_Angle";
      }
  }
  catch (...) {
      cout << "ERROR: Earth_SC_Moon_Angle() unknown exception caught.\n";
      throw;
  }  
  
  
  // ******************** Test #1 Results ********************
  if(test == "pass"){
      cout << "SUCCESS: NOMINAL CASE WAS PASSED WITHOUT ERROR.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Kalman_Filter_Iteration"){
      cout << "FAILURE: Test #1 was failed in Kalman_Filter_Iteration().\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "State_Error"){
      cout << "FAILURE: Test #1 was failed in State_Error().\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Quaternion_To_Attitude"){
      cout << "FAILURE: Test #1 was failed in Quaternion_To_Attitude().\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Position_From_Earth_Range"){
      cout << "FAILURE: Test #1 was failed in Position_From_Earth_Range().\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Position_From_Moon_Range"){
      cout << "FAILURE: Test #1 was failed in Position_From_Moon_Range().\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Earth_SC_Moon_Angle"){
      cout << "FAILURE: Test #1 was failed in Earth_SC_Moon_Angle().\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else {
      cout << "FAILURE: Unknown error occurred.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }


  ////////////////////////////////// TEST #2 ////////////////////////////////////////////////////////////////////
  test = "pass";
  cout << "                 Test #2: Kalman_Filter_Iteration() Input Exceptions\n";
  cout << "------------------------------------------------------------------------------------------\n";

  // ******************** Kalman_Filter_Iteration ********************
  double X_ref8[6] = {-4000, 50, 1000, -2.394162, 0.445166, 0.355992};
  try {
      Kalman_Filter_Iteration(x_hat1, phi1, P1, Y1, R1, X_ref8, time1, X_est1);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Kalman_Filter_Iteration() input exception successfully caught.\n";
      test = "Kalman_Filter_Iteration";
  }
  catch (...) {
      cout << "ERROR: Kalman_Filter_Iteration() unknown exception caught.\n";
      test = "fail";
      throw;
  } 
  // ******************** Test #2 Results ********************
  if(test == "pass"){
      cout << "FAILURE: Kalman_Filter_Iteration() INPUT EXCEPTIONS WERE NOT SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Kalman_Filter_Iteration"){
      cout << "SUCCESS: Kalman_Filter_Iteration() INPUT EXCEPTIONS WERE SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else {
      cout << "FAILURE: Kalman_Filter_Iteration() UNKNOWN ERROR OCCURRED.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }

  ////////////////////////////////// TEST #3 ////////////////////////////////////////////////////////////////////
  test = "pass";
  string test2 = "pass";
  cout << "                 Test #3: State_Error() Input Exceptions\n";
  cout << "------------------------------------------------------------------------------------------\n";

  // ******************** State_Error ********************
  double X_ref9[6] = {3000, 3000, 3000, 2, 3, 4}; 
  try {
      State_Error(X_ref9, X_est2, posError2, velError2);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: State_Error() input exception successfully caught.\n";
      test = "State_Error";
  }
  catch (...) {
      cout << "ERROR: State_Error() unknown exception caught.\n";
      test = "Fail";
      throw;
  }   

  double X_est9[6] = {3000, 3000, 3000, 2.2, 3.2, 4.3};
  try {
      State_Error(X_ref2, X_est9, posError2, velError2);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: State_Error() input exception successfully caught.\n";
      test2 = "State_Error";
  }
  catch (...) {
      cout << "ERROR: State_Error() unknown exception caught.\n";
      test2 = "fail";
      throw;
  }
  
  // ******************** Test #3 Results ********************
  if(test == "pass" | test2 == "pass"){
      cout << "FAILURE: State_Error() INPUT EXCEPTIONS WERE NOT SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "State_Error" & test2 == "State_Error"){
      cout << "SUCCESS: State_Error() INPUT EXCEPTIONS WERE SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else {
      cout << "FAILURE: State_Error() UNKNOWN ERROR OCCURRED.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }

  ////////////////////////////////// TEST #4 ////////////////////////////////////////////////////////////////////
  test = "pass";
  cout << "                 Test #4: Quaternion_To_Attitude() Input Exceptions\n";
  cout << "------------------------------------------------------------------------------------------\n";

  // ******************** Quaternion_To_Attitude ********************
  double q10[4] = {1, 1, 1, 1};
  try {
      Quaternion_To_Attitude(q10, r_SC_body3);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Quaternion_To_Attitude() input exception successfully caught.\n";
      test = "Quaternion_To_Attitude";
  }
  catch (...) {
      cout << "ERROR: Quaternion_To_Attitude() unknown exception caught.\n";
      test = "fail";
      throw;
  }
  // ******************** Test #4 Results ********************
  if(test == "pass"){
      cout << "FAILURE: Quaternion_To_Attitude() INPUT EXCEPTIONS WERE NOT SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Quaternion_To_Attitude"){
      cout << "SUCCESS: Quaternion_To_Attitude() INPUT EXCEPTIONS WERE SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else {
      cout << "FAILURE: Quaternion_To_Attitude() UNKNOWN ERROR OCCURRED.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }

  ////////////////////////////////// TEST #5 ////////////////////////////////////////////////////////////////////
  test = "pass";
  test2 = "pass";
  string test3 = "pass";
  string test4 = "pass";
  cout << "                 Test #5: Position_From_Earth_Range() Input Exceptions\n";
  cout << "------------------------------------------------------------------------------------------\n";

  // ******************** Position_From_Earth_Range ********************
  double q_E11[4] = {1, 1, 1, 1};
  try {
      Position_From_Earth_Range(q_E11, alpha4, beta4, theta4, r_E_SC4);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Position_From_Earth_Range() input exception successfully caught.\n";
      test = "Position_From_Earth_Range";
  }
  catch (...) {
      cout << "ERROR: Position_From_Earth_Range() unknown exception caught.\n";
      test = "fail";
      throw;
  }

  double alpha11 = 361;
  try {
      Position_From_Earth_Range(q_E4, alpha11, beta4, theta4, r_E_SC4);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Position_From_Earth_Range() input exception successfully caught.\n";
      test2 = "Position_From_Earth_Range";
  }
  catch (...) {
      cout << "ERROR: Position_From_Earth_Range() unknown exception caught.\n";
      test2 = "fail";
      throw;
  }

  double beta11 = 361;
  try {
      Position_From_Earth_Range(q_E4, alpha4, beta11, theta4, r_E_SC4);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Position_From_Earth_Range() input exception successfully caught.\n";
      test3 = "Position_From_Earth_Range";
  }
  catch (...) {
      cout << "ERROR: Position_From_Earth_Range() unknown exception caught.\n";
      test3 = "fail";
      throw;
  }

  double theta11 = 181;
  try {
      Position_From_Earth_Range(q_E4, alpha4, beta4, theta11, r_E_SC4);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Position_From_Earth_Range() input exception successfully caught.\n";
      test4 = "Position_From_Earth_Range";
  }
  catch (...) {
      cout << "ERROR: Position_From_Earth_Range() unknown exception caught.\n";
      test4 = "fail";
      throw;
  } 


  // ******************** Test #5 Results ********************
  if(test == "pass" | test2 == "pass" | test3 == "pass" | test4 == "pass"){
      cout << "FAILURE: Position_From_Earth_Range() INPUT EXCEPTIONS WERE NOT SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Position_From_Earth_Range" & test2 == "Position_From_Earth_Range" & test3 == "Position_From_Earth_Range" & test4 == "Position_From_Earth_Range"){
      cout << "SUCCESS: Position_From_Earth_Range() INPUT EXCEPTIONS WERE SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else {
      cout << "FAILURE: Position_From_Earth_Range() UNKNOWN ERROR OCCURRED.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }

  ////////////////////////////////// TEST #6 ////////////////////////////////////////////////////////////////////
  test = "pass";
  test2 = "pass";
  test3 = "pass";
  test4 = "pass";
  cout << "                 Test #6: Position_From_Moon_Range() Input Exceptions\n"; 
  cout << "------------------------------------------------------------------------------------------\n";

  // ******************** Position_From_Moon_Range ********************
  double q_M12[4] = {1, 1, 1, 1};
  try {
      Position_From_Moon_Range(r_E_M5, q_M12, alpha5, beta5, theta5, r_E_SC5);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Position_From_Moon_Range() input exception successfully caught.\n";
      test = "Position_From_Moon_Range";
  }
  catch (...) {
      cout << "ERROR: Position_From_Moon_Range() unknown exception caught.\n";
      test = "fail";
      throw;
  }

  double alpha12 = 361;
  try {
      Position_From_Moon_Range(r_E_M5, q_M5, alpha12, beta5, theta5, r_E_SC5);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Position_From_Moon_Range() input exception successfully caught.\n";
      test2 = "Position_From_Moon_Range";
  }
  catch (...) {
      cout << "ERROR: Position_From_Moon_Range() unknown exception caught.\n";
      test2 = "fail";
      throw;
  }

  double beta12 = 361;
  try {
      Position_From_Moon_Range(r_E_M5, q_M5, alpha5, beta12, theta5, r_E_SC5);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Position_From_Moon_Range() input exception successfully caught.\n";
      test3 = "Position_From_Moon_Range";
  }
  catch (...) {
      cout << "ERROR: Position_From_Moon_Range() unknown exception caught.\n";
      test3 = "fail";
      throw;
  }

  double theta12 = 181;
  try {
      Position_From_Moon_Range(r_E_M5, q_M5, alpha5, beta5, theta12, r_E_SC5);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Position_From_Moon_Range() input exception successfully caught.\n";
      test4 = "Position_From_Moon_Range";
  }
  catch (...) {
      cout << "ERROR: Position_From_Moon_Range() unknown exception caught.\n";
      test4 = "fail";
      throw;
  } 


  // ******************** Test #6 Results ********************
  if(test == "pass" | test2 == "pass" | test3 == "pass" | test4 == "pass"){
      cout << "FAILURE: Position_From_Moon_Range() INPUT EXCEPTIONS WERE NOT SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Position_From_Moon_Range" & test2 == "Position_From_Moon_Range" & test3 == "Position_From_Moon_Range" & test4 == "Position_From_Moon_Range"){
      cout << "SUCCESS: Position_From_Moon_Range() INPUT EXCEPTIONS WERE SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else {
      cout << "FAILURE: Position_From_Moon_Range() UNKNOWN ERROR OCCURRED.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }

  ////////////////////////////////// TEST #7 ////////////////////////////////////////////////////////////////////
  test = "pass";
  cout << "                 Test #7: Earth_SC_Moon_Angle() Input Exceptions\n";
  cout << "------------------------------------------------------------------------------------------\n";

  // ******************** Earth_SC_Moon_Angle ********************
  double r_E_SC13[3] = {3000, 3000, 3000};
  try {
      Earth_SC_Moon_Angle(r_E_SC13, r_E_M5);
  }
  catch (InvalidInputs &e) {
      cout << "SUCCESS: Earth_SC_Moon_Angle() input exception successfully caught.\n";
      test = "Earth_SC_Moon_Angle";
  }
  catch (...) {
      cout << "ERROR: Earth_SC_Moon_Angle() unknown exception caught.\n";
      test = "fail";
      throw;
  } 

  // ******************** Test #7 Results ********************
  if(test == "pass"){
      cout << "FAILURE: Earth_SC_Moon_Angle() INPUT EXCEPTIONS WERE NOT SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else if(test == "Earth_SC_Moon_Angle"){
      cout << "SUCCESS: Earth_SC_Moon_Angle() INPUT EXCEPTIONS WERE SUCCESSFULLY THROWN.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }
  else {
      cout << "FAILURE: Earth_SC_Moon_Angle() UNKNOWN ERROR OCCURRED.\n";
      cout << "------------------------------------------------------------------------------------------\n\n";
  }

  cout << "############# END OF NAVIGATION UNIT TEST SCRIPT #########################################\n\n";

  return 0;
}