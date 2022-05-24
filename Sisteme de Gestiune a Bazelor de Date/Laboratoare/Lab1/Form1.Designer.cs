
namespace Lab1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.stergereButton = new System.Windows.Forms.Button();
            this.dataGridView_Magazin = new System.Windows.Forms.DataGridView();
            this.dataGridView_Angajat = new System.Windows.Forms.DataGridView();
            this.denumireTextBox = new System.Windows.Forms.TextBox();
            this.numarOraseTextBox = new System.Windows.Forms.TextBox();
            this.denumireMagazinLabel = new System.Windows.Forms.Label();
            this.numarOraseLabel = new System.Windows.Forms.Label();
            this.idMagazinTextBox = new System.Windows.Forms.TextBox();
            this.numeTextBox = new System.Windows.Forms.TextBox();
            this.prenumeTextBox = new System.Windows.Forms.TextBox();
            this.dataNasteriiTextBox = new System.Windows.Forms.TextBox();
            this.observatiiTextBox = new System.Windows.Forms.RichTextBox();
            this.idMagazinLabel = new System.Windows.Forms.Label();
            this.numeLabel = new System.Windows.Forms.Label();
            this.prenumeLabel = new System.Windows.Forms.Label();
            this.dataNasteriiLabel = new System.Windows.Forms.Label();
            this.observatiiLabel = new System.Windows.Forms.Label();
            this.magazinIdLabel = new System.Windows.Forms.Label();
            this.magazinIdTextBox = new System.Windows.Forms.TextBox();
            this.actualizareButton = new System.Windows.Forms.Button();
            this.messageToUser = new System.Windows.Forms.Label();
            this.adaugareButton = new System.Windows.Forms.Button();
            this.idAngajatTextBox = new System.Windows.Forms.TextBox();
            this.idAngajatLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_Magazin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_Angajat)).BeginInit();
            this.SuspendLayout();
            // 
            // stergereButton
            // 
            this.stergereButton.BackgroundImage = global::Lab1.Properties.Resources.button;
            this.stergereButton.Location = new System.Drawing.Point(1052, 73);
            this.stergereButton.Margin = new System.Windows.Forms.Padding(4);
            this.stergereButton.Name = "stergereButton";
            this.stergereButton.Size = new System.Drawing.Size(152, 38);
            this.stergereButton.TabIndex = 0;
            this.stergereButton.Text = "Șterge angajat";
            this.stergereButton.UseVisualStyleBackColor = true;
            this.stergereButton.Click += new System.EventHandler(this.stergereButton_Click);
            // 
            // dataGridView_Magazin
            // 
            this.dataGridView_Magazin.BackgroundColor = System.Drawing.SystemColors.InactiveBorder;
            this.dataGridView_Magazin.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_Magazin.Location = new System.Drawing.Point(39, 57);
            this.dataGridView_Magazin.Margin = new System.Windows.Forms.Padding(4);
            this.dataGridView_Magazin.Name = "dataGridView_Magazin";
            this.dataGridView_Magazin.RowHeadersWidth = 51;
            this.dataGridView_Magazin.Size = new System.Drawing.Size(456, 185);
            this.dataGridView_Magazin.TabIndex = 1;
            this.dataGridView_Magazin.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_Magazin_CellClick);
            // 
            // dataGridView_Angajat
            // 
            this.dataGridView_Angajat.BackgroundColor = System.Drawing.SystemColors.InactiveBorder;
            this.dataGridView_Angajat.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_Angajat.Location = new System.Drawing.Point(589, 57);
            this.dataGridView_Angajat.Margin = new System.Windows.Forms.Padding(4);
            this.dataGridView_Angajat.Name = "dataGridView_Angajat";
            this.dataGridView_Angajat.RowHeadersWidth = 51;
            this.dataGridView_Angajat.Size = new System.Drawing.Size(456, 185);
            this.dataGridView_Angajat.TabIndex = 2;
            this.dataGridView_Angajat.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_Angajat_CellClick);
            // 
            // denumireTextBox
            // 
            this.denumireTextBox.Location = new System.Drawing.Point(215, 304);
            this.denumireTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.denumireTextBox.Name = "denumireTextBox";
            this.denumireTextBox.Size = new System.Drawing.Size(164, 22);
            this.denumireTextBox.TabIndex = 3;
            // 
            // numarOraseTextBox
            // 
            this.numarOraseTextBox.Location = new System.Drawing.Point(215, 334);
            this.numarOraseTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.numarOraseTextBox.Name = "numarOraseTextBox";
            this.numarOraseTextBox.Size = new System.Drawing.Size(164, 22);
            this.numarOraseTextBox.TabIndex = 4;
            // 
            // denumireMagazinLabel
            // 
            this.denumireMagazinLabel.AutoSize = true;
            this.denumireMagazinLabel.Location = new System.Drawing.Point(81, 307);
            this.denumireMagazinLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.denumireMagazinLabel.Name = "denumireMagazinLabel";
            this.denumireMagazinLabel.Size = new System.Drawing.Size(126, 17);
            this.denumireMagazinLabel.TabIndex = 5;
            this.denumireMagazinLabel.Text = "Denumire magazin";
            // 
            // numarOraseLabel
            // 
            this.numarOraseLabel.AutoSize = true;
            this.numarOraseLabel.Location = new System.Drawing.Point(117, 336);
            this.numarOraseLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.numarOraseLabel.Name = "numarOraseLabel";
            this.numarOraseLabel.Size = new System.Drawing.Size(90, 17);
            this.numarOraseLabel.TabIndex = 6;
            this.numarOraseLabel.Text = "Număr orașe";
            // 
            // idMagazinTextBox
            // 
            this.idMagazinTextBox.Location = new System.Drawing.Point(779, 296);
            this.idMagazinTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.idMagazinTextBox.Name = "idMagazinTextBox";
            this.idMagazinTextBox.Size = new System.Drawing.Size(164, 22);
            this.idMagazinTextBox.TabIndex = 7;
            // 
            // numeTextBox
            // 
            this.numeTextBox.Location = new System.Drawing.Point(779, 327);
            this.numeTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.numeTextBox.Name = "numeTextBox";
            this.numeTextBox.Size = new System.Drawing.Size(164, 22);
            this.numeTextBox.TabIndex = 8;
            // 
            // prenumeTextBox
            // 
            this.prenumeTextBox.Location = new System.Drawing.Point(779, 357);
            this.prenumeTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.prenumeTextBox.Name = "prenumeTextBox";
            this.prenumeTextBox.Size = new System.Drawing.Size(164, 22);
            this.prenumeTextBox.TabIndex = 9;
            // 
            // dataNasteriiTextBox
            // 
            this.dataNasteriiTextBox.Location = new System.Drawing.Point(779, 387);
            this.dataNasteriiTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.dataNasteriiTextBox.Name = "dataNasteriiTextBox";
            this.dataNasteriiTextBox.Size = new System.Drawing.Size(164, 22);
            this.dataNasteriiTextBox.TabIndex = 10;
            // 
            // observatiiTextBox
            // 
            this.observatiiTextBox.Location = new System.Drawing.Point(779, 417);
            this.observatiiTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.observatiiTextBox.Name = "observatiiTextBox";
            this.observatiiTextBox.Size = new System.Drawing.Size(164, 67);
            this.observatiiTextBox.TabIndex = 11;
            this.observatiiTextBox.Text = "";
            // 
            // idMagazinLabel
            // 
            this.idMagazinLabel.AutoSize = true;
            this.idMagazinLabel.Location = new System.Drawing.Point(693, 299);
            this.idMagazinLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.idMagazinLabel.Name = "idMagazinLabel";
            this.idMagazinLabel.Size = new System.Drawing.Size(78, 17);
            this.idMagazinLabel.TabIndex = 12;
            this.idMagazinLabel.Text = "ID Magazin";
            // 
            // numeLabel
            // 
            this.numeLabel.AutoSize = true;
            this.numeLabel.Location = new System.Drawing.Point(675, 330);
            this.numeLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.numeLabel.Name = "numeLabel";
            this.numeLabel.Size = new System.Drawing.Size(96, 17);
            this.numeLabel.TabIndex = 13;
            this.numeLabel.Text = "Nume angajat";
            // 
            // prenumeLabel
            // 
            this.prenumeLabel.AutoSize = true;
            this.prenumeLabel.Location = new System.Drawing.Point(655, 360);
            this.prenumeLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.prenumeLabel.Name = "prenumeLabel";
            this.prenumeLabel.Size = new System.Drawing.Size(116, 17);
            this.prenumeLabel.TabIndex = 14;
            this.prenumeLabel.Text = "Prenume angajat";
            // 
            // dataNasteriiLabel
            // 
            this.dataNasteriiLabel.AutoSize = true;
            this.dataNasteriiLabel.Location = new System.Drawing.Point(683, 390);
            this.dataNasteriiLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.dataNasteriiLabel.Name = "dataNasteriiLabel";
            this.dataNasteriiLabel.Size = new System.Drawing.Size(88, 17);
            this.dataNasteriiLabel.TabIndex = 15;
            this.dataNasteriiLabel.Text = "Data nașterii";
            // 
            // observatiiLabel
            // 
            this.observatiiLabel.AutoSize = true;
            this.observatiiLabel.Location = new System.Drawing.Point(699, 443);
            this.observatiiLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.observatiiLabel.Name = "observatiiLabel";
            this.observatiiLabel.Size = new System.Drawing.Size(72, 17);
            this.observatiiLabel.TabIndex = 16;
            this.observatiiLabel.Text = "Observații";
            // 
            // magazinIdLabel
            // 
            this.magazinIdLabel.AutoSize = true;
            this.magazinIdLabel.Location = new System.Drawing.Point(130, 278);
            this.magazinIdLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.magazinIdLabel.Name = "magazinIdLabel";
            this.magazinIdLabel.Size = new System.Drawing.Size(78, 17);
            this.magazinIdLabel.TabIndex = 17;
            this.magazinIdLabel.Text = "ID Magazin";
            // 
            // magazinIdTextBox
            // 
            this.magazinIdTextBox.Location = new System.Drawing.Point(215, 275);
            this.magazinIdTextBox.Name = "magazinIdTextBox";
            this.magazinIdTextBox.Size = new System.Drawing.Size(164, 22);
            this.magazinIdTextBox.TabIndex = 18;
            // 
            // actualizareButton
            // 
            this.actualizareButton.BackgroundImage = global::Lab1.Properties.Resources.button;
            this.actualizareButton.Location = new System.Drawing.Point(1052, 184);
            this.actualizareButton.Name = "actualizareButton";
            this.actualizareButton.Size = new System.Drawing.Size(152, 38);
            this.actualizareButton.TabIndex = 19;
            this.actualizareButton.Text = "Actualizează angajat";
            this.actualizareButton.UseVisualStyleBackColor = true;
            this.actualizareButton.Click += new System.EventHandler(this.actualizareButton_Click);
            // 
            // messageToUser
            // 
            this.messageToUser.AutoSize = true;
            this.messageToUser.Location = new System.Drawing.Point(13, 477);
            this.messageToUser.Name = "messageToUser";
            this.messageToUser.Size = new System.Drawing.Size(0, 17);
            this.messageToUser.TabIndex = 20;
            // 
            // adaugareButton
            // 
            this.adaugareButton.BackgroundImage = global::Lab1.Properties.Resources.button;
            this.adaugareButton.Location = new System.Drawing.Point(1052, 128);
            this.adaugareButton.Name = "adaugareButton";
            this.adaugareButton.Size = new System.Drawing.Size(152, 38);
            this.adaugareButton.TabIndex = 21;
            this.adaugareButton.Text = "Adaugă angajat";
            this.adaugareButton.UseVisualStyleBackColor = true;
            this.adaugareButton.Click += new System.EventHandler(this.adaugareButton_Click);
            // 
            // idAngajatTextBox
            // 
            this.idAngajatTextBox.BackColor = System.Drawing.SystemColors.Window;
            this.idAngajatTextBox.Location = new System.Drawing.Point(779, 263);
            this.idAngajatTextBox.Name = "idAngajatTextBox";
            this.idAngajatTextBox.Size = new System.Drawing.Size(164, 22);
            this.idAngajatTextBox.TabIndex = 22;
            // 
            // idAngajatLabel
            // 
            this.idAngajatLabel.AutoSize = true;
            this.idAngajatLabel.Location = new System.Drawing.Point(700, 266);
            this.idAngajatLabel.Name = "idAngajatLabel";
            this.idAngajatLabel.Size = new System.Drawing.Size(73, 17);
            this.idAngajatLabel.TabIndex = 23;
            this.idAngajatLabel.Text = "ID Angajat";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Lab1.Properties.Resources.background;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1219, 536);
            this.Controls.Add(this.idAngajatLabel);
            this.Controls.Add(this.idAngajatTextBox);
            this.Controls.Add(this.adaugareButton);
            this.Controls.Add(this.messageToUser);
            this.Controls.Add(this.actualizareButton);
            this.Controls.Add(this.magazinIdTextBox);
            this.Controls.Add(this.magazinIdLabel);
            this.Controls.Add(this.observatiiLabel);
            this.Controls.Add(this.dataNasteriiLabel);
            this.Controls.Add(this.prenumeLabel);
            this.Controls.Add(this.numeLabel);
            this.Controls.Add(this.idMagazinLabel);
            this.Controls.Add(this.observatiiTextBox);
            this.Controls.Add(this.dataNasteriiTextBox);
            this.Controls.Add(this.prenumeTextBox);
            this.Controls.Add(this.numeTextBox);
            this.Controls.Add(this.idMagazinTextBox);
            this.Controls.Add(this.numarOraseLabel);
            this.Controls.Add(this.denumireMagazinLabel);
            this.Controls.Add(this.numarOraseTextBox);
            this.Controls.Add(this.denumireTextBox);
            this.Controls.Add(this.dataGridView_Angajat);
            this.Controls.Add(this.dataGridView_Magazin);
            this.Controls.Add(this.stergereButton);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Pet Store";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_Magazin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_Angajat)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button stergereButton;
        private System.Windows.Forms.DataGridView dataGridView_Magazin;
        private System.Windows.Forms.DataGridView dataGridView_Angajat;
        private System.Windows.Forms.TextBox denumireTextBox;
        private System.Windows.Forms.TextBox numarOraseTextBox;
        private System.Windows.Forms.Label denumireMagazinLabel;
        private System.Windows.Forms.Label numarOraseLabel;
        private System.Windows.Forms.TextBox idMagazinTextBox;
        private System.Windows.Forms.TextBox numeTextBox;
        private System.Windows.Forms.TextBox prenumeTextBox;
        private System.Windows.Forms.TextBox dataNasteriiTextBox;
        private System.Windows.Forms.RichTextBox observatiiTextBox;
        private System.Windows.Forms.Label idMagazinLabel;
        private System.Windows.Forms.Label numeLabel;
        private System.Windows.Forms.Label prenumeLabel;
        private System.Windows.Forms.Label dataNasteriiLabel;
        private System.Windows.Forms.Label observatiiLabel;
        private System.Windows.Forms.Label magazinIdLabel;
        private System.Windows.Forms.TextBox magazinIdTextBox;
        private System.Windows.Forms.Button actualizareButton;
        private System.Windows.Forms.Label messageToUser;
        private System.Windows.Forms.Button adaugareButton;
        private System.Windows.Forms.TextBox idAngajatTextBox;
        private System.Windows.Forms.Label idAngajatLabel;
    }
}

