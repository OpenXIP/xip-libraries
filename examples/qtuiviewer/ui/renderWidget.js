var fieldLevel;
var fieldWindow;
var triggerShow;
var nodeWindowLevelManip;
var nodePopup;

function Form(ui)
{
    
     this.ui = ui;
     
     this.ui.lineEdit.text = 'start';
     
/* There are two ways to interact with the scenegraph. Like in the HTML viewer we can call
/* getParam(nodeName.fieldName) and setParam(nodeName.fieldName, value) (see further below).
/* 
/* The new and probably better way would be to call widget.getNode(nodeName), 
/* widget.getField(nodeName, fieldName) and widget.getTrigger(nodeName, triggerName) to actually
/* receive a pointer on the node/field. To set and get their values we can call field.getCurStr()
/* and field.setCurStr(). */
     
     // get nodes
     nodeWindowLevelManip = this.ui.widget.getNode('WindowLevelManip');
     nodePopup = this.ui.widget.getNode('Popup');
     var nodeName = nodePopup.getNodeName();
     
     this.ui.lineEdit.text = 'node name: '+ nodeName;
     
     // get fields
     fieldLevel = this.ui.widget.getField('WindowLevelManip', 'level');
     fieldWindow = this.ui.widget.getField('WindowLevelManip', 'window');
     triggerShow = this.ui.widget.getTrigger('Popup', 'show');
     
     // get field values
     var valLevel = fieldLevel.getCurStr();
     var valWindow = fieldWindow.getCurStr();
     
     // Set default value for the sliders
     // Using ui.findChild(name) because the sliders are inside a groupbox
     ui.findChild("levelSlider").value = valLevel*100;
     ui.findChild("windowSlider").value = valWindow*100;
     
     var current = 1; // current active render area
     
     // connect controls   
     this.ui.btnReset.clicked.connect(this, "reset");
     this.ui.btnPopup.clicked.connect(this, "popup");
     this.ui.findChild("levelSlider").valueChanged.connect(this, "setLevel");
     this.ui.findChild("windowSlider").valueChanged.connect(this, "setWindow");
     
     // connect Qt signal to callback function
     this.ui.widget["stateChanged(QString,QString)"].connect(this, "stateChanged");

     // connect field signals
     fieldLevel["stateChanged(QString,QString)"].connect(this, "stateChanged");
     fieldWindow["stateChanged(QString,QString)"].connect(this, "stateChanged");
     
}

// setParam and getParam to interact with the scenegraph through the widget
Form.prototype.setParam = function(p,v)
{
    this.ui.widget.setParam(p+','+v);
}

Form.prototype.getParam = function(p)
{
    return this.ui.widget.getParam(p);
}

// callback function connected to the Qt signal
// returns the new value of a sensor-controlled field
Form.prototype.stateChanged = function(v, p)
{
    this.ui.lineEdit.text = 'State changed: '+p+', '+v;
    
    if(p == 'RenderArea.current'){
        this.current = v;   
        this.ui.lineEdit.text = 'Area: '+this.current;     
    }
    if(p == 'WindowLevelManip.window'){
        this.ui.findChild("windowSlider").value = v*100; // update the value of the slider
    }
    if(p == 'WindowLevelManip.level'){
        this.ui.findChild("levelSlider").value = v*100; // update the value of the slider
    }
}

// pass value of level slider to the level field of the node
Form.prototype.setLevel = function()
{    
    var value = (this.ui.findChild("levelSlider").value)/100;
    this.ui.lineEdit.text = 'Level ' + value; 
   
    fieldLevel.setStr(value);
}    

// pass value of window slider to the window field of the node
Form.prototype.setWindow = function()
{   
    var value = (this.ui.findChild("windowSlider").value)/100;   
    this.ui.lineEdit.text = 'Window ' + value;
    
    fieldWindow.setStr(value);  
} 

// reset everything
Form.prototype.reset = function()
{
    this.ui.findChild("windowSlider").value = 42.9688;
    this.ui.findChild("levelSlider").value = 31.0059;
    this.setParam('MprExaminer0.orientation', 'FEET');
    this.setParam('MprExaminer0.viewOrientation', '');
	this.setParam('MprExaminer0.viewAll', '');
    this.setParam('MprExaminer1.orientation', 'LEFT');
    this.setParam('MprExaminer1.viewOrientation', '');
	this.setParam('MprExaminer1.viewAll', '');
    this.setParam('MprExaminer2.orientation', 'POSTERIOR');
    this.setParam('MprExaminer2.viewOrientation', '');
	this.setParam('MprExaminer2.viewAll', '');
    this.setParam('MprExaminer0.dogEar', 'TRUE');
    this.setParam('MprExaminer1.dogEar', 'TRUE');
    this.setParam('MprExaminer2.dogEar', 'TRUE');
    this.setParam('MprExaminer0.border', 'TRUE');
    this.setParam('MprExaminer1.border', 'TRUE');
    this.setParam('MprExaminer2.border', 'TRUE');
    this.setParam('MprExaminer0.orientationCube', 'TRUE');
    this.setParam('MprExaminer1.orientationCube', 'TRUE');
    this.setParam('MprExaminer2.orientationCube', 'TRUE');
    
}

Form.prototype.popup = function()
{
    triggerShow.trigger();
}

