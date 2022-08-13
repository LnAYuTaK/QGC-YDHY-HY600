import QtQml.Models 2.12

import QGroundControl               1.0
import QGroundControl.Controls      1.0
import QGroundControl.FlightDisplay 1.0
//新增加的导航栏
ToolStrip{
    id:     _root
    title:  qsTr("菜单")
    signal displayRightMenulist
    RightMenuToolStripList{
       id:rightMenuToolStripList
    }
   model:rightMenuToolStripList.model  
}

