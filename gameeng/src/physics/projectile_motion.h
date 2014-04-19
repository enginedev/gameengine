//
//  projectile_motion.h
//  gameeng
//
//  Created by Armon Carigiet on 16.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#ifndef __gameeng__projectile_motion__
#define __gameeng__projectile_motion__

#include <iostream>
#include <vector>
#include <math.h>
#include "position.h"
#include "velocity.h"
#include "acceleration.h"


// Drag coefficients
#define Cw_air 				0.7
#define Cw_parachute 		1.33
#define Cw_paraglider 		0.6
#define Cw_human 			0.78
#define Cw_penguin 			0.03
#define Cw_truck 			0.8
#define Cw_ford_model_t 	0.9
#define Cw_drops 			0.02
#define Cw_airplane 		0.08
#define Cw_ball		 		0.45


// ro values 	(kg/m^3)
#define ro_air 				1.2941
#define ro_ammonia 			0.771
#define ro_helium 			0.1785
#define ro_carbon_dioxide 	1.977
#define ro_sulfur_dioxide 	2.926
#define ro_hydrogen 		0.0899


#define _M_Gravity_Earth 	9.81
#define _M_Gravity_Space 	0.00
#define _M_Gravity_Moon		1.62
#define _M_Gravity_Mars		3.71
#define _M_Gravity_Jupiter	24.79
#define _M_Gravity_Pluto 	0,58 
#define _M_Gravity_Enceladus 0.11

using namespace physics;

namespace physics{
	namespace projectile_motion {
		
		enum limit{
			slate_throw_limit_x_position=0,
			slate_throw_limit_y_position,
			slate_throw_limit_z_position,
			slate_throw_limit_velocity,
			slate_throw_limit_x_velocity,
			slate_throw_limit_y_velocity,
			slate_throw_limit_z_velocity,
		};
		
		struct _trajectory_point{
			position::position position;
			velocity::velocity velocity;
			acceleration::acceleration acceleration;
			float t;
		};
		typedef struct _trajectory_point trajectory_point;
		
		class object{
		public:
			float k;
			float m;
			
			void set_airfrictioncoefficient(float A, float ro, float Cw);
			
		};
		
		class trajectory{
		private:
			bool allocated;
		public:
			float dt;
			float g;
			trajectory_point* points;
			//struct trajectory_point *points;
			size_t points_count;
			projectile_motion::object obj;
			
			velocity::velocity Vnul;
			position::position Pnul;
			
			bool set_object(projectile_motion::object o);
			bool set_start_velocity(velocity::velocity v);
			bool set_start_position(position::position p);
			bool set_time_period(float t);
			bool set_gravity(float gravity);
			bool calculate(float limit_low, float limit_high, int limit_type);
			bool calculate(object obj, float dt, velocity::velocity v, position::position p, float g, float limit_low, float limit_high, int limit_type);
			void dealloc();
			
		};
	}
}



#endif /* defined(__gameeng__projectile_motion__) */
