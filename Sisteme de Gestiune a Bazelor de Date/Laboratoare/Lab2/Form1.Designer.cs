
namespace Lab2
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
            this.dataGrid_Parent = new System.Windows.Forms.DataGridView();
            this.tableName_Parent = new System.Windows.Forms.Label();
            this.dataGrid_Child = new System.Windows.Forms.DataGridView();
            this.tableName_Child = new System.Windows.Forms.Label();
            this.panel_Parent = new System.Windows.Forms.Panel();
            this.panel_Child = new System.Windows.Forms.Panel();
            this.addButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.messageToUser = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Parent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Child)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGrid_Parent
            // 
            this.dataGrid_Parent.BackgroundColor = System.Drawing.Color.WhiteSmoke;
            this.dataGrid_Parent.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.dataGrid_Parent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGrid_Parent.Location = new System.Drawing.Point(46, 65);
            this.dataGrid_Parent.Name = "dataGrid_Parent";
            this.dataGrid_Parent.RowHeadersWidth = 51;
            this.dataGrid_Parent.RowTemplate.Height = 24;
            this.dataGrid_Parent.Size = new System.Drawing.Size(361, 227);
            this.dataGrid_Parent.TabIndex = 0;
            this.dataGrid_Parent.RowHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGrid_Parent_RowHeaderMouseClick);
            // 
            // tableName_Parent
            // 
            this.tableName_Parent.AutoSize = true;
            this.tableName_Parent.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tableName_Parent.Location = new System.Drawing.Point(41, 25);
            this.tableName_Parent.Name = "tableName_Parent";
            this.tableName_Parent.Size = new System.Drawing.Size(75, 25);
            this.tableName_Parent.TabIndex = 1;
            this.tableName_Parent.Text = "Parent";
            // 
            // dataGrid_Child
            // 
            this.dataGrid_Child.BackgroundColor = System.Drawing.Color.WhiteSmoke;
            this.dataGrid_Child.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.dataGrid_Child.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGrid_Child.Location = new System.Drawing.Point(531, 65);
            this.dataGrid_Child.Name = "dataGrid_Child";
            this.dataGrid_Child.RowHeadersWidth = 51;
            this.dataGrid_Child.RowTemplate.Height = 24;
            this.dataGrid_Child.Size = new System.Drawing.Size(356, 227);
            this.dataGrid_Child.TabIndex = 2;
            this.dataGrid_Child.RowHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGrid_Child_RowHeaderMouseClick);
            // 
            // tableName_Child
            // 
            this.tableName_Child.AutoSize = true;
            this.tableName_Child.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tableName_Child.Location = new System.Drawing.Point(526, 25);
            this.tableName_Child.Name = "tableName_Child";
            this.tableName_Child.Size = new System.Drawing.Size(62, 25);
            this.tableName_Child.TabIndex = 3;
            this.tableName_Child.Text = "Child";
            // 
            // panel_Parent
            // 
            this.panel_Parent.BackColor = System.Drawing.Color.WhiteSmoke;
            this.panel_Parent.Location = new System.Drawing.Point(46, 307);
            this.panel_Parent.Name = "panel_Parent";
            this.panel_Parent.Size = new System.Drawing.Size(361, 156);
            this.panel_Parent.TabIndex = 4;
            // 
            // panel_Child
            // 
            this.panel_Child.BackColor = System.Drawing.Color.WhiteSmoke;
            this.panel_Child.Location = new System.Drawing.Point(531, 307);
            this.panel_Child.Name = "panel_Child";
            this.panel_Child.Size = new System.Drawing.Size(343, 213);
            this.panel_Child.TabIndex = 0;
            // 
            // addButton
            // 
            this.addButton.BackgroundImage = global::Lab2.Properties.Resources.button;
            this.addButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.addButton.Location = new System.Drawing.Point(940, 92);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(98, 40);
            this.addButton.TabIndex = 5;
            this.addButton.Text = "Adaugă";
            this.addButton.UseVisualStyleBackColor = true;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // updateButton
            // 
            this.updateButton.BackgroundImage = global::Lab2.Properties.Resources.button;
            this.updateButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.updateButton.Location = new System.Drawing.Point(940, 161);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(98, 40);
            this.updateButton.TabIndex = 6;
            this.updateButton.Text = "Actualizează";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // deleteButton
            // 
            this.deleteButton.BackgroundImage = global::Lab2.Properties.Resources.button;
            this.deleteButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.deleteButton.Location = new System.Drawing.Point(940, 231);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(98, 40);
            this.deleteButton.TabIndex = 7;
            this.deleteButton.Text = "Șterge";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // messageToUser
            // 
            this.messageToUser.AutoSize = true;
            this.messageToUser.Location = new System.Drawing.Point(12, 503);
            this.messageToUser.Name = "messageToUser";
            this.messageToUser.Size = new System.Drawing.Size(0, 17);
            this.messageToUser.TabIndex = 8;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(120F, 120F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.BackgroundImage = global::Lab2.Properties.Resources.background;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1082, 547);
            this.Controls.Add(this.messageToUser);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.addButton);
            this.Controls.Add(this.panel_Child);
            this.Controls.Add(this.panel_Parent);
            this.Controls.Add(this.tableName_Child);
            this.Controls.Add(this.dataGrid_Child);
            this.Controls.Add(this.tableName_Parent);
            this.Controls.Add(this.dataGrid_Parent);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "Pet Store";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Parent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Child)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGrid_Parent;
        private System.Windows.Forms.Label tableName_Parent;
        private System.Windows.Forms.DataGridView dataGrid_Child;
        private System.Windows.Forms.Label tableName_Child;
        private System.Windows.Forms.Panel panel_Parent;
        private System.Windows.Forms.Panel panel_Child;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Label messageToUser;
    }
}

