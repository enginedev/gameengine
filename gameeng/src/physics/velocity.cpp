//
//  velocity.cpp
//  gameeng
//
//  Created by Armon Carigiet on 16.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#include "velocity.h"

physics::velocity::velocity create_velocity(float abs, float alpha, float beta){
	
	physics::velocity::velocity v={
		abs*cosf(alpha)*cosf(beta),
		abs*sinf(alpha),
		abs*cosf(alpha)*cosf(M_PI-beta)
	};
	
	return v;
}
