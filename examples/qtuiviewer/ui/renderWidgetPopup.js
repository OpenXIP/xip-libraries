// Constructor
function Form(ui)
{
     this.ui = ui;
     
     this.ui.findChild('output').text = 'Begin';
       
     this.current = this.getParam('RenderArea.current');
     this.checkDogEar(this.current);
     this.checkBorder(this.current);
     this.checkCube(this.current);

     // Add field sensors
     this.setParam('AddFieldSensor', 'RenderArea.current'); 
     this.setParam('AddFieldSensor', 'MprExaminer' + 0 + '.dogEar');   
     this.setParam('AddFieldSensor', 'MprExaminer' + 1 + '.dogEar');   
     this.setParam('AddFieldSensor', 'MprExaminer' + 2 + '.dogEar');  
     this.setParam('AddFieldSensor', 'MprExaminer' + 0 + '.border');   
     this.setParam('AddFieldSensor', 'MprExaminer' + 1 + '.border');   
     this.setParam('AddFieldSensor', 'MprExaminer' + 2 + '.border');    
     this.setParam('AddFieldSensor', 'MprExaminer' + 0 + '.cube');   
     this.setParam('AddFieldSensor', 'MprExaminer' + 1 + '.cube');   
     this.setParam('AddFieldSensor', 'MprExaminer' + 2 + '.cube');   
     
     // connect Qt signal to callback function   
     this.ui.widget["stateChanged(QString,QString)"].connect(this, "stateChanged");
     // connect controls
     this.ui.checkBoxDogEar.clicked.connect(this, 'toggleDogEar');
     this.ui.checkBoxBorder.clicked.connect(this, 'toggleBorder');
     this.ui.checkBoxCube.clicked.connect(this, 'toggleCube');
     
     
     this.ui.findChild('output').text = 'Connected '+this.current;
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
    //this.ui.findChild('output').text = 'State changed: '+p+', '+v;
    
    if(p == 'RenderArea.current'){
        this.current = v;   
        this.ui.findChild('output').text = 'Area: '+this.current;     
        this.checkDogEar(this.current);
        this.checkBorder(this.current); 
        this.checkCube(this.current); 
    }
    if(p == 'MprExaminer' + 0 + '.dogEar'){
        this.checkDogEar(0); 
    }
    if(p == 'MprExaminer' + 1 + '.dogEar'){
        this.checkDogEar(1); 
    }
    if(p == 'MprExaminer' + 2 + '.dogEar'){
        this.checkDogEar(2); 
    }
    if(p == 'MprExaminer' + 0 + '.border'){
        this.checkBorder(0); 
    }
    if(p == 'MprExaminer' + 1 + '.border'){
        this.checkBorder(1); 
    }
    if(p == 'MprExaminer' + 2 + '.border'){
        this.checkBorder(2); 
    }
    if(p == 'MprExaminer' + 0 + '.orientationCube'){
        this.checkCube(0); 
    }
    if(p == 'MprExaminer' + 1 + '.orientationCube'){
        this.checkCube(1); 
    }
    if(p == 'MprExaminer' + 2 + '.orientationCube'){
        this.checkCube(2); 
    }
}

// DOG EAR
// connected to the clicked signal of the dog ear check box
Form.prototype.toggleDogEar = function()
{    
    var dogEar = this.getParam('MprExaminer' + this.current + '.dogEar');
    if(dogEar == 'TRUE'){
        this.setParam('MprExaminer' + this.current + '.dogEar', 'FALSE');
    }
    else{
        this.setParam('MprExaminer' + this.current + '.dogEar', 'TRUE');
    }
}

// checks whether or not the dogEar field of the current (c) viewport 
// is set to true or false, then checks or unchecks the box
Form.prototype.checkDogEar = function(c)
{
    var dogEar = this.getParam('MprExaminer' + c + '.dogEar');  
    if(dogEar == 'TRUE'){
        this.ui.checkBoxDogEar.checked = true;
    }
    else{
        this.ui.checkBoxDogEar.checked = false;
    }  
}

// BORDER
// connected to the clicked signal of the border check box
Form.prototype.toggleBorder = function()
{    
    var border = this.getParam('MprExaminer' + this.current + '.border');
    if(border == 'TRUE'){
        this.setParam('MprExaminer' + this.current + '.border', 'FALSE');
    }
    else{
        this.setParam('MprExaminer' + this.current + '.border', 'TRUE');
    }
}

// checks whether or not the border field of the current (c) viewport 
// is set to true or false, then checks or unchecks the box
Form.prototype.checkBorder = function(c)
{
    var border = this.getParam('MprExaminer' + c + '.border');  
    if(border == 'TRUE'){
        this.ui.checkBoxBorder.checked = true;
    }
    else{
        this.ui.checkBoxBorder.checked = false;
    }  
}

// CUBE
// connected to the clicked signal of the cube check box
Form.prototype.toggleCube = function()
{    
    var cube = this.getParam('MprExaminer' + this.current + '.orientationCube');
    if(cube == 'TRUE'){
        this.setParam('MprExaminer' + this.current + '.orientationCube', 'FALSE');
    }
    else{
        this.setParam('MprExaminer' + this.current + '.orientationCube', 'TRUE');
    }
}

// checks whether or not the orientationCube field of the current (c) viewport 
// is set to true or false, then checks or unchecks the box
Form.prototype.checkCube = function(c)
{
    var cube = this.getParam('MprExaminer' + c + '.orientationCube');  
    if(cube == 'TRUE'){
        this.ui.checkBoxCube.checked = true;
    }
    else{
        this.ui.checkBoxCube.checked = false;
    }  
}

