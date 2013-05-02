using CustomPropGrid;

namespace MainApp
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
            this.panelRenderArea = new System.Windows.Forms.Panel();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.gridPage = new CustomPropGrid.CustomPropertyGrid();
            this.SuspendLayout();
            // 
            // panelRenderArea
            // 
            this.panelRenderArea.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.panelRenderArea.Location = new System.Drawing.Point(12, 12);
            this.panelRenderArea.Name = "panelRenderArea";
            this.panelRenderArea.Size = new System.Drawing.Size(476, 469);
            this.panelRenderArea.TabIndex = 2;
            // 
            // openFileDialog
            // 
            this.openFileDialog.DefaultExt = "iv";
            this.openFileDialog.Filter = "Inventor|*.iv";
            this.openFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog_FileOk);
            // 
            // gridPage
            // 
            this.gridPage.Location = new System.Drawing.Point(499, 15);
            this.gridPage.Name = "gridPage";
            this.gridPage.Size = new System.Drawing.Size(250, 445);
            this.gridPage.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(761, 493);
            this.Controls.Add(this.gridPage);
            this.Controls.Add(this.panelRenderArea);
            this.MinimumSize = new System.Drawing.Size(500, 200);
            this.Name = "Form1";
            this.Text = "Main App";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelRenderArea;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private CustomPropertyGrid gridPage;
    }
}

