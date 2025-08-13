#ifdef _WINDOWS_

#ifndef Ch_D3D11_Inc_h
#define Ch_D3D11_Inc_h

#ifndef CRT
#define CRT
#endif

///////////////////////////////////////////////////////////////////////////////////////
//DirectX関連
///////////////////////////////////////////////////////////////////////////////////////

#include"BaseIncluder/ChD3D11I.h"

///////////////////////////////////////////////////////////////////////////////////////
//D3D11AddStruct
///////////////////////////////////////////////////////////////////////////////////////

//Object本体//
#include"Direct3D11/ChTexture/ChTexture11.h"
#include"Direct3D11/ChMesh/ChMesh11.h"
#include"Direct3D11/ChPolygonBoard/ChPolygonBoard11.h"
#include"Direct3D11/ChSprite/ChSprite11.h"
//ライブラリで用意したShaderを利用するクラス//
#include"Direct3D11/ChCB/ChCBBase11.h"
#include"Direct3D11/ChCB/ChCBPolygon/ChCBPolygon11.h"
#include"Direct3D11/ChCB/ChCBSprite/ChCBSprite11.h"
#include"Direct3D11/ChCB/ChCBLight/ChCBLight11.h"
#include"Direct3D11/ChCB/ChCBBone/ChCBBone11.h"
#include"Direct3D11/ChCB/ChCBCircleCulling/ChCBCircleCulling11.h"
#include"Direct3D11/ChCB/ChCBBasicShapes/ChCBBasicShapes11.h"
#include"Direct3D11/ChCB/ChCBBlur/ChCBBlur11.h"
#include"Direct3D11/ChCB/ChCBHighlight/ChCBHighlight11.h"
//サンプルシェーダー//
#include"Direct3D11/ChSampleShader/PolygonShader/ChBaseDrawMesh11.h"
#include"Direct3D11/ChSampleShader/PolygonShader/ChBaseDrawPolygonBoard11.h"
#include"Direct3D11/ChSampleShader/SpriteShader/ChBaseDrawSprite11.h"
#include"Direct3D11/ChSampleShader/SpriteShader/ChCircleCullingSpriteShader11.h"
#include"Direct3D11/ChSampleShader/SpriteShader/ChBasicShapesShader11.h"
#include"Direct3D11/ChSampleShader/SpriteShader/ChBasicBlurShader11.h"
#include"Direct3D11/ChSampleShader/SpriteShader/ChBasicHighlightShader11.h"

//空間操作//
#include"Direct3D11/ChCameraController/ChCameraController11.h"
//Object操作//
#include"Direct3D11/ChShader/ChShader11.h"
//Component//

//D3DObject//
#include"../ChCppDirect3DLibrary/BaseIncluder/ChD3DOI.h"

#ifdef _DEBUG

#ifdef _DLL
#pragma comment(lib,"ChD3D11Library_MDd.lib")
#else
#pragma comment(lib,"ChD3D11Library_MTd.lib")
#endif

#else

#ifdef _DLL
#pragma comment(lib,"ChD3D11Library_MD.lib")
#else
#pragma comment(lib,"ChD3D11Library_MT.lib")
#endif

#endif

#endif

//CopyRight Chronoss0518 2018/08//
#endif