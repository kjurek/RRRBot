#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <iostream>
#include <stdexcept>

class CCommandState;

class CCommandException : public std::runtime_error
{
public:
	CCommandException(std::string message)
		: std::runtime_error(message)
	{ }
};

class CCommand
{
public:
	friend class CCommandRunningState;
	friend class CCommandPausedState;
	friend class CCommandAbortedState;
	friend class CCommandCompletedState;
	friend bool operator==(const CCommand& a, const CCommand& b);
	friend bool operator<(const CCommand& a, const CCommand& b);

	CCommand();
	virtual ~CCommand();
	
	virtual std::shared_ptr<CCommand> clone() = 0;
	virtual std::string name() const = 0;
	virtual void parseInput(std::istream& is) = 0;
	virtual void commandStep() = 0;
	virtual bool hasNextStep() = 0;

	virtual void execute();
	virtual void pause();
	virtual void resume();
	virtual void abort();
	bool isCompleted() const { return m_completed; }
private:
	CCommandState* m_pState;
	std::atomic<bool> m_completed;
};

#endif