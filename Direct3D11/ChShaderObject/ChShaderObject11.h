#ifndef Ch_D3D11_SObject_h
#define Ch_D3D11_SObject_h

namespace ChD3D11
{
	class ShaderObject11:public ChCp::Initializer
	{
	public://Constractor Destructor//

		virtual ~ShaderObject11()
		{
			Release();
		}

	public://Init And Release//

		virtual void Release();

	protected://Create Functions//

		//VertexShader用//
		void CreateVertexShader(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize);

		//PixelShader用//
		void CreatePixelShader(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize);

		//VertexShader用//
		void CreateGeometryShader(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize);

		//VertexShader用//
		void CreateComputeShader(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize);

		//VertexShader用//
		void CreateDomainShader(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize);

		//VertexShader用//
		void CreateHullShader(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize);

	public://Set Functions//

		virtual void SetShader(ID3D11DeviceContext* _dc) = 0;

	protected://Set Functions//

		void SetVertexShader(
			ID3D11DeviceContext* _dc,
			ID3D11InputLayout* _lInput);

		void SetPixelShader(ID3D11DeviceContext* _dc);

		void SetGeometryShader(ID3D11DeviceContext* _dc);

		void SetComputeShader(ID3D11DeviceContext* _dc);

		void SetDomainShader(ID3D11DeviceContext* _dc);

		void SetHullShader(ID3D11DeviceContext* _dc);

	private://Member Value//

		ID3D11DeviceChild* shader = nullptr;

	};

	class VertexShader11 final :public ShaderObject11
	{
	public:

		virtual ~VertexShader11() { Release(); }

	public://Init And Release//

		void Init(
			ID3D11Device* _device,
			const D3D11_INPUT_ELEMENT_DESC* _desc,
			const unsigned long _descNum,
			const void* _binary,
			const unsigned long _binarySize);

		void Release()override;

	public://Set Functions//

		inline void SetShader(ID3D11DeviceContext* _dc)override { SetVertexShader(_dc, lInput); }

	private://Create Functions//

		void CreateInputLayout(
			ID3D11Device* _device,
			ID3D11InputLayout** _lInput,
			const D3D11_INPUT_ELEMENT_DESC* _desc,
			const unsigned long _descNum,
			const void* _binary,
			const unsigned long _binarySize);

	private://Member Value//

		ID3D11InputLayout* lInput = nullptr;
	};

	class PixelShader11 final :public ShaderObject11
	{
	public:

		virtual ~PixelShader11() { Release(); }

	public://Init And Release//

		inline void Init(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize)
		{
			CreatePixelShader(_device, _binary, _binarySize);
		}

	public://Set Functions//

		inline void SetShader(ID3D11DeviceContext* _dc)override { SetPixelShader(_dc); }

	};

	class GeometryShader11 final :public ShaderObject11
	{
	public:

		virtual ~GeometryShader11() { Release(); }

	public://InitAndRelease//

		inline void Init(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize)
		{
			CreateGeometryShader(_device, _binary, _binarySize);
		}

	public://Set Function/

		inline void SetShader(ID3D11DeviceContext* _dc)override
		{
			SetGeometryShader(_dc);
		}
	};

	class ComputeShader11 final :public ShaderObject11
	{
	public://Constructor Destructor

		virtual ~ComputeShader11()
		{
			Release();
		}

	public://InitAndRelease//

		inline void Init(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize)
		{
			CreateComputeShader(_device, _binary, _binarySize);
		}

	public://Set Functions//

		inline void SetShader(ID3D11DeviceContext* _dc)override
		{
			SetComputeShader(_dc);
		}
	};

	class DomainShader11 final :public ShaderObject11
	{
	public://Constructor Destructor//

		virtual ~DomainShader11()
		{
			Release();
		}

	public://Init And Release//

		inline void Init(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize)
		{
			CreateDomainShader(_device, _binary, _binarySize);
		}

	public://Set Functions//

		inline void SetShader(ID3D11DeviceContext* _dc)override
		{
			SetDomainShader(_dc);
		}
	};

	class HullShader11 final :public ShaderObject11
	{
	public:

		virtual ~HullShader11()
		{
			Release();
		}

	public://Init And Release//

		inline void Init(
			ID3D11Device* _device,
			const void* _binary,
			const unsigned long _binarySize)
		{
			CreateHullShader(_device, _binary, _binarySize);
		}

	public://Set Functions//

		inline void SetShader(ID3D11DeviceContext* _dc)override
		{
			SetHullShader(_dc);
		}

	};

}


#endif