#include "Shot.h"

Shot::Shot()
{

}

void Shot::init(Microsoft::WRL::ComPtr<ID3D11Device> device)
{
	sp.pos = { 200, 200 };
	sp.angle = 0;
	sp.act = 10;
	sp.radius = 8;

	spriteShot = std::make_unique<sprite>(device.Get(), L".\\resources\\ammo\\rocket.png");

	HRESULT hr{ S_OK };

	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	D3D11_SAMPLER_DESC sampler_desc{};
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MipLODBias = 0;
	sampler_desc.MaxAnisotropy = 16;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampler_desc.BorderColor[0] = 0;
	sampler_desc.BorderColor[1] = 0;
	sampler_desc.BorderColor[2] = 0;
	sampler_desc.BorderColor[3] = 0;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&sampler_desc, sampler_state_shot.GetAddressOf());

	{
		D3D11_INPUT_ELEMENT_DESC input_element_desc[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		create_vs_from_cso(device.Get(),
			"sprite_vs.cso",
			sprite_vertex_shader_shot.GetAddressOf(),
			sprite_input_layout_shot.GetAddressOf(),
			input_element_desc,
			ARRAYSIZE(input_element_desc));
		create_ps_from_cso(device.Get(),
			"sprite_ps.cso",
			sprite_pixel_shader_shot.GetAddressOf());
	}
}

void Shot::update(DirectX::XMFLOAT2 pos, float angle, bool shotCount)
{
	float tempX1 = 0;
	float tempY1 = 0;

	if (shotCount)
	{
		tempX1 = cosf(angle * 3.14 / 180) * (pos.x + 50 - (pos.x + 64)) - sinf(angle * 3.14 / 180) * (pos.y + 70 - (pos.y + 64)) + pos.x + 64;
		tempY1 = sinf(angle * 3.14 / 180) * (pos.x + 50 - (pos.x + 64)) + cosf(angle * 3.14 / 180) * (pos.y + 70 - (pos.y + 64)) + pos.y + 64;
	}
	else
	{
		tempX1 = cosf(angle * 3.14 / 180) * (pos.x + 80 - (pos.x + 64)) - sinf(angle * 3.14 / 180) * (pos.y + 70 - (pos.y + 64)) + pos.x + 64;
		tempY1 = sinf(angle * 3.14 / 180) * (pos.x + 80 - (pos.x + 64)) + cosf(angle * 3.14 / 180) * (pos.y + 70 - (pos.y + 64)) + pos.y + 64;
	}

	switch (sp.act)
	{
	case 0:

		sp.pos.x = tempX1;
		sp.pos.y = tempY1;
		sp.angle = angle;
		sp.speed.x = sinf(angle * 3.14 / 180) * 8;
		sp.speed.y = -cosf(angle * 3.14 / 180) * 8;

		++sp.act;
	case 1:
		sp.pos.x += sp.speed.x;
		sp.pos.y += sp.speed.y;
		break;
	}
}

void Shot::render(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context, float elapsed_time)
{

	{
		immediate_context->IASetInputLayout(sprite_input_layout_shot.Get());
		immediate_context->VSSetShader(sprite_vertex_shader_shot.Get(), nullptr, 0);
		immediate_context->PSSetShader(sprite_pixel_shader_shot.Get(), nullptr, 0);

		immediate_context->PSSetSamplers(0, 1, sampler_state_shot.GetAddressOf());

		spriteShot->render(immediate_context.Get(), sp.pos.x - 8, sp.pos.y - 8, 16, 16, 1.0f, 1.0f, 1.0f, 1.0f, sp.angle);

	}

}

void Shot::initEnemy(Microsoft::WRL::ComPtr<ID3D11Device> device)
{

	sp.pos = { 200, 200 };
	sp.angle = 0;
	sp.act = 10;
	sp.radius = 8;

	spriteShot = std::make_unique<sprite>(device.Get(), L".\\resources\\ammo\\shot.png");

	HRESULT hr{ S_OK };

	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	D3D11_SAMPLER_DESC sampler_desc{};
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MipLODBias = 0;
	sampler_desc.MaxAnisotropy = 16;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampler_desc.BorderColor[0] = 0;
	sampler_desc.BorderColor[1] = 0;
	sampler_desc.BorderColor[2] = 0;
	sampler_desc.BorderColor[3] = 0;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&sampler_desc, sampler_state_shot.GetAddressOf());

	{
		D3D11_INPUT_ELEMENT_DESC input_element_desc[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		create_vs_from_cso(device.Get(),
			"sprite_vs.cso",
			sprite_vertex_shader_shot.GetAddressOf(),
			sprite_input_layout_shot.GetAddressOf(),
			input_element_desc,
			ARRAYSIZE(input_element_desc));
		create_ps_from_cso(device.Get(),
			"sprite_ps.cso",
			sprite_pixel_shader_shot.GetAddressOf());
	}
}

void Shot::updateEnemy(DirectX::XMFLOAT2 pos, float angle)
{
	switch (sp.act)
	{
	case 0:

		sp.pos.x = pos.x + 24;
		sp.pos.y = pos.y + 24;
		sp.angle = angle;
		sp.speed.x = sinf(angle * 3.14 / 180) * 4;
		sp.speed.y = -cosf(angle * 3.14 / 180) * 4;

		++sp.act;
		break;
	case 1:
		sp.pos.x += sp.speed.x;
		sp.pos.y += sp.speed.y;
		break;
	}
}

void Shot::renderEnemy(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediate_context, float elapsed_time)
{

	{
		immediate_context->IASetInputLayout(sprite_input_layout_shot.Get());
		immediate_context->VSSetShader(sprite_vertex_shader_shot.Get(), nullptr, 0);
		immediate_context->PSSetShader(sprite_pixel_shader_shot.Get(), nullptr, 0);

		immediate_context->PSSetSamplers(0, 1, sampler_state_shot.GetAddressOf());

		spriteShot->render(immediate_context.Get(), sp.pos.x, sp.pos.y, 16, 16, 1.0f, 1.0f, 1.0f, 1.0f, sp.angle);

	}

}

Shot::~Shot()
{
}