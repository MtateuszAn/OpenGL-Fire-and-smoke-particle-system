#pragma once
class DeltaTime
{
	float oldTime = 0;
	float deltaTime = 0;
	float frameTime = 0;

	void updateDeltaTime(){
		frameTime = 0;
	}

};

