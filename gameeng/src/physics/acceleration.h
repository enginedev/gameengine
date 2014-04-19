//
//  acceleration.h
//  gameeng
//
//  Created by Armon Carigiet on 17.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#ifndef __gameeng__acceleration__
#define __gameeng__acceleration__

#include <iostream>
#include <math.h>


namespace physics {
	namespace acceleration{
		struct _acceleration{
			float x;
			float y;
			float z;
		};
		typedef struct _acceleration acceleration;
		
		physics::acceleration::acceleration create_acceleration(float abs, float alpha, float beta);
		
	}
}

#endif /* defined(__OpenglTests__acceleration__) */
