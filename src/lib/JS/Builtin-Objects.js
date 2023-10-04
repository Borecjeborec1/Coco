const STRING_FUNCTIONS = {
    charAt: { name: "JS_charAt", argCount: 1 },
    charCodeAt: { name: "JS_charCodeAt", argCount: 1 },
    concat: { name: "JS_concat", argCount: Infinity },
    includes: { name: "JS_includes", argCount: 1 },
    endsWith: { name: "JS_endsWith", argCount: 1 },
    indexOf: { name: "JS_indexOf", argCount: 1 },
    lastIndexOf: { name: "JS_lastIndexOf", argCount: 1 },
    localeCompare: { name: "JS_localeCompare", argCount: 2 },
    match: { name: "JS_match", argCount: 1 },
    matchAll: { name: "JS_matchAll", argCount: 1 },
    normalize: { name: "JS_normalize", argCount: 1 },
    padEnd: { name: "JS_padEnd", argCount: 2 },
    padStart: { name: "JS_padStart", argCount: 2 },
    repeat: { name: "JS_repeat", argCount: 1 },
    replace: { name: "JS_replace", argCount: 2 },
    search: { name: "JS_search", argCount: 1 },
    slice: { name: "JS_slice", argCount: 2 },
    split: { name: "JS_split", argCount: 2 },
    startsWith: { name: "JS_startsWith", argCount: 1 },
    substr: { name: "JS_substr", argCount: 2 },
    substring: { name: "JS_substring", argCount: 2 },
    toLocaleLowerCase: { name: "JS_toLocaleLowerCase", argCount: 1 },
    toLocaleUpperCase: { name: "JS_toLocaleUpperCase", argCount: 1 },
    toLowerCase: { name: "JS_toLowerCase", argCount: 0 },
    toUpperCase: { name: "JS_toUpperCase", argCount: 0 },
    toString: { name: "JS_toString", argCount: 0 },
    trim: { name: "JS_trim", argCount: 0 },
    trimEnd: { name: "JS_trimEnd", argCount: 0 },
    trimStart: { name: "JS_trimStart", argCount: 0 },
};

const NUMBER_FUNCTIONS = {
    toFixed: { name: "JS_toFixed", argCount: 1 },
    toExponential: { name: "JS_toExponential", argCount: 1 },
    toPrecision: { name: "JS_toPrecision", argCount: 1 },
    toString: { name: "JS_toString", argCount: 0 },
    valueOf: { name: "JS_valueOf", argCount: 0 },
    toLocaleString: { name: "JS_toLocaleString", argCount: 0 },
    isFinite: { name: "JS_isFinite", argCount: 1 },
    isNaN: { name: "JS_isNaN", argCount: 1 },
    // 'parseInt': { name: 'JS_parseInt', argCount: 2 },
    // 'parseFloat': { name: 'JS_parseFloat', argCount: 1 },
};

const BOOLEAN_FUNCTIONS = {
    toString: { name: "JS_toString", argCount: 0 },
    valueOf: { name: "JS_valueOf", argCount: 0 },
};

const ARRAY_FUNCTIONS = {
    concat: { name: "JS_concat", argCount: Infinity },
    copyWithin: { name: "JS_copyWithin", argCount: 2 },
    entries: { name: "JS_entries", argCount: 0 },
    every: { name: "JS_every", argCount: 1 },
    fill: { name: "JS_fill", argCount: 3 },
    filter: { name: "JS_filter", argCount: 1 },
    find: { name: "JS_find", argCount: 1 },
    findIndex: { name: "JS_findIndex", argCount: 1 },
    flat: { name: "JS_flat", argCount: 1 },
    flatMap: { name: "JS_flatMap", argCount: 1 },
    forEach: { name: "JS_forEach", argCount: 1 },
    includes: { name: "JS_includes", argCount: 1 },
    indexOf: { name: "JS_indexOf", argCount: 1 },
    isArray: { name: "JS_isArray", argCount: 1 },
    join: { name: "JS_join", argCount: 1 },
    keys: { name: "JS_keys", argCount: 0 },
    lastIndexOf: { name: "JS_lastIndexOf", argCount: 1 },
    map: { name: "JS_map", argCount: 1 },
    pop: { name: "JS_pop", argCount: 0 },
    push: { name: "JS_push", argCount: 1 },
    reduce: { name: "JS_reduce", argCount: 2 },
    reduceRight: { name: "JS_reduceRight", argCount: 2 },
    reverse: { name: "JS_reverse", argCount: 0 },
    shift: { name: "JS_shift", argCount: 0 },
    slice: { name: "JS_slice", argCount: 2 },
    some: { name: "JS_some", argCount: 1 },
    sort: { name: "JS_sort", argCount: 1 },
    splice: { name: "JS_splice", argCount: Infinity },
    toLocaleString: { name: "JS_toLocaleString", argCount: 0 },
    toSource: { name: "JS_toSource", argCount: 0 },
    toString: { name: "JS_toString", argCount: 0 },
    unshift: { name: "JS_unshift", argCount: 1 },
    values: { name: "JS_values", argCount: 0 },
};

