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
import java.io.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.applet.Applet;
import java.net.*;
import javax.imageio.*;
import java.util.*;
import java.security.AccessController;
import java.security.PrivilegedAction;


public class Mainapplet extends Applet {

    static final int leftWidth   =  10;
    static final int rightWidth  =  195;
    static final int topHeight    =  100;
    static final int bottomHeight =  10;
    
    
    static{
        try 
        {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        }
        catch(Exception e)
        {
            System.out.println("Native UI class not found");
        }
    }

    //Constructor
    public Mainapplet() {
        
    }

	public void setParam(String object, String command)
	{
		// when we call repaint, the paint() method on the given component
		// does not immediately get called to paint its surface.
		// The call to repaint() tells the system that the component needs to be repainted.
		// The system can collect a number of repaint requests and perform them by repainting
		// the component a single time. So may be that’s why there is the delay.
		// You can try by calling "update" rather then repaint().

		mivCanvas.set(object, command);
		Graphics g = comp.getGraphics();
		if (g != null)
		{
			mivCanvas.update(g);
			g.dispose();
		}
	}

	public String getParam(String object)
	{
		System.out.println("\ngetParam start");
		System.out.println(object);
		System.out.println(mivCanvas.get(object));
		System.out.println("getParam end\n");
		return mivCanvas.get(object);
	}


    public void init()
    {
        initComponents();
       
        try
        {
            mivCanvas = new ivCanvas();
        }
        catch(Exception e)
        {
			System.out.println("mivCanvas failed"); 
			showError();
        }
        if(mivCanvas.succeeded == false)
        {
			System.out.println("mivCanvas.succeeded failed");
			showError();
        }
        else
        {
			add(mivCanvas, BorderLayout.CENTER);
            mivCanvas.initialize();
            panelBase = null;
            bDemoPanel = false;
        }
		
		System.out.println("loadLibrary"); 
		loadLibrary();

		if (null != mivCanvas)
		{
			try
			{
				System.out.println("loadGraphOpenGL");
				mivCanvas.loadGraphOpenGL("testCases/3dviewer.iv");
			}
			catch (Exception e)
			{
				System.out.println("printStackTrace"); 
				e.printStackTrace();
			}
		}

		if (!mivCanvas.set("Load.name", "C:/home/sylvain/data/Acetabulum"))
		{
			System.out.println("Sorry could not set file name");
		}
		else
		{
			System.out.println("repaint");
			mivCanvas.repaint();
		}
		//loadCustomIv();
		//loadDicom();
    }

	public void loadDicom()
	{
		System.out.println("loadDicom");

		String filePth = "";
		javax.swing.JFileChooser myFileChooser = new javax.swing.JFileChooser();
		myFileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		
		try
		{
			myFileChooser.setCurrentDirectory(new File(getCodeBase().toURI()));
		}
		catch (Exception d)
		{

		}

		File chosenFile;
		int returnVal = myFileChooser.showOpenDialog(null);

		if (returnVal == JFileChooser.APPROVE_OPTION)
		{
			chosenFile = myFileChooser.getSelectedFile();
			if (chosenFile.exists())
			{
				filePth = chosenFile.getAbsolutePath();
				System.out.println(filePth);

				if (!mivCanvas.set("Load.name", filePth))
				{
					System.out.println("Sorry could not set file name");
				}
				else
				{
					System.out.println("repaint");
					mivCanvas.repaint();
				}
			}

		}
		else
		{
			return;
		}
		
		//testGraph();

		//if (!mivCanvas.set("DirLight.color", "0 0 1"))
		//	System.out.println("Sorry could not set field");
		//else
		//	mivCanvas.repaint();
		if (!mivCanvas.set("VRTViewportBorder.activeColor", "0.0 0.0 1.0"))
		{
			System.out.println("VRTExaminer.activeColor failed");
		}
	}

	public void rotate()
	{
		if (!mivCanvas.set("MprExaminer1.mode", "ROTATE") ||
			!mivCanvas.set("MprExaminer2.mode", "ROTATE") ||
			!mivCanvas.set("MprExaminer3.mode", "ROTATE") ||
			!mivCanvas.set("VRTExaminer.mode", "ROTATE"))
		{
			System.out.println("MprExaminer rotate failed");
		}
		else
		{
			System.out.println("repaint");
			mivCanvas.repaint();
		}
	}

