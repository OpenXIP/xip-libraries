function Reset(ui)
{
     this.ui = ui;
     
     this.form = new Form(ui);
     
     // connect controls   
     this.ui.btnReset.clicked.connect(this, "reset");
}

// reset everything
Reset.prototype.reset = function()
{
    this.ui.findChild("windowSlider").value = 42.9688;
    this.ui.findChild("levelSlider").value = 31.0059;
    this.form.setParam('MprExaminer0.orientation', 'FEET');
    this.form.setParam('MprExaminer0.viewOrientation', '');
	this.form.setParam('MprExaminer0.viewAll', '');
    this.form.setParam('MprExaminer1.orientation', 'LEFT');
    this.form.setParam('MprExaminer1.viewOrientation', '');
	this.form.setParam('MprExaminer1.viewAll', '');
    this.form.setParam('MprExaminer2.orientation', 'POSTERIOR');
    this.form.setParam('MprExaminer2.viewOrientation', '');
	this.form.setParam('MprExaminer2.viewAll', '');
    this.form.setParam('MprExaminer0.dogEar', 'TRUE');
    this.form.setParam('MprExaminer1.dogEar', 'TRUE');
    this.form.setParam('MprExaminer2.dogEar', 'TRUE');
    this.form.setParam('MprExaminer0.border', 'TRUE');
    this.form.setParam('MprExaminer1.border', 'TRUE');
    this.form.setParam('MprExaminer2.border', 'TRUE');
    this.form.setParam('MprExaminer0.orientationCube', 'TRUE');
    this.form.setParam('MprExaminer1.orientationCube', 'TRUE');
    this.form.setParam('MprExaminer2.orientationCube', 'TRUE');
    
}


