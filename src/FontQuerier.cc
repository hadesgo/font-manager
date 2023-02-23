#include <stdlib.h>
#include <napi.h>
#include <string>
#include "FontDescriptor.h"

// these functions are implemented by the platform
ResultSet *getAvailableFonts();
ResultSet *findFonts(FontDescriptor *, bool, bool);
FontDescriptor *findFont(FontDescriptor *, bool, bool);
FontDescriptor *substituteFont(char *, char *);

// converts a ResultSet to a JavaScript array
Napi::Array collectResults(Napi::Env env, ResultSet *results)
{
  Napi::Array res = Napi::Array::New(env, results->size());

  int i = 0;
  for (ResultSet::iterator it = results->begin(); it != results->end(); it++)
  {
    res.Set(i++, (*it)->toJSObject(env));
  }

  delete results;
  return res;
}

// converts a FontDescriptor to a JavaScript object
Napi::Value wrapResult(Napi::Env env, FontDescriptor *result)
{
  if (result == NULL)
    return Napi::Number::New(env, NULL);

  Napi::Object res = result->toJSObject(env);
  delete result;
  return res;
}

Napi::Array getAvailableFontsSync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  return collectResults(env, getAvailableFonts());
}

Napi::Array findFontsSync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() < 1 || !info[0].IsObject() || info[0].IsFunction())
    throw Napi::Error::New(env, "Expected a font descriptor");
  Napi::Object desc = info[0].As<Napi::Object>();
  FontDescriptor *descriptor = new FontDescriptor(env, desc);
  bool isCompareItalic = false;
  bool isCompareMonospace = false;

  Napi::Value italic = desc.Get(Napi::String::New(env, "italic"));
  if (!italic.IsEmpty() && italic.IsBoolean())
  {
    isCompareItalic = true;
  }
  else
  {
    isCompareItalic = false;
  }

  Napi::Value monospace = desc.Get(Napi::String::New(env, "monospace"));
  if (!monospace.IsEmpty() && monospace.IsBoolean())
  {
    isCompareMonospace = true;
  }
  else
  {
    isCompareMonospace = false;
  }

  return collectResults(env, findFonts(descriptor, isCompareItalic, isCompareMonospace));
}

Napi::Value findFontSync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() < 1 || !info[0].IsObject() || info[0].IsFunction())
    throw Napi::Error::New(env, "Expected a font descriptor");

  Napi::Object desc = info[0].As<Napi::Object>();
  FontDescriptor *descriptor = new FontDescriptor(env, desc);
  bool isCompareItalic = false;
  bool isCompareMonospace = false;

  Napi::Value italic = desc.Get(Napi::String::New(env, "italic"));
  if (!italic.IsEmpty() && italic.IsBoolean())
  {
    isCompareItalic = true;
  }
  else
  {
    isCompareItalic = false;
  }

  Napi::Value monospace = desc.Get(Napi::String::New(env, "monospace"));
  if (!monospace.IsEmpty() && monospace.IsBoolean())
  {
    isCompareMonospace = true;
  }
  else
  {
    isCompareMonospace = false;
  }

  Napi::Value res = wrapResult(env, findFont(descriptor, isCompareItalic, isCompareMonospace));
  delete descriptor;
  return res;
}

Napi::Value substituteFontSync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1 || !info[0].IsString())
    throw Napi::Error::New(env, "Expected postscript name");

  if (info.Length() < 2 || !info[1].IsString())
    throw Napi::Error::New(env, "Expected substitution string");

  std::string postscriptName = info[0].As<Napi::String>().Utf8Value();
  std::string substitutionString = info[1].As<Napi::String>().Utf8Value();

  char *name = (char *)postscriptName.c_str();
  char *subString = (char *)substitutionString.c_str();

  return wrapResult(env, substituteFont(name, subString));
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "getAvailableFontsSync"),
              Napi::Function::New(env, getAvailableFontsSync));
  exports.Set(Napi::String::New(env, "findFontsSync"),
              Napi::Function::New(env, findFontsSync));
  exports.Set(Napi::String::New(env, "findFontSync"),
              Napi::Function::New(env, findFontSync));
  exports.Set(Napi::String::New(env, "substituteFontSync"),
              Napi::Function::New(env, substituteFontSync));
  return exports;
}

NODE_API_MODULE(addon, Init)
