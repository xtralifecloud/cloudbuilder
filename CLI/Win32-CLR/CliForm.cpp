#include "precompiled.h"
#include "CliForm.h"

using namespace CLIApp;

System::Void CliForm::onIdle(System::Object ^sender, System::EventArgs ^e) {
	// Processes callbacks
	cli->idle();
}

System::Void CliForm::CliForm_Load(System::Object^ sender, System::EventArgs^ e) {
	cli = new MyCLI(this);
	// Register an IDLE method to integrate the main loop
	Application::Idle += gcnew EventHandler(this, &CliForm::onIdle);
	Application::AddMessageFilter(this);
	appendToConsole("Welcome! Type help [RETURN] to list available commands.\n");
}

System::Void CliForm::btnExecute_Click(System::Object^ sender, System::EventArgs^ e) {
	// Fetch the command
	msclr::interop::marshal_context context;
	runCommand(context.marshal_as<const char *>(txtCommand->Text));
}

System::Void CliForm::txtCommand_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	switch (e->KeyCode) {
	case Keys::Up: recallPreviousCommand(); break;
	case Keys::Down: recallNextCommand(); break;
	}
}

System::Void CliForm::txtConsole_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	txtCommand->Focus();
}

void CliForm::appendToConsole(const char *text) {
	appendToConsole(gcnew String(text), Color::LightGray);
}

void CliForm::appendToConsole(String ^text, Color color) {
	int start = txtConsole->Text->Length;
	txtConsole->AppendText(text);
	// Color inserted text
	txtConsole->SelectionStart = start;
	txtConsole->SelectionLength = text->Length;
	txtConsole->SelectionColor = color;
	// Scroll to bottom
	txtConsole->SelectionStart = txtConsole->Text->Length;
	txtConsole->ScrollToCaret();
}

void CliForm::enableControls(bool whetherTo) {
	txtCommand->Enabled = whetherTo;
	btnExecute->Enabled = whetherTo;
	if (whetherTo)
		txtCommand->Focus();
}

void CliForm::recallPreviousCommand() {
	txtCommand->Text = gcnew String(cli->recallPreviousCommand());
}

void CliForm::recallNextCommand() {
	txtCommand->Text = gcnew String(cli->recallNextCommand());
}

void CliForm::runCommand(const char *command) {
	// Print the command
	appendToConsole("-> " + gcnew String(command) + "\n", Color::Lime);
	// Execute it
	txtCommand->Clear();
	enableControls(false);
	CloudBuilder::eErrorCode ec = cli->executeCommand(command);
	if (ec != enNoErr) {
		if (ec != -1)
			shouldPrintText(errorString(ec), CLI::kERR);
		enableControls(true);
	}
}

void CliForm::didFinishCommand() {
	long time = cli->millisecondsElapsedSinceLastExecute();
	appendToConsole("Done!	", Color::LightGray);
	// Display the time in the t.ttt format
	appendToConsole(String::Format("({0}.{1:D3} sec)\n", time / 1000, time % 1000), Color::FromArgb(192, 192, 96));
	enableControls(true);
}

void CliForm::shouldPrintText(const char *message, CLI::typelog kind) {
	String ^result = gcnew String(message);
	Color col;
	result->Replace("\r", "\n");

	switch (kind) {
		case CLI::kLOG: col = Color::LightGray; break;
		case CLI::kCMD: col = Color::LightGray; break;
		case CLI::kERR: col = Color::FromArgb(255, 128, 128); break;
		case CLI::kSCRIPT: col = Color::LightGray; break;
		default: col = Color::Yellow; break;
	}

	appendToConsole(result + "\n", col);
	enableControls(true);
}

bool CliForm::PreFilterMessage(Message %m) {
	// To allow for scrolling on hover
	if (m.Msg == 0x20a) {
		POINT pos = {m.LParam.ToInt32() & 0xffff, m.LParam.ToInt32() >> 16};
		HWND hWnd = WindowFromPoint(pos);
		if (hWnd && hWnd != m.HWnd.ToPointer() && Control::FromHandle(IntPtr(hWnd))) {
			SendMessage(hWnd, m.Msg, m.WParam.ToInt32(), m.LParam.ToInt32());
			return true;
		}
	}
	return false;
}
