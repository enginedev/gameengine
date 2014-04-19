//
//  projectile_motion.cpp
//  gameeng
//
//  Created by Armon Carigiet on 16.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#include "projectile_motion.h"

using namespace physics;

// slate_throw::object

void projectile_motion::object::set_airfrictioncoefficient(float A, float ro, float Cw){
	this->k=0.5*A*ro*Cw;
}


// slate_throw::trajectory

//bool slate_throw::trajectory::init(){
//	points=(trajectory_point *)malloc(0);
//	if (points) {
//		return true;
//	}else{
//		return false;
//	}
//}

bool projectile_motion::trajectory::set_object(projectile_motion::object o){
	if(o.m != 0 && o.k != 0){
		this->obj=o;
		return true;
	}else{
		return false;
	}
}

bool projectile_motion::trajectory::set_start_velocity(velocity::velocity v){
	if (v.x>0 && v.y>0 && v.z>0) {
		this->Vnul=v;
		return true;
	}else{
		return false;
	}
}
bool projectile_motion::trajectory::set_start_position(position::position p){
	this->Pnul=p;
	return true;
}

bool projectile_motion::trajectory::set_time_period(float t){
	if (t>0) {
		this->dt=t;
		return true;
	}else{
		return false;
	}
}
bool projectile_motion::trajectory::set_gravity(float gravity){
	this->g=gravity;
	return true;
}

bool projectile_motion::trajectory::calculate(float limit_low, float limit_high, int limit_type){
		if (this->obj.k==0 || this->obj.m==0 || allocated) {
			return false;
		}else{
			
			// should be replaced with limit specific allocation
			//size_t point_ammount = dt*(limit_high-limit_low)/sqrtf((v.x*v.x)+(v.y*v.y)+(v.z*v.z)) + 2;
			size_t point_ammount = 100;
			
			points=(trajectory_point*)malloc(point_ammount*sizeof(projectile_motion::trajectory_point));
			
			//points = new slate_throw::trajectory_point[point_ammount];
			
			float c=this->obj.k/this->obj.m;
			bool terminate=false;
			float tmpVelocity;
			//float *limit_pointer;
			
			points[0].velocity.x=Vnul.x;
			points[0].velocity.y=Vnul.y;
			points[0].velocity.z=Vnul.z;
			points[0].position.x=Pnul.x;
			points[0].position.y=Pnul.y;
			points[0].position.z=Pnul.z;
			points[0].acceleration.x = -c * sqrtf((Vnul.x*Vnul.x) + (Vnul.y*Vnul.y) + (Vnul.z*Vnul.z))*Vnul.x;
			points[0].acceleration.y = -c * sqrtf((Vnul.x*Vnul.x) + (Vnul.y*Vnul.y) + (Vnul.z*Vnul.z))*Vnul.y;
			points[0].acceleration.z = -c * sqrtf((Vnul.x*Vnul.x) + (Vnul.y*Vnul.y) + (Vnul.z*Vnul.z))*Vnul.z;
			
			
			for(int i=1;terminate==false;i++){
				
				if(i>=point_ammount){
					point_ammount+=50;
					points=(trajectory_point*)realloc(points, point_ammount);
				}
				// numeric integration
				// a = -(k/m)*v^2
				// Ax+1 = -(k/m)*sqrt(Vx^2+Vy^2+Vz^2)*Vx		=> Vx+1 = Vx + Ax * dt
				// Ay+1 = -(k/m)*sqrt(Vx^2+Vy^2+Vz^2)*Vy -g		=> Vy+1 = Vy + Ay * dt
				// Az+1 = -(k/m)*sqrt(Vx^2+Vy^2+Vz^2)*Vz 		=> Vz+1 = Vz + Az * dt
				// k/m = c => const
				
				tmpVelocity=sqrtf((points[i-1].velocity.x*points[i-1].velocity.x) + (points[i-1].velocity.y*points[i-1].velocity.y) + (points[i-1].velocity.z*points[i-1].velocity.z));
				
				points[i].acceleration.x = -c * tmpVelocity*points[i-1].velocity.x;
				points[i].acceleration.y = -c * tmpVelocity*points[i-1].velocity.y -g;
				points[i].acceleration.z = -c * tmpVelocity*points[i-1].velocity.z;
				
				points[i].velocity.x = points[i-1].velocity.x + points[i].acceleration.x * dt;
				points[i].velocity.y = points[i-1].velocity.y + points[i].acceleration.y * dt;
				points[i].velocity.z = points[i-1].velocity.z + points[i].acceleration.z * dt;
				
				points[i].position.x = points[i-1].position.x + points[i].velocity.x * dt;
				points[i].position.y = points[i-1].position.y + points[i].velocity.y * dt;
				points[i].position.z = points[i-1].position.z + points[i].velocity.z * dt;
				
				//if (*limit_pointer>=limit_high) {
				//	terminate=true;
				//}
				//limit_pointer+=sizeof(physics::slate_throw::trajectory_point);
				
				if (limit_type==slate_throw_limit_x_position){
					if(points[i].position.x>=limit_high){
						points_count=i+1;
						terminate=true;
						allocated=true;
					}
				}else if (limit_type==slate_throw_limit_y_position){
					if(points[i].position.y>=limit_high){
						points_count=i+1;
						terminate=true;
						allocated=true;
					}
				}else if (limit_type==slate_throw_limit_z_position){
					if(points[i].position.z>=limit_high){
						points_count=i+1;
						terminate=true;
						allocated=true;
					}
				}else if (limit_type==slate_throw_limit_velocity){
					if(tmpVelocity>=limit_high){
						points_count=i+1;
						terminate=true;
						allocated=true;
					}
				}else if (limit_type==slate_throw_limit_x_velocity){
					if(points[i].velocity.x>=limit_high){
						points_count=i+1;
						terminate=true;
						allocated=true;
					}
				}else if (limit_type==slate_throw_limit_y_velocity){
					if(points[i].velocity.y>=limit_high){
						points_count=i+1;
						terminate=true;
						allocated=true;
					}
				}else if (limit_type==slate_throw_limit_z_velocity){
					if(points[i].velocity.z>=limit_high){
						points_count=i+1;
						terminate=true;
						allocated=true;
					}
				}else{
					free(points);
					terminate=true;
					allocated=false;
					return false;
				}
				
				
			}
			
			return true;
		}

}

