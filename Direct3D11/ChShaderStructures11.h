
//SStruct = ShaderStructure//
#ifndef Ch_D3D11_SStruct_h
#define Ch_D3D11_SStruct_h

#ifndef CH_CONSTANTS_BUFFER_STATIC_METHODS
#define CH_CONSTANTS_BUFFER_STATIC_METHODS(methodName,dcMethodName)\
static inline void methodName(\
	ID3D11DeviceContext* _dc,\
	unsigned long _registerNo,\
	std::vector<ConstantBuffer11<content>*>& _constants){\
	if (ChPtr::NullCheck(_dc))return;\
	std::vector<ID3D11Buffer*>buffers;\
\
	for (auto&& con : _constants){\
		if (ChPtr::NullCheck(con))continue;\
		if (!con->IsInit())continue;\
		if (con->registerNo != _registerNo)continue;\
		buffers.push_back(con->buf);}\
\
	ConstantBuffer11<content>::methodName(_dc, _registerNo, buffers);\
}\
\
static inline void methodName(\
	ID3D11DeviceContext* _dc,\
	unsigned long _registerNo,\
	std::vector<ID3D11Buffer*>& _buffers){\
	if (_buffers.empty())return;\
	if (ChPtr::NullCheck(_dc))return;\
\
	_dc->dcMethodName(_registerNo, _buffers.size(), &_buffers[0]);\
}

#endif

namespace ChD3D11
{
	class TextureBase11;

	struct SkinMeshVertex11 : public Ch3D::MeshVertex
	{
		float blendPow[96];
	};

	class ShaderObjectBase11 :public ChCp::Initializer
	{
	public:

		virtual ~ShaderObjectBase11() { Release(); }

	public://Init And Release//

		inline void Init() { SetInitFlg(true); }

		inline virtual void Release()
		{
			SetInitFlg(false);
			if (ChPtr::NullCheck(buf))return;
			buf->Release();
			buf = nullptr;
		};

	public://Add Functions//

		//Flgメソッド//
		inline void AddCPUAccessFlg(const D3D11_CPU_ACCESS_FLAG& _flg) { cpuAccessFlg |= _flg; }

	public://Set Functions//

		//Flgメソッド//
		inline void SetUsageFlg(const D3D11_USAGE& _flg) { usage = _flg; }

		//Flgメソッド//
		inline void SetCPUAccessFlg(const D3D11_CPU_ACCESS_FLAG& _flg) { cpuAccessFlg = _flg; }

		template<class T>
		inline void SetDynamicBuffer(ID3D11DeviceContext* _dc, const T* _buf, const unsigned long _bufSize)
		{
			if (!(usage & D3D11_USAGE::D3D11_USAGE_DYNAMIC))return;

			D3D11_MAPPED_SUBRESOURCE map;
			ZeroMemory(&map, sizeof(D3D11_MAPPED_SUBRESOURCE));

			//  Disable GPU access to the vertex buffer data.
			_dc->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
			//  Update the vertex buffer here.
			memcpy(map.pData, _buf, _bufSize);
			//  Reenable GPU access to the vertex buffer data.
			_dc->Unmap(buf, 0);
		}

	public://Update Functions//

		template<class T>
		inline void UpdateResouce(
			ID3D11DeviceContext* _dc,
			const T* _content)
		{

			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;
			if (ChPtr::NullCheck(_content))return;

			_dc->UpdateSubresource(buf, 0, nullptr, _content, 0, 0);
		}

	protected://Create Functions//

		template<class T>
		inline D3D11_BUFFER_DESC CreateBufferDesc(const unsigned long _num)
		{
			D3D11_BUFFER_DESC desc;
			ChStd::MZero(&desc);
			desc.ByteWidth = sizeof(T) * _num;
			desc.Usage = usage;
			desc.BindFlags = bindFlg;
			desc.CPUAccessFlags = cpuAccessFlg;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;
			return desc;
		}

		inline D3D11_SUBRESOURCE_DATA CreateSubresourceData(void* _buf)
		{
			D3D11_SUBRESOURCE_DATA data;
			ChStd::MZero(&data);
			data.pSysMem = _buf;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			return data;
		}

	protected:

		ID3D11Buffer* buf = nullptr;

