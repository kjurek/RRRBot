#include <QMessageBox>
#include <sstream>
#include <vector>
#include <memory>
#include "rrrbotapplication.h"
#include "PressKeyCommand.h"
#include "MouseClickCommand.h"

RRRBotApplication::RRRBotApplication(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.GetProcessInfoButton, SIGNAL(clicked()), this, SLOT(handleGetProcessInfoButton()));
	connect(ui.LaunchCommandButton, SIGNAL(clicked()), this, SLOT(handleLaunchCommandButton()));
	connect(ui.ClearButton, SIGNAL(clicked()), this, SLOT(handleClearButtonCommand()));
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
		for (int i = 0; i < ui.tabWidget->count(); ++i)
		{
			if (i != ui.tabWidget->currentIndex())
			{
				ui.tabWidget->setTabEnabled(i, true);
			}
		}
	}
	catch (CProcessManagerException e)
	{
		QMessageBox::information(NULL, "Error!", e.what());
	}
}

void RRRBotApplication::handleLaunchCommandButton()
{
	try {
		std::vector<std::unique_ptr<CCommand> > commands;
		commands.push_back(std::make_unique<RRRBot::Commands::CPressKeyCommand>(&m_processManager));
		//commands.push_back(new RRRBot::Commands::CMouseClickCommand(&m_processManager));

		std::stringstream ss(ui.ConsoleInputEdit->text().toStdString());
		std::string commandName;
		ss >> commandName;

		for (auto& command : commands)
		{
			if (command->name() == commandName)
			{
				command->parseInput(ss);
				command->execute();
				ui.CommandOutputEdit->append((commandName + " completed").c_str());
			}
		}
	}
	catch (CCommandException e)
	{
		ui.CommandOutputEdit->append(e.what());
	}


}

void RRRBotApplication::handleClearButtonCommand()
{
	ui.CommandOutputEdit->clear();
}