#pragma once

#define ID_BUTTON_DONE                  1000

class MainApplicationDialog
{
public:
	MainApplicationDialog();
	virtual ~MainApplicationDialog();

	INT_PTR DoModal();
};

