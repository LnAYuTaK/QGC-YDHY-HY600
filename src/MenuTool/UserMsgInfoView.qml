import QtQuick          2.3
import QtQuick.Window   2.2
import QtQuick.Controls 1.2

import QGroundControl               1.0
import QGroundControl.Palette       1.0
import QGroundControl.Controls      1.0
import QGroundControl.Controllers   1.0
import QGroundControl.ScreenTools   1.0
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
//  z:      QGroundControl.zOrderTopMost
   //调色板    虽然用不到就是了--。
   QGCPalette { id: qgcPal }
  //右侧的复选table
   QGCFlickable{
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

        SubMenuButton{
            id:                 vehcileMsg
            setupIndicator:     false
            exclusiveGroup:     setupButtonGroup
            text:               "飞行信息"
        }
        SubMenuButton{
            id:                 userMsg
            setupIndicator:     false
            exclusiveGroup:     setupButtonGroup
            text:               "用戶信息"
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
      source:                 ""
      property string title
      Connections {
          target: panelLoader.item
          onPopout: {
              var windowedPage = windowedAnalyzePage.createObject(mainWindow)
              windowedPage.title = panelLoader.title
              windowedPage.source = panelLoader.source
              _root.popout()
          }
      }

  }

}
