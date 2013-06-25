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
/* All code is written my me,Ben Ratzlaff and is available for any free use except where noted. 
 *I assume no responsibility for how anyone uses the information available*/

using System;
using System.Collections;

namespace CustomPropGrid
{
	/// <summary>
	/// A wrapper around a Hashtable for Setting objects. Setting objects are intended to use with the CustomPropertyGrid
	/// </summary>
	public class Settings
	{
		private Hashtable settings;		
		public Settings()
		{
			settings = new Hashtable();
		}

		/// <summary>
		/// Get the key collection for this Settings object. Every key is a string
		/// </summary>
		public ICollection Keys
		{
			get{return settings.Keys;}
		}

		/// <summary>
		/// Get/Set the Setting object tied to the input string
		/// </summary>
		public Setting this[string key]
		{
			get{return (Setting)settings[key];}
			set{settings[key]=value;value.Name=key;}
		}

		/// <summary>
		/// Gets the Setting object tied to the string. If there is no Setting object, one will be created with the defaultValue
		/// </summary>
		/// <param name="key">The name of the setting object</param>
		/// <param name="defaultvalue">if there is no Setting object tied to the string, a Setting will be created with this as its Value</param>
		/// <returns>The Setting object tied to the string</returns>
		public Setting GetSetting(string key, object defaultvalue)
		{
			if(settings[key]==null)
			{
				settings[key]=new Setting(defaultvalue, null, null, null,null);
				((Setting)settings[key]).Name=key;
			}

			return (Setting)settings[key];
		}

        /// <summary>
        /// Removes the Setting object tied to the string. 
        /// </summary>
        /// <param name="key">The name of the setting object</param>
        /// <returns>void</returns>
        public void RemoveSetting(string key)
        {
            if (settings[key] != null)
            {
                settings.Remove(key);
            }
        }
	}
}
