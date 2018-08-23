/* Copyright 2018 Juergen Messerer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TESTVALUES_H
#define TESTVALUES_H

#include <QStringList>
#include "RequestData/RequestCommand.h"

struct TestValues
{
  QStringList values1 = {"5","10","20",""};
  QStringList values2 = {"7","44","33",""};
  QStringList values3 = {"true", "false", "true"};
  QStringList values4 = {"false", "true", "false"};

  RequestVector commandVector = {{ RequestCmd::WlanList},
                                   {RequestCmd::WlanState},
                                   {RequestCmd::EthState }};

};

#endif // TESTVALUES_H
