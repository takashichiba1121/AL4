#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
class Model
{
public: // サブクラス
	// 頂点データ構造体
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos; // xyz座標
		DirectX::XMFLOAT3 normal; // 法線ベクトル
		DirectX::XMFLOAT2 uv;  // uv座標
	};
	//マテリアル
	struct Material
	{
		std::string name; //マテリアル名
		DirectX::XMFLOAT3 ambient; //アンビエント影響度
		DirectX::XMFLOAT3 diffuse; //ディフューズ影響度
		DirectX::XMFLOAT3 specular; //スペキュラー影響度
		float alpha; //アルファ
		std::string textureFilename; //テクスチャファイル名
		//コンストラクタ
		Material() {
			ambient = { 0.3f,0.3,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
private:
	// デバイス
	static ID3D12Device* device;

private:
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;
	//頂点データ配列
	//static VertexPosNorma1Uv
	std::vector<VertexPosNormalUv> vertices;
	//頂点インデックス配列
	//static unsigned short indices[planeCount*3];
	std::vector<unsigned short> indices;
	//マテリアル
	Material material;

	uint32_t textureIndex;
private:

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// モデル作成
	/// </summary>
	void CreateModel(const std::string& filename);

	/// <summary>
	/// マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string& directory, const std::string& filename);
public:
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// モデルの作成（objファイル）
	/// </summary>
	/// <param name="filename">objの入っているファイル名</param>
	/// <returns></returns>
	static Model* CreateFromOBJ(const std::string& filename);


	DirectX::XMFLOAT3 GetAmbient() { return material.ambient; }

	DirectX::XMFLOAT3 GetDiffuse() { return material.diffuse; }

	DirectX::XMFLOAT3 GetSpecular() { return material.specular; }

	float Getalpha() { return material.alpha; }

	void Draw(ID3D12GraphicsCommandList* cmdList);
};

