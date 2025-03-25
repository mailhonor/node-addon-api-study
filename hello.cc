
#include <napi.h>

Napi::Value hello(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  return Napi::String::New(env, "hello-world");
}

Napi::Value addNumber(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  int64_t arg0 = info[0].As<Napi::Number>().ToNumber().Int64Value();
  int64_t arg1 = info[1].As<Napi::Number>().ToNumber().Int64Value();
  int64_t sum = arg0 + arg1;
  Napi::Number result = Napi::Number::New(env, sum);
  return result;
}

Napi::Value createObject(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object result = Napi::Object::New(env);
  result.Set(Napi::String::New(env, "one"), Napi::String::New(env, "ooo"));
  result.Set(Napi::String::New(env, "two"), Napi::Number::New(env, 222));
  return result;
}

Napi::Value createArray(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Array result = Napi::Array::New(env);
  result.Set(Napi::Number::New(env, 0), Napi::String::New(env, "ooo"));

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "one"), Napi::String::New(env, "ooo"));
  obj.Set(Napi::String::New(env, "two"), Napi::Number::New(env, 222));
  result.Set(Napi::Number::New(env, 1), obj);
  result.Set(Napi::Number::New(env, 2), obj);

  return result;
}

Napi::Value runCallback(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Function cb = info[0].As<Napi::Function>();
  cb.Call(env.Global(), {});
  return Napi::Boolean::New(env, true);
}

class createClass;
class createClass : public Napi::ObjectWrap<createClass>
{
public:
  createClass(const Napi::CallbackInfo &info);
  ~createClass();

public:
  Napi::Value set(const Napi::CallbackInfo &info);
  Napi::Value get(const Napi::CallbackInfo &info);

protected:
  int times_{0};
};

createClass::createClass(const Napi::CallbackInfo &info) : Napi::ObjectWrap<createClass>(info)
{
  info.This().As<Napi::Object>().Set("myValue", Napi::String::New(this->Env(), ""));
}

createClass::~createClass()
{
}

Napi::Value createClass::set(const Napi::CallbackInfo &info)
{
  Napi::Value last = info.This().As<Napi::Object>().Get("myValue");
  info.This().As<Napi::Object>().Set("myValue", info[0]);
  return last;
}

Napi::Value createClass::get(const Napi::CallbackInfo &info)
{
  Napi::Value last = info.This().As<Napi::Object>().Get("myValue");
  return last;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{

  exports.Set(Napi::String::New(env, "hello"), Napi::Function::New(env, hello));
  exports.Set("addNumber", Napi::Function::New(env, addNumber));
  exports.Set("createObject", Napi::Function::New(env, createObject));
  exports.Set("createArray", Napi::Function::New(env, createArray));
  exports.Set("runCallback", Napi::Function::New(env, runCallback));

  // auto t = DefineClass(env, "createClass", properties, (void *)NULL);
  auto t = createClass::DefineClass(env, "createClass", {createClass::InstanceMethod("set", &createClass::set, napi_default_method), createClass::InstanceMethod("get", &createClass::get, napi_default_method)}, (void *)NULL);
  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(t);
  env.SetInstanceData<Napi::FunctionReference>(constructor);
  exports.Set("createClass", t);
  return exports;
}

NODE_API_MODULE(test, Init)