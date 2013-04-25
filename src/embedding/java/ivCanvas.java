import java.awt.Frame;
import java.awt.Component;
import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Label;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Graphics;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.MouseEvent;
import java.util.Date;
import javax.swing.Timer;
import java.awt.event.KeyEvent;
import java.lang.reflect.Method;
import java.security.AccessController;
import java.security.PrivilegedAction;

public class ivCanvas extends Canvas implements ComponentListener ,java.awt.event.KeyListener,java.awt.event.MouseListener,java.awt.event.MouseMotionListener
{
      
    //event Ids declarations
    static final int BACKSPACE    = 10001;
    static final int DELETE       = 10002;      
    static final int HOME         = 10003;
    static final int END          = 10004;
    static final int PAGE_UP      = 10005;
    static final int PAGE_DOWN    = 10006;
    static final int LEFT_ARROW   = 10007;
    static final int RIGHT_ARROW  = 10008;
    static final int UP_ARROW     = 10009;
    static final int DOWN_ARROW   = 10010;
   
    //OpenGL initialization status variable
    private boolean bInitOpenGL = false;


    //load the dll having the native method implementations 
    static {
        System.loadLibrary("ivCanvas");
    }
    
    
    
    //Initialization
    public void initialize()
    {
        //Initialize the sceneManager and OpenInventor 
        initialSetup();
        
        addComponentListener( this);
        //Listeners for keyboard and mouse
        addKeyListener(this);
        addMouseListener(this);
        addMouseMotionListener(this);
    }
    public void componentHidden(ComponentEvent e) {
    }
    public void componentMoved(ComponentEvent e) {
    }
    public void componentResized(ComponentEvent e) {
      repaint();
    }
    public void componentShown(ComponentEvent e) {
    }
    
    public void keyPressed(java.awt.event.KeyEvent evt) {
        formKeyPressed(evt);
    }
    public void keyReleased(java.awt.event.KeyEvent evt) {
        formKeyReleased(evt);
    }
    
    
    
    
    
    public void mouseMoved(java.awt.event.MouseEvent evt) {
        formMouseEvent(evt);
    }
    public void mouseDragged(java.awt.event.MouseEvent evt) {
        formMouseEvent(evt);
    }
    
    
    
    
    //These handlers translate keyboard events to strings of form
    //keyID|time|modifiers. These strings are then sent to C++ for creation
    //of SoEvent object, which is handled by Inventor
    public void mousePressed(java.awt.event.MouseEvent evt) {
         formMouseEvent(evt);
    }

    public void mouseReleased(java.awt.event.MouseEvent evt) {
         formMouseEvent(evt);
    }
    
    
    
    //Key press handler
    private void formKeyPressed(java.awt.event.KeyEvent evt)
    {
       String evtString;
       String keyCode = new String();
       if(evt.getKeyCode() == KeyEvent.VK_BACK_SPACE)
       {
            keyCode = Integer.toString(BACKSPACE);
            
       }
       else if(evt.getKeyCode() == KeyEvent.VK_DELETE)
       {
            keyCode = Integer.toString(DELETE);
            
       }
       else if(evt.getKeyCode() == KeyEvent.VK_HOME)
       {
            keyCode = Integer.toString(HOME);
            
       }
       else if(evt.getKeyCode() == KeyEvent.VK_END)
       {
            keyCode = Integer.toString(END);
            
       }
       else if(evt.getKeyCode() == KeyEvent.VK_PAGE_UP)
       {
            keyCode = Integer.toString(PAGE_UP);
            
       }
       else if(evt.getKeyCode() == KeyEvent.VK_PAGE_DOWN)
       {
           keyCode = Integer.toString(BACKSPACE);
           
       } 
       else if(evt.getKeyCode() == KeyEvent.VK_LEFT)
       {
           keyCode = Integer.toString(LEFT_ARROW);
           
       }
       else if(evt.getKeyCode() == KeyEvent.VK_RIGHT)
       {
           keyCode = Integer.toString(RIGHT_ARROW);
           
       }
       else if(evt.getKeyCode() == KeyEvent.VK_UP)
       {
           keyCode = Integer.toString(UP_ARROW);
           
       }
       else if(evt.getKeyCode() == KeyEvent.VK_DOWN)
       {
           keyCode = Integer.toString(DOWN_ARROW);
           
       }
       else if(evt.getKeyCode() == KeyEvent.VK_ENTER)
       {
           keyCode = Integer.toString('\n');
       }
       else if(evt.getKeyChar()!= KeyEvent.CHAR_UNDEFINED)
       {
           char key = evt.getKeyChar();
           keyCode = Character.toString(key);
       }
       
       String thisTime = Long.toString(evt.getWhen()/1000);
       
       int modifiers =0;
       
       if((evt.getModifiers() & KeyEvent.SHIFT_MASK) == KeyEvent.SHIFT_MASK)
       {
           modifiers = 1 + modifiers;
       }
       if((evt.getModifiers() & KeyEvent.ALT_MASK) == KeyEvent.ALT_MASK )
       {
           modifiers = 100 + modifiers;
       }
       if((evt.getModifiers() & KeyEvent.CTRL_MASK) == KeyEvent.CTRL_MASK )
       {
           modifiers = 10 + modifiers ;
       }
       
       String modifiersString = Integer.toString(modifiers);
       
       String resultString = keyCode+"|"+thisTime+"|"+modifiersString;
       
       keyPressedEvent(resultString);
              
    }
    
