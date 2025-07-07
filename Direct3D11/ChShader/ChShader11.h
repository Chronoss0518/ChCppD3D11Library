#ifndef Ch_D3D11_Shader_h
#define Ch_D3D11_Shader_h


#include"../ChShaderObject/ChShaderObject11.h"
#include"../ChShaderParts/ChShaderParts11.h"
#include"../ChSampleShader/SpriteShader/ChBaseDrawSprite11.h"

namespace ChD3D11
{
	class DirectX3D11;

	class TextureBase11;
	class Texture11;
	class RenderTarget11;
	class DepthStencilTexture11;
	class Sprite11;

	//※LightはShader内のBaseLightとPointLightを利用してください//
	//独自で構築しているShaderクラス//
	class ShaderController11 final :public ChCp::Initializer
	{
	public://Init And Release//

		void Init(
			DirectX3D11& _chDevice,
			const ChVec2& _windSize);

		void Init(
			DirectX3D11& _chDevice,
			const float& _windWitdh,
			const float& _windHeight);

		void Init(
			ID3D11Device* _d,
			ID3D11DeviceContext* _dc,
			IDXGISwapChain* _sc,
			const ChVec2& _windSize);

		void Init(
			ID3D11Device* _d,
			ID3D11DeviceContext* _dc,
			IDXGISwapChain* _sc,
			const float& _windWitdh,
			const float& _windHeight);

		virtual void Release();

	public://Set Functions//

		//描画させるレンダーターゲットを登録する//
		void SetRenderTarget(RenderTarget11& _tex);

		inline void SetBackColor(const ChVec4& _color)
		{
			if (!*this)return;
			backColor = _color;
		}

		inline void SetWindPos(const ChVec2& _pos)
		{
			if (!*this)return;
			view.SetTopLeftPos(_pos);
		}

		inline void SetWindSize(const ChVec2& _size)
		{
			if (!*this)return;
			view.SetSize(_size);
		}

	public://Draw Functions//

		//描画開始前に呼ぶ関数//
		void DrawStart();

		//すべての描画終了時に呼ぶ関数//
		void DrawEnd();

		//すべての描画終了時に呼ぶ関数//
		void DrawEnd(ChD3D11::TextureBase11& _tex);

	protected://Member Value//

		Sprite11 outSprite;

		Shader::BaseDrawSprite11 spriteShader;

		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* dc = nullptr;

		//DepthStencilBuffer用//
		DepthStencilTexture11 dsBuffer;

		ShaderParts::ViewPort view;
		
		//背景色//
		ChVec4 backColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ShaderParts::DrawWindow window;

	public:

		static inline ShaderController11& GetIns()
		{
			static ShaderController11 ins;
			return ins;
		}

	private:

		ShaderController11() {}

		virtual ~ShaderController11() { Release(); }

	};

	inline ShaderController11& Shader11() { return ShaderController11::GetIns(); }
}

#endif
//CopyRight Chronoss0518 2018/08