/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick              2.3
import QtQuick.Controls     1.2
import QtQuick.Dialogs      1.2
import QtQuick.Layouts      1.2

import QGroundControl                1.0
import QGroundControl.Palette        1.0
import QGroundControl.Controls       1.0
import QGroundControl.Controllers    1.0
import QGroundControl.ScreenTools    1.0
import QGroundControl.NetWorkManager 1.0
import QGroundControl.MenuTool       1.0


//具体实现
//LogDownloadCotroller.cc
//QGCFileDialogController.cc
AnalyzePage {
    id:                 logDownloadPage
    pageComponent:      pageComponent
    pageDescription:    qsTr("Log Download allows you to download binary log files from your vehicle. Click Refresh to get list of available logs.")

    property real _margin:          ScreenTools.defaultFontPixelWidth *0.5
    property real _butttonWidth:    ScreenTools.defaultFontPixelWidth * 10


    QGCPalette { id: palette; colorGroupEnabled: enabled }

    LogDownloadController{id: logController }


    Component {
        id: pageComponent

        RowLayout {
            width:  availableWidth
            height: availableHeight

            Connections {
                target: logController
                onSelectionChanged: {
                    tableView.selection.clear()
                    for(var i = 0; i < logController.model.count; i++) {
                        var o = logController.model.get(i)
                        if (o && o.selected) {
                            tableView.selection.select(i, i)
                        }
                    }
                }
            }

            TableView {
                id: tableView
                Layout.fillHeight:  true
                model:              logController.model
                selectionMode:      SelectionMode.MultiSelection
                Layout.fillWidth:   true

                TableViewColumn {
                    title: qsTr("Id")
                    width: ScreenTools.defaultFontPixelWidth * 4
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            var o = logController.model.get(styleData.row)
                            return o ? o.id : ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Date")
                    width: ScreenTools.defaultFontPixelWidth * 10
                    horizontalAlignment: Text.AlignHCenter
                    delegate: Text  {
                        text: {
                            var o = logController.model.get(styleData.row)
                            if (o) {
                                //-- Have we received this entry already?
                                if(logController.model.get(styleData.row).received) {
                                    var d = logController.model.get(styleData.row).time
                                    if(d.getUTCFullYear() < 2010)
                                        return qsTr("Date Unknown")
                                    else
                                        return d.toLocaleString()
                                }
                            }
                            return ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Size")
                    width: ScreenTools.defaultFontPixelWidth * 8
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignRight
                        text: {
                            var o = logController.model.get(styleData.row)
                            return o ? o.sizeStr : ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Status")
                    width: ScreenTools.defaultFontPixelWidth * 10
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            var o = logController.model.get(styleData.row)
                            return o ? o.status : ""
                        }
                    }
                }
            }



            Column {
                spacing:            _margin
                Layout.alignment:   Qt.AlignTop | Qt.AlignLeft
                QGCButton {
                    enabled:    !logController.requestingList && !logController.downloadingLogs
                    text:       qsTr("Refresh")
                    width:      _butttonWidth
                    onClicked: {
                        if (!QGroundControl.multiVehicleManager.activeVehicle || QGroundControl.multiVehicleManager.activeVehicle.isOfflineEditingVehicle) {
                            mainWindow.showMessageDialog(qsTr("Log Refresh"), qsTr("You must be connected to a vehicle in order to download logs."))
                        } else {
                            logController.refresh()
                        }
                    }
                }
                QGCButton {
                    enabled:    !logController.requestingList && !logController.downloadingLogs && tableView.selection.count > 0
                    text:       qsTr("Download")
                    width:      _butttonWidth
                    onClicked: {
                        //-- Clear selection
                        for(var i = 0; i < logController.model.count; i++) {
                            var o = logController.model.get(i)
                            if (o) o.selected = false
                        }
                        //-- Flag selected log files
                        tableView.selection.forEach(function(rowIndex){
                            var o = logController.model.get(rowIndex)
                            if (o) o.selected = true
                        })
                        if (ScreenTools.isMobile) {
                            // You can't pick folders in mobile, only default location is used
                            logController.download()
                        } else {
                            fileDialog.title =          qsTr("Select save directory")
                            fileDialog.selectExisting = true
                            fileDialog.folder =         QGroundControl.settingsManager.appSettings.logSavePath
                            fileDialog.selectFolder =   true
                            fileDialog.openForLoad()
                        }
                    }

                    QGCFileDialog {
                        id: fileDialog
                        onAcceptedForLoad: {
                            logController.download(QGroundControl.settingsManager.appSettings.logSavePath)
                            close()
                        }
                    }
                }

               QGCButton {
                    enabled:    !logController.requestingList && !logController.downloadingLogs && logController.model.count > 0
                    text:       qsTr("筛选")
                    width:      _butttonWidth
                    //筛选日期
                    onClicked: {
                        logController.filerData("Today")
                    }
                }
               QGCButton {
                    enabled:    !logController.requestingList && !logController.downloadingLogs && logController.model.count > 0
                    text:       qsTr("发送日志")
                    width:      _butttonWidth

                    onClicked:{
                        //-- Clear selection
                        for(var i = 0; i < logController.model.count; i++) {
                            var o = logController.model.get(i)
                            if (o) o.selected = false
                        }
                        //-- Flag selected log files
                        tableView.selection.forEach(function(rowIndex){
                            var o = logController.model.get(rowIndex)
                            if (o) o.selected = true
                            console.log(o.id)
                        })
                        logController.sendLog();

                    }

                  }
                QGCButton {
                    enabled:    !logController.requestingList && !logController.downloadingLogs && logController.model.count > 0
                    text:       qsTr("Erase All")
                    width:      _butttonWidth
                    onClicked:  mainWindow.showComponentDialog(
                        eraseAllMessage,
                        qsTr("Delete All Log Files"),
                        mainWindow.showDialogDefaultWidth,
                        StandardButton.Yes | StandardButton.No)
                    Component {
                        id: eraseAllMessage
                        QGCViewMessage {
                            message:    qsTr("All log files will be erased permanently. Is this really what you want?")
                            function accept() {
                                logController.eraseAll()
                                hideDialog()
                            }
                        }
                    }
                }
                QGCButton {
                    text:       qsTr("Cancel")
                    width:      _butttonWidth
                    enabled:    logController.requestingList || logController.downloadingLogs
                    onClicked:  logController.cancel()
                }
            }
        }
    }
}