    //Key release handler
    private void formKeyReleased(java.awt.event.KeyEvent evt) {                                 
       String evtString;
       String keyCode = new String();
       if(evt.getKeyCode() == KeyEvent.VK_BACK_SPACE)
       {
            keyCode = Integer.toString(BACKSPACE);
          //  System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_DELETE)
       {
            keyCode = Integer.toString(DELETE);
           // System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_HOME)
       {
            keyCode = Integer.toString(HOME);
         //   System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_END)
       {
            keyCode = Integer.toString(END);
          //  System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_PAGE_UP)
       {
            keyCode = Integer.toString(PAGE_UP);
          //  System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_PAGE_DOWN)
       {
           keyCode = Integer.toString(BACKSPACE);
        //   System.out.println(keyCode);
       } 
       else if(evt.getKeyCode() == KeyEvent.VK_LEFT)
       {
           keyCode = Integer.toString(LEFT_ARROW);
            System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_RIGHT)
       {
           keyCode = Integer.toString(RIGHT_ARROW);
         //   System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_UP)
       {
           keyCode = Integer.toString(UP_ARROW);
         //   System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_DOWN)
       {
           keyCode = Integer.toString(DOWN_ARROW);
         //   System.out.println(keyCode);
       }
       else if(evt.getKeyCode() == KeyEvent.VK_ENTER)
       {
           keyCode = Integer.toString('\n');
       }
       else if(evt.getKeyChar()!= KeyEvent.CHAR_UNDEFINED)
       {
           char key = evt.getKeyChar();
           keyCode = Character.toString(key);
       }
       
       String thisTime = Long.toString(evt.getWhen()/1000);
       
       int modifiers =0;
       if((evt.getModifiers() & KeyEvent.SHIFT_MASK) == KeyEvent.SHIFT_MASK)
       {
           modifiers = 1 + modifiers;
       }
       if((evt.getModifiers() & KeyEvent.ALT_MASK) == KeyEvent.ALT_MASK )
       {
           modifiers = 100 + modifiers;
       }
       if((evt.getModifiers() & KeyEvent.CTRL_MASK) == KeyEvent.CTRL_MASK )
       {
           modifiers = 10 + modifiers ;
       }
       
       String modifiersString = Integer.toString(modifiers);
       String resultString = keyCode+"|"+thisTime+"|"+modifiersString;
       keyReleasedEvent(resultString);
    } 
    
    
    
    
    //This handler translates mouse events to strings of form
    //MouseEventID|time|modifiers. These strings are then sent to C++ for creation
    //of SoEvent object, which is handled by Inventor

    //any mouse event
    private void formMouseEvent(java.awt.event.MouseEvent evt) {                                  
        int mouseEventId = evt.getID();
        int buttonID = evt.getButton();
        int xcord = evt.getX();
        int ycord = evt.getComponent().getHeight() - evt.getY();
        long time = evt.getWhen()/1000;
        int modifiers =0;
       
        if((evt.getModifiers() & KeyEvent.SHIFT_MASK) == KeyEvent.SHIFT_MASK)
        {
             modifiers = 1 + modifiers;
        }
        if((evt.getModifiers() & KeyEvent.ALT_MASK) == KeyEvent.ALT_MASK )
        {
            modifiers = 100 + modifiers;
        }
        if((evt.getModifiers() & KeyEvent.CTRL_MASK) == KeyEvent.CTRL_MASK )
        {
            modifiers = 10 + modifiers ;
        }
        String modifiersString = Integer.toString(modifiers);
        String resultString = mouseEventId+"|"+buttonID+"|"+xcord+"|"+ycord+"|"+time+"|"+modifiers;
        //System.out.println(resultString);
        if(mouseEventId==501 || mouseEventId==502 || mouseEventId==503 || mouseEventId==506)
        {
            mouseEventHandler(resultString);
        }      
    }  
   
    
    //called when the canvas is destroyed, this 
    // is responsible for claening up pixelBuffer
    //and releasing OpenGL resources
    protected void finalize() throws Throwable {
        try {
            cleanupOpenGL();
        } 
        catch(Exception e){
            e.printStackTrace();
        }
    }
    
    //Overloaded method which in turn calls paintOpenGL
    public void paint(Graphics g)
    {
		update(g);
    }

	public void update(Graphics g)
	{
		if (bInitOpenGL == false)
		{
			bInitOpenGL = true;
			initializeOpenGL();

		}
		paintOpenGL();
	}

	

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//JDK 1.6 Canvas has a bug that causes the canvas to flicker during resize. This is to overcome 
	//that flickering problem. Code example taken from jogl
	///////////////////////////////////////////////////////////////////////////////////////////////////////


	public void addNotify()
	{
		super.addNotify();
		disableBackgroundErase();
	}

	private static boolean disableBackgroundEraseInitialized;
	private static Method  disableBackgroundEraseMethod;
	
	
	private void disableBackgroundErase() {
		if (!disableBackgroundEraseInitialized) {
			try {
				AccessController.doPrivileged(new PrivilegedAction() { 
					public Object run() {
						try {
							disableBackgroundEraseMethod =
								getToolkit().getClass().getDeclaredMethod("disableBackgroundErase",
										new Class[] { Canvas.class });
							disableBackgroundEraseMethod.setAccessible(true);
						} catch (Exception e) {
						}
						return null;
					}
				});
			} catch (Exception e) {
			}
			disableBackgroundEraseInitialized = true;
		}
		if (disableBackgroundEraseMethod != null) {
			try {
				disableBackgroundEraseMethod.invoke(getToolkit(), new Object[] { this });
			} catch (Exception e) {
				// FIXME: workaround for 6504460 (incorrect backport of 6333613 in 5.0u10)
				
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////

    
    //native entry for loading dlls 
    public native boolean loadLibraries(String libraries); 
     
    // native entry point for initializing OpenGL state.
    public native void initializeOpenGL();     
    // native entry point for Painting in OpenGL
    public native void paintOpenGL();
    // native entry point for cleaning up OpenGL.
    public native void cleanupOpenGL();
    // native entry point for initializing the DB and sceneManager
    public native void initialSetup();
    // native entry point for processing the queue in sceneManager
    public native void processQueue();
    
    // native entry for handling mouse and Keyboards event
    public native void keyPressedEvent(String KeyPressed);
    public native void keyReleasedEvent(String KeyReleased);
    public native void mouseEventHandler(String mouseButtonEventDesc);
  
    // native entry for loading Graph
    public native void loadGraphOpenGL(String Path);
    //native entry for setting background color
    public native void setBackgroundColor(int red, int black, int green);
    //native entry for Set the viewport region
    public native void setViewportRegion(int width, int hieght);
    
    //native entry for getting a field value of a node in a loaded scene graph
    public native String get(String param);
    
    //native entry for getting a field value of a node in a loaded scene graph
    public native boolean set(String param,String value);
    
    //dummy methods
    //not implemented because there are no corresponding events in inventor
    
    public void keyTyped(KeyEvent e) {
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }
      
}