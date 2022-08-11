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

//AnalyzePage是所有分析视图的基类 用于构建分析视图
//植保的界面
AnalyzePage {
    id:                 logDownloadPage
    pageComponent:      pageComponent
    pageDescription:    qsTr("用户飞行信息界面，显示飞行的各种信息")
    //间隔
    property real   _margin:                            ScreenTools.defaultFontPixelWidth *0.5
    //按键大小
    property real   _butttonWidth:                      ScreenTools.defaultFontPixelWidth * 10

    PlanMasterController{
        id:                     _planController
        flyView:                true
        Component.onCompleted:  start()
    }

    //Data控制器获取架次信息
    DataController {id:dataController}

    Component {
        id: pageComponent
    RowLayout {
          width:  availableWidth
          height: availableHeight
          Connections {
                 target: dataController
          }
          FlyViewMap {
              id:                     map
              planMasterController:   _planController
              Layout.fillHeight:      true
              Layout.fillWidth:       true
              rightPanelWidth:        ScreenTools.defaultFontPixelHeight * 9
              pipMode:                true
              mapName:                "FlightDisplayView"
          }
    //架次列表
    TableView {
        id: tableView
        Layout.fillHeight:  true
        width :  parent.width*0.8
        TableViewColumn  {
             title: qsTr("ID")
             width: ScreenTools.defaultFontPixelWidth * 4
             horizontalAlignment: Text.AlignHCenter
         }
        TableViewColumn  {
             title: qsTr("亩数")
             width: ScreenTools.defaultFontPixelWidth * 4
             horizontalAlignment: Text.AlignHCenter
         }
        TableViewColumn  {
             title: qsTr("架次")
             width: ScreenTools.defaultFontPixelWidth * 4
             horizontalAlignment: Text.AlignHCenter
         }
    }
    //右侧列布局按钮
    Column {
        spacing:            _margin
        Layout.alignment:   Qt.AlignTop | Qt.AlignLeft
        QGCButton {
            text:       qsTr("补发回传数据")
            width:      _butttonWidth
            onClicked: {
               dataController.printTest()
            }
        }
        QGCButton {
            text:       qsTr("待定")
            width:      _butttonWidth
            onClicked: {
                 console.log("Not Used")
           }
        }
     }
   }
 }
}
