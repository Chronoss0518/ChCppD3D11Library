#ifndef Ch_D3D11_Cam_h
#define Ch_D3D11_Cam_h

#include"../../../ChCppBaseLibrary/BasePack/ChMath3D.h"
#include"../ChPackDate/ChVector3_11.h"
#include"../ChPackDate/ChMatrix_11.h"

namespace ChD3D11
{
	class CameraController11
	{
	public://Get Functions//

		//ViewMatrixを作成する際に、自動で上方向を計算しない。//
		inline ChLMat GetViewMat(
			const ChVec3& _pos,
			const ChVec3& _dir,
			const ChVec3& _up = ChVec3(0.0f, 1.0f, 0.0f))
		{
			ChVec3_11 dir;
			dir = _dir;
			ChVec3_11 up;
			up = _up;

			dir.Normalize();
			up.Normalize();

			ChMat_11 tmpMat;
			tmpMat.CreateViewMat(_pos, dir, up);
			camMat = tmpMat;
			return tmpMat;
		}

		//ViewMatrixを作成する際に、自動で上方向を計算する。//
		ChLMat GetViewMat(
			const ChVec3& _pos,
			const ChVec3& _dir);

		//ViewMatrixを作成する際に、自動で上方向を計算する。//
		inline ChLMat GetViewMat(
			const ChVec3& _pos,
			const ChQua& _rot)
		{

			ChMat_11 tmpMat;

			tmpMat.RotQua(_rot);

			ChVec3_11 dir;
			ChVec3_11 head;

			dir.MatNormal(tmpMat);
			head.MatNormal(tmpMat, ChVec3_11(0.0f, 1.0f, 0.0f));

			return GetViewMat(_pos, dir, head);
		}

		//前回使ったデータを使いまわす//
		inline ChLMat GetViewMat() { return camMat; }

	public://Singleton//

		static CameraController11& GetIns()
		{
			static CameraController11 ins;

			return ins;
		}

	protected:

		CameraController11(){}
		
		~CameraController11(){}

	protected://Member Value//

		ChLMat camMat;

	};

	inline CameraController11& CamCon() { return CameraController11::GetIns(); }

}

#endif