const BUILTIN_JS_FUNCTIONS = {
    ...BOOLEAN_FUNCTIONS,
    ...NUMBER_FUNCTIONS,
    ...STRING_FUNCTIONS,
    ...ARRAY_FUNCTIONS,
};

const VALID_USER_TYPES = {
    int: "int",
    lint: "long int",
    llint: "long long int",
    uint: "unsigned",
    luint: "long unsigned",
    lluint: "long long unsigned",
    float: "double",
    double: "double",
    string: "std::string",
    void: "void",
    json: "nlohman::json",
    boolean: "bool",
};

const IMPLEMENTED_JS_OBJECTS = {
    JSON: "__JSON__",
    Math: "__Math__",
    Number: "__Number__",
    Date: "__Date__",
    String: "__String__",
    Boolean: "__Boolean__",
    Array: "__Array__",
    Map: "__Map__",
    Set: "__Set__",
    BigInt: "__BigInt__",
};

const ARRAY_DATA_TYPES = [
    "Array",
    "Int8Array",
    "Uint8Array",
    "Uint8ClampedArray",
    "Int16Array",
    "Uint16Array",
    "Int32Array",
    "Uint32Array",
    "BigInt64Array",
    "BigUint64Array",
    "Float32Array",
    "Float64Array",
];

const IMPLEMENTED_DATE_METHODS = [
    "toISOString",
    "toString",
    "toDateString",
    "toTimeString",
    "toJSON",
    "getDate",
    "getDay",
    "getFullYear",
    "getHours",
    "getMilliseconds",
    "getMinutes",
    "getMonth",
    "getSeconds",
    "getTime",
    "getTimezoneOffset",
    "setFullYear",
    "setMonth",
    "setDate",
    "setHours",
    "setMinutes",
    "setSeconds",
    "setMilliseconds",
    "toUTCString",
    "toLocaleString",
    "toLocaleDateString",
    "toLocaleTimeString",
];

const IMPLEMENTED_MAP_METHODS = [
    "set",
    "get",
    "has",
    "delete",
    "clear",
    "size",
    "entries",
    "keys",
    "values",
    "forEach",
    "add",
];

const IMPLEMENTED_OBJECT_METHODS = [
    ...IMPLEMENTED_DATE_METHODS,
    ...IMPLEMENTED_MAP_METHODS,
];

const ALLOWED_MODULES = {
    path: "__path__",
    os: "__os__",
    fs: "__fs__",
    child_process: "__child_process__",
};

const OBJECTS_WITH_STATIC_GLOBAL_METHODS = ["Date", "Array"]; // Array holding names that have static methods, that are also global, and custom user variable names for node modules
const DEFAULT_IMPORTS = [
    "nlohmann-json.hh",
    "Global-functions.hh",
    "Array-Methods.hh",
    "Boolean-Methods.hh",
    "String-Methods.hh",
    "Number-Methods.hh",
    "json-operators.hh",
    "string-operators.hh",
    "Array.hh",
    "Bool.hh",
    "Date.hh",
    "JSON.hh",
    "Math.hh",
    "Number.hh",
    "String.hh",
    "Map.hh",
    "Set.hh",
];

const TIMER_FUNCTIONS = [
    "setInterval",
    "setImmediate",
    "setTimeout",
    "clearInterval",
    "clearImmediate",
    "clearTimeout",
];
const ACCEPTED_ENDINGS_FOR_CC_LINKING = [".hh", ".cc", ".c", ".cpp", ".h"];

module.exports = {
    BUILTIN_JS_FUNCTIONS,
    DEFAULT_IMPORTS,
    VALID_USER_TYPES,
    IMPLEMENTED_JS_OBJECTS,
    ARRAY_DATA_TYPES,
    IMPLEMENTED_OBJECT_METHODS,
    ALLOWED_MODULES,
    OBJECTS_WITH_STATIC_GLOBAL_METHODS,
    TIMER_FUNCTIONS,
    ACCEPTED_ENDINGS_FOR_CC_LINKING,
};
