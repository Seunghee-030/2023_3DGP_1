#pragma once

#include "Player.h"
#include "Scene.h"
#include "Timer.h"

class CGameFramework
{
public:
	CGameFramework() { }
	~CGameFramework() { }

private:
	HINSTANCE					m_hInstance = NULL;
	HWND						m_hWnd = NULL;

	bool						m_bActive = true;

	RECT						m_rcClient;

    HDC							m_hDCFrameBuffer = NULL;
    HBITMAP						m_hBitmapFrameBuffer = NULL;
    HBITMAP						m_hBitmapSelect = NULL;

	CPlayer*					m_pPlayer = NULL;
	CPlayer*					m_pPlayer2 = NULL;
	CScene*						m_pScene = NULL;

	CCamera*					m_pCamera = NULL;
	CGameObject*				m_pLockedObject = NULL;
	CGameObject*				m_pLockedObject2 = NULL;

	CGameTimer					m_GameTimer;

	POINT						m_ptOldCursorPos;

	_TCHAR						m_pszFrameRate[50];

	///////////////////////////////////////
	/* CommandQueue & List : GPU는 1개의 명령 Queue를 갖고있고 CPU가 CommandList를 넣어주면 GPU는 1프레임마다 순서대로 실행한다. */
	/* Allocator : 명령 할당자 - 명령 리스트의 메모리를 할당 받는다. */
	ID3D12CommandQueue* m_pd3dCommandQueue;		// 명령 큐 인터페이스 포인터
	ID3D12CommandAllocator* m_pd3dCommandAllocator;	// 명령 할당자 인터페이스 포인터
	ID3D12GraphicsCommandList* m_pd3dCommandList;		// 명령 리스트 인터페이스 포인터
	/* 인터페이스 포인터 관련 변수 */
	ID3D12Device* m_pd3dDevice;		// Direct3D 디바이스 인터페이스에 대한 포인터이다. 주로 리소스를 생성하기 위하여 필요하다.

public:
	void OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void BuildFrameBuffer();
	void ClearFrameBuffer(DWORD dwColor);
	void PresentFrameBuffer();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void SetActive(bool bActive) { m_bActive = bActive; }

	bool togleView = false;
};

