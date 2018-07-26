# Field using a map

A __field__ is a zone, which modies the __particles__ entering it in a 
defined way. (e.g. colorize, teleport, accelerate)

The most important requierement of the __field__ is having an efficient and reliable
way of determinining if a __particle__ is __inside__ its area or not.

One of the ways it can be done is by using CollisionMap. 

The CollisionMap maps every __field__ to its area by using something like 
collisionMap::addObject(const Field& field).

The CollisionMap requires the __Field__ interface to have a __shape()__
function which returns its shape (ofPolyline).

The class maps each point on the screen with the shape its contained by using
std::map.

CollisionMap will have an update() function in which updates the mapping.

The __Particle__ interface will now be required to include in its update parameters
the CollisionMap.

At every update, the __particle__ will call CollisionMap::fieldUpdate(Particle& particle), which
will call the corresponding Field::update(Particle& particle) function if the passed particle
is contained in a __field's__ area according to the map. Nothing happening otherwise.

Pros:
1. The __particle__ instances will be updated in an efficient mode, there being no need of 
checking if every particle is or isn't in a shape.

2. The dependency between the __field__ and __particle__ instances is managed cleanly by 
__CollisionMap__.

Cons:
1. If many __field__ instances are used, there will be a lot of ofPoint instances used, resulting
in a memory overhead and/or slow std::map::find() calls.
2. __Particle__ inteface dependency with __CollisionMap__.

Requierements:
1. The __Field__ inteface to have a public shape() function returning its shape (ofPolyline).
