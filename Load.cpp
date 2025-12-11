#include "Load.h"
#include "ApplicationManager.h"
#include "AddRead.h"
#include "AddWrite.h"
#include "GUI/input.h"
#include "GUI/Output.h"
#include <fstream>

Load::Load(ApplicationManager* pAppManager) : Action(pAppManager) {}

void Load::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Load Flowchart: Enter the file name to load the flowchart: ");
    FileName = pIn->GetString(pOut);
    FileName += ".txt";
    pOut->ClearStatusBar();
}

void Load::Execute()
{
	ReadActionParameters();
	ifstream InFile(FileName);
	Output* pOut = pManager->GetOutput();
	if (!InFile.is_open())
	{
		pOut->PrintMessage("Error: Could not open file " + FileName);
		return;
	}
	//pManager->ClearAll(); // Clear existing flowchart
	int StatementCount;
	InFile >> StatementCount;
	for (int i = 0; i < StatementCount; ++i)
	{
		string StatementType;
		InFile >> StatementType;
		Action* pAction = nullptr;
		if (StatementType == "READ")
		{
			pAction = new AddRead(pManager);
		}
		else if (StatementType == "WRITE")
		{
			pAction = new AddWrite(pManager);
		}
		// Add other statement types as needed
		/*if (pAction)
		{
			pAction->Load(InFile);
			pManager->AddStatement(pAction);
		}*/
	}
	InFile.close();
	pOut->PrintMessage("Flowchart loaded successfully from " + FileName);
}