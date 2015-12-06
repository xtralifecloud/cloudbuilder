#pragma once

#include "mycli.h"

namespace CLIApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Diagnostics;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CliForm
	/// </summary>
	public ref class CliForm : public Form, public System::Windows::Forms::IMessageFilter, public MyCLIResponder
//	public ref class CliForm : public Form
	{
	public:
		CliForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CliForm()
		{
			if (cli) { delete cli; }
			if (components)
			{
				delete components;
			}
		}
	private:

		TextBox^  txtCommand;
		RichTextBox^  txtConsole;
		Button^  btnExecute;
		MyCLI *cli;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->txtCommand = (gcnew System::Windows::Forms::TextBox());
			this->btnExecute = (gcnew System::Windows::Forms::Button());
			this->txtConsole = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// txtCommand
			// 
			this->txtCommand->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtCommand->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtCommand->Location = System::Drawing::Point(13, 349);
			this->txtCommand->Name = L"txtCommand";
			this->txtCommand->Size = System::Drawing::Size(489, 23);
			this->txtCommand->TabIndex = 0;
			this->txtCommand->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CliForm::txtCommand_KeyDown);
			// 
			// btnExecute
			// 
			this->btnExecute->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnExecute->Location = System::Drawing::Point(508, 349);
			this->btnExecute->Name = L"btnExecute";
			this->btnExecute->Size = System::Drawing::Size(75, 23);
			this->btnExecute->TabIndex = 2;
			this->btnExecute->Text = L"&Execute";
			this->btnExecute->UseVisualStyleBackColor = true;
			this->btnExecute->Click += gcnew System::EventHandler(this, &CliForm::btnExecute_Click);
			// 
			// txtConsole
			// 
			this->txtConsole->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtConsole->BackColor = System::Drawing::Color::Black;
			this->txtConsole->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtConsole->ForeColor = System::Drawing::Color::White;
			this->txtConsole->Location = System::Drawing::Point(13, 13);
			this->txtConsole->Name = L"txtConsole";
			this->txtConsole->ReadOnly = true;
			this->txtConsole->Size = System::Drawing::Size(570, 330);
			this->txtConsole->TabIndex = 3;
			this->txtConsole->Text = L"";
			this->txtConsole->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CliForm::txtConsole_KeyPress);
			// 
			// CliForm
			// 
			this->AcceptButton = this->btnExecute;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(595, 381);
			this->Controls->Add(this->txtConsole);
			this->Controls->Add(this->btnExecute);
			this->Controls->Add(this->txtCommand);
			this->Name = L"CliForm";
			this->Text = L"CLI tool";
			this->Load += gcnew System::EventHandler(this, &CliForm::CliForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//////////// Responding to events ////////////
		System::Void onIdle(System::Object ^sender, System::EventArgs ^e);
		System::Void CliForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void btnExecute_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void txtCommand_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
		System::Void txtConsole_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

		//////////// Private methods ////////////
		void appendToConsole(const char *text);
		void appendToConsole(String ^text, Color color);
		void enableControls(bool whetherTo);
		void recallPreviousCommand();
		void recallNextCommand();
		void runCommand(const char *command);

public:
		//////////// MyCLIResponder ////////////
		virtual void shouldPrintText(const char *message, CLI::typelog kind);
		virtual void didFinishCommand();
		virtual bool PreFilterMessage(Message %m);
};
}
