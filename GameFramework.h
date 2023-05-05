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
	/* CommandQueue & List : GPU�� 1���� ��� Queue�� �����ְ� CPU�� CommandList�� �־��ָ� GPU�� 1�����Ӹ��� ������� �����Ѵ�. */
	/* Allocator : ��� �Ҵ��� - ��� ����Ʈ�� �޸𸮸� �Ҵ� �޴´�. */
	ID3D12CommandQueue* m_pd3dCommandQueue;		// ��� ť �������̽� ������
	ID3D12CommandAllocator* m_pd3dCommandAllocator;	// ��� �Ҵ��� �������̽� ������
	ID3D12GraphicsCommandList* m_pd3dCommandList;		// ��� ����Ʈ �������̽� ������
	/* �������̽� ������ ���� ���� */
	ID3D12Device* m_pd3dDevice;		// Direct3D ����̽� �������̽��� ���� �������̴�. �ַ� ���ҽ��� �����ϱ� ���Ͽ� �ʿ��ϴ�.

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

