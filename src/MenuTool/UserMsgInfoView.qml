import QtQuick          2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts  1.2

import QGroundControl               1.0
import QGroundControl.Palette       1.0
import QGroundControl.Controls      1.0
import QGroundControl.ScreenTools   1.0


Rectangle{

  color:  qgcPal.window
  z:      QGroundControl.zOrderTopMost
  QGCFlickable {
       id:                 buttonList
       width:              buttonColumn.width
       anchors.topMargin:  _verticalMargin
       anchors.top:        parent.top
       anchors.bottom:     parent.bottom
       anchors.leftMargin: _horizontalMargin
       anchors.left:       parent.left
       contentHeight:      buttonColumn.height + _verticalMargin
       flickableDirection: Flickable.VerticalFlick
       clip:               true

  }
  Rectangle {
      id:                     divider
      anchors.topMargin:      _verticalMargin
      anchors.bottomMargin:   _verticalMargin
      anchors.leftMargin:     _horizontalMargin
      anchors.left:           buttonList.right
      anchors.top:            parent.top
      anchors.bottom:         parent.bottom
      width:                  1
      color:                  qgcPal.windowShade
  }

}
