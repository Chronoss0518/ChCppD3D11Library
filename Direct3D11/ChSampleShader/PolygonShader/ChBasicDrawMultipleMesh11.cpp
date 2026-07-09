#include<Windows.h>
#include<array>

#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../../ChTexture/ChTexture11.h"

#include"../../ChFrameComponent/ChFrameComponent11.h"

#include"../../ChSprite/ChSprite11.h"
#include"../SpriteShader/ChBaseDrawSprite11.h"
#include"ChBasicDrawMultipleMesh11.h"

template<typename CharaType>
ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::~BasicDrawMultipleMesh11()
{
	Release();
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SamplePolygonShaderBase11::Init(_device);


	SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	multiplePolygon.Init(_device, &GetWhiteTexture(), &GetNormalTexture());

	spriteCreater = ChPtr::Make_S<BaseDrawSprite11>();
	spriteCreater->Init(_device);

	sprite = ChPtr::Make_S<Sprite11>();
	sprite->Init();
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::Release()
{
	SamplePolygonShaderBase11::Release();
	multiplePolygon.Release();
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::InitVertexShader()
{

#include"../PolygonShader/BasicMultipleDrawMeshVertex.inc"

	std::array<D3D11_INPUT_ELEMENT_DESC, 11>decl;

	ChD3D11::FrameComponent11<CharaType>::CreateInputElements(decl);
	
	decl[10] = { "TEXCOORD",  1, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	
	SamplePolygonShaderBase11::CreateVertexShader(&decl[0], decl.size(), main, sizeof(main));

}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::InitGeometryShader()
{
#include"../PolygonShader/BasicMultipleDrawMeshGeometry.inc"

	//SamplePolygonShaderBase11::CreateGeometryShader(main, sizeof(main));
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::InitPixelShader()
{
#include"../PolygonShader/BasicMultipleDrawMeshPixel.inc"

	SamplePolygonShaderBase11::CreatePixelShader(main, sizeof(main));
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::CreateFrameMesh(ID3D11DeviceContext* _dc, ChPtr::Shared<ChCpp::FrameObject<CharaType>>_model)
{
	if (GetDevice() == nullptr)return;
	if (IsDraw())return;

	if (_model->GetComponent<MeshComponent>() != nullptr)return;

	unsigned long maxFrameNo = 0;

	std::vector<UseVertexs> vertexs;
	std::vector<unsigned long> indexs;
	std::array<Textures, CH_DMP_MAX_FRAME_COUNT> textures;
	std::map<Ch3D::TextureType, ChMath::Vector2Base<unsigned int>>textureSizes;

	CreateFrameMesh(_model, vertexs, indexs, maxFrameNo, textures, textureSizes);

	if (vertexs.size() <= 0)return;
	if (indexs.size() <= 0)return;

	auto&& meshCom = _model->SetComponent<MeshComponent>();

	meshCom->indexNum = indexs.size();
	meshCom->indexBuffer.CreateBuffer(
		GetDevice(),
		&indexs[0],
		meshCom->indexNum);

	meshCom->vertexBuffer.CreateBuffer(
		GetDevice(),
		&vertexs[0],
		static_cast<unsigned long>(vertexs.size()));

#if false

	auto useDeffiuseTexture = ChPtr::Make_S<RenderTarget11>();

	auto diffuseTextureMaxSize = textureSizes[Ch3D::TextureType::Diffuse];

	useDeffiuseTexture->CreateRenderTarget(GetDevice(), diffuseTextureMaxSize.w, diffuseTextureMaxSize.h);

	ID3D11RenderTargetView* baseRT;
	ID3D11DepthStencilView* baseDS;

	_dc->OMGetRenderTargets(1, &baseRT, &baseDS);

	useDeffiuseTexture->SetRenderTarget(_dc, nullptr);

	float moveSize = 1.0f / CH_DMP_MAX_FRAME_COUNT;

	float startPos = moveSize;
	startPos *= 2.0f;
	startPos -= 1.0f;

	moveSize *= 2.0f;

	ChVec4 rect = ChVec4::FromRect(-1.0f,1.0f, startPos,-1.0f);

	spriteCreater->DrawStart(_dc);

	for (unsigned long i = 0; i < CH_DMP_MAX_FRAME_COUNT; i++)
	{
		sprite->SetPosRect(rect);

		TextureBase11* tex = &GetWhiteTexture();

		auto it = textures[i].texture.find(Ch3D::TextureType::Diffuse);
		if (it != textures[i].texture.end())
			tex = it->second;

		spriteCreater->Draw(*tex, *sprite);

		rect.left += moveSize;
		rect.right += moveSize;
	}

	spriteCreater->DrawEnd();

	meshCom->useDeffiuseTexture = useDeffiuseTexture;

	_dc->OMSetRenderTargets(1, &baseRT, baseDS);

#endif

}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::CreateFrameMesh(
	ChPtr::Shared<ChCpp::FrameObject<CharaType>>_model,
	std::vector<UseVertexs>& _vertexs,
	std::vector<unsigned long>& _indexs,
	unsigned long& _maxFrameNo,
	std::array<Textures, CH_DMP_MAX_FRAME_COUNT>& _textures,
	std::map<Ch3D::TextureType, ChMath::Vector2Base<unsigned int>>& _textureSize)
{

	CreateFrameData(_model, _vertexs, _indexs, _maxFrameNo, _textures, _textureSize);

	for (auto&& child : _model->GetChildlen<ChCpp::FrameObject<CharaType>>())
	{
		if (child.expired())continue;

		CreateFrameMesh(child.lock(), _vertexs, _indexs, _maxFrameNo, _textures, _textureSize);
	}

}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::CreateFrameData(
	ChPtr::Shared<ChCpp::FrameObject<CharaType>>_model,
	std::vector<UseVertexs>& _vertexs,
	std::vector<unsigned long>& _indexs,
	unsigned long& _maxFrameNo,
	std::array<Textures, CH_DMP_MAX_FRAME_COUNT>& _textures,
	std::map<Ch3D::TextureType, ChMath::Vector2Base<unsigned int>>& _textureSize)
{
	auto&& frameCom = _model->GetComponent<ChCpp::FrameComponent<CharaType>>();
	if (frameCom == nullptr)return;

	auto&& createFrameCom = _model->GetComponent<FrameComponent>();
	if (createFrameCom != nullptr)return;

	if (frameCom->primitives.size() <= 0)return;
	if (frameCom->vertexList.size() <= 0)return;

	createFrameCom = _model->SetComponent<FrameComponent>();

	createFrameCom->frameCom = frameCom;

	auto&& primitives = frameCom->primitives;
	auto&& vertexs = frameCom->vertexList;
	auto&& materials = frameCom->materialList;

	for (size_t i = 0; i < materials.size(); i++)
	{
		auto prim = ChPtr::Make_S<FrameComponent::PrimitiveData>();
		prim->mate = materials[i];

		prim->drawFlg = true;

		prim->frameNo = _maxFrameNo;
		_maxFrameNo++;

		for (unsigned char i = 0; i < ChStd::EnumCast(Ch3D::TextureType::None); i++)
		{
			Ch3D::TextureType type = static_cast<Ch3D::TextureType>(i);

			auto&& texPath = prim->mate->textures.find(type);
			if (texPath == prim->mate->textures.end())continue;
			if ((*texPath).second.empty())continue;

			auto texture = ChPtr::Make_S<Texture11>();
			texture->CreateTexture((*texPath).second, GetDevice());

			if (!texture->IsTex())texture = nullptr;
			prim->textures[type] = texture;

			ChMath::Vector2Base<unsigned int> size = texture->GetTextureSize();
			auto textureMaxSize = _textureSize[type];

			textureMaxSize.w = textureMaxSize.w < size.w ? size.w : textureMaxSize.w;
			textureMaxSize.h = textureMaxSize.h < size.h ? size.h : textureMaxSize.h;

			_textureSize[type].val.Set(textureMaxSize.val);
			_textures[prim->frameNo].texture[type] = texture.get();
		}



		createFrameCom->primitives.push_back(prim);
	}

	unsigned long maxVertexCount = 0;

	for (auto&& primitive : primitives)
	{
 		maxVertexCount = _vertexs.size();

		auto&& material = createFrameCom->primitives[primitive->mateNo];

		for (size_t i = 0; i < primitive->vertexData.size(); i++)
		{
			unsigned long vertexNo = primitive->vertexData[i]->vertexNo;
			auto&& baseVertex = vertexs[vertexNo];
			UseVertexs vertex;
			vertex.pos =  baseVertex->pos;
			vertex.color =  baseVertex->color;
			vertex.normal =  baseVertex->normal;
			vertex.uv = primitive->vertexData[i]->uv;
			vertex.faceNormal = primitive->faceNormal;
			vertex.frameNo = material->frameNo;

			_vertexs.push_back(vertex);
		}

		for (size_t i = 1; i < primitive->vertexData.size() - 1; i++)
		{
			_indexs.push_back(static_cast<unsigned long>(maxVertexCount));
			_indexs.push_back(static_cast<unsigned long>(maxVertexCount + i));
			_indexs.push_back(static_cast<unsigned long>(maxVertexCount + i + 1));
		}
	}
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::SetProjectionMatrix(const ChLMat& _mat)
{
	multiplePolygon.SetProjectionMatrix(_mat);
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::SetViewMatrix(const ChLMat& _mat)
{
	multiplePolygon.SetViewMatrix(_mat);
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::SetMoveUV(const ChVec2& _move, unsigned int _num)
{
	multiplePolygon.SetMoveUV(_move, _num);
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	multiplePolygon.SetVSDrawData(_dc);
	multiplePolygon.SetPSDrawData(_dc);
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::SetShaderModelData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	multiplePolygon.SetVSModelData(_dc);
	multiplePolygon.SetPSModelData(_dc);
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::SetShaderFrameData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	multiplePolygon.SetVSFrameData(_dc);
	multiplePolygon.SetGSFrameData(_dc);
	multiplePolygon.SetPSFrameData(_dc);
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::DrawStart(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (IsDraw())return;
	if (ChPtr::NullCheck(_dc))return;

	SamplePolygonShaderBase11::DrawStart(_dc);
	if (alphaBlendFlg)
		SamplePolygonShaderBase11::SetShaderBlender(GetDC());

}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::Draw(
	ChCpp::FrameObject<CharaType>& _mesh,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (ChPtr::NullCheck(GetDC()))return;

	auto&& meshCom = _mesh.GetComponent<MeshComponent>();
	if (meshCom == nullptr)return;

	for (unsigned long i = 0; i < CH_DMP_MAX_FRAME_COUNT; i++)
	{
		multiplePolygon.SetDrwaFlags(false, i);
	}

	meshCom->vertexBuffer.SetVertexBuffer(GetDC(), 0);
	meshCom->indexBuffer.SetIndexBuffer(GetDC());

	multiplePolygon.SetWorldMatrix(_mat);

	_mesh.UpdateDrawTransform();

	DrawUpdate(_mesh);

	multiplePolygon.SetShaderModelData(GetDC());
	multiplePolygon.SetShaderMaterialData(GetDC());
	multiplePolygon.SetShaderFrameData(GetDC());
	multiplePolygon.SetShaderTexture(GetDC());


	GetDC()->DrawIndexedInstanced(static_cast<unsigned int>(meshCom->indexNum), 1, 0, 0, 0);

}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::DrawUpdate(ChCpp::FrameObject<CharaType>& _object)
{
#if DEBUG
	unsigned long start, end;

	std::string debug;

	debug = "Draw Start:" + _object->GetMyName() + "\n";

	OutputDebugString(debug.c_str());

	start = timeGetTime();
#endif

	DrawMain(_object);

#if DEBUG
	end = timeGetTime();
	debug = "Draw End Time:" + std::to_string(end - start) + "\n";
	OutputDebugString(debug.c_str());
	OutputDebugString(">\n");
	OutputDebugString(">\n");
#endif

	auto&& childlen = _object.GetChildlen<ChCpp::FrameObject<CharaType>>();

	for (auto&& child : childlen)
	{
		if (child.expired())continue;
		DrawUpdate(*child.lock());
	}

}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::DrawMain(ChCpp::FrameObject<CharaType>& _object)
{

	_object.UpdateDrawTransform();
	auto&& frameCom = _object.GetComponent<FrameComponent>();

	if (frameCom == nullptr)return;

	auto&& primitives = frameCom->primitives;

	if (primitives.empty())return;

	ChLMat drawMatrix = _object.GetDrawLHandMatrix();

	for (auto&& prim : primitives)
	{
		if (prim == nullptr)continue;

		auto&& mate11 = *prim->mate;

		multiplePolygon.SetMateDiffuse(mate11.mate.diffuse, prim->frameNo);
		multiplePolygon.SetMateSpecularColor(mate11.mate.specularColor, prim->frameNo);
		multiplePolygon.SetMateSpecularPower(mate11.mate.specularPower, prim->frameNo);
		multiplePolygon.SetMateAmbientColor(mate11.mate.ambient, prim->frameNo);

		multiplePolygon.SetFrameMatrix(drawMatrix, prim->frameNo);
		multiplePolygon.SetDrwaFlags(prim->drawFlg, prim->frameNo);

		multiplePolygon.SetBaseTexture(prim->textures[Ch3D::TextureType::Diffuse].get(), prim->frameNo);
		//multiplePolygon.SetBaseTexture(&GetWhiteTexture());
	}
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::DrawEnd()
{
	SamplePolygonShaderBase11::SetShaderDefaultBlender(GetDC());
	SamplePolygonShaderBase11::DrawEnd();
}

template<typename CharaType>
void ChD3D11::Shader::BasicDrawMultipleMesh11<CharaType>::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;
	SamplePolygonShaderBase11::Update(_dc);
	updateFlg = false;
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChD3D11::Shader::BasicDrawMultipleMesh11);