		unsigned int cpuAccessFlg = 0;
		D3D11_USAGE usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		D3D11_BIND_FLAG bindFlg = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	};

	class IndexBuffer11 : public ShaderObjectBase11
	{
	public:

		virtual ~IndexBuffer11() { Release(); }

	public://Create Functions//

		//Createを呼ぶ前に必要な場合はフラグ関係を操作するメソッドを呼びます//
		inline void CreateBuffer(
			ID3D11Device* _device,
			unsigned long* _indexBuffer,
			const unsigned long _indexNum)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();
			bindFlg = D3D11_BIND_INDEX_BUFFER;
			D3D11_BUFFER_DESC desc = CreateBufferDesc<unsigned long>(_indexNum);
			D3D11_SUBRESOURCE_DATA data = CreateSubresourceData(_indexBuffer);
			format = DXGI_FORMAT_R32_UINT;
			_device->CreateBuffer(&desc, &data, &buf);

			Init();
		}

		//Createを呼ぶ前に必要な場合はフラグ関係を操作するメソッドを呼びます//
		inline void CreateBuffer(
			ID3D11Device* _device,
			unsigned char* _indexBuffer,
			const unsigned char _indexNum)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();
			bindFlg = D3D11_BIND_INDEX_BUFFER;
			D3D11_BUFFER_DESC desc = CreateBufferDesc<unsigned char>(_indexNum);
			D3D11_SUBRESOURCE_DATA data = CreateSubresourceData(_indexBuffer);
			format = DXGI_FORMAT_R8_UINT;
			_device->CreateBuffer(&desc, &data, &buf);

