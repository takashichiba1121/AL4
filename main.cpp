#include <Novice.h>
#include<cmath>
#include"Vector2.h"

const char kWindowTitle[] = "学籍番号";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector2 lineStart = { 0 ,0 }, lineEnd = { 1280,720 };
	Vector2 circle = { 1180,620 };
	float Radius = 100;
	int color = 0;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		/// 
		if (keys[DIK_A])
		{
			circle.x--;
		}
		if (keys[DIK_D])
		{
			circle.x++;
		}
		if (keys[DIK_W])
		{
			circle.y--;
		}
		if (keys[DIK_S])
		{
			circle.y++;
		}

		Vector2 startCenterVec = { circle.x - lineStart.x,circle.y - lineStart.y };
		Vector2 endCenterVec = { circle.x - lineEnd.x,circle.y - lineEnd.y };
		Vector2 startEndVec = { lineEnd.x -lineStart.x,lineEnd.y -lineStart.y  };
		Vector2 normalStartEndVec = startEndVec;

		normalStartEndVec.normalize();
		float distanceProjection = startCenterVec.cross(normalStartEndVec);

		if (fabs(distanceProjection) < Radius)
		{
			float dot1 = startCenterVec.dot(startEndVec);
			float dot2 = endCenterVec.dot(startEndVec);

			if (dot1 * dot2 <= 0)
			{
				color = RED;
			}
			else
			{
				if (startCenterVec.length() < Radius || endCenterVec.length() < Radius)
				{
					color = RED;
				}
				else
				{
					color = BLACK;
				}
			}
		}
		else
		{
			color = BLACK;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(circle.x, circle.y, Radius, Radius, 0, color, kFillModeWireFrame);
		Novice::DrawLine(lineStart.x, lineStart.y, lineEnd.x, lineEnd.y, color);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
