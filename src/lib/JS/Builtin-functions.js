const STRING_FUNCTIONS = {
  'charAt': { name: 'JS_charAt', argCount: 1 },
  'charCodeAt': { name: 'JS_charCodeAt', argCount: 1 },
  'concat': { name: 'JS_concat', argCount: Infinity },
  'includes': { name: 'JS_includes', argCount: 1 },
  'endsWith': { name: 'JS_endsWith', argCount: 1 },
  'indexOf': { name: 'JS_indexOf', argCount: 1 },
  'lastIndexOf': { name: 'JS_lastIndexOf', argCount: 1 },
  'localeCompare': { name: 'JS_localeCompare', argCount: 2 },
  'match': { name: 'JS_match', argCount: 1 },
  'matchAll': { name: 'JS_matchAll', argCount: 1 },
  'normalize': { name: 'JS_normalize', argCount: 1 },
  'padEnd': { name: 'JS_padEnd', argCount: 2 },
  'padStart': { name: 'JS_padStart', argCount: 2 },
  'repeat': { name: 'JS_repeat', argCount: 1 },
  'replace': { name: 'JS_replace', argCount: 2 },
  'search': { name: 'JS_search', argCount: 1 },
  'slice': { name: 'JS_slice', argCount: 2 },
  'split': { name: 'JS_split', argCount: 2 },
  'startsWith': { name: 'JS_startsWith', argCount: 1 },
  'substr': { name: 'JS_substr', argCount: 2 },
  'substring': { name: 'JS_substring', argCount: 2 },
  'toLocaleLowerCase': { name: 'JS_toLocaleLowerCase', argCount: 1 },
  'toLocaleUpperCase': { name: 'JS_toLocaleUpperCase', argCount: 1 },
  'toLowerCase': { name: 'JS_toLowerCase', argCount: 0 },
  'toUpperCase': { name: 'JS_toUpperCase', argCount: 0 },
  'toString': { name: 'JS_toString', argCount: 0 },
  'trim': { name: 'JS_trim', argCount: 0 },
  'trimEnd': { name: 'JS_trimEnd', argCount: 0 },
  'trimStart': { name: 'JS_trimStart', argCount: 0 },
};

const NUMBER_FUNCTIONS = {
  'toFixed': { name: 'JS_toFixed', argCount: 1 },
  'toExponential': { name: 'JS_toExponential', argCount: 1 },
  'toPrecision': { name: 'JS_toPrecision', argCount: 1 },
  'toString': { name: 'JS_toString', argCount: 0 },
  'valueOf': { name: 'JS_valueOf', argCount: 0 },
  'toLocaleString': { name: 'JS_toLocaleString', argCount: 0 },
  'isFinite': { name: 'JS_isFinite', argCount: 1 },
  'isNaN': { name: 'JS_isNaN', argCount: 1 },
  // 'parseInt': { name: 'JS_parseInt', argCount: 2 },
  // 'parseFloat': { name: 'JS_parseFloat', argCount: 1 },
};


const BOOLEAN_FUNCTIONS = {
  'toString': { name: 'JS_toString', argCount: 0 },
  'valueOf': { name: 'JS_valueOf', argCount: 0 },
};

const BUILTIN_JS_FUNCTIONS = { ...BOOLEAN_FUNCTIONS, ...NUMBER_FUNCTIONS, ...STRING_FUNCTIONS }

module.exports = { BUILTIN_JS_FUNCTIONS }