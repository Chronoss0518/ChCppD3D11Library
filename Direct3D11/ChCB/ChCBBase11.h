#ifndef Ch_D3D11_CB_Base_h
#define Ch_D3D11_CB_Base_h

namespace ChD3D11
{
	namespace CB
	{
		class CBBase11 :public ChCp::Initializer
		{
		public://Init And Release//

			void Init(ID3D11Device* _device);

			virtual void Release() {}

		protected:

			void SetShaderTexture(ID3D11DeviceContext* _dc, TextureBase11*  _tex, TextureBase11& _defaultTex, const unsigned long _registerNo);

			inline ID3D11Device* GetDevice() { return device; };

		private:

			ID3D11Device* device = nullptr;

		};

	}

}


#endif