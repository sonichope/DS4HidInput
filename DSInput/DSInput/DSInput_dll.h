#pragma once
#include "DSManager.h"
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

	//プレイヤーライトの変更
	EXPORT_API bool ChangePlayerLight(int id, const UCHAR val);

	//振動の変更
	EXPORT_API void ChangeVibration(int id, UCHAR right, UCHAR left);

	//トリガーのロック
	EXPORT_API void ChangeTriggerLock(int id, UCHAR rMode, UCHAR right, UCHAR lMode, UCHAR left);

	//アウトプットレポートの送信
	EXPORT_API void SendOutput(int id);

	//レポートの更新
	EXPORT_API bool UpdateInputReport();

	//ボタンの取得
	EXPORT_API bool GetButton(int id, UCHAR keyType);

	//ボタンダウンの取得
	EXPORT_API bool GetButtonDown(int id, UCHAR keyType);

	//ボタンアップの取得
	EXPORT_API bool GetButtonUp(int id, UCHAR keyType);

	//軸の取得
	EXPORT_API float GetAxis(int id, UCHAR keyType);

	//管理終了
	EXPORT_API bool EndDS4();
}
