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

namespace CustomPropGrid
{
	/// <summary>
	/// Stores information to be displayed in the CustomPropertyGrid
	/// </summary>
	public class Setting
	{
		private object val;
		private string desc,category,name;
        private string obj, field;

		public event EventHandler ValueChanged;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="val">The current value of the setting</param>
		/// <param name="desc">The setting's description</param>
		/// <param name="category">The setting's category</param>
		/// <param name="update">An eventhandler that will be called if CustomPropertyGrid.InstantUpdate is true</param>
        public Setting(object val, string obj, string field, string desc, string category, EventHandler update)
		{
			this.val=val;
            this.obj = obj;
            this.field = field;
			this.desc=desc;
			this.category=category;
			if(update!=null)
				ValueChanged+=update;
		}

		#region Other constructors that call the one above
        public Setting(object val, string obj, string field, string desc, string category) : this(val, obj, field, desc, category, null) { }
        public Setting(object val, string obj, string field, string desc) : this(val, obj, field, desc, null, null) { }
        public Setting(object val) : this(val, null, null, null, null, null) { }
		#endregion

		#region get/set properties for the private data
		public object Value
		{
			get{return val;}
			set{val=value;}
		}

		public string Description
		{
			get{return desc;}
			set{desc=value;}
		}

		public string Category
		{
			get{return category;}
			set{category=value;}
		}

		public string Name
		{
			get{return name;}
			set{name=value;}
		}

        public string Obj
        {
            get { return obj; }
            set { obj = value; }
        }

        public string Field
        {
            get { return field; }
            set { field = value; }
        }
		#endregion

		/// <summary>
		/// Allows an external object to force calling the event
		/// </summary>
		/// <param name="e"></param>
		public void FireUpdate(EventArgs e)
		{
			//I didnt do this in the Value's set method because sometimes I want to set the Value without firing the event
			//I could do the same thing with a second property, but this works fine.
			if(ValueChanged!=null)
				ValueChanged(this,e);
		}
	}
}
