/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "sitkFunctionCommand.h"
#include "sitkProcessObject.h"

namespace itk::simple
{

FunctionCommand::~FunctionCommand() = default;

FunctionCommand::FunctionCommand() { Command::SetName("FunctionCommand"); }

void
FunctionCommand::Execute()
{
  if (bool(this->m_Function))
  {
    return m_Function();
  }
}

void
FunctionCommand::SetCallbackFunction(void (*pFunction)())
{
  m_Function = pFunction;
}

void
FunctionCommand::SetCallbackFunction(void (*pFunction)(void *), void * clientData)
{
  m_Function = [clientData, pFunction] { pFunction(clientData); };
}

void
FunctionCommand::SetCallbackFunction(const std::function<void()> & func)
{
  m_Function = func;
}

} // namespace itk::simple
