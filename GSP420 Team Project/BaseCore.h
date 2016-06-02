#pragma once
#include <queue>
#include <windows.h>

class SMessage;

class BaseCore {
public:
	static unsigned __stdcall CoreThread(void* core);
	BaseCore();
	virtual bool HandleMessage(SMessage* message);
	virtual void Update(float dt);
	virtual void Quit();
	bool Terminated();
	void SetFrameTime(float seconds);
	void SetFramesPerSecond(float framespersecond);
	float GetLastSPF();
	virtual ~BaseCore();

protected:
	virtual void OnLaunch();
	virtual void Run();
	virtual void CopyMessage();

  std::queue<SMessage*> m_MessageQueue;
	HANDLE m_MessageQueueMutex;
  std::queue<SMessage*> m_QueueBuffer;
	bool m_Quit;
	bool m_Terminated;

private:
	float m_SecondsPerFrame;
	float m_LastSPF;

};
