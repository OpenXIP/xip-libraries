/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
/*
 * Main.java
 *
 */

/**
 *
 * @author Ranajoy Malakar, Anthony Dass
 */


import java.awt.*;
import java.io.File;
import javax.swing.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.FileReader;


public class MainFrame extends Frame implements ActionListener, WindowListener{
    
    
    public void windowClosed(WindowEvent event)  {} 
    public void windowDeiconified(WindowEvent event){}
    public void windowIconified(WindowEvent event){}
    public void windowActivated(WindowEvent event){}
    public void windowDeactivated(WindowEvent event){}
    public void windowOpened(WindowEvent event){} 
    //Constructor
    public MainFrame() {
        initComponents();
       
       //create canvas and add 
        mivCanvas = new ivCanvas();
        add(mivCanvas,BorderLayout.CENTER);
        mivCanvas.initialize();
		
		/*if (!mivCanvas.loadLibraries("radivcore,radivivt,radivannotation,radivsurface"))
			System.out.println("Not all rad extensions could be loaded");*/

		loadLibrary();
        panelBase = null;
        bDemoPanel = false;
        addWindowListener(this);
       
        
    }
    
	//call loadlibrary conditional depending on dlls mentioned in the INI file
	public void loadLibrary()
	{
		try
		{
			BufferedReader br = new BufferedReader(new FileReader("./ivJava.ini"));
			String line = "";
			while ((line = br.readLine()) != null)
			{
				if (line.length() > 0)
				{
					int index = line.indexOf("LoadLibrary=");
					if (index >= 0)
					{
						String Library = line.substring(index + 12);
						Library = Library.replace(';', ',');
						System.out.println("Loading rad extensions : ");
						System.out.println(Library);
						if (!mivCanvas.loadLibraries(Library))
							System.out.println("Not all rad extensions could be loaded");
						break;
					}

				}
				// reads the next line
			}
		}
		catch (Exception ex)
		{
			System.out.println(ex);
		}
	}





    //handle window closing operations
    public void windowClosing(WindowEvent event) 
    { 
        System.exit(0); 
    }
    
    //Initialize
    private void initComponents() 
    {
        setLayout(new java.awt.BorderLayout());
        
        menu = new java.awt.Menu("File");    
        mnuBar = new java.awt.MenuBar();
        mnuFile = new java.awt.MenuItem("Open");
        mnuDemo = new java.awt.MenuItem("Demo");
        
        
        mnuFile.addActionListener(this);
        mnuDemo.addActionListener(this);
    
        menu.add(mnuFile);
        menu.add(mnuDemo);

        mnuBar.add(menu);
        setMenuBar(mnuBar);
  }

  // Actions Performed
  public void actionPerformed(ActionEvent event)
  {
      Object source = event.getSource();
      if (source == mnuFile)
      {
          String filePth= "";
          FileDialog myFileChooser = new java.awt.FileDialog(this);
          File chosenFile;
          myFileChooser.setMode(java.awt.FileDialog.LOAD);
          myFileChooser.setVisible(true);
         
          if(myFileChooser.getFile() == null)
              return;
          else
          {
              chosenFile = new File(myFileChooser.getDirectory()+myFileChooser.getFile());
          }
          if(chosenFile.exists())
          {
              filePth = chosenFile.getAbsolutePath();
          }
          else
              return;
          if(panelBase != null )
          {
              remove(panelBase);
              bDemoPanel = false;
			  validate();
          }

		  if (null != mivCanvas && filePth.length() != 0)
		  {
			  try
			  {
				  mivCanvas.loadGraphOpenGL(filePth);
			  }
			  catch (Exception e)
			  {
				  e.printStackTrace();
			  }
		  }
      }
    else if ( source == mnuDemo)
      {
        if(null != mivCanvas)
            mivCanvas.loadGraphOpenGL("Test");
          
        if( panelBase == null )
         {
            panelBase = new Panel();
            
            panelBase.setBackground(java.awt.Color.GRAY);
            lblSetFieldValue = new Label();
            lblSetFieldName = new Label();
            lblGetparam = new Label();
            txtGetParam = new TextField();
            txtSetFieldName = new TextField();
            txtSetFieldValue = new TextField();
            btnGetParam = new Button();
            btnSetParam = new Button();
            
            lblSetFieldValue.setText("Current Color");
            lblSetFieldName.setText("FieldName");
            lblGetparam.setText("Field Value");
            txtGetParam.setText("Get Light Color");
            txtSetFieldName.setText("DirLight.color");
            txtSetFieldValue.setText("0 1 0");
            
            btnGetParam.setLabel("GetLightColor");
            btnGetParam.addActionListener(this);
            btnSetParam.setLabel("SetLightColor");
            btnSetParam.addActionListener(this);
            
            GridBagLayout layout = new GridBagLayout();
            panelBase.setLayout(layout);
            GridBagConstraints c = new GridBagConstraints();
            c.insets = new Insets(5,5,5,5);

            c.fill = GridBagConstraints.HORIZONTAL;
            c.weightx = 0;
            c.gridwidth =1;

            c.gridx = 0;
            c.gridy = 0;
            panelBase.add(lblGetparam,c);
            
            c.gridx = 1;
            c.gridy = 0;
            c.weightx = GridBagConstraints.REMAINDER;
            c.gridwidth =3;
            panelBase.add(txtGetParam);
            
            c.gridx = 0;
            c.gridy = 1;
            c.weightx = GridBagConstraints.REMAINDER;
            c.gridwidth =3;
            panelBase.add(btnGetParam,c);  
            
            
            c.insets = new Insets(100,5,5,5);
            c.weightx = 0;
            c.gridwidth =1;
            c.gridx = 0;
            c.gridy = 2;
            panelBase.add(lblSetFieldName,c);
            
            
            c.gridx = 1;
            c.gridy = 2;
            panelBase.add(txtSetFieldName,c);
            
            c.insets = new Insets(5,5,5,5);
            c.gridx = 0;
            c.gridy = 3;
            panelBase.add(lblSetFieldValue,c);
            
            c.gridx = 1;
            c.gridy = 3;
            panelBase.add(txtSetFieldValue,c);
            
            c.gridx = 0;
            c.gridy = 4;
            c.weightx = GridBagConstraints.REMAINDER;
            c.gridwidth =3;
            panelBase.add(btnSetParam,c);          
            panelBase.setVisible(true);
        }
 
        if(bDemoPanel == false)
        {
            add(panelBase,BorderLayout.EAST);
            validate();
            bDemoPanel = true;
            pack();
            
        }   
        mivCanvas.repaint();
      }
    
      else if ( source == btnGetParam)
      {
            
          String color = mivCanvas.get("DirLight.color");
          txtGetParam.setText(color);
      }
      else if( source == btnSetParam)
      {
            if(!mivCanvas.set(txtSetFieldName.getText(),txtSetFieldValue.getText()))
            System.out.println("Sorry could not set field");
            else
                mivCanvas.repaint();
      }

  }
     
    // Variables declaration 
    private java.awt.Menu menu;
    private java.awt.MenuBar mnuBar;
    private java.awt.MenuItem mnuFile;
    private java.awt.MenuItem mnuDemo;
    boolean bDemoPanel;
  
    Panel              panelBase;
    Button             btnGetParam;
    Button             btnSetParam;
    TextField          txtGetParam;
    TextField          txtSetFieldName;
    TextField          txtSetFieldValue;
    Label              lblGetparam;
    Label              lblSetFieldName;
    Label              lblSetFieldValue;
    
    ivCanvas            mivCanvas;
   
   
}
