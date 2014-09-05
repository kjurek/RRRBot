#include <QMessageBox>
#include <qfiledialog.h>
#include <sstream>
#include <vector>
#include <memory>
#include "rrrbotapplication.h"
#include "PressKeyCommand.h"
#include "MouseClickCommand.h"
#include "MoveCommand.h"
#include "UpdatePlayerInfoCommand.h"

RRRBotApplication::RRRBotApplication(QWidget *parent)
	:	QMainWindow(parent)
{
	ui.setupUi(this);
	m_infoTabTimer = new QTimer(this);
	m_healTabTimer = new QTimer(this);

	connect(ui.GetProcessInfoButton, SIGNAL(clicked()), this, SLOT(handleGetProcessInfoButton()));
	connect(ui.LaunchCommandButton, SIGNAL(clicked()), this, SLOT(handleLaunchCommandButton()));
	connect(ui.ConsoleClearButton, SIGNAL(clicked()), this, SLOT(handleConsoleClearButtonCommand()));
	connect(ui.LogClearButton, SIGNAL(clicked()), this, SLOT(handleLogClearButtonCommand()));
	connect(ui.actionLoad_Config, SIGNAL(triggered()), this, SLOT(handleLoadConfig()));
	connect(m_infoTabTimer, SIGNAL(timeout()), this, SLOT(handleRefreshPlayerInfoTab()));
	connect(m_healTabTimer, SIGNAL(timeout()), this, SLOT(handleHealTab()));
}

RRRBotApplication::~RRRBotApplication()
{

}

void RRRBotApplication::handleGetProcessInfoButton()
{
	try {
		m_processManager.configureByWindowTitle(ui.ProcessNameEdit->text().toStdString());
		std::ostringstream os;
		
		os << m_processManager.getProcessId();
		ui.ProcessIdValue->setText(os.str().c_str());

		os.str("");
		os.clear();

		os << m_processManager.getWindowHandle();
		ui.WindowHandleValue->setText(os.str().c_str());

		os.str("");
		os.clear();

		os << m_processManager.getProcessHandle();
		ui.ProcessHandleValue->setText(os.str().c_str());

		os.str("");
		os.clear();

		auto modules = m_processManager.getModules();
		for (auto& module : modules)
		{
			os << module.first << ": " << module.second;
			ui.ModulesComboBox->addItem(os.str().c_str());
			os.str("");
			os.clear();
		}
		ui.actionLoad_Config->setEnabled(true);
	}
	catch (CProcessManagerException e)
	{
		QMessageBox::information(NULL, "Error!", e.what());
	}
}

void RRRBotApplication::handleLaunchCommandButton()
{
	try 
	{		
		std::stringstream ss(ui.ConsoleInputEdit->text().toStdString());
		std::string commandName;
		ss >> commandName;

		auto requestedCommand = m_core.getCommand(commandName);
		if (nullptr != requestedCommand.get())
		{
			requestedCommand->parseInput(ss);
			requestedCommand->execute();
			ui.CommandOutputEdit->append((commandName + " completed").c_str());
		}
		else
		{
			ui.CommandOutputEdit->append(("error " + commandName + " not found").c_str());
		}
	}
	catch (std::exception& e)
	{
		ui.CommandOutputEdit->append(e.what());
	}
}

void RRRBotApplication::handleConsoleClearButtonCommand()
{
	ui.CommandOutputEdit->clear();
}


void RRRBotApplication::handleLogClearButtonCommand()
{
	ui.LogEdit->clear();
}

