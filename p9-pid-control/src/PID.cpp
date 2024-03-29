#include "PID.h"
#include <math.h>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {

/*
where
Kp = proptional
ki = integral
kd = differential
cte = cross track error

*/

  previous_cte_      = 0.0 ;
  integral_cte_      = 0.0 ;
  difference_cte_    = 0.0 ;
  sum_square_error_  = 0.0 ;
  counter_			 = 0 ;

  sum_absolute_value_error_ = 0.0 ;

  twiddle_best_error_ = 999999.0 ;

  PID::Kp = Kp ;
  PID::Ki = Ki ;
  PID::Kd = Kd ;

  tune_Kp = .1 ;
  tune_Ki = 2.76871e-46 ;
  tune_Kd = 8.1425e-38  ;
  twiddle_counter = 0 ;

  speed_goal = 0.0 ;

  sum_speed = 0.0 ;
  mean_speed = 0.0 ;
  previous_steer_value = 0.0 ;
  max_speed = 0.0 ;

  // tune_Kp = 2.92385e-39 ;
  // tune_Ki = 2.76871e-46 ;
  // tune_Kd = 8.1425e-38  ;

}

void PID::UpdateError(double cte) {

	counter_ += 1 ;

	current_cte_ = cte ;

	difference_cte_ = cte - previous_cte_ ;

    integral_cte_ += cte ;

	// halve intergal error every 1000 steps to avoid too much build up.
	if ( counter_ % 1000 == 0) {

		integral_cte_ = integral_cte_ / 2 ;
	}

	sum_absolute_value_error_ += fabs(cte) ;

	// 1.
	sum_square_error_ += cte * cte ;
	// 2.
	mean_squared_error_ = sum_square_error_ / counter_ ;

	// debugging
	if (counter_ % 100 == 0) {
		
		cout << "\t" << endl ;

		cout << "Counter\t" << counter_ <<
		"  current_cte_\t" << current_cte_ <<
		"  previous_cte_\t" << previous_cte_ <<
		"  sum_absolute_value_error_\t" << sum_absolute_value_error_ <<
		"  mean_squared_error_\t" << mean_squared_error_ << endl ;
	}

	previous_cte_ = cte ;

}

double PID::TotalError() {

	if (counter_ % 100 == 0) {

		cout << "P total error: " << - Kp * current_cte_ << endl ;
        cout << "I total error: " << - Kd * difference_cte_ << endl ;
        cout << "D total error: " << - Ki * integral_cte_ << endl ;

	}
	
	return  - Kp * current_cte_ - Kd * difference_cte_ - Ki * integral_cte_ ;
}

