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

#ifndef JAWT_INFO_H
#define JAWT_INFO_H

// Helper class for accessing JAWT Information.
class JAWT_Info 
{
private:
    JAWT awt;
    JAWT_DrawingSurface* ds;
    JAWT_DrawingSurfaceInfo* dsi;
    JAWT_Win32DrawingSurfaceInfo* dsi_win;

public:
    JAWT_Info(JNIEnv *env, jobject panel)
    {
        jboolean result;
        jint lock;

        // Get the AWT
        awt.version = JAWT_VERSION_1_3;
        result = JAWT_GetAWT(env, &awt);
        assert(result != JNI_FALSE);
        // Get the drawing surface
        ds = awt.GetDrawingSurface(env, panel);
        if(ds == NULL)
            return;
        // Lock the drawing surface
        lock = ds->Lock(ds);
        assert((lock & JAWT_LOCK_ERROR) == 0);

        // Get the drawing surface info
        dsi = ds->GetDrawingSurfaceInfo(ds);

        // Get the platform-specific drawing info
        dsi_win = (JAWT_Win32DrawingSurfaceInfo*)dsi->platformInfo;
    }
    
    HWND getHWND()
    {
        if(dsi_win == NULL)
            return NULL;
        return dsi_win->hwnd;
    }

    HDC getHDC()
    {
        if(dsi_win == NULL)
            return NULL;
        return dsi_win->hdc;
    }

    virtual ~JAWT_Info()
    {
        if(ds != NULL)
        {
            // Free the drawing surface info
            ds->FreeDrawingSurfaceInfo(dsi);
            // Unlock the drawing surface
            ds->Unlock(ds);
            // Free the drawing surface
            awt.FreeDrawingSurface(ds);
        }
    }
};

#endif