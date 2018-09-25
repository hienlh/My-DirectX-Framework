#pragma once
class Singleton
{
private:
	static Singleton *__instance;
	Singleton();

public:
	~Singleton();
};

