import QtQml.Models 2.12

import QGroundControl           1.0
import QGroundControl.Controls  1.0
//导航栏内部List
ToolStripActionList {
    id: _root
    model: [
        ToolStripAction {
            text:           qsTr("用户")
            iconSource:     "/res/yonghu.svg"
            onTriggered:    mainWindow.showUserTool()
        },
        ToolStripAction {
            text:           qsTr("日志")
            iconSource:     "/qmlimages/Analyze.svg"
            onTriggered:    mainWindow.showAnalyzeTool()
        },
        ToolStripAction {
            text:           qsTr("设置")
            iconSource:     "/qmlimages/Gears.svg"
            onTriggered:    mainWindow.showSetupTool()
        },
        ToolStripAction {
            text:           qsTr("系统")
            iconSource:     "/res/QGCLogoWhite"
            onTriggered:    mainWindow.showSettingsTool()
        }

    ]
}
