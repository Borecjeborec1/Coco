#### TODO

-   Scoping. Fc move to top of block, classes too probably {High}
-   TS exports {Mid}
-   RegExp Object {Mid}
-   more cli params {Mid}
-   Optimize compiling errors (missing nodemodule, wrong statements, etc) {Mid}
-   JS_methods for nlohmann json. (only for the duplicate methods for more types) {Mid}
-   Typescript discovery {Low}
-   eval {Low}
-   Error Object {Low}
-   Weak Map/Set {Low}
-   Readme todos section
-   Readme possibilities section
-   Readme known bugs sections
-   Create Coco Logo
-   Release!!!!

##### In Future

-   var vs let {Mid}
-   child_process.spawn() {Low} HARD!!!
-   Generated code clenup -> whitespaces, ;, indents, ... {Very Low}

##### Maybe in long long future

-   no strict mode (using json for everything) HARD!!!

##### Bugs

-   Handle % operator for doubles (error: invalid operands of types 'float' and 'float' to binary 'operator%') {Low}
-   fix exists in callbacks (arr.filter((item) => item)) {Mid}
-   Fix the module.exports {Mid}
-   Handle empty mapping in translation. (classes with no methods, etc) {Mid}
-   Fix bug with running async code. nodejs spawns waits for end of the exe and then output all at once. {Mid}
-   Fix nonstrings inside console.time {Mid}

###### Single methods Bugs

-   fix num.toString(213) -> binary formats? {Very Low}
-   fix double stars and other syntaxes (pointer problems) {Very Low}
-   options argument inside toLocaleDateString {Very Low}
-   implement timezone handling in Date {Very Low}
-   Fix concate for JS_array and more arguments {Very Low}
-   String raw static method {Very Very Very Low}
-   cpu model and cpu speed in os module {Very Very Very Low}
-   birth time in fs.stats {Very Very Very Low}
-   Add groups to string JS_match {Very Very Very Low}
-   Normalize string JS_match {Very Very Very Low}
-   Default values in import statements {Very Very Very Low}

#### FINISHED

-   -std=c++17 discovery {High}
-   array {Very High}
-   string {Very High}
-   bool dont have .toString when printing
-   lambda functions {High}
-   length() -> length {High}
-   +/- prefixes {High}
-   objects {Very High}
-   JSON {High}
-   Migration from custom types to custom functions {Very High}
-   testing even the output of c++ to match the nodejs {Mid}
-   rewrite of data types (number->static_cast<double>) {High}
-   accesing objects [], ., [""] {High}
-   enable mutability in fcs {High}
-   array methods {Very High}
-   more vars inside loop [index, value] of .entries {Low}
-   pointer params {Mid}
-   ignore multiple includes {Very High}
-   Fix compile options for tests {High}
-   template literal {High}
-   regex {High}
-   Typescript variable types {Mid}
-   Typescript types in arguments {Mid}
-   operators for diferent data types -> problem with nlohmann json {High}
-   string operators {High}
-   rewrite bin and index js {Low}
-   dont copy whole json content but include it {Mid}
-   fix different data types in array methods {High}
-   Fix flatmap and reduce/reduceright {Low}
-   Date Object implementation{High}
-   String Object implementation{High}
-   Hadle !! operator {Low}
-   Array Object implementation{High}
-   built-in (Array, String, etc...) {Mid}
-   Fix "nonoptions" in node module methods, eg function overload {Mid}
-   Remove unused methods in translation process {High}
-   Handle objects like \_\_dirname, \_\_filename
-   block npm modules {Low}
-   Fix issue with same functions in global scope and built-in class scope (Date.toString gets called as JS_toString(Date)) {Mid}
-   Export compile options to cpp generation for linking files{Mid}
-   Fix ts type declaration leads to undefined variable in asignment {Mid}
-   Add more ts types. llint, lluint, etc {Mid}
-   optional params fix in JS\_ c++ methods {Low}
-   requires, linking files with exports.test{Mid}
-   Object destructuring {Mid}
-   escape characters {Low}
-   Timers - setInterval/setTimeout {Low}
-   need for custom c++ compiling flags (-liphlpapi -lws2_32) {Low}
-   other data types (undefined/null/nan) {High}
-   exporting files with module.exports. {Mid}
-   TS imports, import from {Mid}
-   Map {Low}
-   Set {Low}
-   Spread Operator {Mid}
-   C++ Linking {Very High}
-   basic node modules {High}
-   Async/await -> solved by removing them :D {High}
-   classes {Very High}
-   this! {High}
-   bigint --> long long {Low}
-   Finish unfinished ast type handling (SpreadElement, Catch, ...) {Mid}
-   Fix empty json key acessment {Mid}
-   Fix constructor and prototype {Mid}
-   AST types discovery {Mid}
-   == vs === {Mid}
