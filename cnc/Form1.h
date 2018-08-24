#pragma once
#include"StdAfx.h"
#include"dec.h"
#include"intp.h"
#include"link.h"
#include"string"


// define time interval
#define REAL_TIME 30
#define NONREAL_TIME 50

// link data through pointer
extern PATH_BLOCK *pathBlockPtr;
extern bool       pathBlockValid;
// global variable definition

extern INTP_DATA      intpData;  // memory reserved!!!
extern INTP_DATA     *intpDataPtr;

extern DECODER_DATA      decoderData;  // memory reserved!!!
extern DECODER_DATA      *decoderDataPtr;

namespace cnc {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button_start;
	private: System::Windows::Forms::Button^  button_reset;
	protected: 

	protected: 

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button_mem;

	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button_openFile;


	private: System::Windows::Forms::Label^  label_X;
	private: System::Windows::Forms::Label^  label_Y;
	private: System::Windows::Forms::Label^  label_Z;



	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::RichTextBox^  richTextBox_ncCode;

	private: System::Windows::Forms::TextBox^  textBox_fileName;

	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::Timer^  timer1_real;
	private: System::Windows::Forms::Timer^  timer2_nonreal;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog_openFile;


	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button_mem = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button_openFile = (gcnew System::Windows::Forms::Button());
			this->label_X = (gcnew System::Windows::Forms::Label());
			this->label_Y = (gcnew System::Windows::Forms::Label());
			this->label_Z = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->richTextBox_ncCode = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox_fileName = (gcnew System::Windows::Forms::TextBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->timer1_real = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2_nonreal = (gcnew System::Windows::Forms::Timer(this->components));
			this->openFileDialog_openFile = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
			this->SuspendLayout();
			// 
			// button_start
			// 
			this->button_start->Location = System::Drawing::Point(12, 142);
			this->button_start->Name = L"button_start";
			this->button_start->Size = System::Drawing::Size(75, 92);
			this->button_start->TabIndex = 0;
			this->button_start->Text = L"Start";
			this->button_start->UseVisualStyleBackColor = true;
			// 
			// button_reset
			// 
			this->button_reset->Location = System::Drawing::Point(102, 142);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(75, 92);
			this->button_reset->TabIndex = 1;
			this->button_reset->Text = L"Reset";
			this->button_reset->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(183, 250);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 37);
			this->button3->TabIndex = 2;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(264, 250);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 37);
			this->button4->TabIndex = 3;
			this->button4->Text = L"button4";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(345, 250);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 37);
			this->button5->TabIndex = 4;
			this->button5->Text = L"button5";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button_mem
			// 
			this->button_mem->Location = System::Drawing::Point(12, 250);
			this->button_mem->Name = L"button_mem";
			this->button_mem->Size = System::Drawing::Size(75, 37);
			this->button_mem->TabIndex = 5;
			this->button_mem->Text = L"MEM";
			this->button_mem->UseVisualStyleBackColor = true;
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(102, 250);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(75, 37);
			this->button7->TabIndex = 6;
			this->button7->Text = L"button7";
			this->button7->UseVisualStyleBackColor = true;
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(183, 142);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(75, 35);
			this->button8->TabIndex = 7;
			this->button8->Text = L"button8";
			this->button8->UseVisualStyleBackColor = true;
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(264, 142);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 35);
			this->button9->TabIndex = 8;
			this->button9->Text = L"button9";
			this->button9->UseVisualStyleBackColor = true;
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(345, 142);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(75, 35);
			this->button10->TabIndex = 9;
			this->button10->Text = L"button10";
			this->button10->UseVisualStyleBackColor = true;
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(183, 194);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(75, 40);
			this->button11->TabIndex = 10;
			this->button11->Text = L"button11";
			this->button11->UseVisualStyleBackColor = true;
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(264, 193);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(75, 41);
			this->button12->TabIndex = 11;
			this->button12->Text = L"button12";
			this->button12->UseVisualStyleBackColor = true;
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(345, 194);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(75, 40);
			this->button13->TabIndex = 12;
			this->button13->Text = L"button13";
			this->button13->UseVisualStyleBackColor = true;
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(426, 142);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(75, 35);
			this->button14->TabIndex = 13;
			this->button14->Text = L"button14";
			this->button14->UseVisualStyleBackColor = true;
			// 
			// button_openFile
			// 
			this->button_openFile->Location = System::Drawing::Point(12, 306);
			this->button_openFile->Name = L"button_openFile";
			this->button_openFile->Size = System::Drawing::Size(75, 22);
			this->button_openFile->TabIndex = 14;
			this->button_openFile->Text = L"open file";
			this->button_openFile->UseVisualStyleBackColor = true;
			this->button_openFile->Click += gcnew System::EventHandler(this, &Form1::button_openFile_Click);
			// 
			// label_X
			// 
			this->label_X->AutoSize = true;
			this->label_X->Location = System::Drawing::Point(22, 22);
			this->label_X->Name = L"label_X";
			this->label_X->Size = System::Drawing::Size(13, 12);
			this->label_X->TabIndex = 15;
			this->label_X->Text = L"X";
			// 
			// label_Y
			// 
			this->label_Y->AutoSize = true;
			this->label_Y->Location = System::Drawing::Point(22, 63);
			this->label_Y->Name = L"label_Y";
			this->label_Y->Size = System::Drawing::Size(13, 12);
			this->label_Y->TabIndex = 16;
			this->label_Y->Text = L"Y";
			// 
			// label_Z
			// 
			this->label_Z->AutoSize = true;
			this->label_Z->Location = System::Drawing::Point(22, 101);
			this->label_Z->Name = L"label_Z";
			this->label_Z->Size = System::Drawing::Size(12, 12);
			this->label_Z->TabIndex = 17;
			this->label_Z->Text = L"Z";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(348, 22);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(33, 12);
			this->label4->TabIndex = 18;
			this->label4->Text = L"label4";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(348, 63);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(33, 12);
			this->label5->TabIndex = 19;
			this->label5->Text = L"label5";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(348, 101);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(33, 12);
			this->label6->TabIndex = 20;
			this->label6->Text = L"label6";
			// 
			// richTextBox_ncCode
			// 
			this->richTextBox_ncCode->Location = System::Drawing::Point(12, 334);
			this->richTextBox_ncCode->Name = L"richTextBox_ncCode";
			this->richTextBox_ncCode->Size = System::Drawing::Size(327, 163);
			this->richTextBox_ncCode->TabIndex = 21;
			this->richTextBox_ncCode->Text = L"";
			// 
			// textBox_fileName
			// 
			this->textBox_fileName->Location = System::Drawing::Point(113, 306);
			this->textBox_fileName->Name = L"textBox_fileName";
			this->textBox_fileName->Size = System::Drawing::Size(388, 22);
			this->textBox_fileName->TabIndex = 22;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(370, 334);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(131, 45);
			this->trackBar1->TabIndex = 23;
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(370, 413);
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(131, 45);
			this->trackBar2->TabIndex = 24;
			// 
			// openFileDialog_openFile
			// 
			this->openFileDialog_openFile->FileName = L"openFileDialog1";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(540, 509);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->textBox_fileName);
			this->Controls->Add(this->richTextBox_ncCode);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label_Z);
			this->Controls->Add(this->label_Y);
			this->Controls->Add(this->label_X);
			this->Controls->Add(this->button_openFile);
			this->Controls->Add(this->button14);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button_mem);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button_reset);
			this->Controls->Add(this->button_start);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 init(decoderDataPtr);
				 intpInit(intpDataPtr);
				 timer1_real->Interval = REAL_TIME; 
				 timer1_real->Enabled = true ;
				 timer2_nonreal->Interval = NONREAL_TIME;
				 timer2_nonreal->Enabled = true ;
			 }
	private: System::Void button_openFile_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				openFileDialog_openFile->InitialDirectory = "";                                                      //檔案開啟的預設路徑“..\\”表示上一層
				openFileDialog_openFile->Filter = "文字檔(*.txt)|*.txt|所有檔案(*.*)|*.*";  //顯示的副檔名篩選| 實際的副檔名篩選
				openFileDialog_openFile->FilterIndex = 2;                                                               //預設的篩選條件
				openFileDialog_openFile->DefaultExt = "*.txt";                                                     //預設為文字檔
				openFileDialog_openFile->FileName = "";                                                               //清除之前檔案路徑字串
				openFileDialog_openFile->RestoreDirectory = true;                                              //指定上一次開啟的路徑
				//show dialog, then check success or not
			   if ( openFileDialog_openFile->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			   {

				 textBox_fileName->Text = openFileDialog_openFile->FileName;
				 richTextBox_ncCode->LoadFile( openFileDialog_openFile->FileName, RichTextBoxStreamType::PlainText );
				 strcpy( decoderDataPtr->fileName, (char*)(void*)Marshal::StringToHGlobalAnsi( openFileDialog_openFile->FileName ) );
				 // comfirm that open file correctly
				 decoderDataPtr->fileOk = true;
				 
			   }
			 }
};
}

