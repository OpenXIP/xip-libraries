# Copyright Siemens Corporate Research Inc. 2008
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

HOW TO CREATE YOUR OWN XIP PLUGIN
---------------------------------

1. Build Xip 0.1/plugin from source.

2. Copy xipplugin.dll from the plugin build directory to Xip 0.1/bin.

3. In Xip 0.1/bin/extensions.xml, after <section name="libraries">,
   add this line:

   <setting key="library">xipplugin</setting>

4. Re-start xipbuilder (Start > All Programs > Xip 0.1 > XipBuilder),
   and open Xip 0.1/plugin/pluginSlicer.xip


TROUBLESHOOTING
---------------

   If the far right node is red with mention 'Unknown Node',
   xipbuilder failed to load the plugin xipplugin.dll.
