/**********************************************************************
**
** Copyright (C) 2018 Luxoft Sweden AB
**
** This file is part of the FaceLift project
**
** Permission is hereby granted, free of charge, to any person
** obtaining a copy of this software and associated documentation files
** (the "Software"), to deal in the Software without restriction,
** including without limitation the rights to use, copy, modify, merge,
** publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so,
** subject to the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
** BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
** ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
** SPDX-License-Identifier: MIT
**
**********************************************************************/

import QtQuick 2.4
import QtQuick.Window 2.2
import facelift.example.mypackage 1.0

Window {
    width: 160
    height: 120
    title: "In-Process"

    // "Server"
    Rectangle {
        id: server
        width: parent.width
        height: parent.height / 2
        color: "wheat"
        visible: myInterface.ready

        MyInterface {
            id: myInterface
            IPC.enabled: true
            IPC.objectPath: "/my/object/path"
            onCounterReset: console.log("Server: the counter has been reset")
        }

        Text {
            anchors.centerIn: parent
            text: "Server counter: " + myInterface.counter
        }
    }

    // "Client"
    Rectangle {
        width: parent.width
        height: parent.height / 2
        anchors.top: server.bottom
        color: "lightsteelblue"
        visible: myProxy.ready

        MyInterfaceIPCProxy {
            id: myProxy
            ipc.objectPath: "/my/object/path"
            onCounterReset: console.log("Client: the counter has been reset")
            onCounterChanged: console.log("Client: counter changed: " + counter)
        }

        Text {
            anchors.centerIn: parent
            text: "Client counter: " + myProxy.counter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: myProxy.resetCounter(0);
        }
    }
}
