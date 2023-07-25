#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "js_value.hpp"

using std::optional;
using std::shared_ptr;

class JSValue;

class JSUndefined {
  JSValue operator==(JSValue &other);
};

class JSBase {
public:
  JSBase();

  virtual JSValue get_property(JSValue key, JSValue parent);
  virtual optional<JSValue>
  get_property_from_list(const std::vector<std::pair<JSValue, JSValue>> &list,
                         JSValue key, JSValue parent);

  std::vector<std::pair<JSValue, JSValue>> properties;
};

class JSBool : public JSBase {
public:
  JSBool(bool v);

  bool internal;
};

class JSNumber : public JSBase {
public:
  JSNumber(double v);
  double internal;
};

class JSString : public JSBase {
public:
  JSString(const char *v);
  JSString(std::string v);
  std::string internal;
};

class JSArray : public JSBase {
public:
  JSArray();
  JSArray(std::vector<JSValue> data);

  virtual JSValue get_property(JSValue key, JSValue parent);

  shared_ptr<std::vector<JSValue>> internal;

  static JSValue push_impl(JSValue thisArg, std::vector<JSValue> &args);
  static JSValue map_impl(JSValue thisArg, std::vector<JSValue> &args);
  static JSValue join_impl(JSValue thisArg, std::vector<JSValue> &args);
  static JSValue reduce_impl(JSValue thisArg, std::vector<JSValue> &args);
  static JSValue filter_impl(JSValue thisArg, std::vector<JSValue> &args);
  static JSValue iterator_impl(JSValue thisArg, std::vector<JSValue> &args);
};

class JSObject : public JSBase {
public:
  JSObject();
  JSObject(std::vector<std::pair<JSValue, JSValue>> data);

  virtual JSValue get_property(JSValue key, JSValue parent);

  shared_ptr<std::vector<std::pair<JSValue, JSValue>>> internal;
};

using ExternFunc = std::function<JSValue(JSValue, std::vector<JSValue> &)>;
using ExternFuncPtr = JSValue (*)(JSValue, std::vector<JSValue> &);
class JSFunction : public JSBase {

public:
  JSFunction(ExternFunc f);
  ExternFunc internal;

  JSValue call(JSValue thisArg, std::vector<JSValue> &);
};

extern JSValue iterator_symbol;

class JSIterator {
public:
  JSIterator();
  JSIterator(JSValue val);
  JSIterator(JSValue val, JSValue parent);
  static JSIterator end_marker();

  JSValue operator*();
  JSIterator operator++();
  bool operator!=(const JSIterator &other);

  JSValue value();

  shared_ptr<JSValue> it;
  optional<shared_ptr<JSValue>> last_value = std::nullopt;
  optional<shared_ptr<JSValue>> parent = std::nullopt;
};