			Init();
		}

	public://Set Functions//

		inline void SetIndexBuffer(ID3D11DeviceContext* _dc)
		{
			if (!*this)return;
			if (ChPtr::NullCheck(_dc))return;
			_dc->IASetIndexBuffer(buf, format, 0);
		}

	private:

		DXGI_FORMAT format = DXGI_FORMAT_R32_UINT;

	};

	template<class vertex = Ch3D::Vertex>
	class VertexBuffer11 : public ShaderObjectBase11
	{
	public:

		virtual ~VertexBuffer11()
		{
			Release();
		}

	public://Create Functions//

		//Createを呼ぶ前に必要な場合はフラグ関係を操作するメソッドを呼びます//
		inline void CreateBuffer(
			ID3D11Device* _device,
			vertex* _vertexArray,
			const unsigned long _vertexNum)
		{
			if (ChPtr::NullCheck(_device))return;
			if (ChPtr::NullCheck(_vertexArray))return;

			Release();
			bindFlg = D3D11_BIND_VERTEX_BUFFER;
			D3D11_BUFFER_DESC desc = CreateBufferDesc<vertex>(_vertexNum);
			D3D11_SUBRESOURCE_DATA data = CreateSubresourceData(_vertexArray);
			_device->CreateBuffer(&desc, &data, &buf);

			Init();
		}

	public://Set Functions//

		inline void SetVertexBuffer(
			ID3D11DeviceContext* _dc,
			const unsigned int _offset)
		{
			if (!IsInit())return;
			std::vector<ID3D11Buffer*>list;
			list.push_back(buf);
			VertexBuffer11<vertex>::SetVertexBuffer(_dc , _offset, list);
		}

	public://Set Functions//

		static inline void SetVertexBuffer(
			ID3D11DeviceContext* _dc,
			const unsigned int _offset,
			const std::vector<VertexBuffer11<vertex>*>& _vertexs)
		{
			if (ChPtr::NullCheck(_dc))return;

			unsigned int strides = sizeof(vertex);
			std::vector<ID3D11Buffer*> buffers;

			for (auto&& vertex : _vertexs)
			{
				if (ChPtr::NullCheck(vertex))continue;
				if (!vertex->IsInit())continue;
				buffers.push_back(vertex->buf);
			}

			VertexBuffer11<vertex>::SetVertexBuffer(_dc, _offset, buffers);
		}

		static inline void SetVertexBuffer(
			ID3D11DeviceContext* _dc,
			const unsigned int _offset,
			const std::vector<ID3D11Buffer*>& _buffers)
		{
			if (ChPtr::NullCheck(_dc))return;
			if (_buffers.empty())return;

			unsigned int strides = sizeof(vertex);

			_dc->IASetVertexBuffers(0, _buffers.size(), &_buffers[0], &strides, &_offset);
		}

	};

	template<class content>
	class ConstantBuffer11 :public ShaderObjectBase11
	{
	public:

		virtual ~ConstantBuffer11() { Release(); }

	public://Create Functions//

		//Createを呼ぶ前に必要な場合はフラグ関係を操作するメソッドを呼びます//
		inline void CreateBuffer(
			ID3D11Device* _device,
			const unsigned long _registerNo)
		{
			if (ChPtr::NullCheck(_device))return;

			Release();
			bindFlg = D3D11_BIND_CONSTANT_BUFFER;
			D3D11_BUFFER_DESC desc = CreateBufferDesc<content>(1);
			unsigned long makeUpBuffer = desc.ByteWidth % 16;
			desc.ByteWidth = makeUpBuffer == 0 ? desc.ByteWidth : desc.ByteWidth + (16 - makeUpBuffer);
			_device->CreateBuffer(&desc, nullptr, &buf);
			registerNo = _registerNo;

			Init();
		}

	public://Set Functions//

		inline void SetRegisterNo(const unsigned long _registerNo) { registerNo = _registerNo; }

		inline void SetToVertexShader(
			ID3D11DeviceContext* _dc)
		{
			if (!IsInit())return;
			if (ChPtr::NullCheck(_dc))return;

			std::vector<ID3D11Buffer*>buffers;
			buffers.push_back(buf);

			ConstantBuffer11<content>::SetToVertexShader(_dc,registerNo, buffers);
		}

		inline void SetToGeometryShader(
			ID3D11DeviceContext* _dc)
		{
			if (!IsInit())return;
			if (ChPtr::NullCheck(_dc))return;

			std::vector<ID3D11Buffer*>buffers;
			buffers.push_back(buf);

			ConstantBuffer11<content>::SetToGeometryShader(_dc, registerNo, buffers);
		}

		inline void SetToHullShader(
			ID3D11DeviceContext* _dc)
		{
			if (!IsInit())return;
			if (ChPtr::NullCheck(_dc))return;

			std::vector<ID3D11Buffer*>buffers;
			buffers.push_back(buf);

			ConstantBuffer11<content>::SetToHullShader(_dc, registerNo, buffers);
		}

		inline void SetToDomainShader(
			ID3D11DeviceContext* _dc)
		{
			if (!IsInit())return;
			if (ChPtr::NullCheck(_dc))return;

			std::vector<ID3D11Buffer*>buffers;
			buffers.push_back(buf);

			ConstantBuffer11<content>::SetToDomainShader(_dc, registerNo, buffers);
		}

		inline void SetToPixelShader(
			ID3D11DeviceContext* _dc)
		{
			if (!IsInit())return;
			if (ChPtr::NullCheck(_dc))return;

			std::vector<ID3D11Buffer*>buffers;
			buffers.push_back(buf);

			ConstantBuffer11<content>::SetToPixelShader(_dc, registerNo, buffers);
		}

		inline void SetToComputeShader(
			ID3D11DeviceContext* _dc)
		{
			if (!IsInit())return;
			if (ChPtr::NullCheck(_dc))return;

			std::vector<ID3D11Buffer*>buffers;
			buffers.push_back(buf);

			ConstantBuffer11<content>::SetToComputeShader(_dc, registerNo, buffers);
		}

	public://Set Functions//

		CH_CONSTANTS_BUFFER_STATIC_METHODS(SetToVertexShader, VSSetConstantBuffers);

		CH_CONSTANTS_BUFFER_STATIC_METHODS(SetToGeometryShader, GSSetConstantBuffers);

		CH_CONSTANTS_BUFFER_STATIC_METHODS(SetToHullShader, HSSetConstantBuffers);

		CH_CONSTANTS_BUFFER_STATIC_METHODS(SetToDomainShader, DSSetConstantBuffers);

		CH_CONSTANTS_BUFFER_STATIC_METHODS(SetToPixelShader, PSSetConstantBuffers);

		CH_CONSTANTS_BUFFER_STATIC_METHODS(SetToComputeShader, CSSetConstantBuffers);

	public://Get Functions//

		inline unsigned long GetRegisterNo() { return registerNo; }

	protected:

		unsigned long registerNo = 0;
	};


}

#endif