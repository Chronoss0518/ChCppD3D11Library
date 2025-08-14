
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawSprite.hlsli"

//���_�V�F�_(VertexShader)//
//�X�v���C�g�o�[�W����//
VS_OUT main(
	float4 pos : POSITION0,
	float2 uv : TEXCOORD0,
	float4 color : COLOR0,
	uint _instanceId : SV_InstanceID
) {
	VS_OUT res;

    MTWStruct str = ModelToWorld(pos, uv);
	
    res.pos = str.pos;

	//�e�N�X�`���}�b�v��̈ʒu���//
	res.uv = uv;

	res.color = color;

	//�o��//
	return res;
}
