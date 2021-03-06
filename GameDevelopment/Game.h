//
// Game.h
//

#pragma once

/* インクルードファイル */
#include <CommonStates.h>
#include <GamePad.h>
#include <Mouse.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <SimpleMath.h>

#include "StepTimer.h"

enum MODE
{
	M01,
	M02,
};

enum STATE
{
	ATTACK,
	DEFENSE,

	NONE
};

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();
	virtual ~Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	std::unique_ptr<DirectX::SpriteBatch>  m_sprite_batch;
	std::unique_ptr<DirectX::SpriteFont>   m_sprite_font;
	std::unique_ptr<DirectX::CommonStates> m_states;
	std::wstring                          m_wstr;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	DirectX::SimpleMath::Vector2 m_screen_pos;		// 画面の座標
	DirectX::SimpleMath::Vector2 m_origin;			// スプライトの原点座標

	std::unique_ptr<DirectX::Mouse>    m_mouse;		// マウス
	DirectX::Mouse::ButtonStateTracker m_tracker;

	std::unique_ptr<DirectX::GamePad> m_gamepad;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_attack;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_defense;
	MODE m_mode;
	STATE m_state;
};