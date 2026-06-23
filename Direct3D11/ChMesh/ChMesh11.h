#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../../ChCppBaseLibrary/CPP/ChBaseObject/ChBaseComponent.h"
#include"../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"
#include"../ChShaderStructures11.h"

#include"../ChTexture/ChTexture11.h"

#include"../../../ChCppBaseLibrary/CPP/ChBaseObject/ChBaseObject.h"
#include"../ChCB/ChCBBone/ChCBBone11.h"

#include<string>
#include<vector>
#include<map>

namespace ChD3D11
{

	class Texture11;

	template<typename CharaType>
	class Mesh11 : public ChCpp::ModelObject<CharaType>
	{
	public://Init And Release//

		void Init(ID3D11Device* _device);

		void Init()override;

		void Release()override;

	public://Create Functions//

		void Create()override;

	protected://Create Functions//

		void CreateFrames();

	public://Get Functions//

		inline ID3D11Device* GetDevice() { return device; }

	private:

		ID3D11Device* device = nullptr;
	};

}

#endif