	public void panzoom()
	{
		if (!mivCanvas.set("MprExaminer1.mode", "PANZOOM") ||
			!mivCanvas.set("MprExaminer2.mode", "PANZOOM") ||
			!mivCanvas.set("MprExaminer3.mode", "PANZOOM") ||
			!mivCanvas.set("VRTExaminer.mode", "PANZOOM"))
		{
			System.out.println("MprExaminer panzoom failed");
		}
		else
		{
			System.out.println("repaint");
			mivCanvas.repaint();
		}
	}

	public void reset()
	{
		//if (!mivCanvas.set("VRTViewportBorder.activeColor", "0.0 0.0 1.0"))
		//{
		//	System.out.println("VRTExaminer.activeColor failed");
		//}
		
		if (!mivCanvas.set("VRTExaminer.orientation", "ANTERIOR"))
		{
			System.out.println("VRTExaminer.orientation ANTERIOR reset failed");
		}
		else
		{
			System.out.println("repaint");
			mivCanvas.repaint();
		}

		if (!mivCanvas.set("VRTExaminer.viewOrientation", ""))
		{
			System.out.println("VRTExaminer viewOrientation failed");
		}
		else
		{
			System.out.println("repaint");
			mivCanvas.repaint();
		}

		if (!mivCanvas.set("VRTExaminer.viewAll", ""))
		{
			System.out.println("VRTExaminer viewAll TRIGGER failed");
		}
		else
		{
			System.out.println("repaint");
			mivCanvas.repaint();
		}

		mivCanvas.repaint();

		if (!mivCanvas.set("VRTExaminer.viewAll", ""))
		{
			System.out.println("VRTExaminer viewAll failed");
		}
		else
		{
			System.out.println("repaint");
			mivCanvas.repaint();
		}

		mivCanvas.repaint();

		//if (!mivCanvas.set("VRTExaminer.viewBoundingBox",
		//	"1 0 0 0, 0 1 0 0, 0 0 1 0, 0 0 0 1"))
		//{
		//	System.out.println("VRTExaminer viewBoundingBox failed");
		//}
		//else
		//{
		//	System.out.println("repaint");
		//	mivCanvas.repaint();
		//}

		//mivCanvas.set("perspectiveCamera1.position","0.0981794 2.37372 -0.336082");
		//mivCanvas.set("perspectiveCamera1.orientation","-0.93869 0.217077 0.26784  2.10375");
		//mivCanvas.set("perspectiveCamera1.nearDistance","1.22474");
		//mivCanvas.set("perspectiveCamera1.farDistance","2.9568");
		//mivCanvas.set("perspectiveCamera1.focalDistance","2.09077");
		//mivCanvas.set("perspectiveCamera1.heightAngle", "0.785398");

		//mivCanvas.set("MprExaminer1.orientation", "FEET");
		//mivCanvas.set("MprExaminer1.viewOrientation", "");
		//mivCanvas.set("MprExaminer1.viewAll", "");

		//mivCanvas.set("MprExaminer2.orientation", "LEFT");
		//mivCanvas.set("MprExaminer2.viewOrientation", "");
		//mivCanvas.set("MprExaminer2.viewAll", "");

		//mivCanvas.set("MprExaminer3.orientation", "ANTERIOR");
		//mivCanvas.set("MprExaminer3.viewOrientation", "");
		//mivCanvas.set("MprExaminer3.viewAll", "");

		//mivCanvas.set("VRTExaminer.orientation", "ANTERIOR");
		//mivCanvas.set("VRTExaminer.viewOrientation", "");
		//mivCanvas.set("VRTExaminer.viewAll", "");
	}

