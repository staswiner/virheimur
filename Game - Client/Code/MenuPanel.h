#pragma once
#include "ImageLoader.h"
#include <vector>
class MenuPanel : public ImageLoader
{
public:
	MenuPanel();
	~MenuPanel();
	void Initialize();
	void DrawMenuPanel();
private:
	ImageLoader iMenuPanel;
};

