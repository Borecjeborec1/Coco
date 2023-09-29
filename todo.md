#### TODO

-   classes {Very High}
-   basic node modules {High}
-   Async/await {High}
-   this! {High}
-   other data types (undefined/null/nan) {High}
-   requires, linking files {Mid}
-   RegExp Object {Mid}
-   more cli params {Mid}
-   Optimize compiling errors (missing nodemodule, wrog statements, etc) {Mid}
-   Object destructuring {Mid}
-   AST types discovery {Mid}
-   Finish unfinished ast type handling (SpreadElement, Catch, ...) {Mid}
-   omptimize the c++ lib files (double->int, double->typename, etc) {Low}
-   optional params fix in JS\_ c++ methods {Low}
-   escape characters {Low}
-   bigint --> long long double {Low}
-   Typescript discovery {Low}
-   need for custom c++ compiling flags (-liphlpapi -lws2_32) {Low}
-   eval {Low}
-   Timers - setInterval/setTimeout {Low}
-   Error Object {Low}
-   Map {Low}
-   Set {Low}
-   fix num.toString(213) -> binary formats? {Very Low}
-   fix double stars and other syntaxes (pointer problems) {Very Low}
-   options argument inside toLocaleDateString {Very Low}
-   implement timezone handling in Date {Very Low}
-   String raw static method {Very Very Very Low}
-   cpu model and cpu speed in os module {Very Very Very Low}
-   birth time in fs.stats {Very Very Very Low}
-   C++ Linking
-   Readme

###### In Future

-   var vs let {Mid}
-   == vs === {Mid}

###### Maybe in long long future

-   no strict mode (using json for everything) HARD!!!

###### Bugs

-   Handle % operator for doubles (error: invalid operands of types 'float' and 'float' to binary 'operator%') {Low}
-   fix exists in callbacks (arr.filter((item) => item)) {Mid}
-   Fix empty json key acessment {Mid}
-   Fix constructor and prototype {Mid}
-   Fix the module.exports {Mid}

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
