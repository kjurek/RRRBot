#ifndef RRRBOTAPPLICATION_H
#define RRRBOTAPPLICATION_H

#include <QtWidgets/QMainWindow>
#include "ui_rrrbotapplication.h"
#include "ProcessManager.h"

class RRRBotApplication : public QMainWindow
{
	Q_OBJECT

public:
	RRRBotApplication(QWidget *parent = 0);
	~RRRBotApplication();

private slots:
	void handleGetProcessInfoButton();
	void handleLaunchCommandButton();
	void handleClearButtonCommand();
private:
	Ui::RRRBotApplicationClass ui;
	CProcessManager m_processManager;
};

#endif // RRRBOTAPPLICATION_H
