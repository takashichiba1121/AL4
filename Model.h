#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
class Model
{
public: // �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos; // xyz���W
		DirectX::XMFLOAT3 normal; // �@���x�N�g��
		DirectX::XMFLOAT2 uv;  // uv���W
	};
	//�}�e���A��
	struct Material
	{
		std::string name; //�}�e���A����
		DirectX::XMFLOAT3 ambient; //�A���r�G���g�e���x
		DirectX::XMFLOAT3 diffuse; //�f�B�t���[�Y�e���x
		DirectX::XMFLOAT3 specular; //�X�y�L�����[�e���x
		float alpha; //�A���t�@
		std::string textureFilename; //�e�N�X�`���t�@�C����
		//�R���X�g���N�^
		Material() {
			ambient = { 0.3f,0.3,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
private:
	// �f�o�C�X
	static ID3D12Device* device;

private:
	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	//���_�f�[�^�z��
	//static VertexPosNorma1Uv
	std::vector<VertexPosNormalUv> vertices;
	//���_�C���f�b�N�X�z��
	//static unsigned short indices[planeCount*3];
	std::vector<unsigned short> indices;
	//�}�e���A��
	Material material;

	uint32_t textureIndex;
private:

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// ���f���쐬
	/// </summary>
	void CreateModel(const std::string& filename);

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string& directory, const std::string& filename);
public:
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// ���f���̍쐬�iobj�t�@�C���j
	/// </summary>
	/// <param name="filename">obj�̓����Ă���t�@�C����</param>
	/// <returns></returns>
	static Model* CreateFromOBJ(const std::string& filename);


	DirectX::XMFLOAT3 GetAmbient() { return material.ambient; }

	DirectX::XMFLOAT3 GetDiffuse() { return material.diffuse; }

	DirectX::XMFLOAT3 GetSpecular() { return material.specular; }

	float Getalpha() { return material.alpha; }

	void Draw(ID3D12GraphicsCommandList* cmdList);
};

