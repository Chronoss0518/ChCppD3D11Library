#ifndef	Ch_BasicShapes_Position_h
#define Ch_BasicShapes_Position_h

#include "BasicShapes.hlsli"

#ifndef BASIC_SHAPES_POSITION_DATA_REGISTERNO
#define BASIC_SHAPES_POSITION_DATA_REGISTERNO 1
#endif

#ifdef __SHADER__
cbuffer BasicShapesPositionData : register(CHANGE_CBUFFER(BASIC_SHAPES_POSITION_DATA_REGISTERNO))
#else
struct BasicShapesPositionData
#endif
{
	ChBasicShapesPositions positions;
};

#endif