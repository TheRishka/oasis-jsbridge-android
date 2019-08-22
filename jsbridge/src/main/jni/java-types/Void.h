/*
 * Copyright (C) 2019 ProSiebenSat1.Digital GmbH.
 *
 * Originally based on Duktape Android:
 * Copyright (C) 2015 Square, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _JSBRIDGE_JAVATYPES_VOID_H
#define _JSBRIDGE_JAVATYPES_VOID_H

#include "JavaType.h"
#include "jni-helpers/JniGlobalRef.h"

namespace JavaTypes {

class Void : public JavaType {

public:
  Void(const JsBridgeContext *, JavaTypeId, bool boxed);

#if defined(DUKTAPE)
  JValue pop(bool) const override;
  JValue popArray(uint32_t count, bool expanded, bool inScript) const override;
  duk_ret_t push(const JValue &, bool inScript) const override;
  duk_ret_t pushArray(const JniLocalRef<jarray> &values, bool expand, bool inScript) const override;
#elif defined(QUICKJS)
  JValue toJava(JSValueConst, bool) const override;
  JValue toJavaArray(JSValueConst, bool inScript) const override;
  JSValue fromJava(const JValue &, bool inScript) const override;
  JSValue fromJavaArray(const JniLocalRef<jarray> &values, bool inScript) const override;
#endif

  JValue callMethod(jmethodID methodId, const JniRef<jobject> &javaThis,
                    const std::vector<JValue> &args) const override;

private:
  bool m_boxed;
};

}  // namespace JavaTypes

#endif