bool projectile_motion::trajectory::calculate(object o, float dt, velocity::velocity v, position::position p, float g, float limit_low, float limit_high, int limit_type){
	if (o.k==0 || o.m==0 || allocated) {
		return false;
	}else{

		// should be replaced with limit specific allocation
		//size_t point_ammount = dt*(limit_high-limit_low)/sqrtf((v.x*v.x)+(v.y*v.y)+(v.z*v.z)) + 2;
		size_t point_ammount = 100;
		
		points=(trajectory_point*)malloc(point_ammount*sizeof(projectile_motion::trajectory_point));
		
		//points = new slate_throw::trajectory_point[point_ammount];
		
		float c=o.k/o.m;
		bool terminate=false;
		float tmpVelocity;
		//float *limit_pointer;
		
		Vnul=v;
		Pnul=p;
		this->g=g;
		this->obj=o;
		
		points[0].velocity.x=v.x;
		points[0].velocity.y=v.y;
		points[0].velocity.z=v.z;
		points[0].position.x=p.x;
		points[0].position.y=p.y;
		points[0].position.z=p.z;
		points[0].acceleration.x = -c * sqrtf((Vnul.x*Vnul.x) + (Vnul.y*Vnul.y) + (Vnul.z*Vnul.z))*Vnul.x;
		points[0].acceleration.y = -c * sqrtf((Vnul.x*Vnul.x) + (Vnul.y*Vnul.y) + (Vnul.z*Vnul.z))*Vnul.y;
		points[0].acceleration.z = -c * sqrtf((Vnul.x*Vnul.x) + (Vnul.y*Vnul.y) + (Vnul.z*Vnul.z))*Vnul.z;
		
				
		for(int i=1;terminate==false;i++){
			
			if(i>=point_ammount){
				point_ammount+=50;
				points=(trajectory_point*)realloc(points, point_ammount);
			}
			// numeric integration
			// a = -(k/m)*v^2
			// Ax+1 = -(k/m)*sqrt(Vx^2+Vy^2+Vz^2)*Vx		=> Vx+1 = Vx + Ax * dt
			// Ay+1 = -(k/m)*sqrt(Vx^2+Vy^2+Vz^2)*Vy -g		=> Vy+1 = Vy + Ay * dt
			// Az+1 = -(k/m)*sqrt(Vx^2+Vy^2+Vz^2)*Vz 		=> Vz+1 = Vz + Az * dt
			// k/m = c => const
			
			tmpVelocity=sqrtf((points[i-1].velocity.x*points[i-1].velocity.x) + (points[i-1].velocity.y*points[i-1].velocity.y) + (points[i-1].velocity.z*points[i-1].velocity.z));
			
			points[i].acceleration.x = -c * tmpVelocity*points[i-1].velocity.x;
			points[i].acceleration.y = -c * tmpVelocity*points[i-1].velocity.y -g;
			points[i].acceleration.z = -c * tmpVelocity*points[i-1].velocity.z;
			
			points[i].velocity.x = points[i-1].velocity.x + points[i].acceleration.x * dt;
			points[i].velocity.y = points[i-1].velocity.y + points[i].acceleration.y * dt;
			points[i].velocity.z = points[i-1].velocity.z + points[i].acceleration.z * dt;
			
			points[i].position.x = points[i-1].position.x + points[i].velocity.x * dt;
			points[i].position.y = points[i-1].position.y + points[i].velocity.y * dt;
			points[i].position.z = points[i-1].position.z + points[i].velocity.z * dt;
			
			//if (*limit_pointer>=limit_high) {
			//	terminate=true;
			//}
			//limit_pointer+=sizeof(physics::slate_throw::trajectory_point);
			
			if (limit_type==slate_throw_limit_x_position){
				if(points[i].position.x>=limit_high){
					points_count=i+1;
					terminate=true;
					allocated=true;
				}
			}else if (limit_type==slate_throw_limit_y_position){
				if(points[i].position.y>=limit_high){
					points_count=i+1;
					terminate=true;
					allocated=true;
				}
			}else if (limit_type==slate_throw_limit_z_position){
				if(points[i].position.z>=limit_high){
					points_count=i+1;
					terminate=true;
					allocated=true;
				}
			}else if (limit_type==slate_throw_limit_velocity){
				if(tmpVelocity>=limit_high){
					points_count=i+1;
					terminate=true;
					allocated=true;
				}
			}else if (limit_type==slate_throw_limit_x_velocity){
				if(points[i].velocity.x>=limit_high){
					points_count=i+1;
					terminate=true;
					allocated=true;
				}
			}else if (limit_type==slate_throw_limit_y_velocity){
				if(points[i].velocity.y>=limit_high){
					points_count=i+1;
					terminate=true;
					allocated=true;
				}
			}else if (limit_type==slate_throw_limit_z_velocity){
				if(points[i].velocity.z>=limit_high){
					points_count=i+1;
					terminate=true;
					allocated=true;
				}
			}else{
				free(points);
				terminate=true;
				allocated=false;
				return false;
			}

			
		}
		
		return true;
	}
}

void projectile_motion::trajectory::dealloc(){
	free(points);
	allocated=false;
}
