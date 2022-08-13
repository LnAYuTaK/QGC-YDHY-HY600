import QtQuick          2.3
import QtQuick.Window   2.2
import QtQuick.Controls 1.2

import QGroundControl               1.0
import QGroundControl.Palette       1.0
import QGroundControl.Controls      1.0
import QGroundControl.Controllers   1.0
import QGroundControl.ScreenTools   1.0

//导航栏用户//显示Page
//2022810
Rectangle {
   id :_root
   color:  qgcPal.window

   signal popout()

   ExclusiveGroup { id: setupButtonGroup }
   readonly property real  _defaultTextHeight:     ScreenTools.defaultFontPixelHeight
   readonly property real  _defaultTextWidth:      ScreenTools.defaultFontPixelWidth
   readonly property real  _horizontalMargin:      _defaultTextWidth / 2
   readonly property real  _verticalMargin:        _defaultTextHeight / 2
   readonly property real  _buttonWidth:           _defaultTextWidth * 18

   z:  QGroundControl.zOrderTopMost
   //调色板
   QGCPalette { id: qgcPal }

  //右侧的复选table
   QGCFlickable {
      id:userInfo
      width:              buttonColumn.width
      anchors.topMargin:  _defaultTextHeight / 2
      anchors.top:        parent.top
      anchors.bottom:     parent.bottom
      anchors.leftMargin: _horizontalMargin
      anchors.left:       parent.left
      contentHeight:      buttonColumn.height
      flickableDirection: Flickable.VerticalFlick
      clip:               true
   Column {
       id:         buttonColumn
       spacing:    _defaultTextHeight / 2
        //2022811
        SubMenuButton {
            id:                 vehcileMsg
            setupIndicator:     false
            exclusiveGroup:     setupButtonGroup
            text:               "飞行信息"
            onClicked: {
                panelLoader.source  =  "qrc:/qml/QGroundControl/MenuTool/FlightMsgPage.qml"
                panelLoader.title   =  "ti"
                checked             =  true
            }
         }
     }
  }
  //分割线
  Rectangle {
       id:                     divider
       anchors.topMargin:      _verticalMargin
       anchors.bottomMargin:   _verticalMargin
       anchors.leftMargin:     _horizontalMargin
       anchors.left:           userInfo.right
       anchors.top:            parent.top
       anchors.bottom:         parent.bottom
       width:                  1
       color:                  qgcPal.windowShade
   }
  //加载
  Loader {
      id:                      panelLoader
      anchors.topMargin:      _verticalMargin
      anchors.bottomMargin:   _verticalMargin
      anchors.leftMargin:     _horizontalMargin
      anchors.rightMargin:    _horizontalMargin
      anchors.left:           divider.right
      anchors.right:          parent.right
      anchors.top:            parent.top
      anchors.bottom:         parent.bottom
      property string title
      //这里注意要用qml 的url
      source:               "qrc:/qml/QGroundControl/MenuTool/FlightMsgPage.qml"

      Connections {
          target: panelLoader.item
          //信 popout()
          onPopout: {
              console.log("CreateObject")
              var windowedPage = windowedUserMsgInfoPage.createObject(mainWindow)
              windowedPage.title = panelLoader.title
              windowedPage.source = panelLoader.source
              _root.popout()
          }
      }
  }
  //组件
  Component {
      id: windowedUserMsgInfoPage
      Window {
          width:      ScreenTools.defaultFontPixelWidth  * 100
          height:     ScreenTools.defaultFontPixelHeight * 40
          visible:    true

          property alias source: loader.source

          Rectangle {
              color:          QGroundControl.globalPalette.window
              anchors.fill:   parent

              Loader {
                  id:             loader
                  anchors.fill:   parent
                  onLoaded:       item.popped = true
              }
          }
          onClosing: {
              visible = false
              source = ""
          }
      }
   }
 }
