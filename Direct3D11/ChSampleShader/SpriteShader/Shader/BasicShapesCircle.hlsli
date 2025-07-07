#ifndef	Ch_BasicShapes_Circle_h
#define Ch_BasicShapes_Circle_h

#include "BasicShapes.hlsli"

#ifndef BASIC_SHAPES_CIRCLE_DATA_REGISTERNO
#define BASIC_SHAPES_CIRCLE_DATA_REGISTERNO 1
#endif

#ifdef __SHADER__
cbuffer BasicShapesCircleData : register(CHANGE_CBUFFER(BASIC_SHAPES_CIRCLE_DATA_REGISTERNO))
#else
struct BasicShapesCircleData
#endif
{
	ChBasicShapesCircleDatas circleDatas;
};

#endif