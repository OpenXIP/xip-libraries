using System;
using System.Collections.Generic;
using System.IO;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using CustomPropGrid;
using Ini;
using Renderer;

namespace MainApp
{
    public partial class Form1 : Form
    {
        private ivChildWindow mChildWindow;
        private Settings[] settings = new Settings[2];
        private EventHandler handleEvent;

        private string category = "";
        private string obj = "";
        private string field = "";
        private string fieldName = "";
        private string value = "";
        private string description = "";
        
        public Form1()
        {
            InitializeComponent();

            mChildWindow = new ivChildWindow();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            MainMenu mainMenu = new MainMenu();
            this.Menu = mainMenu;

            // add testcase menu
            MenuItem testcase = mainMenu.MenuItems.Add("&File");
            testcase.MenuItems.Add(new MenuItem("&Load", new EventHandler(this.buttonLoad_Click)));
            testcase.MenuItems.Add(new MenuItem("Cone", new EventHandler(this.loadCone_Click)));       
            testcase.MenuItems.Add("-");

            // add exit
            testcase.MenuItems.Add(new MenuItem("E&xit", new EventHandler(this.exit_Click)));

            if (mChildWindow != null)
            {
                if (!mChildWindow.create(panelRenderArea.Handle, "MainWnd"))
                {
                    MessageBox.Show("Window creation failed!");
                }

                // read configuration file (.ini)
                IniFile ini = new IniFile(@"..\..\config\config.ini");

                string libStr = ini.IniReadValue("Library", "Load");

                if (!mChildWindow.loadLibraries(libStr))
                {
                    MessageBox.Show("Inventor extensions could not be loaded!");
                }

                handleEvent = new EventHandler(updateScene);

                settings[0] = new Settings();
                settings[1] = new Settings();

                XmlParser xp = new XmlParser();
                xp.Load(@"..\..\config\config.xml");
               
                xp.OnElementStart += new OnElementStartD(xp_OnElementStart);
                xp.OnElementEnd += new OnElementEndD(xp_OnElementEnd);
                xp.OnElementData += new OnElementDataD(xp_OnElementData);

                xp.Parse();

                gridPage.Settings = settings[0];
            }
        }

        private void xp_OnElementStart(string name, string ns, int numAttributes, Array attribs)
        {
            switch (name)
            {
                case "Category":
                    foreach (attr a in attribs) 
                    {
                        if (a.attrName == "Name")
                            this.category = a.attrVal;

                    }
                    break;
                case "Field":
                    foreach (attr a in attribs)
                    {
                        if (a.attrName == "Object")
                            this.obj = a.attrVal;
                        else if (a.attrName == "Field")
                            this.field = a.attrVal;
                        else if (a.attrName == "Name")
                            this.fieldName = a.attrVal;
                        else if (a.attrName == "Value")
                            this.value = a.attrVal;
                    }
                    break;
            }
        }

        private void xp_OnElementData(string name, string CData)
        {
            if (name == "Field")
                this.description = CData.Trim();
        }

        private void xp_OnElementEnd(string name)
        {
            if (name == "Field")
                settings[0][fieldName] = new Setting(value, obj, field, description, category, handleEvent);
        }

        //show one way to update using reflection
        private void updateScene(object sender, EventArgs evt)
        {
            Setting s = (Setting)sender;

            PropertyValueChangedEventArgs e = (PropertyValueChangedEventArgs)evt;

            String param = s.Obj + "." + s.Field;

            mChildWindow.set(param, (String)e.ChangedItem.Value);
        }

        private void exit_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            if (mChildWindow != null)
            {
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    mChildWindow.loadGraph(openFileDialog.FileName);
                }
            }
        }

        private void loadCone_Click(object sender, EventArgs e)
        {
            if (mChildWindow != null)
            {
                mChildWindow.loadGraph("#Inventor V2.1 ascii\nSeparator { DirectionalLight { } OrthographicCamera { position 0 0 5  height 3 } TransformBoxManip { } DEF Color BaseColor { } Cone { } }");
            }
        }

        private void openFileDialog_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void propertyGrid_Click(object sender, EventArgs e)
        {

        }
    }
}