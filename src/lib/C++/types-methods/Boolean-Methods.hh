#include <string>

std::string JS_toString(bool value) { return value ? "true" : "false"; }
bool JS_valueOf(bool value) { return value ? true : false; }
