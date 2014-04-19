//
//  force.cpp
//  gameeng
//
//  Created by Armon Carigiet on 18.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#include "force.h"

physics::force::force create_force(float abs, float alpha, float beta){
	physics::force::force f={
		abs*cosf(alpha)*cosf(beta),
		abs*sinf(alpha),
		abs*cosf(alpha)*cosf(M_PI-beta)
	};
	
	return f;
}

physics::acceleration::acceleration get_acceleration(physics::force::force f, float m){
	physics::acceleration::acceleration a={
		f.x/m,
		f.y/m,
		f.z/m
	};
	
	return a;
}