    public void loadLibrary() {
        File temporaryIni; 
        /*AccessController.doPrivileged(new PrivilegedAction() {
            public Object run(){
                try {
                    // Get input stream from jar resource
                    InputStream inputStream = ivCanvas.class.getResource("/ivJava.ini").openStream();
                    
                    // Copy resource to filesystem in a temp folder with a unique name
                    temporaryIni = File.createTempFile("ivJava", ".ini");
                    FileOutputStream outputStream = new FileOutputStream(temporaryIni);
                    byte[] array = new byte[148000];
                    int read = 0;
                    while ( (read = inputStream.read(array)) > 0)
                        outputStream.write(array, 0, read);
                    outputStream.close();
                    
                    // Delete on exit the dll
                    temporaryIni.deleteOnExit();
                } catch(Exception e) {
                    e.printStackTrace();
                }
             }
        });*/
        
        try {
            //BufferedReader br = new BufferedReader(new FileReader(temporaryIni.getPath()));
            
            java.net.URL fileURL0 = getClass().getResource("ivJava.ini");
            File configFile = new File(fileURL0.toURI());
            FileReader myReader = new FileReader(configFile);            
            BufferedReader br = new BufferedReader(myReader);
            String line = "";
            while ((line = br.readLine()) != null) {
                if (line.length() > 0) {
                    int index = line.indexOf("LoadLibrary=");
                    if (index >= 0) {
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
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }

   
    //Initialize
    private void initComponents() 
    {
        setLayout(new java.awt.BorderLayout());
    
		//JPanel menubar = new JPanel();
		//menubar.setBackground(new Color(0,0,0));
		//JButton Demo = new JButton();
		//java.net.URL imgURL1 = getClass().getResource("Demo.png");
		//ImageIcon demoIco;
		//if (imgURL1 != null) {
		//    demoIco = new ImageIcon(imgURL1);
		//    Demo.setIcon(demoIco);
		//} else {
		//    System.out.println("Couldn't find file" );
		//}
		//java.net.URL imgURL2 = getClass().getResource("DemoPressed.png");
		//ImageIcon demoPressed;
		//if (imgURL2 != null) {
		//    demoPressed = new ImageIcon(imgURL2);
		//    Demo.setPressedIcon(demoPressed);    
		//} else {
        
		//    System.out.println("Couldn't find file" );
		//}
		//java.net.URL imgURL3 = getClass().getResource("DemoRollOver.png");
		//ImageIcon demoRollOver;
		//if (imgURL3 != null) {
		//    demoRollOver = new ImageIcon(imgURL3);
		//    Demo.setRolloverIcon(demoRollOver);
		//} else {
		//    System.out.println("Couldn't find file" );
		//}
        
		//Demo.setCursor(new Cursor(Cursor.HAND_CURSOR));
		//Demo.setContentAreaFilled(false);
		//Demo.setToolTipText("Demo");
		//Demo.setPreferredSize(new Dimension(45,64));
		//Demo.setMaximumSize(new Dimension(45,64));
		//        Demo.addActionListener(new java.awt.event.ActionListener() {
		//            public void actionPerformed(java.awt.event.ActionEvent evt) {
		//                testGraph();
		//                validate();
		//            }
		//});
        
        
		//JButton File = new JButton();
		//java.net.URL imgURL4 = getClass().getResource("folder.png");
		//ImageIcon fileIco;
		//if (imgURL4 != null) {
		//    fileIco = new ImageIcon(imgURL4);
		//    File.setIcon(fileIco);
		//} else {
		//    System.out.println("Couldn't find file" );
		//}
        
		//java.net.URL imgURL5 = getClass().getResource("folderPressed.png");
		//ImageIcon FilePressed;
		// if (imgURL5 != null) {
		//    FilePressed = new ImageIcon(imgURL5);
		//    File.setPressedIcon(FilePressed);    
		//} else {
        
		//    System.out.println("Couldn't find file" );
		//}
		//java.net.URL imgURL6 = getClass().getResource("folderRollOver.png");
		//ImageIcon FileRollOver;
		//if (imgURL6 != null) {
		//    FileRollOver = new ImageIcon(imgURL6);
		//    File.setRolloverIcon(FileRollOver);
		//} else {
		//    System.out.println("Couldn't find file" );
		//}
        
        
        
		//File.setCursor(new Cursor(Cursor.HAND_CURSOR));
		//File.setContentAreaFilled(false);
		//File.setToolTipText("Browse for IV file");
		//File.setPreferredSize(new Dimension(45,64));
		//File.setMaximumSize(new Dimension(45,64));
		//File.addActionListener(new java.awt.event.ActionListener() {
		//            public void actionPerformed(java.awt.event.ActionEvent evt) {
		//                //loadCustomIv();
		//                loadDicom();
		//            }
		//});
		
		//menubar.setLayout(new BoxLayout(menubar,BoxLayout.X_AXIS));
		//menubar.add(new Box.Filler(new Dimension(10,30),new Dimension(10,30),new Dimension(10,30)));
		//menubar.add(File);
		//menubar.add(new Box.Filler(new Dimension(20,30),new Dimension(20,30),new Dimension(20,30)));
		//menubar.add(Demo);
        
		//add(menubar,BorderLayout.NORTH);
		//mivCanvas.loadGraphOpenGL("C:\home\sylvain\ivjava\ivjava-sylvain\ivjavaWebBrowser\source\bin\3dviewer.iv");
   }
    
    public void loadCustomIv()
    {
		  System.out.println("loadCustomIv");
          String filePth= "";
          javax.swing.JFileChooser myFileChooser = new javax.swing.JFileChooser();
          javax.swing.filechooser.FileFilter filter = new javax.swing.filechooser.FileFilter(){
              public boolean accept(File f) {
                  if (f.isDirectory()) {
                      return true;
                  }
                  
                  String extension = getExtension(f);
                  if (extension != null) {
                      if (extension.equals("iv")) {
                              return true;
                      }
                      else {
                          return false;
                      }
                  }
                  
                  return false;
              }
              
              //The description of this filter
              public String getDescription() {
                  return "Inventor Format";
              }
              
              public String getExtension(File f) {
                  String ext = null;
                  String s = f.getName();
                  int i = s.lastIndexOf('.');
                  
                  if (i > 0 &&  i < s.length() - 1) {
                      ext = s.substring(i+1).toLowerCase();
                  }
                  return ext;
              }
          };
          
          
          myFileChooser.setFileFilter(filter);
          try {
              myFileChooser.setCurrentDirectory(new File(getCodeBase().toURI()));
          } catch (Exception d)
          {
              
          }
          File chosenFile;
          int returnVal = myFileChooser.showOpenDialog(null);

           if (returnVal == JFileChooser.APPROVE_OPTION) 
           {
                chosenFile = myFileChooser.getSelectedFile();
                if(chosenFile.exists())
                {
                    filePth = chosenFile.getAbsolutePath();
                }

           }
           else
           {
                return;
           }

           

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
    
    
   public void testGraph()
   {
        if(null != mivCanvas)
            mivCanvas.loadGraphOpenGL("Test");
          
        if( panelBase == null )
         {
            panelBase = new Panel();
            
            panelBase.setBackground(java.awt.Color.BLACK);
            lblSetFieldValue = new Label();
            lblSetFieldName = new Label();
            lblGetparam = new Label();
            txtGetParam = new TextField();
            txtSetFieldName = new TextField();
            txtSetFieldValue = new TextField();
            btnGetParam = new Button();
            btnSetParam = new Button();
            
            lblSetFieldValue.setForeground(Color.GRAY);
            lblSetFieldValue.setText("Current Color");
            lblSetFieldName.setText("FieldName");
            lblSetFieldName.setForeground(Color.GRAY);
            lblGetparam.setText("Field Value");
            lblGetparam.setForeground(Color.GRAY);
            txtGetParam.setText("Get Light Color");
            txtSetFieldName.setText("DirLight.color");
            txtSetFieldValue.setText("0 1 0");
            
            btnGetParam.setLabel("GetLightColor");
            btnGetParam.addActionListener(new java.awt.event.ActionListener() {
                    public void actionPerformed(java.awt.event.ActionEvent evt) {
                            String color = mivCanvas.get("DirLight.color");
                            txtGetParam.setText(color);
                    }
                });
            btnSetParam.setLabel("SetLightColor");
            btnSetParam.addActionListener(new java.awt.event.ActionListener() {
                public void actionPerformed(java.awt.event.ActionEvent evt) {
					System.out.println(txtSetFieldName.getText());
					System.out.println(txtSetFieldValue.getText());

                     if(!mivCanvas.set(txtSetFieldName.getText(),txtSetFieldValue.getText()))
                        System.out.println("Sorry could not set field");
                    else
                        mivCanvas.repaint();;
            }
            });
            
           
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
            bDemoPanel = true;
        }   
        mivCanvas.repaint();
   }


   private void showError()
   {
       URL errorPage= null;
       try {
           errorPage = new URL(getCodeBase().toString() + "Troubleshooter.htm");
       } catch(MalformedURLException ME) {
           System.out.println("Could not form URL to display help file");
       }
       getAppletContext().showDocument(errorPage);
   }

     
    // Variables declaration 
   
 
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
