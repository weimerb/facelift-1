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

#pragma once

#include "benchmark/models/BenchmarkModelPropertyAdapter.h"
#include <functional>
#include <QStringBuilder>

using namespace benchmark::models;


class BenchmarkModelCppImplementation : public BenchmarkModelPropertyAdapter
{
public:
    BenchmarkModelCppImplementation(QObject *parent = nullptr) :
        BenchmarkModelPropertyAdapter(parent)
    {
        m_smallModel.setSize(2000);
        m_smallModel.setGetter(std::bind(&BenchmarkModelCppImplementation::smallModelData, this, std::placeholders::_1));

        m_largeModel.setSize(2000);
        m_largeModel.setGetter(std::bind(&BenchmarkModelCppImplementation::largelModelData, this, std::placeholders::_1));
    }

    SmallStruct smallModelData(int)
    {
        SmallStruct entry;
        entry.setid(42);
        return entry;
    }

    LargeStruct largelModelData(int)
    {
        static const QStringList sl {QStringLiteral("I stand amid the roar"),
                                     QStringLiteral("Of a surf-tormented shore,"),
                                     QStringLiteral("Grains of the golden sand--"),
                                     QStringLiteral("How few! yet how they creep"),
                                     QStringLiteral("Through my fingers to the deep,")};
                                     // TODO: check why adding more leads to a crash over IPC:
                                     //QStringLiteral("While I weep, while I weep")};
                                     //QStringLiteral("O God! can I not grasp"),
                                     //QStringLiteral("Them with a tighter clasp?"),
                                     //QStringLiteral("O God! can I not save")};

        LargeStruct entry;
        entry.setid(42);
        entry.setname(QStringLiteral("The quick brown fox jumps over the lazy dog. "
                                     "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG. "
                                     "The quick brown fox jumps over the lazy dog. "
                                     "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG."));
        entry.settexts(sl);
        entry.setbmenum(BmEnum::BE1);
        return entry;
    }
};
