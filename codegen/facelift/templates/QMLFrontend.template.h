{% set class = '{0}'.format(interface) %}
{%- macro printif(name) -%}
{%- if name -%}{{name}}
{% endif -%}
{%- endmacro -%}

/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>

#include "QMLFrontend.h"
#include "{{class}}.h"

// Dependencies
{% for property in interface.properties -%}
{{- printif(property|requiredInclude) }}
{{- printif(property|requiredQMLInclude) }}
{%- endfor -%}
{% for operation in interface.operations -%}
{% for parameter in operation.parameters -%}
{{- printif(parameter|requiredInclude) }}
{%- endfor %}
{%- endfor %}
{% for event in interface.signals -%}
{% for parameter in event.parameters -%}
{{- printif(parameter|requiredInclude) }}
{%- endfor %}
{%- endfor %}

{{module|namespaceOpen}}

/**
* \class {{class}}QMLFrontend
* \ingroup {{interface.module.name|toValidId}}
* \inqmlmodule {{interface.module.name}}
*/

/**
 * This is the class registered as a QML component for the {{interface}} interface
 */
class {{class}}QMLFrontend : public facelift::QMLFrontendBase {

    Q_OBJECT

public:

    static constexpr const char* INTERFACE_NAME = "{{interface}}";

    {{class}}QMLFrontend(QObject* parent = nullptr) :
        facelift::QMLFrontendBase(parent) {
    }

    void init({{class}}& provider) {
        m_provider = &provider;
        {% for property in interface.properties %}
        connect(m_provider, &{{class}}::{{property.name}}Changed, this, &{{class}}QMLFrontend::{{property.name}}Changed);
        {% if property.type.is_model -%}
        m_{{property}}Model.init(m_provider->{{property}}());
        {% endif %}
        {% endfor %}

        {% for event in interface.signals %}
        {% if event.parameters|hasListParameter %}
        connect(m_provider, &{{class}}::{{event.name}}, this, [this] (
            {%- set comma = joiner(", ") -%}
            {%- for parameter in event.parameters -%}
                {{ comma() }}
                {{parameter|returnType}} {{parameter.name}}
            {%- endfor -%}) {
            emit {{class}}QMLFrontend::{{event.name}}(
            {%- set comma2 = joiner(", ") -%}
            {%- for parameter in event.parameters -%}
                {{comma2()}}
                {%- if parameter.type.is_list -%}
                    facelift::toQMLCompatibleType({{parameter.name}})
                {%- else -%}
                    {{parameter.name}}
                {%- endif -%}
            {%- endfor -%});
        });
        {% else %}
        connect(m_provider, &{{class}}::{{event.name}}, this, &{{class}}QMLFrontend::{{event.name}});
        {% endif %}
        {% endfor %}
    }

    {% for property in interface.properties %}

    {{- printif(property.comment)}}
    {% if property.type.is_model -%}
    Q_PROPERTY(QObject* {{property}} READ {{property}} NOTIFY {{property.name}}Changed)
    QObject* {{property}}() {
    	return &m_{{property}}Model;
    }

    facelift::ModelListModel<{{property|nestedType|fullyQualifiedCppName}}> m_{{property}}Model;

    {% elif property.type.is_list %}
    // Using QVariantList, since exposing QList<ActualType> to QML does not seem to work
    Q_PROPERTY(QVariantList {{property}} READ {{property}} NOTIFY {{property.name}}Changed)
    QVariantList {{property}}() const {
        return facelift::toQMLCompatibleType(m_provider->{{property}}());
    }
    {%- elif property.type.is_interface %}
    Q_PROPERTY(QObject* {{property}} READ {{property}} NOTIFY {{property.name}}Changed)

    {{property|returnType}}QMLFrontend* {{property}}() {
        synchronizeInterfaceProperty(m_{{property}}Frontend, m_provider->{{property}}());
        return m_{{property}}Frontend;
    }

    QPointer<{{property|returnType}}QMLFrontend> m_{{property}}Frontend;

    {%- else %}
        {% if property.readonly %}
    Q_PROPERTY({{property|qmlCompatibleType}} {{property}} READ {{property}} NOTIFY {{property.name}}Changed)
        {%- else %}
    Q_PROPERTY({{property|qmlCompatibleType}} {{property}} READ {{property}} WRITE set{{property}} NOTIFY {{property.name}}Changed)
    void set{{property}}(const {{property|returnType}}& newValue) {
        // qDebug() << "Request to set property {{property}} to " << newValue;
        Q_ASSERT(m_provider);
    	m_provider->set{{property}}(newValue);
    }
        {%- endif %}

    virtual const {{property|returnType}}& {{property}}() const {
        Q_ASSERT(m_provider);
        // qDebug() << "Read property {{property}}. Value: " << m_provider->{{property}}() ;
        return m_provider->{{property}}();
    }
    {%- endif %}

    Q_SIGNAL void {{property}}Changed();
    {% endfor %}

    {% for operation in interface.operations %}
    Q_INVOKABLE virtual {{operation|returnType}} {{operation}}(
        {%- set comma = joiner(", ") -%}
        {%- for parameter in operation.parameters -%}
        {{ comma() }}
        {{parameter|qmlCompatibleType}} {{parameter.name}}
        {%- endfor -%}
    ) {
        Q_ASSERT(m_provider);
        return m_provider->{{operation}}(
                {%- set comma = joiner(", ") -%}
                {%- for parameter in operation.parameters -%}
                {{ comma() }}{{parameter.name}}
                {%- endfor -%}
                );
    }

    {% endfor -%}

    {% for event in interface.signals %}
    Q_SIGNAL void {{event}}(
        {%- set comma = joiner(", ") -%}
        {%- for parameter in event.parameters -%}
        {{ comma() }}
        {{parameter|qmlCompatibleType}} {{parameter.name}}
        {%- endfor -%}
    );
    {% endfor %}

    QPointer<{{class}}> m_provider;
};


{{module|namespaceClose}}

