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

    //更新架次显示
//    Connections {
//        target: dataController
//        Component.onCompleted: {
//            dataController.sendDataNumAdd.connect(upFlightData)
//        }
//    }
    function upFlightData(){
        console.log("Recive")
    }

    Component {
        id: pageComponent
    RowLayout {
          width:  availableWidth
          height: availableHeight
//          Connections {
//                 target: dataController
//          }
          FlyViewMap {
              id:                     map
              planMasterController:   _planController
              Layout.fillHeight:      true
              Layout.fillWidth:       true
              rightPanelWidth:        ScreenTools.defaultFontPixelHeight * 9
              pipMode:                true
              mapName:                "FlightDisplayView"
          }

    TableView {
        id: tableView
        Layout.fillHeight:  true
        width :  parent.width*0.8
        clip  :  true
        //每一列的属性
        TableViewColumn  {
             resizable :false
             movable   :false
             role  : "userId"
             title: qsTr("ID")
             width: ScreenTools.defaultFontPixelWidth * 5
             horizontalAlignment: Text.AlignHCenter

         }
        TableViewColumn  {
             role :  "area"
             title: qsTr("亩数")
             movable    :false
             resizable : false
             width: ScreenTools.defaultFontPixelWidth * 5
             horizontalAlignment: Text.AlignHCenter
         }
        TableViewColumn  {
             role: "flghtTimes"
             title: qsTr("架次")
             movable    :false
             resizable : false
             width: ScreenTools.defaultFontPixelWidth * 5
             horizontalAlignment: Text.AlignHCenter
         }
         //设置每个单元格的字体样式
        itemDelegate: Text {
            text: styleData.value
            color: styleData.selected ? "black" : styleData.textColor
            elide: styleData.elideMode
        }

        model: ListModel{
                 id: flightMsgModel
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

            }
        }
        QGCButton {
            text:       qsTr("取消")
            width:      _butttonWidth
            onClicked: {

           }
        }
     }
   }
 }
}
