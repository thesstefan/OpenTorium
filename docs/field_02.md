# Field using a map

A __field__ is a zone, which modies the __particles__ entering it in a 
defined way. (e.g. colorize, teleport, accelerate)

The most important requierement of the __field__ is having an efficient and reliable
way of determinining if a __particle__ is __inside__ its area or not.

One of the ways it can be done is by using __ZoneMap__. 

The ZoneMap maps every __field__ to its area by using something like 
collisionMap::addObject(const Field& field).

The CollisionMap requires the __Field__ interface to have a __shape()__
function which returns its shape (ofPolyline).

The class contains an array of __Field__ instances and a bidimensional array
of chars, which determine if a point is inside or not in a field zone.

The bidimensional array is created by taking each pixel of the screen and finding
if its included in a zone, and setting the coresponding char with a value accordingly.

The bit notation of the chars would be X0X1X2X3. If an X is 1, it means that the 
n-th field in the array contains the point. We can handle overlapping field zones
using that method, but we need to define a max number of fields contained by a map and
possibly increase the size of the type used.

ZoneMap will have an update() function in which updates the mapping.

Ideally, the class will also have an updateParticles() function which updates the particle-array.

Pros:
1. The __particle__ instances will be updated in an efficient mode, there being no need of 
checking if every particle is or isn't in a shape.

2. The dependency between the __field__ and __particle__ instances is managed cleanly by 
__ZoneMap__.

Cons:
1. If a very big screen is used, the need of storing every char can cause a memory overhead.

Requierements:
1. The __Field__ inteface to have a public shape() function returning its shape (ofPolyline).
