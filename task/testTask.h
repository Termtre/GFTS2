#pragma once

#include "task.h"

class TestTask : public Task
{
public:
	TestTask(int);
	~TestTask() {}

	void calculate();

};