#pragma once
#include "DS4Manager.h"
#define EXPORT_API __declspec(dllexport)

extern "C" 
{
	//管理スタート
	EXPORT_API bool StartDS4();

	//コントローラの取得
	EXPORT_API bool GetController();

	//コントローラのチェック
	EXPORT_API bool ControllerCheck(int id);

	//色の変更
	EXPORT_API bool ChangeColor(int id, const UCHAR r, const UCHAR g, const UCHAR b);

	//振動の変更
	EXPORT_API void ChangeVibration(int id, UCHAR right, UCHAR left);

	//アウトプットレポートの送信
	EXPORT_API void SendOutput(int id);

	//レポートの更新
	EXPORT_API bool UpdateInputReport();

	//ボタンの取得
	EXPORT_API bool GetButton(int id, DS4KeyType keyType);

	//ボタンダウンの取得
	EXPORT_API bool GetButtonDown(int id, DS4KeyType keyType);

	//ボタンアップの取得
	EXPORT_API bool GetButtonUp(int id, DS4KeyType keyType);

	//軸の取得
	EXPORT_API float GetAxis(int id, DS4AxisType keyType);

	//管理終了
	EXPORT_API bool EndDS4();
}
