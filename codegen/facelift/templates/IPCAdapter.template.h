{#*********************************************************************
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
*********************************************************************#}

/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

{{classExportDefines}}

#include "facelift-ipc.h"
#include "FaceliftUtils.h"

#include "{{module.fullyQualifiedPath}}/{{interfaceName}}.h"
#include "{{module.fullyQualifiedPath}}/{{interfaceName}}QMLFrontend.h"

{% if interface.isAsynchronousIPCEnabled %}
#include "{{module.fullyQualifiedPath}}/{{interfaceName}}IPCLocalServiceAdapter.h"
{% endif %}

#ifdef DBUS_IPC_ENABLED
#include "{{module.fullyQualifiedPath}}/{{interfaceName}}IPCDBusAdapter.h"
#endif

{% for property in interface.referencedInterfaceTypes %}
#ifdef DBUS_IPC_ENABLED
#include "{{property.fullyQualifiedPath}}{% if generateAsyncProxy %}Async{% endif %}IPCDBusAdapter.h"
#endif
{% if interface.isAsynchronousIPCEnabled %}
#include "{{property.fullyQualifiedPath}}{% if generateAsyncProxy %}Async{% endif %}IPCLocalServiceAdapter.h"
{% endif %}
{% endfor %}

{{module.namespaceCppOpen}}

class {{interfaceName}}IPCQMLFrontendType;

class {{classExport}} {{interfaceName}}IPCAdapter: public ::facelift::IPCServiceAdapter<{{interfaceName}}>
{
    Q_OBJECT

public:

    using BaseType = ::facelift::IPCServiceAdapter<{{interfaceName}}>;

    {{interfaceName}}IPCAdapter(QObject* parent = nullptr);

#ifdef DBUS_IPC_ENABLED
    {{interfaceName}}IPCDBusAdapter m_ipcDBusServiceAdapter;
#endif

{% if interface.isAsynchronousIPCEnabled %}
    {{interfaceName}}IPCLocalServiceAdapter m_ipcLocalServiceAdapter;
{% endif %}

};

{{module.namespaceCppClose}}
