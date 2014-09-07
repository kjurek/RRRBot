#ifndef RRRBOTAPPLICATION_H
#define RRRBOTAPPLICATION_H

#include <memory>
#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <mutex>
#include "ui_rrrbotapplication.h"
#include "ProcessManager.h"
#include "ConfigLoader.h"
#include "Core.h"

class RRRBotApplication : public QMainWindow
{
	Q_OBJECT

public:
	RRRBotApplication(QWidget *parent = 0);
	~RRRBotApplication();

	private slots:
	void handleGetProcessInfoButton();
	void handleLaunchCommandButton();
	void handleConsoleClearButtonCommand();
	void handleLogClearButtonCommand();
	void handleLoadConfig();
	void handleRefreshInfoTab();
	void handleHealTab();
private:
	Ui::RRRBotApplicationClass ui;
	QTimer* m_infoTabTimer;
	QTimer* m_healTabTimer;

	CProcessManager m_processManager;
	RRRBot::Config::CConfigLoader m_configLoader;
	RRRBot::Core::CCore m_core;

	void stopTimers();
	void startTimers();
};

#endif // RRRBOTAPPLICATION_H