void RRRBotApplication::handleLoadConfig()
{
	stopTimers();
	QString configFilePath = QFileDialog::getOpenFileName();
	m_configLoader.load(configFilePath.toStdString());
	
	auto playerOffsets = m_configLoader.getPlayerOffsets();
	auto mouseOffsets = m_configLoader.getMouseOffsets();
	m_core.m_offsetManager.configure(m_processManager, playerOffsets, mouseOffsets);

	// add some commands
	m_core.registerCommand(std::make_shared<RRRBot::Commands::CUpdatePlayerInfoCommand>(m_processManager, m_core));
	m_core.registerCommand(std::make_shared<RRRBot::Commands::CPressKeyCommand>(m_processManager));
	m_core.registerCommand(std::make_shared<RRRBot::Commands::CMouseClickCommand>(m_processManager, m_core));
	m_core.registerCommand(std::make_shared<RRRBot::Commands::CMoveCommand>(m_processManager, m_core));

	for (int i = 1; i < ui.tabWidget->count(); ++i)
	{
		ui.tabWidget->setTabEnabled(i, true);
	}

	auto& logEdit = ui.LogEdit;

	auto appendOffsetFunc = [&logEdit](int offset, std::string offsetName)
	{
		std::ostringstream os;
		os << offsetName << ": " << offset;
		logEdit->append(os.str().c_str());
	};

	logEdit->append("Mouse offsets:");
	appendOffsetFunc(mouseOffsets.x, "x");
	appendOffsetFunc(mouseOffsets.y, "y");

	logEdit->append("");
	logEdit->append("Player offsets:");
	appendOffsetFunc(playerOffsets.base, "base");
	appendOffsetFunc(playerOffsets.x, "x");
	appendOffsetFunc(playerOffsets.y, "y");
	appendOffsetFunc(playerOffsets.z, "z");
	appendOffsetFunc(playerOffsets.hp, "hp");
	appendOffsetFunc(playerOffsets.maxHp, "maxHp");
	appendOffsetFunc(playerOffsets.mp, "mp");
	appendOffsetFunc(playerOffsets.maxMp, "maxMp");
	appendOffsetFunc(playerOffsets.flightTime, "flightTime");
	appendOffsetFunc(playerOffsets.maxFlightTime, "maxFlightTime");
	appendOffsetFunc(playerOffsets.name, "name");
	appendOffsetFunc(playerOffsets.rotH, "rotH");
	appendOffsetFunc(playerOffsets.rotV, "rotV");
	appendOffsetFunc(playerOffsets.move, "move");
	startTimers();
}

void RRRBotApplication::handleRefreshPlayerInfoTab()
{
	try
	{
		m_core.getCommand("UpdatePlayerInfo")->execute();
		std::ostringstream os;
		auto player = m_core.getPlayer();

		os << "(" << player.x << ", " << player.y << ", " << player.z << ")";
		ui.PositionValue->setText(os.str().c_str());

		os.str("");
		os.clear();

		os << "horizontal: " << player.rotH << " vertical: " << player.rotV;
		ui.AngleValue->setText(os.str().c_str());
		ui.NameValue->setText(QString::fromWCharArray(player.name.c_str()));

		os.str("");
		os.clear();

		os << player.hp << " / " << player.maxHp;
		ui.HpValue->setText(os.str().c_str());

		os.str("");
		os.clear();

		os << player.mp << " / " << player.maxMp;
		ui.MpValue->setText(os.str().c_str());

		os.str("");
		os.clear();

		os << player.flightTime << " / " << player.maxFlightTime;
		ui.FlightTimeValue->setText(os.str().c_str());
	}
	catch (std::exception& e)
	{
		ui.LogEdit->append(e.what());
	}
}

void RRRBotApplication::handleHealTab()
{
	if (ui.HealTabEnabledCheck->checkState() == Qt::Unchecked)
	{
		return;
	}

	try
	{
		m_core.getCommand("UpdatePlayerInfo")->execute();
		auto player = m_core.getPlayer();
		float hpPercentage = 100 * (static_cast<float>(player.hp) / static_cast<float>(player.maxHp));
		float mpPercentage = 100 * (static_cast<float>(player.mp) / static_cast<float>(player.maxMp));
		
		if (hpPercentage < ui.HPUseSpin->value())
		{
			QMessageBox::information(NULL, "info", QString("Pressing ") + ui.HPHealKeyEdit->keySequence().toString(QKeySequence::NativeText));
		}

		if (mpPercentage < ui.MPUseSpin->value())
		{
			QMessageBox::information(NULL, "info", QString("Pressing ") + ui.MPHealKeyEdit->keySequence().toString(QKeySequence::NativeText));
		}
	}
	catch (std::exception& e)
	{
		ui.LogEdit->append(e.what());
	}
}

void RRRBotApplication::stopTimers()
{
	m_healTabTimer->stop();
	m_infoTabTimer->stop();
}

void RRRBotApplication::startTimers()
{
	m_healTabTimer->start(500);
	m_infoTabTimer->start(500);
}