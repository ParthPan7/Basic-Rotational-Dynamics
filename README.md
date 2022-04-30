# Basic Rotational Dynamics

**Objective**  
Understanding effect of force/torque on an object rotating around fixed geometrical axis (Uniform Circular Motion).

**What is visual Expectations ?**

The point object (or particle) should exihibit the rotation/ circular movement around a fixed axis namely, a central axis (This could be a vector emanating from centre posessing a tip at (X,Y,Z)). There by, it suggests that the point object should cover every position on the circular trajectory possesing fixed radius,_R_. 

**How that can be achieved ?**

The contingent question - What are the physical quantities impacting the movement of circular trajectory ? 

For the simplest of _translatory motion_ the position of particle under influence of underlying force can certainly deduce an _acceleration_. Similarly, a circular motion do have analogous physical quanties namingly :

Torque, ![formula](https://render.githubusercontent.com/render/math?math=\tau)

Technically, ![formula](https://render.githubusercontent.com/render/math?math=\tau) torque is an entity resembles force while comparing it to translatory motion. Formally, it is defined as certain magnitude of force apply to cause an object to rotate [1]. Yet, torque is concoction of several other parameters ( including Force) such as :

![formula](https://render.githubusercontent.com/render/math?math=\phi) - angle from which force is technically being applied.

![formula](https://render.githubusercontent.com/render/math?math=\iota) -  lever arm which is length calculated from centre to actual pivot point (position where a point object is imagined to be placed).



_Corollary :_

Since, assumption is being drawn for our case that there isn't any Physical link (thought we can draw virtual radius from centre to pivot point) exist between centre of imaginary circle drawn covering hypothetical circular trajectory and pivot point. Therefore, external force should have to be exterted exactly at Pivot point lying on that vary object (refer _figure 1_).      



_figure 1 : Torque pictorial representation_

_figure 1_ depicts that force is being applied at angle ![formula](https://render.githubusercontent.com/render/math?math=\phi) yielding vertical force component ![formula](https://render.githubusercontent.com/render/math?math=F.sin\phi ) at pivot point covering radial distance ![formula](https://render.githubusercontent.com/render/math?math=\iota).

Therefore, Torque ![formula](https://render.githubusercontent.com/render/math?math=\tau) is computed with yielded formula ![formula](https://render.githubusercontent.com/render/math?math=\tau\equiv\iota\times\F.sin\phi).

The underlying formulation suggests that Force applied at a pivot point of lever exactly at radial distance ![formula](https://render.githubusercontent.com/render/math?math=\iota) and at right angle  ![formula](https://render.githubusercontent.com/render/math?math=\phi\equiv\90) gives maximum torque possible ![formula](https://render.githubusercontent.com/render/math?math=\tau_{max}\equiv\F.\iota).  

The torque is also defined as Moment of Interia times angular acceleration ![formula](https://render.githubusercontent.com/render/math?math=\tau\equiv\I.\alpha) [2]. 

Succinctly, Moment of Inertia, _I_ ![formula](https://render.githubusercontent.com/render/math?math=\I\equiv\m\r^2) can serve as a resistive factor to control the acceleration of 
![formula](https://render.githubusercontent.com/render/math?math=\alpha) of a particle or a point object in a world space. 

_Meaningful deductions_

![formula](https://render.githubusercontent.com/render/math?math=\alpha\propto\1/I);

![formula](https://render.githubusercontent.com/render/math?math=\alpha\propto\tau)

1. Increasing Torque increases angular speed ![formula](https://render.githubusercontent.com/render/math?math=\omega) and in turn an angular acceleration, ![formula](https://render.githubusercontent.com/render/math?math=\alpha).

2. Increasing Moment of Inertia _I_ can provide resistance over angular velocity of rotation.

**Kinematic relations to solve the problem**

The angular acceleration, ![formula](https://render.githubusercontent.com/render/math?math=\alpha) by definition is:

![formula](https://render.githubusercontent.com/render/math?math=\alpha\equiv\d{\omega}/d{t})

![formula](https://render.githubusercontent.com/render/math?math=\int_{\omega_{0}}^{\omega}\d{\omega}\equiv\alpha\int_{0}^{t}d{t})

![formula](https://render.githubusercontent.com/render/math?math=\omega\equiv\omega_{0})+![formula](https://render.githubusercontent.com/render/math?math=\omega\t)![formula](https://render.githubusercontent.com/render/math?math=-1)


Dervied Equation 1, can be applied to deduce the updated angular velocity at each frame.

Similary, we can deduce the relation of angular displacement ![formula](https://render.githubusercontent.com/render/math?math=\theta) using Equation 1 substitution of angular velocity into ![formula](https://render.githubusercontent.com/render/math?math=\omega\equiv\d{\theta}/d{t}) yields a required relation of :

![formula](https://render.githubusercontent.com/render/math?math=\theta\equiv\theta_{0}) + ![formula](https://render.githubusercontent.com/render/math?math=\omega_{0}.t) + ![formula](https://render.githubusercontent.com/render/math?math=(1/2).\alpha.\t^2) ![formula](https://render.githubusercontent.com/render/math?math=-2)

Finally, the angular displacment, ![formula](https://render.githubusercontent.com/render/math?math=\theta) from Equation 2 can be used to find an updated position while transforming ![formula](https://render.githubusercontent.com/render/math?math=\theta) to cartesian coordinate system.

 ![formula](https://render.githubusercontent.com/render/math?math=\x\equiv\x_{origin}) +  ![formula](https://render.githubusercontent.com/render/math?math=R.\cos\{\theta})


 ![formula](https://render.githubusercontent.com/render/math?math=\y\equiv\y_{origin}) +  ![formula](https://render.githubusercontent.com/render/math?math=R.\sin\{\theta})

Here,

![formula](https://render.githubusercontent.com/render/math?math=R) is a radial distance from centre to pivot point.

![formula](https://render.githubusercontent.com/render/math?math=x_{origin}) and ![formula](https://render.githubusercontent.com/render/math?math=y_{origin}) forming an axial position to carry out rotation around.

**References**

**[1]** _Physics.uoguelph.ca. 2022. Torque and Rotational Motion Tutorial | Physics. [online] Available at: <https://www.physics.uoguelph.ca/torque-and-rotational-motion-tutorial> [Accessed 30 April 2022]._

**[2]** _En.wikipedia.org. 2022. Rotation around a fixed axis - Wikipedia. [online] Available at: <https://en.wikipedia.org/wiki/Rotation_around_a_fixed_axis> [Accessed 30 April 2022]._