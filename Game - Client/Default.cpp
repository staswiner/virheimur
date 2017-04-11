#include "Default.h"



Default::Default()
{
	BlenderConversion = rotate(mat4(), radians(-90.0f), vec3(1, 0, 0));

	BlenderConversionCenter = translate(mat4(), vec3(0,3,0));
	BlenderConversionCenter = rotate(BlenderConversionCenter, radians(-90.0f), vec3(1, 0, 0));;
}


Default::~Default()
{
}
