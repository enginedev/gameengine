//
//  force.h
//  gameeng
//
//  Created by Armon Carigiet on 18.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#ifndef __gameeng__force__
#define __gameeng__force__

#include <iostream>
#include <math.h>
#include "acceleration.h"

namespace physics {
	namespace force{
		struct _force{
			float x;
			float y;
			float z;
		};
		typedef struct _force force;
		
		physics::force::force create_force(float abs, float alpha, float beta);
		physics::acceleration::acceleration get_acceleration(physics::force::force f, float m);
	}
}

#endif /* defined(__gameeng__force__) */
