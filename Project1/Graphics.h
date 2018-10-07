#pragma once

class CGraphics
{
private:
	CGraphics* __instance;

private:
	CGraphics() = default;

public:
	~CGraphics() = default;

	CGraphics* GetInstance();
};
