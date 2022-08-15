import QtQuick              2.3
import QtQuick.Controls     1.2
import QtQuick.Dialogs      1.2
import QtQuick.Layouts      1.2

import QGroundControl                       1.0
import QGroundControl.Palette               1.0
import QGroundControl.Controls              1.0
import QGroundControl.FactSystem            1.0
import QGroundControl.Controllers           1.0
import QGroundControl.ScreenTools           1.0
import QGroundControl.FlightMap             1.0
import QGroundControl.MultiVehicleManager   1.0
import QGroundControl.Vehicle               1.0
import QGroundControl.QGCPositionManager    1.0
import QGroundControl.Airspace      1.0
import QGroundControl.Airmap        1.0
import QGroundControl.FlightDisplay 1.0
import QGroundControl.MenuTool      1.0

//AnalyzePage是所有分析视图的基类 用于构建分析视图
//植保的界面
AnalyzePage {
    id:                 logDownloadPage
    pageComponent:      pageComponent
    pageDescription:    qsTr("这里显示飞行架次等飞行信息.点击左侧上传即可回传当日日志 ")
    //间隔
    property var    _multVehicleMgr:                    QGroundControl.multiVehicleManager

    property real   _margin:                            ScreenTools.defaultFontPixelWidth *0.5
    //按键大小
    property real   _butttonWidth:                      ScreenTools.defaultFontPixelWidth * 10

    property var    _dataController:                    toolbar.dataController

    property var    _planController:                    flightView.planController
    Component {
        id: pageComponent
    RowLayout {
          width:  availableWidth
          height: availableHeight
          spacing  :_margin
          FlyViewMap {
              id:     map
              height: parent.height
              width : parent.width*0.3
              planMasterController:   _planController
              rightPanelWidth:        ScreenTools.defaultFontPixelHeight * 9
              pipMode:                true
              mapName:                "FlightDisplayView"
          }
          TableView {
            id: tableView
            Layout.fillHeight:  true
            Layout.fillWidth:  true
            clip  :  true
            //每一列的属性
            TableViewColumn  {
                 resizable :false
                 movable   :false
                 role  : "userId"
                 title: qsTr("ID")
                 width: ScreenTools.defaultFontPixelWidth * 10
                 horizontalAlignment: Text.AlignHCenter
            }
            TableViewColumn {
                 role :  "area"
                 title: qsTr("亩数")
                 movable    :false
                 resizable : false
                 width: ScreenTools.defaultFontPixelWidth * 10
                 horizontalAlignment: Text.AlignHCenter
             }
            TableViewColumn  {
                 role: "flghtTimes"
                 title: qsTr("架次")
                 movable    :false
                 resizable : false
                 width: ScreenTools.defaultFontPixelWidth * 10
                 horizontalAlignment: Text.AlignHCenter
             }
            //设置每个单元格的字体样式
            itemDelegate: Text {
                text: styleData.value
                color: styleData.selected ? "black" : styleData.textColor
                elide: styleData.elideMode
            }
            model: ListModel {
                 id: flightMsgModel
            }
      }

     Column {
              id :buttonlist
              spacing:         10
              Layout.alignment: Qt.AlignRight
              Layout.margins :_margin
              Layout.fillHeight:  true
              QGCButton{
                  text:       qsTr("刷新")
                  width:      _butttonWidth
                  onClicked:{
                      if (!QGroundControl.multiVehicleManager.activeVehicle || QGroundControl.multiVehicleManager.activeVehicle.isOfflineEditingVehicle) {
                          mainWindow.showMessageDialog(qsTr("刷新"), qsTr("你必须连接上无人机."))
                      } else {
//
                      }
                  }

              }

              QGCButton{
                  text:       qsTr("回传")
                  width:      _butttonWidth
                  onClicked:{
                      if (!QGroundControl.multiVehicleManager.activeVehicle || QGroundControl.multiVehicleManager.activeVehicle.isOfflineEditingVehicle) {
                          mainWindow.showMessageDialog(qsTr("日志回传"), qsTr("你必须连接上无人机."))
                      } else {
//
                      }
                  }

              }



     }



  }
}
}
